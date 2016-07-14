/*****************************************************************************************

	Lhings library - Lhings STUN connectivity
		Created by Lhings (November 2013)

	This library implements the Lhings STUN-Based connectivity protocol.
	It is optimized for Arduino. However, it implements communication basics
	that can be used by any device that wants to connect to Lhings using this 
	protocol.

	The STUN protocol is based on UDP communications on Port 3478.
	For more info about this protocol, please visit: 
	[RFC 5389](http://tools.ietf.org/html/rfc5389)

	Before you start using this library, you must have created your "Lhings User Account".
	Sign up in http://lhings.com

	* Community & Help:
	Support Center at http://support.lhings.com
	
	* Libraries & examples: 
	Repositories at http://github.com/lhings
	
	* Latest news:
	Blog: http://blog.lhings.com
	Twitter: http://twitter.com/lhings - Follow us: @Lhings
	
	Lhings licenses to you the right to use, modify, copy, and distribute
	the Software when using Lhings for device connectivity.
	
	
	arduino_lhings_library_release_number = ar002b
	
	Copyright (C) 2013 Lyncos Technologies S.L.  All rights reserved.

******************************************************************************************/


#include "Lhings.h"


LhingsClass Lhings;
unsigned char Lhings_server_IP[] = {54,228,195,78};		// Lhings Server address

extern Action_List Lhings_ActionList[];
extern Event_List  *Lhings_EventList[];
extern Status_List *Lhings_StatusList[];



// ** DEVICE DESCRIPTOR **
// Edit your device "actions", "events" and "state variables" (if any).
// This JSON represents your device features and interaction in the cloud.
prog_char JSON_Descriptor[] PROGMEM = "{\r\n"
								"\"version\": \"1\",\r\n"
								"\"deviceType\": \"arduino\",\r\n"
								"\"friendlyName\": \"arduino\",\r\n"
								"\"manufacturer\": \"arduino\",\r\n"
								"\"modelName\": \"Arduino UNO\",\r\n"
								"\"serialNumber\": \"0017880a54ce\",\r\n";
								

// Helper vars.
prog_char DescriptorPOST[] PROGMEM = "POST /laas/iapi/v1/devices/";
prog_char DescriptorContentType[] PROGMEM = "\r\nContent-Type: application/json\r\n";
prog_char DescriptorAction_button[] PROGMEM = "\",\"description\": \"action\",\"inputs\":[],\"outputs\":[],\"controlURL\": \"/";
prog_char DescriptorAction_with_input_open[] PROGMEM = "\",\"description\": \"action\",\"inputs\":[{\"name\": \" \",\"type\": \"";	
prog_char DescriptorAction_with_input_close[] PROGMEM =	"\",\"relatedStateVariable\": null}],\"outputs\":[],\"controlURL\": \"/";				
prog_char DescriptorStatus[] PROGMEM = "\",\"modifiable:\": false, \"type\": \"string\"}";	


						
//---------------------------------------------------------------------------
//
void LhingsClass::begin(void)
{ 
	// Global vars. 
	Lhings_localPort = 8002;
	Lhings_retry_cont = 0;
	Lhings_retry_multiplier = 2;
	Lhings_retry_cont_keepalive = 0;
	Lhings_retry_multiplier_keepalive = 30;
	Lhings_action_flag = false;
	
	//UDP Init.
	Udp.begin(Lhings_localPort);
	randomSeed(analogRead(0));
	
	// Time variables
	Lhings_TimeStamp = 0;
	Lhings_TimeRef = 0;
	setTime(Lhings_TimeRef);
	
	// Lhings loop - State machine
	generateTransID();
	Lhings_status = STATUS_START_SESSION;
	Lhings_DescriptorSize = 0;

	return;
}


//---------------------------------------------------------------------------
//
//	begin - Initializes Lhings vars. - Device UUID as input
//
boolean LhingsClass::begin(char *devName, char *devUUID, char *userName, char *apiKey)
{ 
	int len;
	
	begin();
	
	#ifdef SERIAL_LOGS
	if(Lhings_Logs){
		Serial.println("Lhings begin");
	}
	#endif
	
	// Check inputs
	len = strlen((const char*)devName);
	if(len > LHINGS_DEVNAME_LEN) return false;
	strcpy(Lhings_devName, (const char*)devName);
	len = strlen((const char*)userName);
	if(len > LHINGS_USERNAME_LEN) return false;
	strcpy(Lhings_userName, (const char*)userName);
	len = strlen((const char*)apiKey);
	if(len != 36) return false;
	strcpy(Lhings_apiKey, (const char*)apiKey);
	
	// Get number of actions
	len=0;
	while(Lhings_ActionList[len].name != NULL){
		Lhings_DescriptorSize += (2*strlen(Lhings_ActionList[len].name)); 
		
		// Check action Args 
		if(Lhings_ActionList[len].type == ACT_STRING)
			Lhings_DescriptorSize += 59;
		else if(Lhings_ActionList[len].type == ACT_INTEGER)
			Lhings_DescriptorSize += 60;
			
		len++;
	}
	Lhings_ActionNum = len;
	
	// Get number of events
	len=0;
	while(Lhings_EventList[len] != NULL){
		Lhings_DescriptorSize += strlen(Lhings_EventList[len]);
		len++;
	}
	Lhings_EventNum = len;
	
	// Get number of actions
	len=0;
	while(Lhings_StatusList[len] != NULL){
		Lhings_DescriptorSize += strlen(Lhings_StatusList[len]);
		len++;
	}
	if(len > LHINGS_STATUS_MAX_VARS){
	
		// Too many stat vars! 
		// NOTE: enhance LHINGS_STATUS_MAX_VARS at Lhings.h if you have enough memory
		Lhings_StatusNum = LHINGS_STATUS_MAX_VARS;
		
		#ifdef SERIAL_LOGS
		if(Lhings_Logs){
			Serial.println("Too many stat vars.");	
		}
		#endif
	}
	else{
		Lhings_StatusNum = len;
	}
	
	// Set descriptor size
	Lhings_DescriptorSize += 58+(79*Lhings_ActionNum)+((Lhings_ActionNum>1)?((Lhings_ActionNum-1)*3):0)+(12*Lhings_EventNum)+((Lhings_EventNum>1)?((Lhings_EventNum-1)*3):0)+(51*Lhings_StatusNum)+((Lhings_StatusNum>1)?((Lhings_StatusNum-1)*3):0);
	
	// Set Device Id. (UUID)
	if(*devUUID != NULL){
		
		// UUID Hardcoded
		len = strlen((const char*)devUUID);
		if(len != 36) 
			return false;
		strcpy((char*)&Lhings_str_UUID[0], (const char*)devUUID);
		getUUIDbin(&Lhings_hex_UUID[0]);
		
		Lhings_Registered = true;
		
		#ifdef SERIAL_LOGS
		if(Lhings_Logs){
			Serial.println("UUID hardcoded");	
		}
		#endif
	}
	else{
		
		// Auto-generated UUID
		if( !readUUID() ){
			Lhings_Registered = false;
	
			#ifdef SERIAL_LOGS
			if(Lhings_Logs){
				Serial.println("registering UUID");
			}
			#endif
		}
		else{
			Lhings_Registered = true;
		
			#ifdef SERIAL_LOGS
			if(Lhings_Logs){
				Serial.println("UUID registered");
			}
			#endif
		}
	}
	
	return true;
}

