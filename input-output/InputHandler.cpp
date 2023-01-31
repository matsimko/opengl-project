#include "InputHandler.h"
#include <algorithm>
#include "GLFWmapping.h"


void InputHandler::handle(InputEvent e)
{
	//notify listeners; GLFW_REPEAT is ignored (MouseButton doesn't even have the repeat option
	if (e.state != InputState::IGNORED) {
		for (auto listener : listeners) {
			listener->onInput(e);
		}
	}

}

void InputHandler::addListener(InputListener* listener)
{
	listeners.push_back(listener);
}

void InputHandler::removeListener(InputListener* listener)
{
	listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
}