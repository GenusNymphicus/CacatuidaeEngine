#ifndef CACATUIDAE_INPUT_KEYBOARD_H
#define CACATUIDAE_INPUT_KEYBOARD_H

#include <vector>
#include <map>
#include <string>
#include <functional>
#include "KeyState.h"

namespace cac
{
    class IWindow;
    class OGLWindow;
    
    class Keyboard 
    {
    public:
	void setWindow(IWindow* window);
	void update(unsigned int context);
	//Key Actions
	void bind(int key, KeyState keyState,std::string actionString, unsigned int context = 0);

	void setInputCallback(std::function<void(std::string)> callback) { this->callback = callback; }
	
    private:
	struct KeyAction
	{
	    KeyState state;
	    std::string actionString;
	    unsigned int context;
	    
	    KeyAction() {}
	    KeyAction(std::string actionString, KeyState state,unsigned int context) 
	    : actionString(actionString),
	      context(context),
	      state(state)
	    {
	    } 
	};
	
	std::function<void(std::string)> callback;
	cac::OGLWindow* window;
	std::map<int, KeyState> lastKeyStates;
	std::map<int, std::vector<KeyAction>> mappedKeys;
	
    };
}


#endif