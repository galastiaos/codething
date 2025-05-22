#include <iostream>
#include <SDL2/SDL.h>//SDL2 folder because g++ doesnt like just sdl.h
using namespace std; //i hate std:: everything. Unless this gets big enough(spoiler alert, it wont) im gonna keep this in.
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
//area of screen window
int main(int argc,  char *argv[]){
	SDL_Window* window = NULL; //a window to hold the "canvas"
	SDL_Surface* screensurface = NULL; //a canvas for our window
	if(SDL_Init(SDL_INIT_VIDEO) < 0 ){ //intializing sdl
		printf("SDL Couldnt be init with error %s\n", SDL_GetError()); //damn it something broke(gnome probably if this happens)
	} else { //ok lets keep going
		window = SDL_CreateWindow("SDL TUT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);//initializing said window
		if(window == NULL){ //said window didn't initialize for whatever reason
			cout << "Couldnt create window sdl error:%s\n" << SDL_GetError();
		}else{//it did
			screensurface = SDL_GetWindowSurface(window); //make the render inside of the window
			SDL_FillRect(screensurface, NULL, SDL_MapRGB(screensurface->format,0xff,0xff,0xff)); //Make a white square inside of the render, using the format property of the surfacestruct
			SDL_UpdateWindowSurface(window); //redraw the window
			SDL_Event e; //an event
			bool quit=false; //flag to check whether to leave or not
			while(!quit){ //were still running-------------------------------                              
				while(SDL_PollEvent(&e)){ //what?                       |
					if(e.type == SDL_QUIT){ //if we exit the window |
						quit=true;//not anymore <----------------
					}
				}
			}
		}
	}
	SDL_DestroyWindow(window); //goodbye window
	SDL_Quit();//goodbye sdl
	return 0;//goodbye main()
}
