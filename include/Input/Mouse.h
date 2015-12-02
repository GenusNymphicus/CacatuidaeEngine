#ifndef CACATUIDAE_INPUT_MOUSE_H
#define CACATUIDAE_INPUT_MOUSE_H

#include "Input/IInputDevice.h"
#include "EMouseInput.h"
#include <map>
#include <vector>
#include <string>

namespace cac
{
    class OGLWindow;
    class Mouse : public IInputDevice
    {
    public:
	virtual void setWindow(IWindow* window) override;
	virtual void update(unsigned int context) override;
	
	//Key Actions
	void bind(EMouseInput inputMethod, std::string actionString, unsigned int context = 0);
	void getCursorPosition(int& xPos, int& yPos);
	
    private:
	enum class EMouseButtons
	{
	    LEFT_BUTTON,
	    RIGHT_BUTTON
	};
	struct MouseAction
	{
	    std::string actionString;
	    int context;
	    MouseAction(std::string actionString, int context) : actionString(actionString), context(context) {}
	};
	
	cac::OGLWindow* window = nullptr;
	int xPos = 0, yPos = 0;
	
	std::map<EMouseButtons, EMouseInput> previousStates;
	std::map<EMouseInput, std::vector<MouseAction>> mappedActions;
	
    };
}
#endif