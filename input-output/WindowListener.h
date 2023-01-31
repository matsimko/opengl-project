#pragma once

class Window;

class WindowListener {
public:
	//sending window is enough, as you can get the new dimensions from it
	virtual void onResize(Window* window) = 0;
};
