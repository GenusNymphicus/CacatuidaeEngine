#include "Input/InputManager.h"
#include "Input/InputKeys.h"

#include "Graphics/Renderer/IWindow.h"

#include <GLFW/glfw3.h>

void cac::InputManager::initialize(cac::IWindow* window)
{
    currentContext = 0;
    keyboard.setWindow(window);
    mouse.setWindow(window);
}



void cac::InputManager::update()
{
    keyboard.update(currentContext);
    mouse.update(currentContext);
}

void cac::InputManager::setInputCallback(std::function<void(std::string)> callback)
{
    keyboard.setInputCallback(callback);
    mouse.setInputCallback(callback);
}
