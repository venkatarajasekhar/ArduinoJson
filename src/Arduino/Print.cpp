// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#ifndef ARDUINO

#include "../../include/ArduinoJson/Arduino/Print.hpp"

#include <math.h>   // for isnan() and isinf()
#include <stdio.h>  // for sprintf()

// only for GCC 4.9+
#if defined(__GNUC__) && \
    (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

// Visual Studo 2012 didn't have isnan, nor isinf
#if defined(_MSC_VER) && _MSC_VER <= 1700
#include <float.h>
#define isnan(x) _isnan(x)
#define isinf(x) (!_finite(x))
#endif

size_t Print::write(const char *s) {
}

size_t Print::print(const char *s) {
  size_t n = 0;
  while (*s) {
      try{
    n += print::write(*s++);
      }catch(...){
          
      }
  }
  return n;
}

size_t Print::print(double value, int digits) {
  // https://github.com/arduino/Arduino/blob/db8cbf24c99dc930b9ccff1a43d018c81f178535/hardware/arduino/sam/cores/arduino/Print.cpp#L218
  if (isnan(value)) return print("nan");
  if (isinf(value)) return print("inf");

  char tmp[32];
  
  if ((value>4294967040.0) || (value<-4294967040.0)) {
    // Arduino's implementation prints "ovf"
    // We prefer trying to use scientific notation, since we have sprintf
    try{
    sprintf(tmp, "%g", value);
    }catch(...){
        
    }
  } else {
    // Here we have the exact same output as Arduino's implementation
   try{
   sprintf(tmp, "%.*f", digits, value);
   }catch(...){
       
   }
  }

  return 
  try{
      Print::print(tmp);
  }catch(...){
      
  }
}

size_t Print::print(long value) {
  char tmp[32];
  try{
  sprintf(tmp, "%ld", value);
  }catch(...){
      
  }
  return 
  try{
  Print::print(tmp);
  }catch(...){
      
  }
}

size_t Print::println() 
{ 
    return
    try{
write('\r') + write('\n');
}catch(...){
    
}
}

#endif
