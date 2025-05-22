#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
int main(int argc, char *argv[]){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cerr << "SDL is being a fucking bitch. heres its bullshit excuse: " << SDL_GetError() << std::endl;
		return 1;
	}
	std::cout << "yay!" << std::endl;
	SDL_DisplayMode displayMode;
	if(SDL_GetDesktopDisplayMode(0, &displayMode) != 0){
		std::cerr << "SDL is too retarded to get the desktop display mode. Heres why: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	const int SCREEN_WIDTH = displayMode.w;
	const int SCREEN_HEIGHT = displayMode.h;
	const int CURSOR_SIZE = 32;
	const int MOVE_SPEED = 5;
	SDL_Window* window = SDL_CreateWindow("Arrow Key Cursor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
        	std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
       		SDL_Quit();
        	return 1;
    	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    	if (renderer == nullptr) {
        	std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        	SDL_DestroyWindow(window);
        	SDL_Quit();
        	return 1;
    	}

    	SDL_Rect cursorRect;
    	cursorRect.w = CURSOR_SIZE;
    	cursorRect.h = CURSOR_SIZE;
    	cursorRect.x = SCREEN_WIDTH / 2 - CURSOR_SIZE / 2;
    	cursorRect.y = SCREEN_HEIGHT / 2 - CURSOR_SIZE / 2;

    	bool quit = false;
    	SDL_Event event;

    	while (!quit) {
        	while (SDL_PollEvent(&event) != 0) {
            		if (event.type == SDL_QUIT) {
                		quit = true;
            		} else if (event.type == SDL_KEYDOWN) {
               			switch (event.key.keysym.sym) {
                    		case SDLK_UP:
                        	cursorRect.y -= MOVE_SPEED;
                        	break;
                    		case SDLK_DOWN:
                        	cursorRect.y += MOVE_SPEED;
                        	break;
                    		case SDLK_LEFT:
                        	cursorRect.x -= MOVE_SPEED;
                        	break;
                    		case SDLK_RIGHT:
                        	cursorRect.x += MOVE_SPEED;
                        	break;
                    		case SDLK_ESCAPE:
                        	quit = true;
                        	break;
                	}

                // Keep cursor within screen bounds
                if (cursorRect.x < 0) cursorRect.x = 0;
                if (cursorRect.y < 0) cursorRect.y = 0;
                if (cursorRect.x > SCREEN_WIDTH - cursorRect.w) cursorRect.x = SCREEN_WIDTH - cursorRect.w;
                if (cursorRect.y > SCREEN_HEIGHT - cursorRect.h) cursorRect.y = SCREEN_HEIGHT - cursorRect.h;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // Draw the "cursor" (a simple rectangle)
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer, &cursorRect);

        // Update the screen
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Roughly 60 FPS
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
