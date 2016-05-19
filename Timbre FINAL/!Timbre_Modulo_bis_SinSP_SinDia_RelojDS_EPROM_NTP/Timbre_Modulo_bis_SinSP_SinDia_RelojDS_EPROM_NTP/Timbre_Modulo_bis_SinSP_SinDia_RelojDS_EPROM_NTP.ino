#include <EEPROM.h>
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <UIPEthernet.h>

byte Ayuda=1;
byte Ta;
byte ActuB;
int THS;
char NumeroC[3];
byte DiaB = 0;
byte Tmin;
byte Seg = 0;
byte Min = 00;
byte Hs = 00;
bool LIBRE[8];
int TL = 8000;
int TC = 4000;
boolean Th = false;
boolean Vaca = false ;
char Datos[40];
char Acc[10];
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFF};
IPAddress ip(192, 168, 2, 78);
//IPAddress gateway(192, 168, 1, 1);
//IPAddress subnet(255, 255, 255, 0);
boolean lastConnected = false;
EthernetServer server(35);
boolean alreadyConnected = false;
tmElements_t tm;
// NTP Servers:
IPAddress timeServer(193,92,150,3); // time-a.timefreq.bldrdoc.gov
// IPAddress timeServer(132, 163, 4, 102); // time-b.timefreq.bldrdoc.gov
// IPAddress timeServer(132, 163, 4, 103); // time-c.timefreq.bldrdoc.gov 
const int timeZone = -3;     // Central European Time
//const int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)
EthernetUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets
const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

void setup() {
  pinMode(2, OUTPUT);
  pinMode(8, INPUT);
  Ethernet.begin(mac, ip);
  server.begin();
  Wire.begin();
  Serial.begin(9600);
 //EEPROM.write(254, 0);
  Ta = EEPROM.read(254);
  ntpSyncDS1307();
}

void loop() {
  
  byte Silencios;
  EthernetClient client = server.available();

  if (digitalRead(8) == 1 && Th == true) {
    Ethernet.begin(mac, ip);
    server.begin();
    Th = false;
  }

  if (digitalRead(8) == 0 && Th != true) {
    Th = true;
  }
  
  RTC.read(tm);
  if (tm.Wday != EEPROM.read(255)){
    ntpSyncDS1307();
  }

  if(tm.Minute!=Tmin){
    Tmin=255;
  }

  if (!LIBRE[tm.Wday]) {
    byte THN;
    THS=0;
    for ( THN = 0; THS < Ta - 4; THN++) {
      THS=THN*4;
      byte TMIN = THS+1;
      byte TSIL = TMIN+1;
      if (EEPROM.read(THS) == tm.Hour && EEPROM.read(TMIN) == tm.Minute && EEPROM.read(THS) != 0 && EEPROM.read(TMIN) != Tmin) {
        Tmin = EEPROM.read(TMIN);
        if (EEPROM.read(TSIL) == 0) {
          Alarma();
          //server.println("Sone");
        }
        else {
          Silencios = EEPROM.read(TSIL);
          Silencios--;
          EEPROM.write(TSIL, Silencios);
        }
      }
    }
  }

  if (client) {
    LeerDatos();
    client.flush();
  }
}

