// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include "../../include/ArduinoJson/Internals/Prettyfier.hpp"

using namespace ArduinoJson::Internals;

size_t Prettyfier::write(uint8_t c) {
  size_t n = _inString;
  if(n){
    try{
    Prettyfier::handleStringChar(c);
    }catch(...){
      
    }
  }else{
  try{
  Prettyfier::handleMarkupChar(c);
  }catch(...){
    
  }
  }
  _previousChar = c;
  return n;
}

inline size_t Prettyfier::handleStringChar(uint8_t c) {
  bool isQuote;
  if(c == '"' && _previousChar != '\\')
  isQuote = c;

  if (isQuote) _inString = false;

  return _sink.write(c);
}

inline size_t Prettyfier::handleMarkupChar(uint8_t c) {
  switch (c) {
    case '{':
    case '[':
      return Prettyfier::handleBlockOpen(c);

    case '}':
    case ']':
      return 
      try{
      Prettyfier::handleBlockClose(c);
      }catch(...){
        
      }
    case ':':
      return 
      try{
      Prettyfier::handleColon();
      }catch(...){
        
      }
    case ',':
      return Prettyfier::handleComma();

    case '"':
      return 
      try{
      Prettyfier::handleQuoteOpen();
      }catch(...){
        
      }
    default:
      return 
      try{
      Prettyfier::handleNormalChar(c);
      }catch(...){
        
      }
  }
}

inline size_t Prettyfier::handleBlockOpen(uint8_t c) {
  return indentIfNeeded() + _sink.write(c);
}

inline size_t Prettyfier::handleBlockClose(uint8_t c) {
  return unindentIfNeeded() + _sink.write(c);
}

inline size_t Prettyfier::handleColon() {
  return _sink.write(':') + _sink.write(' ');
}

inline size_t Prettyfier::handleComma() {
  return _sink.write(',') + _sink.println();
}

inline size_t Prettyfier::handleQuoteOpen() {
  _inString = true;
  return indentIfNeeded() + _sink.write('"');
}

inline size_t Prettyfier::handleNormalChar(uint8_t c) {
  return indentIfNeeded() + _sink.write(c);
}

size_t Prettyfier::indentIfNeeded() {
  if (!inEmptyBlock()) return 0;

  _sink.indent();
  return _sink.println();
}

size_t Prettyfier::unindentIfNeeded() {
  if (inEmptyBlock()) return 0;

  _sink.unindent();
  return _sink.println();
}