//---------------------------------------------------------------------------
//
//	close - Disconnects device from Lhings
//
void LhingsClass::close(void)
{ 
	Lhings_status = STATUS_CLOSE_SESSION;
	return;
}


//---------------------------------------------------------------------------
//
//	reset - Erases UUID from non-volatile memory
//
//			NOTE: This method must be used if your device has been DELETED
//			in your dashboard. It will erase the UUID. Then you will need
//			to reprogram your device to obtain a new UUID.
//
void LhingsClass::reset(void)
{ 
	eraseUUID();
	return;
}


//---------------------------------------------------------------------------
//
//	logs - Enable serial logs
//
void LhingsClass::enableLogs(void)
{
	Lhings_Logs = true;	
	return;
}

//---------------------------------------------------------------------------
//
//	logs - Disable serial logs
//
void LhingsClass::disableLogs(void)
{
	Lhings_Logs = false;	
	return;
}


//---------------------------------------------------------------------------
//
//	isConnected - TRUE if device is connected to Lhings
//
boolean LhingsClass::isConnected(void)
{ 
	if((Lhings_status >= STATUS_CONNECTED) && (Lhings_status < STATUS_CLOSE_SESSION))
		return true;
	else 
		return false;
}

//---------------------------------------------------------------------------
//
//	loop - STUN protocol state machine
//
void LhingsClass::loop(void)
{ 
	int len, i, k;
	char c;
	
	switch( Lhings_status ){
	
		case STATUS_INIT:
			begin();
			break;
			
		case STATUS_START_SESSION:
		
			// Send Init. Session packet
			Lhings_action_flag = false;
			Lhings_TimeRef = now();
			Lhings_TimeRef_Keepalive = now();
			write();
			Lhings_status = STATUS_START_SESSION_RESP;
			
			break;
			
		case STATUS_START_SESSION_RESP:
			
			// Get UDP packet
			if( !getResponse() ){  		
				if( timeout() )
					Lhings_status = STATUS_START_SESSION;
				break;
			}
			
			// Process response	
			if(processResponse()){
				
				// Send descriptor
				writeDescriptor();
				#ifdef SERIAL_LOGS
				if(Lhings_Logs){
					Serial.println("Lhings Connected!");
				}
				#endif
			}
			break;
			
		case STATUS_SEND_DESCRIPTOR:
			
			// Send descriptor
			writeDescriptor();
			
			break;
			
		case STATUS_WAIT_DESCRIPTOR_RESP:
		
			len = TcpClient.available();
			i = len;
			k = 0;
			strcpy((char*)&Lhings_payload_buffer[0], (const char*)"");
			
			while(len>0){
				c = TcpClient.read();
				
				#ifdef SERIAL_RAW_LOGS
					Serial.print(c);	
				#endif
				
				if((i-len) < 17){
					Lhings_payload_buffer[k++] = c;
				}
				
				len--;
			}
	
			// Check server response
			Lhings_payload_buffer[k] = '\0';
			
			if(strcmp((const char*)&Lhings_payload_buffer[0], "HTTP/1.1 201 Crea") == 0) {
				#ifdef SERIAL_LOGS
				if(Lhings_Logs){
					Serial.println("Descriptor OK");
				}
				#endif
			}
			else{
			
				TcpClient.stop();
				Lhings_status = STATUS_SEND_DESCRIPTOR;
			
				#ifdef SERIAL_LOGS
				if(Lhings_Logs){
					Serial.println("Retry Descriptor");
				}
				#endif
				return;
			}
			
			TcpClient.stop();
			Lhings_status = STATUS_CONNECTED;
			
			break;
			
		case STATUS_CONNECTED:
		
			// Get UDP packet
			if( !getResponse() ){		
				if( timeoutKeepalive() ){
					Lhings_status = STATUS_KEEP_ALIVE;
					generateTransID();
					Lhings_retry_cont = 0;
					Lhings_retry_multiplier = 2;
				}
				break;
			}

			processResponse();
			break;
		
		case STATUS_KEEP_ALIVE:
		
			// Send Keep_Alive message
			Lhings_TimeRef = now();
			write();
			Lhings_status = STATUS_WAIT_RESP;
			break;
			
		case STATUS_WAIT_RESP:
		
			// Get UDP packet
			if( !getResponse() ){  		
				if( timeout() )
					Lhings_status = STATUS_START_SESSION;
				break;
			}
			
			// Process response	
			processResponse();
			break;
			
		case STATUS_SEND_RESPONSE:
		
			// Send Action/Status msg.
			Lhings_TimeRef = now();
			write();
			
			// Set as connected
			Lhings_retry_cont = 0;
			Lhings_retry_multiplier = LHINGS_KEEP_ALIVE_TIME;
			Lhings_TimeRef = now();

			Lhings_status = STATUS_CONNECTED;
			break;

		case STATUS_SEND_EVENT:
		
			Lhings_status = STATUS_WAIT_EVENT_RESPONSE;

			// Send Action/Status msg.
			Lhings_TimeRef = now();
			write();

			break;
		
		case STATUS_WAIT_EVENT_RESPONSE:
			// Get UDP packet
			if( !getResponse() ){  		
				if( timeout() ){
					Lhings_status = STATUS_SEND_EVENT;
				}
				break;
			}
			// Process response	
			processResponse();
			Lhings_status = STATUS_CONNECTED;
			break;

		case STATUS_CLOSE_SESSION:
		
			// Send Close Session packet
			Lhings_TimeRef = now();
			generateTransID();
			write();
			Lhings_status = STATUS_CLOSED;
			
			break;
			
		case STATUS_CLOSED:
		
			getResponse();
			break;
			
		default:
			break;
	}
	
	return;
}



