#include <SDL2/SDL.h>
#include <iostream>
#define SCREEN_WIDTH
#define SCREEN_HEIGHT
int main(int argc, char *argv[]){
	SDL_Window *window = NULL;
	SDL_Renderer *rend = NULL;
	if(SDL_Init(SDL_INIT_VIDEO) < 0 ){//sdl didnt initialize properly
		std::cout << "SDL broke in init with error: " << SDL_GetError();//say that to the user
		return 1;//exit the program
	}
	window = SDL_CreateWindow(
		"SDL",//title
		SDL_WINDOWPOS_UNDEFINED,//x on screen
		SDL_WINDOWPOS_UNDEFINED,//y on screen
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN//flags?
	);
	if(window==NULL){
		std::cout << "Window couldnt be created! SDL_error:" << SDL_GetError() << std::endl;
	}
	return 0;
}
