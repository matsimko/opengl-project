#pragma once
#include "CursorEvent.h"

class CursorListener {
public:
	virtual void onCursorMoved(CursorEvent e) = 0;

};