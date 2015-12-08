#include "Input/Keyboard.h"
#include <GLFW/glfw3.h>
#include "Graphics/Renderer/OGLWindow.h"
#include <iostream>

void cac::Keyboard::setWindow(cac::IWindow* window)
{
    cac::OGLWindow* oglWindow = dynamic_cast<OGLWindow*>(window);
    this->window = oglWindow;
}


void cac::Keyboard::bind(int key, cac::KeyState state, std::string actionString, unsigned int context)
{
    if(!mappedKeys.count(key))
    {
	mappedKeys[key] = std::vector<KeyAction>();
	lastKeyStates[key] = cac::KeyState::RELEASED;
    }
    mappedKeys[key].push_back(KeyAction(actionString, state, context));
}


void cac::Keyboard::update(unsigned int context)
{
    for(auto keyActions : mappedKeys)
    {
	cac::KeyState keyState  = cac::KeyState::NONE;;
	cac::KeyState lastKeyState = lastKeyStates[keyActions.first];

	int state = glfwGetKey(window->getContext(), keyActions.first);
	if(state == GLFW_PRESS && lastKeyState == cac::KeyState::RELEASED)
	    keyState = cac::KeyState::PRESSED;
	else if((lastKeyState == cac::KeyState::PRESSED || lastKeyState == cac::KeyState::HELD ))
	{
	    if(state == GLFW_RELEASE)
		keyState = cac::KeyState::RELEASED;
	    else if(state == GLFW_PRESS)
		keyState = cac::KeyState::HELD;
	}
	
	if(keyState != cac::KeyState::NONE)
	    lastKeyStates[keyActions.first] = keyState;
	
	for(auto& action : keyActions.second)
	{ 
	    if(action.state == keyState)
		callback(action.actionString);
	}
    };
}