void LeerDatos() {
  byte Com;
  byte Tb;
  EthernetClient client = server.available();
  if (client.available() > 0) {
    // read the bytes incoming from the client:
    Tb = 0;
    for (Com = 0; Com < 40; Com++) {
      if (Tb == 0) {
        Datos[Com] = client.read();
      }
      else {
        Datos[Com] = '\0';
      }
      if (Datos[Com] == ';') {
        Datos[Com] = ' ';
        Tb = 1;
      }
    }        
    Serial.println(Datos);
    Acc[0] = Datos[0];
    Acc[1] = Datos[1];
    Acc[2] = Datos[2];
    Acc[3] = Datos[3];
    Acc[4] = Datos[4];
    Acc[5] = Datos[5];
    Acc[6] = '\0';
    if (strcmp(Acc, "Set   ") == 0) {
      Set();
    }
    if (strcmp(Acc, "Hora  ") == 0) {
      Hora();
    }
    if (strcmp(Acc, "Act   ") == 0) {
      ActuB=0;
      if (Ta!=0){
            Act(); 
      }
    }
    if (strcmp(Acc, "Borrar") == 0) {
      Borrar();

    }
    if (strcmp(Acc, "Sil   ") == 0) {
      Silencio();
    }
    if (strcmp(Acc, "Vac   ") == 0) {
      Vaca = !Vaca;
    }
    if (strcmp(Acc, "State ") == 0) {
      State();
    }
    if (strcmp(Acc, "Dura  ") == 0){
      Dura();
    }
    if (strcmp(Acc, "Libre ") == 0){
      Libre();
  }
    if (strcmp(Acc, "Libres") == 0){
      Libres();
  }
    if (strcmp(Acc, "Durar ") == 0){
      Durar();
  }
      if (strcmp(Acc, "OK ") == 0){
      Serial.println("Entro");
      int TA;
      TA=Ta/4;
      TA--;
      if (ActuB<TA){
      ActuB++;
      Act();
      }
  }
}
}

void Set() {
  byte TMIN, TTIPO, TSIL;
  if (Ta < 240) {
    EEPROM.write(Ta, Convercion(Datos[10], Datos[11]));
    TMIN = Ta + 1;
    EEPROM.write(TMIN, Convercion(Datos[15], Datos[16]));
    TSIL = Ta + 2;
    EEPROM.write(TSIL, 0);
    TTIPO = TMIN+2;
    if (Datos[28]=='L'){
      EEPROM.write(TTIPO, 1);
    }
    if (Datos[28]=='C'){
      EEPROM.write(TTIPO, 2);
    }
    Ta = Ta+4;
    EEPROM.write(254,Ta);
  }
}

void Hora() {
  tmElements_t tm;
  char Dia[4];
  Dia[0] = Datos[6];
  Dia[1] = Datos[7];
  Dia[2] = Datos[8];
  Dia[3] = '\0';

  Hs = Convercion(Datos[9], Datos[10]);
  Min = Convercion(Datos[11], Datos[12]);
  Seg = 0;

  if (strcmp(Dia, "Lun") == 0) {
    DiaB =  7 ;
  }
  if (strcmp(Dia, "Mar") == 0) {
    DiaB = 1;
  }
  if (strcmp(Dia, "Mie") == 0) {
    DiaB = 2;
  }
  if (strcmp(Dia, "Jue") == 0) {
    DiaB = 3;
  }
  if (strcmp(Dia, "Vie") == 0) {
    DiaB = 4;
  }
  if (strcmp(Dia, "Sab") == 0) {
    DiaB = 5;
  }
  if (strcmp(Dia, "Dom") == 0) {
    DiaB = 6;
  }
  tm.Wday = DiaB;
  EEPROM.write(255,DiaB);
  tm.Hour = Hs;
  tm.Minute = Min;
  tm.Second = 0;
  RTC.write(tm);
  Ayuda=1;
  }

void Alarma() {
  byte TTIPO = THS+3;
  if (Vaca == false) {
    if (EEPROM.read(TTIPO)==1) {
      digitalWrite(2, HIGH);
      delay(TL);
      digitalWrite(2, LOW);
    }
    if (EEPROM.read(TTIPO)==2) {
      digitalWrite(2, HIGH);
      delay(TC);
      digitalWrite(2, LOW);
    }
  }
}

