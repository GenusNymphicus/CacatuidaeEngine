#ifndef CACATUIDAE_INPUT_INPUTMANAGER_H
#define CACATUIDAE_INPUT_INPUTMANAGER_H


#include <vector>
#include <map>
#include <string>
#include <functional>
#include "Keyboard.h"
#include "Mouse.h"

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
	Mouse* getMouse() { return &mouse; }
    private:

	 unsigned int currentContext;
	 
	 Keyboard keyboard;
	 Mouse mouse;
    };
}

#endif