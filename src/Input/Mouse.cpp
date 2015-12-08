#include "Input/Mouse.h"
#include <GLFW/glfw3.h>
#include "Graphics/Renderer/OGLWindow.h"

void cac::Mouse::setWindow(IWindow* window)
{
    cac::OGLWindow* oglWindow = dynamic_cast<OGLWindow*>(window);
    this->window = oglWindow;
    
    previousStates[EMouseButtons::LEFT_BUTTON] = EMouseInput::NONE;;
    previousStates[EMouseButtons::RIGHT_BUTTON] = EMouseInput::NONE;;
}

void cac::Mouse::getCursorPosition(int& xPos, int& yPos)
{
    xPos = this->xPos;
    yPos = this->yPos;
}

void cac::Mouse::bind(cac::EMouseInput inputMethod, std::string actionString, unsigned int context)
{
    if(!mappedActions.count(inputMethod))
    {
	mappedActions[inputMethod] = std::vector<MouseAction>();
    }
    
    mappedActions[inputMethod].push_back(MouseAction(actionString, context));
}


void cac::Mouse::update(unsigned int context)
{
    int leftButtonState = glfwGetMouseButton(window->getContext(), GLFW_MOUSE_BUTTON_LEFT);
    int rightButtonState = glfwGetMouseButton(window->getContext(), GLFW_MOUSE_BUTTON_RIGHT);
    
    EMouseInput leftMouseInputState = EMouseInput::NONE;
    EMouseInput rightMouseInputState = EMouseInput::NONE;
    
    if(leftButtonState == GLFW_PRESS && (previousStates[EMouseButtons::LEFT_BUTTON] == EMouseInput::NONE || previousStates[EMouseButtons::LEFT_BUTTON] == EMouseInput::LEFT_BUTTON_RELEASE))
	leftMouseInputState = EMouseInput::LEFT_BUTTON_PRESS;
    else if(previousStates[EMouseButtons::LEFT_BUTTON] == EMouseInput::LEFT_BUTTON_HOLD || previousStates[EMouseButtons::LEFT_BUTTON] == EMouseInput::LEFT_BUTTON_PRESS)
    {
	if(leftButtonState == GLFW_RELEASE)
	    leftMouseInputState = EMouseInput::LEFT_BUTTON_RELEASE;
	else if(leftButtonState == GLFW_PRESS)
	    leftMouseInputState = EMouseInput::LEFT_BUTTON_HOLD;
    }
    
    if(rightButtonState == GLFW_PRESS && (previousStates[EMouseButtons::RIGHT_BUTTON] == EMouseInput::NONE || previousStates[EMouseButtons::RIGHT_BUTTON] == EMouseInput::RIGHT_BUTTON_RELEASE))
	rightMouseInputState = EMouseInput::RIGHT_BUTTON_PRESS;
    else if(previousStates[EMouseButtons::RIGHT_BUTTON] == EMouseInput::RIGHT_BUTTON_HOLD || previousStates[EMouseButtons::RIGHT_BUTTON] == EMouseInput::RIGHT_BUTTON_PRESS)
    {
	if(rightButtonState == GLFW_RELEASE)
	    rightMouseInputState = EMouseInput::RIGHT_BUTTON_RELEASE;
	else if(rightButtonState == GLFW_PRESS)
	    rightMouseInputState = EMouseInput::RIGHT_BUTTON_HOLD;
    }
    
    previousStates[EMouseButtons::LEFT_BUTTON] = leftMouseInputState;
    previousStates[EMouseButtons::RIGHT_BUTTON] = rightMouseInputState;
    
    
    double xPos, yPos;
    glfwGetCursorPos(window->getContext(), &xPos, &yPos);
    this->xPos = (int) xPos;
    this->yPos = (int) yPos;
    
    for (auto& mouseAction : mappedActions)
    {	
	if(mouseAction.first == leftMouseInputState || mouseAction.first == rightMouseInputState)
	{
	    for(auto& action : mouseAction.second)
	    {
		if(action.context == context)
		    callback(action.actionString);
	    }
	}
    }
}

