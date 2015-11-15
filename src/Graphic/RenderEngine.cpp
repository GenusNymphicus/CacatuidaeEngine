#include "Graphic/RenderEngine.h"



template<class Renderer> bool cac::RenderEngine<Renderer>::initialize(cac::WindowDesc windowDescription)
{
    return renderer.initialize(windowDescription) == 0;
}

template<class Renderer> void cac::RenderEngine<Renderer>::clearScreen()
{
    renderer.clearScreen();
}

template<class Renderer> void cac::RenderEngine<Renderer>::render()
{

}

template<class Renderer> void cac::RenderEngine<Renderer>::updateScreen()
{
    renderer.swapBuffers();
}
