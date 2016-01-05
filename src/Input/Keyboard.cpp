#include "Input/Keyboard.h"
#include <Input/KeyEventMessage.h>
#include <GLFW/glfw3.h>
#include "Graphics/Renderer/OGLWindow.h"
#include <iostream>

std::map<int, int> keyEvents;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keyEvents[key] = action;
}


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

void cac::Keyboard::setKeyEventCallback(std::function<void(Message*)> keyEventCallback)
{
  glfwSetKeyCallback(window->getContext(), key_callback);
  this->keyEventCallback = keyEventCallback;
  listenToKeyEvents = true;
}

void cac::Keyboard::updateKeyEvents()
{
  for(auto& key : keyEvents)
  {
    KeyState state;
    if(key.second == GLFW_PRESS)
    {
      state = KeyState::PRESSED;
    }
    else if(key.second == GLFW_RELEASE)
    {
      state = KeyState::RELEASED;
    }
    else if(key.second == GLFW_REPEAT)
      state = KeyState::HELD;
    else 
      state = KeyState::NONE;
    
    KeyEventMessage message(key.first, state);
    message.content = "Key event";
    keyEventCallback(&message);
  }
  
  keyEvents.clear();
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
    }
    
    if(listenToKeyEvents)
      updateKeyEvents();
}
