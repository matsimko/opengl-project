#include "CursorHandler.h"

CursorHandler::CursorHandler()
{
	prevX = prevY = 0;
}

void CursorHandler::handle(CursorEvent e)
{
	e.prevX = prevX;
	e.prevY = prevY;
	for (auto listener : listeners) {
		listener->onCursorMoved(e);
	}
	prevX = e.x;
	prevY = e.y;
}

void CursorHandler::addListener(CursorListener* listener)
{
	listeners.push_back(listener);
}

void CursorHandler::removeListener(CursorListener* listener)
{
	listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
}

void CursorHandler::setPrevCursorPos(double x, double y)
{
	prevX = x;
	prevY = y;
}