//---------------------------------------------------------------------------
//
//	read - read & check STUN data packets
//
int LhingsClass::read(void) {

	int i;
	
	// Check empty message
	if(Lhings_buffer_len <= 0)
		return 4;
		
	// Check first to bits
	if( (Lhings_buffer[0]&0b11000000) != 0x00)
		return CORRUPTED_MSG;
		
	// Check Magic cookie
	if( (Lhings_buffer[4] != 0x21) || (Lhings_buffer[5] != 0x12) || (Lhings_buffer[6] != 0xa4) || (Lhings_buffer[7] != 0x42) )
		return CORRUPTED_MSG;
	
	// Check message length
	long len;
	len = (Lhings_buffer[2]<<8)+Lhings_buffer[3];
	if( len != (Lhings_buffer_len - 20) )
		return CORRUPTED_MSG;
	
	// Check message type 
	long mClass = getMessageType();
	long mMsgType = 0;
	mMsgType = (Lhings_msg_type[1]<<8)+Lhings_msg_type[0];
	
	if(Lhings_status == STATUS_START_SESSION_RESP){
	
		// Check Binding Error response
		if( (mMsgType == MSG_BINDING) && (mClass == CLASS_ERROR) ) {	
			
			// Check ERROR-CODE: TIME_STAMP
			if( (Lhings_buffer[26] == 0x06) && (Lhings_buffer[27] == 0x05) ){
				
				// Set TimeStamp
				Lhings_TimeRef = 0x00000000;
				Lhings_TimeRef = Lhings_buffer[32];
				Lhings_TimeRef = (Lhings_TimeRef<<8)+Lhings_buffer[33];
				Lhings_TimeRef = (Lhings_TimeRef<<8)+Lhings_buffer[34];
				Lhings_TimeRef = (Lhings_TimeRef<<8)+Lhings_buffer[35];
				setTime(Lhings_TimeRef);
				
				// Restore vars.
				generateTransID();
				Lhings_retry_cont = 0;
				Lhings_retry_multiplier = 2;
				Lhings_status = STATUS_START_SESSION;
			}
			else{
				if( Lhings_Registered ){
					// Close session - this device has been deleted in your dashboard
					#ifdef SERIAL_LOGS
					if(Lhings_Logs){
						Serial.println("Device deleted, please reset");
					}
					#endif
					
					close();
					return CLOSE_MSG;
				}
				else{
					// Not recognized error
					Lhings_retry_cont = 7;
					Lhings_retry_multiplier = 10;
				}
			}
			
			return CLASS_ERROR;
		}
		else{
			if( !Lhings_Registered ){
				
				// Get Device UUID from Lhings
				long uIdx;
				uIdx = getAttributeIndex(ATT_UUID);
				if( uIdx == 1 ){
					return CORRUPTED_MSG;
				}
				
				for(i=0; i<16; i++)
					Lhings_hex_UUID[i] = Lhings_buffer[uIdx+4+i];
				getUUIDstr();
				
				saveUUID();
				Lhings_Registered = true;
				
				#ifdef SERIAL_LOGS
				if(Lhings_Logs){
					Serial.print("Setting UUID: ");
					Serial.write(&Lhings_str_UUID[0], 36);
					Serial.println();
				}
				#endif
			}
		}
		
		return mClass;
	}
	
	// Check TimeStamp
	long TimeIdx, TimeNow, TimeRes;
	time_t TimeAux = 0x00000000;
	TimeIdx = getAttributeIndex(ATT_TIMESTAMP);
	if( TimeIdx == 1 ){
		#ifdef SERIAL_RAW_LOGS
			Serial.println("Error: Timestamp");
		#endif
		
		return CORRUPTED_MSG;
	}
	TimeAux =  Lhings_buffer[TimeIdx+4]; 	TimeAux <<= 8;
	TimeAux += Lhings_buffer[TimeIdx+5]; 	TimeAux <<= 8; 
	TimeAux += Lhings_buffer[TimeIdx+6];	TimeAux <<= 8;
	TimeAux += Lhings_buffer[TimeIdx+7];
	TimeNow = now();
	
	if(TimeNow > TimeAux) 	TimeRes = (TimeNow - TimeAux);
	else					TimeRes = (TimeAux - TimeNow);
	/*
	if( TimeRes >= LHINGS_TIMESTAMP_MAX_DELAY ) {
		#ifdef SERIAL_LOGS
			Serial.println("Error: Timestamp");
		#endif
	
		return CORRUPTED_MSG;
	}
	*/
	
	// Check UUID
	long Idx;
	Idx = getAttributeIndex(ATT_UUID);
	if( Idx != 1 ){
		
		for(i=0; i<16; i++){
			if(Lhings_buffer[i+Idx+4] != Lhings_hex_UUID[i]){
		
				#ifdef SERIAL_RAW_LOGS
					Serial.println("Ignore UUID");
				#endif
				return CORRUPTED_MSG;
			}
		}
	}
	
	
	// Check Message Integrity
	unsigned char *hashptr;
	Sha1.initHmac((const uint8_t*)Lhings_apiKey, 36);
	for(i=0; i<(Lhings_buffer_len-24); i++)
		Sha1.write(Lhings_buffer[i]);
	hashptr = Sha1.resultHmac();	
	for(i=0; i<20; i++){
		if( Lhings_buffer[(Lhings_buffer_len-20)+i] != hashptr[i] ){
			#ifdef SERIAL_RAW_LOGS
				Serial.println("Error: wrong signature");
			#endif
	
			return CORRUPTED_MSG;
		}
	}

	// Read payload/args in case of action
	long ActIdx;
	long ActNamelen;
	if( (mMsgType == MSG_ACTION) && (mClass == CLASS_REQUEST) ) {

		// Find Att.
		ActIdx = getAttributeIndex(ATT_NAME);
		if( ActIdx == 1 )
			return CORRUPTED_MSG;

		// Get Action name
		ActNamelen = Lhings_buffer[ActIdx+2];
		ActNamelen = (ActNamelen<<8)+Lhings_buffer[ActIdx+3]; 
		if(ActNamelen > LHINGS_NAME_MAX_SIZE){
			#ifdef SERIAL_RAW_LOGS
				Serial.println("ERROR: action name too long");
			#endif
			return CORRUPTED_MSG; 
		}
		for(i=0; i<ActNamelen; i++)
			Lhings_name_buffer[i] = Lhings_buffer[ActIdx+4+i];
		Lhings_name_buffer[ActNamelen] = '\0';
	
		#ifdef SERIAL_LOGS
		if(Lhings_Logs){
			Serial.print("ACTION: ");
			Serial.write(&Lhings_name_buffer[0], strlen((const char*)Lhings_name_buffer));
			Serial.println();
		}
		#endif

		// Set Action flag
		Lhings_action_flag = true;
		Lhings_payload_type = EVT_EMPTY;
		Lhings_payload_buffer[0] = '\0';
		Lhings_payload_buffer_len = 0;
		
		// Find Payload/Args Att.
		ActIdx = getAttributeIndex(ATT_PAYLOAD);
		if(ActIdx != 1){
		
			// Get Action payload
			ActNamelen = Lhings_buffer[ActIdx+2];
			ActNamelen = (ActNamelen<<8)+Lhings_buffer[ActIdx+3]; 
			if(ActNamelen > LHINGS_PAYLOAD_MAX_SIZE){
				#ifdef SERIAL_RAW_LOGS
					Serial.println("ERROR: action payload too long");
				#endif
				return CORRUPTED_MSG; 
			}
			for(i=0; i<ActNamelen; i++)
				Lhings_payload_buffer[i] = Lhings_buffer[ActIdx+4+i];
			Lhings_payload_buffer[ActNamelen] = '\0';
		
			#ifdef SERIAL_RAW_LOGS
				Serial.println("Payload: ");
				Serial.write(Lhings_payload_buffer,ActNamelen);
				Serial.println();
			#endif
		
			Lhings_payload_type = EVT_PAYLOAD;
			Lhings_payload_buffer_len = ActNamelen;
		}
		else{

			// Find Args Att.
			ActIdx = getAttributeIndex(ATT_ARGS);
			if(ActIdx != 1){
		
				// Get Action args
				ActNamelen = Lhings_buffer[ActIdx+2];
				ActNamelen = (ActNamelen<<8)+Lhings_buffer[ActIdx+3]; 
				if(ActNamelen > LHINGS_PAYLOAD_MAX_SIZE){
					#ifdef SERIAL_RAW_LOGS
						Serial.println("ERROR: action args too long");
					#endif
					return CORRUPTED_MSG; 
				}
				for(i=0; i<ActNamelen; i++)
					Lhings_payload_buffer[i] = Lhings_buffer[ActIdx+4+i];
				Lhings_payload_buffer[ActNamelen] = '\0';
			
				#ifdef SERIAL_RAW_LOGS
					Serial.println("Args: ");
					Serial.write(Lhings_payload_buffer,ActNamelen);
					Serial.println();
				#endif
			
				Lhings_payload_type = EVT_ARGS;
				Lhings_payload_buffer_len = ActNamelen;
			}
		}
	}
	
	// Get Transaction ID
	for(i=0; i<12; i++)
		Lhings_TransID[i] = Lhings_buffer[i+8];
		
	return mClass;
}

