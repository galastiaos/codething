#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300
#define FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"
#define FONT_SIZE 28

void speak(const char* text) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "espeak \"%s\"", text);
    system(cmd);
}

// Render text centered horizontally at given y
void renderTextCentered(SDL_Renderer* renderer, TTF_Font* font, const char* text, int y) {
    SDL_Color color = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        fprintf(stderr, "TTF_RenderText_Solid failed: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_FreeSurface(surface);

    SDL_Rect dest = {(WINDOW_WIDTH - textWidth) / 2, y, textWidth, textHeight};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
}

// Event-aware delay to keep window responsive
void delayWithEvents(Uint32 ms) {
    Uint32 start = SDL_GetTicks();
    SDL_Event e;
    while (SDL_GetTicks() - start < ms) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                exit(0);
        }
        SDL_Delay(10);
    }
}

void renderPrompt(SDL_Renderer* renderer, TTF_Font* font, const char* prompt) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderTextCentered(renderer, font, prompt, 200);
    SDL_RenderPresent(renderer);
}

int main() {
    int num1, num2, guess;
    char buffer[256];

    printf("Enter the first number: ");
    scanf("%d", &num1);
    printf("Enter the second number: ");
    scanf("%d", &num2);

    int top = (num1 >= num2) ? num1 : num2;
    int bottom = (num1 < num2) ? num1 : num2;
    int result = top + bottom;

    if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0) {
        fprintf(stderr, "Init error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Addition Tutor",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont(FONT_PATH, FONT_SIZE);

    if (!window || !renderer || !font) {
        fprintf(stderr, "SDL or font init failed: %s\n", SDL_GetError());
        return 1;
    }

    // Make sure the window is all black before starting
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // Narration and display steps
    snprintf(buffer, sizeof(buffer),
             "We have the problem %d plus %d. We start by writing the bigger number, %d, on top, and the smaller number, %d, below it.",
             top, bottom, top, bottom);
    speak(buffer);
    delayWithEvents(500);

    // Show top number
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    snprintf(buffer, sizeof(buffer), "%d", top);
    renderTextCentered(renderer, font, buffer, 50);
    SDL_RenderPresent(renderer);
    speak("Let's write the first number on top.");
    delayWithEvents(1000);

    // Show plus bottom number
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    snprintf(buffer, sizeof(buffer), "%d", top);
    renderTextCentered(renderer, font, buffer, 50);
    snprintf(buffer, sizeof(buffer), "+%d", bottom);
    renderTextCentered(renderer, font, buffer, 100);
    SDL_RenderPresent(renderer);
    speak("Now the second number below with a plus sign.");
    delayWithEvents(1000);

    // Show separator line
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    snprintf(buffer, sizeof(buffer), "%d", top);
    renderTextCentered(renderer, font, buffer, 50);
    snprintf(buffer, sizeof(buffer), "+%d", bottom);
    renderTextCentered(renderer, font, buffer, 100);
    renderTextCentered(renderer, font, "-----", 140);
    SDL_RenderPresent(renderer);
    speak("Let's figure out what they add up to.");
    delayWithEvents(1000);

    speak("What is the result of adding them?");
    renderPrompt(renderer, font, "What is the result?");
    printf("Your answer: ");
    scanf("%d", &guess);

    if (guess == result) {
        speak("That's correct! Great job.");
    } else {
        snprintf(buffer, sizeof(buffer), "That's incorrect. The right answer is %d.", result);
        speak(buffer);
    }

    // Clear screen and show final message
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    snprintf(buffer, sizeof(buffer), "The result was %d.", result);
    renderTextCentered(renderer, font, buffer, 120);

    if (guess == result) {
        renderTextCentered(renderer, font, "Good job!", 180);
    } else {
        renderTextCentered(renderer, font, "You'll get it next time.", 180);
    }
    SDL_RenderPresent(renderer);

    // Main event loop to keep window open until closed
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = 1;
        }
        SDL_Delay(100);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

