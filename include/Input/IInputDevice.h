#ifndef CACATUIDAE_INPUT_DEVICE_H
#define CACATUIDAE_INPUT_DEVICE_H

#include <functional>
#include <string>

namespace cac
{
    class IWindow;
    class IInputDevice 
    {
    public:
	virtual void setWindow(IWindow* window) = 0;
	virtual void update(unsigned int context) = 0;
	virtual void setInputCallback(std::function<void(std::string)> callback) { this->callback = callback; }
	
	
    protected:
	std::function<void(std::string)> callback;
    };
}

#endif