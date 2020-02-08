#include <iostream>
#include "app.h"

int main(int argc, char* argv[])
{
	int return_code = 0;
	App app;
	try {
		app.init();
		app.run();
	}
	catch (char* errMsg) {
		std::cerr << "Error: " << errMsg << std::endl;
		return_code = 1;
	}
	catch (...) {
		std::cerr << "Unknow error!" << std::endl;
		return_code = 1;
	}
	if (return_code) {
		const char* sdlErrMsg = SDL_GetError();
		if (sdlErrMsg) {
			std::cerr << "SDL Error Message: " << sdlErrMsg << std::endl;
		}
	}
	app.clear();
	return return_code;
}
