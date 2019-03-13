#include "xbee_programmer.h"
#include <cstring>
void setup() {
  while(init()) {
    Serial.println("Trying again");
  }
  send_command("AF");
  
  while(!Serial5.available());
  while(Serial5.available()) {
    Serial.println((char)46);
    delay(10);
  }
 
}



void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("...");
  delay(300);
}
