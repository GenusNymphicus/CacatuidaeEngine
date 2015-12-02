#ifndef CACATUIDAE_INPUT_KEYBOARD_H
#define CACATUIDAE_INPUT_KEYBOARD_H

#include <vector>
#include <map>
#include "KeyState.h"
#include "IInputDevice.h"

namespace cac
{
    class IWindow;
    class OGLWindow;
    
    class Keyboard : public IInputDevice
    {
    public:
	virtual void setWindow(IWindow* window) override;
	virtual void update(unsigned int context) override;
	
	//Key Actions
	void bind(int key, KeyState keyState,std::string actionString, unsigned int context = 0);


    private:
	struct KeyAction
	{
	    std::string actionString;
	    unsigned int context;
	    KeyState state;
	    
	    KeyAction() {}
	    KeyAction(std::string actionString, KeyState state,unsigned int context) 
	    : actionString(actionString),
	      context(context),
	      state(state)
	    {
	    } 
	};
	

	cac::OGLWindow* window;
	std::map<int, KeyState> lastKeyStates;
	std::map<int, std::vector<KeyAction>> mappedKeys;
    };
}


#endif