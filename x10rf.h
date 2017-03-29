/*
  x10rf.h
  Library for sending x10 messages by RF.
  Created by Pieter Paul Baron (embedded [at] ppbaron.nl), November 2013.
  Released into the public domain.

  Updated in rletendu, March 2017 : encapsulate in class, added debug option
  Library to send x10 messages via a cheap 433Mhz OOK device. No X10 Firecracker (CMA17A) necessary.
  Decoding messages is not implemented.
  This library can emulate x10 switches and security devices and also RFXMeter and RFXSensor devices manufactured by RFXCom. (www.rfxcom.com)
*/

// ensure this library description is only included once
#ifndef x10rf_h
#define x10rf_h

//#define X10RF_DEBUG

// Setup debug printing macros.
#ifdef X10RF_DEBUG
// Define where debug output will be printed.
#ifndef DEBUG_X10RF_PRINTER
#define DEBUG_X10RF_PRINTER Serial
#endif
#define DEBUG_X10RF_PRINT(...) { DEBUG_X10RF_PRINTER.print(__VA_ARGS__); }
#define DEBUG_X10RF_PRINTLN(...) { DEBUG_X10RF_PRINTER.println(__VA_ARGS__); }
#else
#define DEBUG_X10RF_PRINT(...) {}
#define DEBUG_X10RF_PRINTLN(...) {}
#endif

enum x10_switch_cmd {
  ON = 0x00,
  OFF = 0x20,
  BRIGHT = 0x88,
  DIM = 0x98,
  ALL_ON = 0x90,
  ALL_OFF = 0x80,
};

#include <stdlib.h>
#include "Arduino.h"

class x10rf
{
  public:
    x10rf(uint8_t tx_pin, uint8_t led_pin, uint8_t rf_repeats);
    void begin();
    void x10Security(uint8_t address, uint8_t command);
    void send_temperature(uint8_t rfxm_address, float temperature);
    void send_meter(uint8_t rfxm_address, long value);
    void send_switch(char house_code, uint8_t unit_code, enum x10_switch_cmd command);
  private:
    void RFXmeter(uint8_t rfxm_address, uint8_t rfxm_packet_type, long rfxm_value);
    void RFXsensor(uint8_t rfxs_address, uint8_t rfxs_type, char rfxs_packet_type, uint8_t rfxs_value);
    void x10Switch(char house_code, uint8_t unit_code, enum x10_switch_cmd command);
    void SendX10RfByte(uint8_t data);
    void SendX10RfBit(unsigned int databit);
    void SendCommand(uint8_t *date, uint8_t size);
    void Send_high();
    void Send_low();
    uint8_t _tx_pin;
    uint8_t _led_pin;
    uint8_t _rf_repeats;
};


// Very Scrappy way to add modules in arduino subfolder ...
// But the only one found using ARDUINO IDE
#if defined(ARDUINO) && defined (X10_SRC_INCLUDE)
#include "x10rf.cpp"
#endif


#endif
