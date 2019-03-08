#include "xbee_tx.h"
#include <arduino.h>


XBee::XBee(void* sensors, bool flags[], const uint8_t num_sens_bytes, const uint8_t num_flags) 
        : num_sens_bytes(num_sens_bytes), num_flags(num_flags), package_number(0), sensors((uint8_t*)sensors), flags((uint8_t*) flags) {
         
          //Activating serial communication
          Serial5.begin(9600);
          Serial5.setTimeout(25);

          //Resetting module
          reset();

          //Setting up sleep pin
          //pinMode(SLEEP_PIN, OUTPUT);
          //digitalWrite(SLEEP_PIN, LOW);       
          
          //Calculating size of compressed flags
          if (num_flags == 0) {
              size_compressed_flags = 0;
          }
          else {
              size_compressed_flags = (num_flags-1)/8 + 1;
          }
    }


void XBee::reset(void) {
    pinMode(RESET_PIN, OUTPUT);
    digitalWrite(RESET_PIN, LOW);
    delay(1);
    pinMode(RESET_PIN, INPUT);
}

void XBee::transmit(void) {
    Serial5.write('<');
    Serial5.write((uint8_t*)&(++package_number), sizeof(package_number));
    transmit_flags();
    Serial5.write(sensors, num_sens_bytes);
    Serial5.write('>');
}


void XBee::sleep(void) {
    digitalWrite(SLEEP_PIN, HIGH);
}

void XBee::wake_up(void) {
    digitalWrite(SLEEP_PIN, LOW);
}


void XBee::bools_to_byte(const uint8_t bools[], const uint8_t number_of_bools, uint8_t *byte_with_bools) {
    *byte_with_bools = 0;
    for (int i = 0; i < number_of_bools; ++i) {
        *byte_with_bools |= bools[i] << i;
    }
}



void XBee::transmit_flags(void) {
    uint8_t flag_byte;
    uint8_t bools_left = 8;
    for (int i=0; i < num_flags; i += 8) {
        //Calculate how many flags in the next compressed byte
        if (num_flags - i < 8) {
            bools_left = num_flags - i;
        }       
        bools_to_byte(&flags[i], bools_left, &flag_byte); 
        Serial5.write(flag_byte);
    }
    
}
