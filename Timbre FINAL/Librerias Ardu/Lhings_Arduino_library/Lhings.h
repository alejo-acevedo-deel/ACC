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


#ifndef Lhings_h
#define Lhings_h

#include <SPI.h>
#include <EEPROM.h>    
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "Time.h"
#include "sha1.h"


// These #define are very restrictive in order to be used in limited devices as Arduino UNO
// In the need of more status vars and longer messages, feel free to enhance these values.
#define LHINGS_BUFFER_MAX_SIZE		300
#define LHINGS_PAYLOAD_MAX_SIZE		40
#define LHINGS_STATUS_MAX_VARS		2
#define LHINGS_USERNAME_LEN			30
#define LHINGS_DEVNAME_LEN			20
#define LHINGS_STATUS_MAX_SIZE		15	
#define LHINGS_NAME_MAX_SIZE		20


#define LHINGS_PORT_UDP 			3478
#define LHINGS_TIMEOUT				1
#define	LHINGS_MAX_RETRY			7
#define LHINGS_KEEP_ALIVE_TIME		30
#define	LHINGS_TIMESTAMP_MAX_DELAY	30




// Comment these two lines to avoid using the Serial port
#define SERIAL_LOGS				// Logs with string messages
//#define SERIAL_RAW_LOGS			// Logs with Hex data (more detailed)




// STUN Message types
#define MSG_BINDING			0x0001
#define MSG_KEEP_ALIVE		0x0EEA
#define MSG_EVENT			0x0EE4
#define MSG_ACTION			0x0EE5 
#define MSG_STATUS			0x0AEE 

// STUN Message classes
#define	CLASS_REQUEST		0b0000000000000000
#define CLASS_INDICATION	0b0000000000010000
#define CLASS_SUCCESS		0b0000000100000000
#define CLASS_ERROR			0b0000000100010000

#define CORRUPTED_MSG		0xFF
#define CLOSE_MSG			0xF5

// STUN Attributes
#define	ATT_USERNAME		0x0006
#define	ATT_MSG_INTEGRITY	0x0008
#define	ATT_ERROR_CODE		0x0009
#define	ATT_UNKNOWN_ATT		0x000A
#define	ATT_XOR_M_ADDRESS	0x0020
#define	ATT_TIMESTAMP		0x0C01
#define	ATT_BEGIN_SESSION	0x0C02
#define	ATT_UUID			0x0C03
#define	ATT_NAME			0x0C12
#define	ATT_PAYLOAD			0x0C18
#define	ATT_ARGS			0x0C19

// STUN Start-Session options
#define SESSION_CLOSE		0x00
#define SESSION_OPEN		0x01
#define SESSION_REGISTER	0x02

// EVENT MSG Type
#define EVT_EMPTY			0
#define EVT_PAYLOAD			1
#define EVT_ARGS			2

// ACTION Type
#define ACT_BUTTON			0
#define ACT_STRING			1
#define ACT_INTEGER			2



// State machine
static enum
{
	STATUS_INIT = 0, 			
	STATUS_START_SESSION,		
	STATUS_START_SESSION_RESP,
	STATUS_SEND_DESCRIPTOR,
	STATUS_WAIT_DESCRIPTOR_RESP,
	STATUS_CONNECTED,
	STATUS_KEEP_ALIVE,
	STATUS_WAIT_RESP,
	STATUS_SEND_RESPONSE,
	STATUS_SEND_EVENT,
	STATUS_WAIT_EVENT_RESPONSE,
	STATUS_CLOSE_SESSION,
	STATUS_CLOSED,
	
} Lhings_status = STATUS_INIT;


typedef const char Event_List;
typedef const char Status_List;

typedef struct action_list{
	const char *name;
	int type;
}Action_List;




class LhingsClass {

private:
	unsigned char 	Lhings_str_UUID[37];
	unsigned char 	Lhings_hex_UUID[16];
	unsigned char 	Lhings_TransID[12];
	char 			Lhings_devName[LHINGS_DEVNAME_LEN];
	char 			Lhings_userName[LHINGS_USERNAME_LEN];
	char 			Lhings_apiKey[36];
	time_t 			Lhings_TimeStamp;
	time_t 			Lhings_TimeRef;
	time_t			Lhings_TimeRef_Keepalive;
	unsigned char 	Lhings_msg_type[2];
	long 			randNumber;
	EthernetUDP 	Udp;
	EthernetClient  TcpClient;
	unsigned int  	Lhings_localPort;
	unsigned char 	Lhings_retry_cont;
	unsigned char 	Lhings_retry_cont_keepalive;
	long			Lhings_retry_multiplier;
	long			Lhings_retry_multiplier_keepalive;
	unsigned char 	Lhings_buffer[LHINGS_BUFFER_MAX_SIZE];
	long 			Lhings_buffer_len;
	long			Lhings_payload_buffer_len;
	unsigned char	Lhings_payload_type;
	boolean			Lhings_action_flag;
	char 			Lhings_status_buffer[LHINGS_STATUS_MAX_VARS][LHINGS_STATUS_MAX_SIZE];	
	int				Lhings_ActionNum;
	int				Lhings_EventNum;
	int				Lhings_StatusNum;
	int 			Lhings_DescriptorSize;
	boolean			Lhings_Logs;
	boolean			Lhings_Registered;
	
	void 			begin(void);
	void 			write(void);
	int				read(void);
	boolean			writeDescriptor(void);
	void			setMessageType(long mMessageType, long mClass);
	long 			getMessageType(void);
	long			getAttributeIndex(long mAtt);
	boolean 		getResponse(void);
	boolean	 		processResponse(void);
	boolean			timeout(void);
	boolean			timeoutKeepalive(void);
	void 			generateTransID(void);
	void			eraseUUID(void);
	void 			saveUUID(void);
	boolean 		readUUID(void);
	void 			getUUIDbin(unsigned char *data);
	void 			getUUIDstr(void);
	void 			printProgMemStr(const prog_char str[]);
	int 			getlenProgMemStr(const prog_char str[]);
	unsigned char 	itoahex(unsigned char input);
	void 			ipAddrToStr(unsigned char *input, char *output); 
	
public:

	unsigned char	Lhings_payload_buffer[LHINGS_PAYLOAD_MAX_SIZE];
	unsigned char	Lhings_name_buffer[LHINGS_NAME_MAX_SIZE];
	
	boolean 		begin(char *devName, char *devUUID, char *userName, char *apiKey);
	boolean			isConnected(void);
	void 			loop(void);
	boolean			actionAvailable(void);
	boolean 		actionAvailable(char *name);
	int 			actionPayloadAvailable(void);
	void 			eventWrite(char *name);
	void 			eventWrite(char *name, char *payload, int len, boolean type);
	boolean			statusWrite(char *status_name, char *status_content);
	void 			close(void); 
	void			reset(void);
	void			enableLogs(void);
	void			disableLogs(void);

};

extern LhingsClass Lhings;

#endif
