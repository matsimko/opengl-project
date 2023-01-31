#pragma once
#include "CursorEvent.h"
#include "CursorListener.h"
#include <vector>

//I could make a generic observer base class with 3 generic parameters (eventsource, eventobject and listener),
//which would implement the boilerplate management of listeners

class CursorHandler {

private:
	std::vector<CursorListener*> listeners;
	double prevX;
	double prevY;
public:
	CursorHandler();
	void handle(CursorEvent e);
	void addListener(CursorListener* listener);
	void removeListener(CursorListener* listener);

	void setPrevCursorPos(double x, double y);
};