//---------------------------------------------------------------------------
//
//	write - writes STUN data packet
//
void LhingsClass::write(void) {

	unsigned char *ptr;
	int i, k, outdatalen = 0, mMsgType = 0;
	int Userlen, Userlenpad, Namelen, Namelenpad, Payloadlenpad;
	long msg_len;
	
	ptr = &Lhings_buffer[0];
	mMsgType = (Lhings_msg_type[1]<<8)+Lhings_msg_type[0];
	
	// Set lengths
	Userlen = strlen((const char*)Lhings_userName);					// Set Username attribute length
	Userlenpad = 0;
	while( ((Userlen+4+Userlenpad)%4) != 0 )
		Userlenpad++;
	msg_len = 4+Userlen+Userlenpad;
	
	// Start/Close session length
	if((Lhings_status == STATUS_START_SESSION) || (Lhings_status == STATUS_CLOSE_SESSION)){
		Namelen = strlen((const char*)Lhings_devName);				// Set UserName attribute length
		Namelenpad = 0;
		while( ((Namelen+4+Namelenpad)%4) != 0 )
			Namelenpad++;
			
		msg_len += ((4+Namelen+Namelenpad) + 8);					// Name + Begin Session
	}
	
	// Event request length
	if(mMsgType == MSG_EVENT){
		Namelen = strlen((const char*)Lhings_name_buffer);			// Set EventName attribute length
		Namelenpad = 0;
		while( ((Namelen+4+Namelenpad)%4) != 0 )
			Namelenpad++;
			
		msg_len += (4+Namelen+Namelenpad);							// Name
		
		// Set Event Payload length
		if(Lhings_payload_buffer_len > 0){
			Payloadlenpad = 0;
			while( ((Lhings_payload_buffer_len+4+Payloadlenpad)%4) != 0 )
				Payloadlenpad++;
				
			msg_len += (4+Lhings_payload_buffer_len+Payloadlenpad);	// Payload att. len	
		}
	}
	
	// Status request
	int lon = 0, lonpad;
	if(mMsgType == MSG_STATUS){
	
		// ARGS: in this library 8 status vars. MAX, all of them of "string" type
		// #args + lenArg1 + lenArg2 + Mask + [lenString(2bytes) + lenName(2bytes) + String (N bytes) + Name(N bytes)] + [value(4bytes) + Name(N bytes)]
		if(Lhings_StatusNum > 0){
		
			// Set status parameters: msg. length 
			lon = 2+Lhings_StatusNum; 
			for(i=0; i<Lhings_StatusNum; i++)
				lon += (4+strlen((const char*)Lhings_StatusList[i])+strlen((const char*)Lhings_status_buffer[i]));
			lonpad = 0;
			while( ((4+lon+lonpad)%4) != 0 )
				lonpad++;

			msg_len += (4+lon+lonpad);													// Sum ARGS Att. size
			
			if((4+lon+lonpad) >= LHINGS_PAYLOAD_MAX_SIZE){
			
				// There are to many stat vars. - buffer length is limited
				// NOTE: if memory is available, you could enhance the size of LHINGS_PAYLOAD_MAX_SIZE in Lhings.h file
				lon = 0;	
				#ifdef SERIAL_LOGS
				if(Lhings_Logs){
					Serial.println("Too many status vars.");
				}
				#endif
			}
			else{
			
				// Set header attribute and length
				i = 0;
				Lhings_payload_buffer[i++] = 0x0C;											// STUN Status Att.
				Lhings_payload_buffer[i++] = 0x19;											// STUN Status Att.
				Lhings_payload_buffer[i++] = (unsigned char)((lon&0xFF00)>>8);				// Msg. size
				Lhings_payload_buffer[i++] = (unsigned char)(lon&0x00FF);					// Msg. size

				// Set ARGs header
				int iSt, exp=1;
				Lhings_payload_buffer[i++] = Lhings_StatusNum;																			// # of Args.
				for(iSt=0; iSt<Lhings_StatusNum; iSt++)
					Lhings_payload_buffer[i++] = (unsigned char)(strlen(Lhings_StatusList[iSt])+strlen(Lhings_status_buffer[iSt]));		// Length N vars.
				for(iSt=0; iSt<Lhings_StatusNum; iSt++)
					exp *= 2;
				Lhings_payload_buffer[i++] = exp-1;																						// Mask (binary 111..)

				
				// Set ARGs content
				for(k=0; k<Lhings_StatusNum; k++){
				
					iSt = strlen((const char*)Lhings_status_buffer[k]);
					Lhings_payload_buffer[i++] = (unsigned char)((iSt&0xFF00)>>8);				// Var string value size
					Lhings_payload_buffer[i++] = (unsigned char)(iSt&0x00FF);					// Var string value size

					iSt = strlen((const char*)Lhings_StatusList[k]);
					Lhings_payload_buffer[i++] = (unsigned char)((iSt&0xFF00)>>8);				// Var name value size
					Lhings_payload_buffer[i++] = (unsigned char)(iSt&0x00FF);					// Var name value size

					for(iSt=0; iSt<strlen((const char*)Lhings_status_buffer[k]); iSt++)
						Lhings_payload_buffer[i++] = Lhings_status_buffer[k][iSt];				// Var. string value
					for(iSt=0; iSt<strlen((const char*)Lhings_StatusList[k]); iSt++)
						Lhings_payload_buffer[i++] = Lhings_StatusList[k][iSt];					// Var. name value
				}
					
				// Padding
				for(iSt=0; iSt<lonpad; iSt++)
					Lhings_payload_buffer[i++] = 0x00;
			}
		}
		else{
			msg_len += 8;
		}
	}
	
	if(Lhings_Registered)	
		msg_len += (8 + 20 + 24);														// TimeStamp, UUID, Msg. Integrity
	else
		msg_len += (8 + 24);															// TimeStamp, Msg. Integrity
	
	
	// ** HEADER **  
	if((Lhings_status == STATUS_START_SESSION) || (Lhings_status == STATUS_CLOSE_SESSION)){	
		setMessageType(MSG_BINDING, CLASS_REQUEST);
	}
	else if(Lhings_status == STATUS_KEEP_ALIVE){
		setMessageType(MSG_KEEP_ALIVE, CLASS_REQUEST);
	}
	else if(mMsgType == MSG_ACTION){
		setMessageType(MSG_ACTION, CLASS_SUCCESS);
	}
	else if(mMsgType == MSG_STATUS){
		setMessageType(MSG_STATUS, CLASS_SUCCESS);
	}	
	else if(mMsgType == MSG_EVENT){
		setMessageType(MSG_EVENT, CLASS_REQUEST);
		generateTransID();
	}
	
	*ptr++ = Lhings_msg_type[1];									// Msg type [1]                              
	*ptr++ = Lhings_msg_type[0];									// Msg.type [0]
		
	*ptr++ = (unsigned char)((msg_len&0xFF00)>>8);					// Msg. length [1]                            
	*ptr++ = (unsigned char)(msg_len);								// Msg. length [0]
	*ptr++ = 0x21; 													// Magic cookie (always set to this)                         	
	*ptr++ = 0x12;                             	
	*ptr++ = 0xa4;                             	
	*ptr++ = 0x42; 	
	for(i=0; i<12; i++) *ptr++ = Lhings_TransID[i];					// Transaction ID             
		outdatalen = 20;											// Header length
	
	// ** ATTRIBUTES **	
	*ptr++ = (unsigned char)((ATT_USERNAME&0xFF00)>>8);				// Attribute type: USERNAME
	*ptr++ = (unsigned char)((ATT_USERNAME&0x00FF));
	*ptr++ = 0x00;													// Attribute length
	*ptr++ = (unsigned char)Userlen;
	for(i=0; i<Userlen; i++)										// username 
		*ptr++ = Lhings_userName[i];
	for(i=0; i<Userlenpad; i++)										// padding 
		*ptr++ = 0x00;								
	outdatalen += (4+Userlen+Userlenpad);
						
	*ptr++ = (unsigned char)((ATT_TIMESTAMP&0xFF00)>>8);			// Attribute type: TIMESTAMP
	*ptr++ = (unsigned char)((ATT_TIMESTAMP&0x00FF));						
	*ptr++ = 0x00;													// Attribute length: 4
	*ptr++ = 0x04; 	
	Lhings_TimeStamp = now();										// Time stamp 
	*ptr++ = (unsigned char)((Lhings_TimeStamp&0xFF000000)>>24);		  						
	*ptr++ = (unsigned char)((Lhings_TimeStamp&0x00FF0000)>>16);
	*ptr++ = (unsigned char)((Lhings_TimeStamp&0x0000FF00)>>8);							
	*ptr++ = (unsigned char)((Lhings_TimeStamp&0x000000FF));
	outdatalen += 8;

	if(Lhings_Registered){	
		*ptr++ = (unsigned char)((ATT_UUID&0xFF00)>>8);				// Attribute type: UUID
		*ptr++ = (unsigned char)((ATT_UUID&0x00FF));					
		*ptr++ = 0x00;												// Attribute length: 16 	
		*ptr++ = 0x10;							
		for(i=0; i<16; i++)							
			*ptr++ = Lhings_hex_UUID[i];	
		outdatalen += 20;
	}
			
	if((Lhings_status == STATUS_START_SESSION) || (Lhings_status == STATUS_CLOSE_SESSION)){			
		*ptr++ = (unsigned char)((ATT_NAME&0xFF00)>>8);				// Attribute type: NAME (device)
		*ptr++ = (unsigned char)((ATT_NAME&0x00FF));				
		*ptr++ = 0x00;												// Attribute length
		*ptr++ = (unsigned char)Namelen;
		for(i=0; i<Namelen; i++)									// Device Name
			*ptr++ = Lhings_devName[i];	
		for(i=0; i<Namelenpad; i++)									// padding
			*ptr++ = 0x00;						 
		outdatalen += (4+Namelen+Namelenpad);
	}
	
	if(mMsgType == MSG_EVENT){			
		*ptr++ = (unsigned char)((ATT_NAME&0xFF00)>>8);				// Attribute type: NAME (event)
		*ptr++ = (unsigned char)((ATT_NAME&0x00FF));				
		*ptr++ = 0x00;												// Attribute length
		*ptr++ = (unsigned char)Namelen;
		for(i=0; i<Namelen; i++)									// Event Name
			*ptr++ = Lhings_name_buffer[i];	
		for(i=0; i<Namelenpad; i++)									// padding
			*ptr++ = 0x00;						 
		outdatalen += (4+Namelen+Namelenpad);
		
		if(Lhings_payload_buffer_len > 0){
		
			if(Lhings_payload_type == EVT_ARGS){
				*ptr++ = (unsigned char)((ATT_ARGS&0xFF00)>>8);		// Attribute type: ARGS (event)
				*ptr++ = (unsigned char)((ATT_ARGS&0x00FF));	
			}
			else{
				*ptr++ = (unsigned char)((ATT_PAYLOAD&0xFF00)>>8);	// Attribute type: PAYLOAD (event)
				*ptr++ = (unsigned char)((ATT_PAYLOAD&0x00FF));	
			}
			*ptr++ = 0x00;											// Attribute length
			*ptr++ = (unsigned char)Lhings_payload_buffer_len;
			for(i=0; i<Lhings_payload_buffer_len; i++)				// Event Payload
				*ptr++ = Lhings_payload_buffer[i];	
			for(i=0; i<Payloadlenpad; i++)							// padding
				*ptr++ = 0x00;						 
			outdatalen += (4+Lhings_payload_buffer_len+Payloadlenpad);
		}
	}
	
	if(mMsgType == MSG_STATUS){
		if(lon == 0){
			*ptr++ = (unsigned char)((ATT_ARGS&0xFF00)>>8);			// Attribute type: ARGS (empty status)
			*ptr++ = (unsigned char)((ATT_ARGS&0x00FF));				
			*ptr++ = 0x00;											// Attribute length
			*ptr++ = 0x01;
			*ptr++ = 0x00;											// Padding
			*ptr++ = 0x00;
			*ptr++ = 0x00;
			*ptr++ = 0x00;
			outdatalen += 8;
		}
		else{
			
			if((outdatalen+4+lon+lonpad) >= (LHINGS_BUFFER_MAX_SIZE - 50)){
				#ifdef SERIAL_RAW_LOGS
					Serial.println("ERROR: status buffer out of range");
				#endif
	
				return;
			}
			
			for(i=0;i<(4+lon+lonpad); i++)
				*ptr++ = Lhings_payload_buffer[i];
			outdatalen += (4+lon+lonpad);
		}
	}
	
	if((Lhings_status == STATUS_START_SESSION) || (Lhings_status == STATUS_CLOSE_SESSION)){	
		*ptr++ = (unsigned char)((ATT_BEGIN_SESSION&0xFF00)>>8);	// Attribute type: BEGIN_SESSION
		*ptr++ = (unsigned char)((ATT_BEGIN_SESSION&0x00FF));		 							
		*ptr++ = 0x00;												// Attribute length: 1	
		*ptr++ = 0x01;
		
		if(Lhings_status == STATUS_START_SESSION){	
			if(Lhings_Registered)
				*ptr++ = SESSION_OPEN;								// Open Session Byte
			else
				*ptr++ = SESSION_REGISTER;							// Register UUID & Start Session Byte
		}
		else{
			*ptr++ = SESSION_CLOSE;									// Close Session Byte	
		}	
		*ptr++ = 0x00;												// padding 					
		*ptr++ = 0x00;					
		*ptr++ = 0x00;
		outdatalen += 8;
	}
	
	// ** MESSAGE-INTEGRITY
	unsigned char *hashptr;
	Sha1.initHmac((const uint8_t*)Lhings_apiKey, 36);
	for(i=0; i<outdatalen; i++)
		Sha1.write(Lhings_buffer[i]);
	hashptr = Sha1.resultHmac();
	*ptr++ = (unsigned char)((ATT_MSG_INTEGRITY&0xFF00)>>8);		// Attribute type: MESSAGE_INTEGRITY
	*ptr++ = (unsigned char)((ATT_MSG_INTEGRITY&0x00FF));
	*ptr++ = 0x00;													// Attribute length: 20
	*ptr++ = 0x14;
	for(i=0; i<20; i++)												// attribute content: Hash result
		*ptr++ = hashptr[i];
	outdatalen += 24;

	// Prepare packet and send to Lhings Server
	if(outdatalen < LHINGS_BUFFER_MAX_SIZE){
		Udp.beginPacket(Lhings_server_IP, LHINGS_PORT_UDP);
		Udp.write(Lhings_buffer, outdatalen);
		Udp.endPacket();
	}
	else{
		#ifdef SERIAL_RAW_LOGS
			Serial.println("ERROR: write buffer out of range");
		#endif
	}
	
	#ifdef SERIAL_RAW_LOGS
		Serial.println("Write hex:");
		Serial.write(Lhings_buffer, outdatalen);
		Serial.println();
	#endif
				
	return;
}


