#ifndef XBEE_PROGRAMMER
#define XBEE_PROGRAMMER

#include <stdint.h>

uint8_t init();
uint8_t check_response(const char c1[], const char c2[]);
uint8_t ok();
uint8_t send_command(const char command[]);


#endif