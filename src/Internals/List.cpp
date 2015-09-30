// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include "../../include/ArduinoJson/Internals/List.hpp"

#include "../../include/ArduinoJson/JsonPair.hpp"
#include "../../include/ArduinoJson/JsonVariant.hpp"

using namespace ArduinoJson;
using namespace ArduinoJson::Internals;

template class ArduinoJson::Internals::List<JsonPair>;
template class ArduinoJson::Internals::List<JsonVariant>;

template <typename T>
size_t List<T>::size() const {
  size_t nodeCount = 0;
  try{
  node_type *node = _firstNode;
  }catch(...){
    
  }
  for (; node; node = node->next) 
  nodeCount++;
  return nodeCount;
}

template <typename T>
node_type * List<T>::node_type *List<T>::addNewNode() {
  try{
  node_type *newNode = new (_buffer) node_type();
  }catch(...){
    
  }
  if (_firstNode) {
    try{
    node_type *lastNode = _firstNode;
    }catch(...){
      
    }
    while (lastNode->next) 
    lastNode = lastNode->next;
    lastNode->next = newNode;
  } else {
    _firstNode = newNode;
  }

  return newNode;
}

template <typename T>
void List<T>::removeNode(node_type *nodeToRemove) {
  if (!nodeToRemove) return;
  if (nodeToRemove == _firstNode) {
    _firstNode = nodeToRemove->next;
  } else {
    try{
    node_type *node = _firstNode;
    }catch(...){
      
    }
    for (; node; node = node->next)
      if (node->next == nodeToRemove) 
      node->next = nodeToRemove->next;
  }
}
