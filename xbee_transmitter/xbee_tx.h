#ifndef XBEE
#define XBEE

#include <stdint.h>

#define RESET_PIN 39 
#define SLEEP_PIN 16 //Don't know what this should be yet

/*
 *  Class for transmitting and receiving data through XBee.
 *
 *  Variables:
 *      num_sens_bytes              Number of bytes in sensor array.
 *      num_flags                   Number of bytes in flag array.
 *      size_compressed_flags       Number of bytes for storing compressed flags.
 *      package_number              Incremented for every package that is transmitted.
 *      *sensors                    Pointer to array of sensor data. 
 *      *flags                      Pointer to array of flag data.
 *
 *  Important methods:
 *      XBee()                      Constructor
 *      transmit();                 Method for transmitting package number, sensor data and flag data. 
 *                                  Remember to update sensor/flag data before transmitting.
 */
class XBee {
  
    uint8_t num_sens_bytes;
    uint8_t num_flags;
    uint8_t size_compressed_flags;
    
    uint16_t package_number;
    uint8_t *sensors;
    uint8_t *flags;

    /*
     *   Compresses flags and transmits through xbee.
     */   
    void transmit_flags(void);

    
    /*
     *   Compresses array of up to 8 bools to 1 byte.
     *   Input:
     *       bools[]                     Array of bools.
     *       number_of_bools             Size of bools[] array.
     *       *byte_with_bools            Pointer to byte where compressed data is stored.
     */
    void bools_to_byte(const uint8_t bools[], const uint8_t number_of_bools, uint8_t *byte_with_bools);

    
public:
   
    /*
     *   Constructor
     *   Input:
     *       void* sensors               Array of sensor data. Remember to cast to (void*).
     *       bool flags[]                Array of flags.
     *       uint8_t num_sens            Number of Bytes in sensor array.
     *       uint8_t num_flags           Number of Bytes in flag array.
     */
    XBee(void* sensors, bool flags[], const uint8_t num_sens, const uint8_t num_flags);

    /* 
     *  Transmits package number and sensor/flag data.
     *  Compresses flag array before transmitting.
     *  Format                          <[package_number][flags][sensors]> 
     */
    void transmit(void);

    
    /*
     *   Restart XBee module
     */
    void reset(void);


    /*
     * Put module to sleep.
     */
    void sleep(void);

    /*
     * Wake up module
     */
    void wake_up(void); 
};

#endif