void Act() {

  String str;
  char HSAct[30];
  char MINAct[5];
  int Actu=-1;
  byte ActuM;
    Actu =  ActuB * 4;
    ActuM = Actu + 1;
    Separar(EEPROM.read(Actu));
    HSAct[0] = NumeroC[0];
    HSAct[1] = NumeroC[1];
    HSAct[2] = '\0';
    strcat(HSAct, " : ");
    Separar(EEPROM.read(ActuM));
    HSAct[5] = NumeroC[0];
    HSAct[6] = NumeroC[1];
    HSAct[7] = '\0';
    ActuM = ActuM+2;
    if (EEPROM.read(ActuM) == 2) {
      strcat(HSAct, " Timbre Corto \0");
    }
    if (EEPROM.read(ActuM) == 1) {
      strcat(HSAct, " Timbre Largo \0");
    }
    ActuM--;
    if (EEPROM.read(ActuM) != 0) {
      strcat(HSAct, "  Sil \0");
      Separar(EEPROM.read(ActuM));
      strcat(HSAct, NumeroC);
    }
    else strcat(HSAct, " \n");
    server.println(HSAct);
}

void Borrar() {

  char Indice[4];
  byte Borrar1 = 0;
  byte IndiceB = 0;

  Indice[0] = Datos[10];
  Indice[1] = Datos[11];
  Indice[2] = '\0';

  IndiceB = atoi(Indice);
  IndiceB = IndiceB*4;
  for (IndiceB = IndiceB; IndiceB <= Ta; IndiceB++) {
    Borrar1 = IndiceB + 4;
    EEPROM.write(IndiceB,EEPROM.read(Borrar1));
    Borrar1++;
    IndiceB++;
    EEPROM.write(IndiceB,EEPROM.read(Borrar1));
    Borrar1++;
    IndiceB++;
    EEPROM.write(IndiceB,EEPROM.read(Borrar1));
    Borrar1++;
    IndiceB++;
    EEPROM.write(IndiceB,EEPROM.read(Borrar1));
  }
  Ta = Ta-4;
  EEPROM.write(254,Ta);
}

void Silencio() {

  char Indice[4];
  char Dias[4];
  byte IndiceS;

  Indice[0] = Datos[10];
  Indice[1] = Datos[11];
  IndiceS = atoi(Indice);
  if (IndiceS<10){
      Dias[0] = Datos[12];
      Dias[1] = Datos[13];
  }
  else {  
    Dias[0] = Datos[13];
    Dias[1] = Datos[14];
  }
  IndiceS = IndiceS * 4;
  IndiceS = IndiceS + 2;
  EEPROM.write(IndiceS, Convercion(Dias[0], Dias[1]));
}

void State() {
  tmElements_t tm;
  char  HSAct[30];
  RTC.read(tm);  
  Separar(tm.Hour);
  HSAct[0] = NumeroC[0];
  HSAct[1] = NumeroC[1];
  HSAct[2] = ':';
  Separar(tm.Minute);
  HSAct[3] = NumeroC[0];
  HSAct[4] = NumeroC[1];
  HSAct[5] = '\0';

  if (tm.Wday == 7) {

    strcat(HSAct, " Lunes \0");

  }
  if (tm.Wday == 1) {

    strcat(HSAct, " Martes \0");

  }
  if (tm.Wday == 2) {

    strcat(HSAct, " Miercoles \0");

  }
  if (tm.Wday == 3) {

    strcat(HSAct, " Jueves \0");

  }
  if (tm.Wday == 4) {

    strcat(HSAct, " Vierners \0");

  }
  if (tm.Wday == 5) {

    strcat(HSAct, " Sabado \0");

  }
  if (tm.Wday == 6) {

    strcat(HSAct, " Domingo \0");

  }
  if (Vaca == true) {
    strcat(HSAct, " On \0");
  }
  if (Vaca == false) {
    strcat(HSAct, " Off \0");
  }

  strcat(HSAct, " 5 \0");

  Serial.println(HSAct);
  server.print(HSAct);
}