//---------------------------------------------------------------------------
//
//	writeDescriptor - sends device descriptor defined in JSON_Descriptor
//
boolean LhingsClass::writeDescriptor(void) {

	char ss[5];
	int cont, i;
	unsigned char ip[16];
	
	if(TcpClient.connect(Lhings_server_IP, 8080)) {
				
		// Http Header
		printProgMemStr(DescriptorPOST);
		TcpClient.write(&Lhings_str_UUID[0], 36);
		#ifdef SERIAL_RAW_LOGS
			Serial.write(&Lhings_str_UUID[0], 36);
		#endif
		TcpClient.print("/descriptor HTTP/1.1\r\n");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("/descriptor HTTP/1.1\r\n");
		#endif
		TcpClient.print("Host: ");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("Host: ");
		#endif
		
		ipAddrToStr((unsigned char*)&Lhings_server_IP[0], (char*)&ip[0]);
		TcpClient.write(&ip[0], strlen((const char*)ip));
		#ifdef SERIAL_RAW_LOGS
			Serial.write(&ip[0], strlen((const char*)ip));
		#endif
		TcpClient.print("\r\n");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("\r\n");
		#endif
		TcpClient.print("X-Api-Key: ");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("X-Api-Key: ");
		#endif
		TcpClient.write((const uint8_t*)&Lhings_apiKey[0], 36);
		#ifdef SERIAL_RAW_LOGS
			Serial.write((const uint8_t*)&Lhings_apiKey[0], 36);
		#endif
		TcpClient.print("\r\nContent-Length: ");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("\r\nContent-Length: ");
		#endif
		
		i = getlenProgMemStr(JSON_Descriptor) + Lhings_DescriptorSize; 
		itoa(i, ss, 10);
		TcpClient.write((const uint8_t*)&ss[0], strlen((const char*)ss));
		#ifdef SERIAL_RAW_LOGS
			Serial.write((const uint8_t*)&ss[0], strlen((const char*)ss));
		#endif
		printProgMemStr(DescriptorContentType);
		TcpClient.print("Connection: close\r\n");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("Connection: close\r\n");
		#endif
		TcpClient.print("\r\n");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("\r\n");
		#endif
		
		// Descriptor content - Json
		printProgMemStr(JSON_Descriptor);
		
		// Set actions
		TcpClient.print("\"actionList\":[");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("\"actionList\":[");
		#endif
		
		cont = 0;
		while(Lhings_ActionList[cont].name != NULL ){
			
			// Action - Button type
			if(Lhings_ActionList[cont].type == ACT_BUTTON){
				TcpClient.print("{\"name\": \"");
				#ifdef SERIAL_RAW_LOGS
					Serial.print("{\"name\": \"");
				#endif
				TcpClient.print(Lhings_ActionList[cont].name);
				#ifdef SERIAL_RAW_LOGS
					Serial.print(Lhings_ActionList[cont].name);
				#endif
				printProgMemStr(DescriptorAction_button);
				TcpClient.print(Lhings_ActionList[cont].name);
				#ifdef SERIAL_RAW_LOGS
					Serial.print(Lhings_ActionList[cont].name);
				#endif
				TcpClient.print("\"}");
				#ifdef SERIAL_RAW_LOGS
					Serial.print("\"}");
				#endif
			}
			else{
				TcpClient.print("{\"name\": \"");
				#ifdef SERIAL_RAW_LOGS
					Serial.print("{\"name\": \"");
				#endif
				TcpClient.print(Lhings_ActionList[cont].name);
				#ifdef SERIAL_RAW_LOGS
					Serial.print(Lhings_ActionList[cont].name);
				#endif
				printProgMemStr(DescriptorAction_with_input_open);
				if(Lhings_ActionList[cont].type == ACT_STRING){
					TcpClient.print("string");
					#ifdef SERIAL_RAW_LOGS
						Serial.print("string");
					#endif
				}
				else if(Lhings_ActionList[cont].type == ACT_INTEGER){
					TcpClient.print("integer");
					#ifdef SERIAL_RAW_LOGS
						Serial.print("integer");
					#endif
				}
				printProgMemStr(DescriptorAction_with_input_close);
				
				TcpClient.print(Lhings_ActionList[cont].name);
				#ifdef SERIAL_RAW_LOGS
					Serial.print(Lhings_ActionList[cont].name);
				#endif
				TcpClient.print("\"}");
				#ifdef SERIAL_RAW_LOGS
					Serial.print("\"}");
				#endif
			}  
			
			if(Lhings_ActionList[cont+1].name != NULL){
				TcpClient.print(",\r\n");
				#ifdef SERIAL_RAW_LOGS
					Serial.print(",\r\n");
				#endif
			}
			cont++;
		}
		TcpClient.print("],\r\n");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("],\r\n");
		#endif
		
		// Set events
		TcpClient.print("\"eventList\":[");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("\"eventList\":[");
		#endif
		cont = 0;
		while(Lhings_EventList[cont] != NULL ){
			
			TcpClient.print("{\"name\": \"");
			#ifdef SERIAL_RAW_LOGS
				Serial.print("{\"name\": \"");
			#endif
			TcpClient.print(Lhings_EventList[cont]);
			#ifdef SERIAL_RAW_LOGS
				Serial.print(Lhings_EventList[cont]);
			#endif
			TcpClient.print("\"}");
			#ifdef SERIAL_RAW_LOGS
				Serial.print("\"}");
			#endif
			
			if(Lhings_EventList[cont+1] != NULL){
				TcpClient.print(",\r\n");
				#ifdef SERIAL_RAW_LOGS
					Serial.print(",\r\n");
				#endif
			}
			cont++;
		}
		TcpClient.print("],\r\n");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("],\r\n");
		#endif
		
		// Set status
		TcpClient.print("\"stateVariableList\":[");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("\"stateVariableList\":[");
		#endif
		
		cont = 0;
		while(Lhings_StatusList[cont] != NULL ){
			
			TcpClient.print("{\"name\": \"");
			#ifdef SERIAL_RAW_LOGS
				Serial.print("{\"name\": \"");
			#endif
			
			TcpClient.print(Lhings_StatusList[cont]);
			#ifdef SERIAL_RAW_LOGS
				Serial.print(Lhings_StatusList[cont]);
			#endif
			printProgMemStr(DescriptorStatus);
			
			if(Lhings_StatusList[cont+1] != NULL){
				TcpClient.print(",\r\n");
				#ifdef SERIAL_RAW_LOGS
					Serial.print(",\r\n");
				#endif
			}
			cont++;
		}
		TcpClient.print("]}\r\n");
		#ifdef SERIAL_RAW_LOGS
			Serial.print("]}\r\n");
		#endif
		
		Lhings_status = STATUS_WAIT_DESCRIPTOR_RESP;
		
		#ifdef SERIAL_RAW_LOGS
			Serial.println("Lhings: TCP connected");
		#endif
	} 
	else{

		Lhings_status = STATUS_SEND_DESCRIPTOR;
		
		#ifdef SERIAL_RAW_LOGS
			Serial.println("Lhings: TCP connection failed");
		#endif
	}

	return true;
}


