#ifndef CACATUIDAE_CORE_MESSAGE_H
#define CACATUIDAE_CORE_MESSAGE_H

#include <string>
namespace cac 
{
  struct Message 
  {
    Message(int type = 0) : type(type) {}
    virtual ~Message() {}
    
    const int type;
    std::string content = "";
  };
}

#endif