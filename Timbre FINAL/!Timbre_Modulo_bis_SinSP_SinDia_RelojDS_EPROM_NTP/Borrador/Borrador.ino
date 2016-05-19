#include <EEPROM.h>
int i;

void setup() {
  // put your setup code here, to run once:
  EEPROM.begin();
  Serial.begin(9600);
    for (int a = 0;a< 255; a++){
    EEPROM.write(a,255);
    EEPROM.write(254,0);
    
  }
  Serial.println("Termin");

}

void loop() {
  // put your main code here, to run repeatedly:

}
