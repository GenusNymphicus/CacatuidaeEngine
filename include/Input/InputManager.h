#ifndef CACATUIDAE_INPUT_INPUTMANAGER_H
#define CACATUIDAE_INPUT_INPUTMANAGER_H


#include <vector>
#include <map>
#include <string>
#include <functional>
#include "Keyboard.h"

namespace cac
{
    class IWindow;
    class InputManager
    {
    public:
	void initialize(IWindow* window);
	void setInputCallback(std::function<void(std::string)> callback);
	void update();
	
	Keyboard* getKeyboard() { return &keyboard; }
    private:

	 unsigned int currentContext;
	 
	 Keyboard keyboard;
    };
}

#endif