//---------------------------------------------------------------------------
//
//	actionAvailable - TRUE if any action is received
//					  Payload/Args, if any, is in Lhings_payload_buffer[]
//
boolean LhingsClass::actionAvailable(void) {

	if( !Lhings_action_flag )
		return false;

	Lhings_action_flag = false;
	return true;
}

//---------------------------------------------------------------------------
//
//	actionAvailable - TRUE if action with "name X" is received
//					  Payload, if any, is in Lhings_payload_buffer[]
//
boolean LhingsClass::actionAvailable(char *name) {

	int i;
	if( !Lhings_action_flag )
		return false;
		
	if(strcmp((const char*)name, (const char*)&Lhings_name_buffer[0]) == 0){
		Lhings_action_flag = false;
		return true;
	}
	else
		return false;
}


//---------------------------------------------------------------------------
//
//	actionPayloadAvailable -  Returns Payload Length if payload/args have been received,
//					 		  0 otherwise. 
//
int LhingsClass::actionPayloadAvailable(void) {

	if((Lhings_payload_type != EVT_ARGS) && (Lhings_payload_type != EVT_PAYLOAD))
		return 0;
		
	return Lhings_payload_buffer_len;
}


//---------------------------------------------------------------------------
//
//	eventWrite - sends event notification
//
void LhingsClass::eventWrite(char *name) {

	int mMsgType = 0, i;
	strcpy((char*)&Lhings_name_buffer[0], (const char*)name);

	// Set NO payload
	Lhings_payload_buffer_len = 0;
	
	#ifdef SERIAL_LOGS
	if(Lhings_Logs){
		Serial.print("EVENT: ");
		Serial.write(&Lhings_name_buffer[0], strlen((const char*)Lhings_name_buffer));
		Serial.println();
	}
	#endif

	mMsgType = MSG_EVENT;
	Lhings_msg_type[1] = (unsigned char)((mMsgType&0xFF00)>>8);
	Lhings_msg_type[0] = (unsigned char)(mMsgType&0x00FF);    

	generateTransID();
	Lhings_retry_cont = 0;
	Lhings_retry_multiplier = 2;

	Lhings_status = STATUS_SEND_EVENT;
	return;
}