void Dura(){
  char Tl[3];
  char Tc[3];

  Tl[0] = Datos[7];
  Tl[1] = Datos[8];

  Tc[0] = Datos[10];
  Tc[1] = Datos[11];

  TL = Convercion(Tl[0], Tl[1]);
  TC = Convercion(Tc[0], Tc[1]);

  TL=TL*1000;
  TC=TC*1000;
}

void Libre(){
  char HSAct[30];
    if(LIBRE[7]== 1){
      strcat(HSAct, "Lu\0");
    }
    if(LIBRE[1]== 1){
      strcat(HSAct, " Ma\0");
    }
    if(LIBRE[2]== 1){
      strcat(HSAct, " Mi\0");
    }
    if(LIBRE[3]== 1){
      strcat(HSAct, " Ju\0");
    }
    if(LIBRE[4]== 1){
      strcat(HSAct, " Vi\0");
    }
    if(LIBRE[5]== 1){
      strcat(HSAct, " Sa\0");
    }
    if(LIBRE[6]== 1){
      strcat(HSAct, " Do\0");
    }
      strcat(HSAct, "\n");
      server.print(HSAct);
}

void Durar(){
    char  HSAct[30];
    int Seg;
  Seg=TC/1000;
  Separar(Seg);
    HSAct[0] = 'C';
  HSAct[1] = NumeroC[0];
  HSAct[2] = NumeroC[1];
    Seg=TL/1000;
  Separar(Seg);
    HSAct[3] = 'L';
  HSAct[4] = NumeroC[0];
  HSAct[5] = NumeroC[1];
  HSAct[6] = '\0';
        server.print(HSAct);
        Serial.println(HSAct);
}

void Libres(){
  LIBRE[7]=strstr(Datos,"Lun");
  LIBRE[1]=strstr(Datos,"Mar");
  LIBRE[2]=strstr(Datos,"Mie");
  LIBRE[3]=strstr(Datos,"Jue");
  LIBRE[4]=strstr(Datos,"Vie");
  LIBRE[5]=strstr(Datos,"Sab");
  LIBRE[6]=strstr(Datos,"Dom");
  
}

void AYUDA(){
  RTC.read(tm);
  while(tm.Second<30) RTC.read(tm);
  tm.Second=tm.Second-30;
  RTC.write(tm);
}

void ntpSyncDS1307() {
  RTC.read(tm);
  EEPROM.write(255,tm.Wday);
  bool Sync=0;
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      unsigned long epoch = secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
      RTC.set(epoch);
      DIA();
      Sync = 1;      
    }
  }
  if (Sync==0){
  AYUDA();
  }
}

