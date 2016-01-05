#ifndef KEY_EVENT_MESSAGE_H
#define KEY_EVENT_MESSAGE_H

#include <Core/Message.h>
#include "KeyState.h"
#include<iostream>
namespace cac 
{
  struct KeyEventMessage : public Message
  {
    KeyEventMessage(int key, KeyState state) : Message(1), key(key), keyState(state) {}
    virtual ~KeyEventMessage() {std::cout<<"Remove keyevent"<<key<<std::endl;}
    
    int key;
    KeyState keyState;
  };
}

#endif