//---------------------------------------------------------------------------
//
//	eventWrite - sends event notification with payload
//
void LhingsClass::eventWrite(char *name, char *payload, int len, boolean type) {

	int mMsgType = 0, i;
	strcpy((char*)&Lhings_name_buffer[0], (const char*)name);
	
	for(i=0; i<len; i++)
		Lhings_payload_buffer[i] = payload[i];

	// Set payload length
	Lhings_payload_buffer_len = len;
	
	// Set payload type
	if(type==EVT_ARGS)
		Lhings_payload_type = EVT_ARGS;
	else
		Lhings_payload_type = EVT_PAYLOAD;
	
	
	#ifdef SERIAL_LOGS
		Serial.print("EVENT: ");
		Serial.write(Lhings_name_buffer, strlen((const char*)Lhings_name_buffer));
		Serial.println();
		Serial.println("Payload: ");
		Serial.write(Lhings_payload_buffer, Lhings_payload_buffer_len);
		Serial.println();
	#endif

	mMsgType = MSG_EVENT;
	Lhings_msg_type[1] = (unsigned char)((mMsgType&0xFF00)>>8);
	Lhings_msg_type[0] = (unsigned char)(mMsgType&0x00FF);    

	generateTransID();
	Lhings_retry_cont = 0;
	Lhings_retry_multiplier = 2;

	Lhings_status = STATUS_SEND_EVENT;
	return;
}


//---------------------------------------------------------------------------
//
boolean LhingsClass::statusWrite(char *status_name, char *status_content) {

	int len, k; 
	bool vSet = false;
	
	// Check status name match
	for(k=0; k<LHINGS_STATUS_MAX_VARS; k++){
	
		if(strcmp(Lhings_StatusList[k], status_name) == 0){
			vSet = true;
			break;
		}
	}
	
	// Write new content
	if( vSet ){
		len = strlen((const char*)status_content);
		
		if(len >= LHINGS_STATUS_MAX_SIZE)
			strncpy(Lhings_status_buffer[k], status_content, LHINGS_STATUS_MAX_SIZE-1);
		else
			strcpy(Lhings_status_buffer[k], status_content);
	}
	else 
		return false;

	return true;
}


//---------------------------------------------------------------------------
//
//	getResponse - gets any data received in STUN port
//
boolean LhingsClass::getResponse(void) {

	// Check packet reception
	int len;
	len = Udp.parsePacket();
	if(len == 0){
		return false;
	}
		
	// Check size of packet
	if(len >= LHINGS_BUFFER_MAX_SIZE){
		#ifdef SERIAL_RAW_LOGS
			Serial.println("Error: input buffer size not supported");
		#endif
		return false;
	}
		
	// Check start session response from server
	Udp.read(Lhings_buffer, len);
	Lhings_buffer_len = len;
	
	#ifdef SERIAL_RAW_LOGS
		Serial.println("Read hex:");
		Serial.write(Lhings_buffer, len);
		Serial.println("");
	#endif
			
	return true;
}

//---------------------------------------------------------------------------
//
//	processResponse - checks class of STUN message
//
boolean LhingsClass::processResponse(void) {

	int mClass;
	int mMsgType = 0;

	// Process response	
	if(Lhings_buffer_len > 0){

		mClass = read();
		mMsgType = (Lhings_msg_type[1]<<8)+Lhings_msg_type[0];

		switch(mClass) 
		{
			case CLASS_SUCCESS:

				Lhings_status = STATUS_CONNECTED;
				generateTransID();
				Lhings_retry_cont = 0;
				Lhings_retry_multiplier = LHINGS_KEEP_ALIVE_TIME;
				Lhings_TimeRef = now();
				return true;
				
			case CLASS_ERROR:

				Lhings_status = STATUS_START_SESSION;
				generateTransID();
				Lhings_retry_cont = 0;
				Lhings_retry_multiplier = 2;
				#ifdef SERIAL_RAW_LOGS
					Serial.println("Error: class resp.");
				#endif
				Lhings_TimeRef = now();
				return false;

			case CLASS_REQUEST:

				Lhings_status = STATUS_CONNECTED;
				Lhings_retry_cont = 0;
				Lhings_retry_multiplier = LHINGS_KEEP_ALIVE_TIME;
				Lhings_TimeRef = now();
			
				#ifdef SERIAL_RAW_LOGS
					Serial.println("Request received");
				#endif
				
				if((mMsgType == MSG_ACTION) || (mMsgType == MSG_STATUS) ){
					
					// Prepare response
					Lhings_status = STATUS_SEND_RESPONSE;
					
					#ifdef SERIAL_LOGS
					if(Lhings_Logs && (mMsgType == MSG_STATUS)){
						Serial.println("STATUS req.");
					}
					#endif
				}
				else 
					return false;

				return true;

			default:
				break;	
		}
	}
	
	Lhings_TimeRef = now();
	return false;
}

//---------------------------------------------------------------------------
//
//	setMessageType - sets STUN message type and class
//
void LhingsClass::setMessageType(long mMessageType, long mClass) {

	long mMsg = 0;
	unsigned char byte1, byte2;
	
	byte1 = (unsigned char)(((mMessageType&0x0070)<<1)+(mMessageType&0x000F));
	byte2 = (unsigned char)((mMessageType&0x0F80)>>6);
	
	mMsg = (byte2<<8)+byte1;
	mMsg |= mClass;
	Lhings_msg_type[0] = (unsigned char)(mMsg&0x00FF);
	Lhings_msg_type[1] = (unsigned char)((mMsg&0xFF00)>>8);
	
	return;
}