void DIA(){
  RTC.read(tm);
  if(tm.Wday==0){
    tm.Wday=5;
  }
  else if(tm.Wday==1){
    tm.Wday=6;
  }
  else if(tm.Wday==2){
    tm.Wday=7;
  }
  else{
    tm.Wday--;
    tm.Wday--;
  }

  RTC.write(tm);
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address) {
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011; // LI, Version, Mode
  packetBuffer[1] = 0; // Stratum, or type of clodk
  packetBuffer[2] = 6; // Polling Interval
  packetBuffer[3] = 0xEC; // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123);
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

void serialEvent() {
  tmElements_t tm;
  int h=-1;
  byte a;
  if (Serial.read() == 'T') {
    RTC.read(tm);
    Serial.print(tm.Hour);
    Serial.print(F(":"));
    Serial.print(tm.Minute);
    Serial.print(F(":"));
    Serial.println(tm.Second);
    Serial.println(tm.Wday);
    Serial.println(Datos);
    Serial.println(EEPROM.read(0));
    for( a=0 ; h<Ta-4 ; a++){
      byte b,c,d;
      h=a*4;
      Serial.print(EEPROM.read(h));
      Serial.print(":");
      b=h+1;
      Serial.print(EEPROM.read(b));
      Serial.print("/");
      c=h+2;
      Serial.print(EEPROM.read(c));
      Serial.print("/");
      d=h+3;
      Serial.println(EEPROM.read(d));
    }
  }}

  byte Convercion(char Dec, char Uni) {
  byte Numero;

  if (Uni == '0') {
    Numero = 0;
  }
  if (Uni == '1') {
    Numero = 1;
  }
  if (Uni == '2') {
    Numero = 2;
  }
  if (Uni == '3') {
    Numero = 3;
  }
  if (Uni == '4') {
    Numero = 4;
  }
  if (Uni == '5') {
    Numero = 5;
  }
  if (Uni == '6') {
    Numero = 6;
  }
  if (Uni == '7') {
    Numero = 7;
  }
  if (Uni == '8') {
    Numero = 8;
  }
  if (Uni == '9') {
    Numero = 9;
  }

  if (Dec == '0') {
    Numero = Numero + 0;
  }
  if (Dec == '1') {
    Numero = Numero + 10;
  }
  if (Dec == '2') {
    Numero = Numero + 20;
  }
  if (Dec == '3') {
    Numero = Numero + 30;
  }
  if (Dec == '4') {
    Numero = Numero + 40;
  }
  if (Dec == '5') {
    Numero = Numero + 50;
  }
  if (Dec == '6') {
    Numero = Numero + 60;
  }
  if (Dec == '7') {
    Numero = Numero + 70;
  }
  if (Dec == '8') {
    Numero = Numero + 80;
  }
  if (Dec == '9') {
    Numero = Numero + 90;
  }
  return Numero;

}

void Separar(byte Numero) {
  byte U, D;
  U = 0;
  D = 0;
  if (Numero < 10) {
    NumeroC[0] = '0';
    U = Numero;
    if (U == 0) {
      NumeroC[1] = '0';
    }
    if (U == 1) {
      NumeroC[1] = '1';
    }
    if (U == 2) {
      NumeroC[1] = '2';
    }
    if (U == 3) {
      NumeroC[1] = '3';
    }
    if (U == 4) {
      NumeroC[1] = '4';
    }
    if (U == 5) {
      NumeroC[1] = '5';
    }
    if (U == 6) {
      NumeroC[1] = '6';
    }
    if (U == 7) {
      NumeroC[1] = '7';
    }
    if (U == 8) {
      NumeroC[1] = '8';
    }
    if (U == 9) {
      NumeroC[1] = '9';
    }
  }
  if (Numero > 9) {
    do {
      Numero = Numero - 10;
      D++;
    } while (Numero >= 10);
    U = Numero;
    if (U == 0) {
      NumeroC[1] = '0';
    }
    if (U == 1) {
      NumeroC[1] = '1';
    }
    if (U == 2) {
      NumeroC[1] = '2';
    }
    if (U == 3) {
      NumeroC[1] = '3';
    }
    if (U == 4) {
      NumeroC[1] = '4';
    }
    if (U == 5) {
      NumeroC[1] = '5';
    }
    if (U == 6) {
      NumeroC[1] = '6';
    }
    if (U == 7) {
      NumeroC[1] = '7';
    }
    if (U == 8) {
      NumeroC[1] = '8';
    }
    if (U == 9) {
      NumeroC[1] = '9';
    }
    if (D == 0) {
      NumeroC[0] = '0';
    }
    if (D == 1) {
      NumeroC[0] = '1';
    }
    if (D == 2) {
      NumeroC[0] = '2';
    }
    if (D == 3) {
      NumeroC[0] = '3';
    }
    if (D == 4) {
      NumeroC[0] = '4';
    }
    if (D == 5) {
      NumeroC[0] = '5';
    }
    if (D == 6) {
      NumeroC[0] = '6';
    }
    if (D == 7) {
      NumeroC[0] = '7';
    }
    if (D == 8) {
      NumeroC[0] = '8';
    }
    if (D == 9) {
      NumeroC[0] = '9';
    }
  }
}


