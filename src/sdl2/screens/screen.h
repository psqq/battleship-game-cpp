#pragma once

class Screen {
public:
	virtual void draw() = 0;
	virtual void onEvent(SDL_Event e) = 0;
	virtual void update(int dt=0) = 0;
};
