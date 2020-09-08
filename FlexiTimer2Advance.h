#ifndef FlexiTimer2Advance_h
#define FlexiTimer2Advance_h

#ifdef __AVR__
#include <avr/interrupt.h>
#elif defined(__arm__) && defined(TEENSYDUINO)
#include <Arduino.h>
#else
#error FlexiTimer2Advance library only works on AVR architecture
#endif


namespace FlexiTimer2Advance {
  extern unsigned long time_units;
  extern void (*func)();
  extern volatile unsigned long count;
  extern volatile char overflowing;
  extern volatile unsigned int tcnt2;
  
  void set(unsigned long ms, void (*f)());
  void set(unsigned long units, int resolution, void (*f)());
  void start();
  void stop();
  void _overflow();
}

#endif