//---------------------------------------------------------------------------
//
//	getMessageType - gets STUN message type and class
//
long LhingsClass::getMessageType(void) {

	long mMsg = (Lhings_buffer[0]<<8)+Lhings_buffer[1];
	long mClass;
	unsigned char byte1, byte2;
	
	mClass = mMsg&0b0000000100010000;
	
	Lhings_msg_type[0] = (unsigned char)(((mMsg&0x0200)>>2)+((mMsg&0x00E0)>>1)+(mMsg&0x000F));
	Lhings_msg_type[1] = (unsigned char)((mMsg&0xFC00)>>10);
	
	return mClass;
}

//---------------------------------------------------------------------------
//
//	getAttributeIndex - gets the index of a defined Attribute inside the STUN 
//						message received. Returns 1 if Attribute not found.
//
long LhingsClass::getAttributeIndex(long mAtt) {
	
	long idx;
	long attLength = 0, attLengthpad = 0;
	
	idx = 20;
	while( idx < Lhings_buffer_len ){
	
		attLength = 0;
		attLengthpad = 0;
		
		if( (Lhings_buffer[idx] == (unsigned char)((mAtt&0xFF00)>>8)) && (Lhings_buffer[idx+1] == (unsigned char)(mAtt&0x00FF)) )
			return idx;
		else{
			attLength = (Lhings_buffer[idx+2]<<8)+Lhings_buffer[idx+3];
			while( ((attLength+4+attLengthpad)%4) != 0 )
				attLengthpad++;
		}

		idx+=(4+attLength+attLengthpad);
	}
	
	return 1;
}

//---------------------------------------------------------------------------
//
//	timeout - checks timeout for STUN message wait and resend
//
boolean LhingsClass::timeout(void) {

	if(now() - Lhings_TimeRef > (LHINGS_TIMEOUT*Lhings_retry_multiplier) ){
			
		// Timeout occurred
		if(Lhings_retry_cont < LHINGS_MAX_RETRY){
			Lhings_retry_cont++;
			Lhings_retry_multiplier *= 2;
		}

		Lhings_TimeRef = now();
		return true;
	}
	
	return false;
}

//---------------------------------------------------------------------------
//
//	timeoutKeepalive - checks timeout for sending STUN keepalives 
//
boolean LhingsClass::timeoutKeepalive(void) {

	if(now() - Lhings_TimeRef_Keepalive > (LHINGS_TIMEOUT*Lhings_retry_multiplier_keepalive) ){

		Lhings_TimeRef_Keepalive = now();
		return true;
	}
	
	return false;
}

//---------------------------------------------------------------------------
//
//	generateTransID - generates Transaction ID for STUN messages
//
void LhingsClass::generateTransID(void) {

    unsigned char *ptr;
    int i=0, c=0;
    ptr  = &Lhings_TransID[0];
     
    while(i<6){ 
   
      randNumber = random(0xFFFF); 
      
      *ptr++ = (unsigned char)(randNumber);
      *ptr++ = (unsigned char)((randNumber&0xFF00)>>8);
      i++;
    }
      
    return; 
}


//---------------------------------------------------------------------------
//
//	eraseUUID - erases the UUID in non-volatile memory
//
//				NOTE: this will change your device unique ID and 
//				it will appear as new device in your dashboard
//
void LhingsClass::eraseUUID(void) {
    
    EEPROM.write(0, '0');
    
    return; 
}


//---------------------------------------------------------------------------
//
//	saveUUID - saves generated UUID in non-volatile memory
//
void LhingsClass::saveUUID(void) {
    
    int i;
    
    EEPROM.write(0, 'A');
    
    for(i=1; i<37; i++)
      EEPROM.write(i, Lhings_str_UUID[i-1]); 
      
    return; 
}

//---------------------------------------------------------------------------
//
//	readUUID - reads UUID stored in non-volatile memory
//
boolean LhingsClass::readUUID(void) {
    
    int i;
    
    if(EEPROM.read(0) != 'A')
      return false;
    
    for(i=1; i<37; i++)
      Lhings_str_UUID[i-1] = EEPROM.read(i); 
	  
	getUUIDbin(&Lhings_hex_UUID[0]);
      
    return true; 
}

//---------------------------------------------------------------------------
//
//	getUUIDbin - translates UUID ascii to hex
//
void LhingsClass::getUUIDbin(unsigned char *data)
{
	unsigned char wAux[2];
	int i, c;

	c = 0;
	for(i=0; i<16; i++){

		wAux[1] = Lhings_str_UUID[c];
		c++;
		wAux[0] = Lhings_str_UUID[c];
		
		// Convert lowercase to uppercase
		if(wAux[1] > 'F') wAux[1] -= 'a'-'A';
		if(wAux[0] > 'F') wAux[0] -= 'a'-'A';

		// Convert 0-9, A-F to 0x0-0xF
		if(wAux[1] > '9')	wAux[1] -= 'A' - 10;
		else	wAux[1] -= '0';

		if(wAux[0] > '9')	wAux[0] -= 'A' - 10;
		else	wAux[0] -= '0';

		// Concatenate
		data[i] = (wAux[1]<<4) |  wAux[0];
		c++;

		if((c==8) || (c==13) || (c==18) || (c==23))
			c++;	
	}
	
	return;
}


//---------------------------------------------------------------------------
//
//	getUUIDstr - translates UUID hex to ascii
//
void LhingsClass::getUUIDstr(void)
{
	unsigned char wAux[2];
	int i, c;
	
	c = 0;
	for(i=0; i<16; i++){
	
		wAux[0] = itoahex((unsigned char)((Lhings_hex_UUID[i]&0xF0)>>4));
		wAux[1] = itoahex((unsigned char)(Lhings_hex_UUID[i]&0x0F));
		
		Lhings_str_UUID[c++] = wAux[0];
		Lhings_str_UUID[c++] = wAux[1];
	
		if((c==8) || (c==13) || (c==18) || (c==23))
			Lhings_str_UUID[c++] = '-';	
	}
	
	Lhings_str_UUID[c] = '\0';	
	
	return;
}


//---------------------- Helper methods -------------------------------------

//---------------------------------------------------------------------------
//
void LhingsClass::printProgMemStr(const prog_char str[]) {

  char c;
  if(!str) return;
  
  while((c = pgm_read_byte(str++))){
    TcpClient.print(c);
	#ifdef SERIAL_RAW_LOGS
		Serial.print(c);
	#endif
  }
}

//---------------------------------------------------------------------------
//
int LhingsClass::getlenProgMemStr(const prog_char str[]) {

  char c;
  int i=0;
  if(!str) return 0;
  while((c = pgm_read_byte(str++))){
    i++;
  }
  
  return i;
}

//---------------------------------------------------------------------------
//
unsigned char LhingsClass::itoahex(unsigned char input) {
    
  if(input < 10)
    return (input+0x30);
  else
	return (input+0x57);
}

//---------------------------------------------------------------------------
//
void LhingsClass::ipAddrToStr(unsigned char *input, char *output) {
    
	char ss[4];
	
	itoa(input[0], ss, 10);
	strcpy((char*)output, (const char*)ss);
	strcat((char*)output, ".");
	itoa(input[1], ss, 10);
	strcat((char*)output, (const char*)ss);
	strcat((char*)output, ".");
	itoa(input[2], ss, 10);
	strcat((char*)output, (const char*)ss);
	strcat((char*)output, ".");
	itoa(input[3], ss, 10);
	strcat((char*)output, (const char*)ss);
 
	return;
}
