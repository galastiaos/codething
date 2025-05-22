#include <SDL2/SDL.h>/home/mrcodester/code/c/checkers/checkers.cbp
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 8
#define CELL 80
#define WIDTH (SIZE * CELL)
#define HEIGHT ((SIZE + 1) * CELL)  // extra row for input display
#define MAX_INPUT 5 // A3B4 + null

char board[SIZE][SIZE];
char input[MAX_INPUT];
int input_pos = 0;
char current_player = 'X';

void init_board() {
    for (int y = 0; y < SIZE; y++)
        for (int x = 0; x < SIZE; x++)
            board[y][x] = ((x + y) % 2 == 1) ? (y < 3 ? 'O' : y > 4 ? 'X' : ' ') : '.';
}

void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void draw_board(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            SDL_Rect rect = { x * CELL, y * CELL, CELL, CELL };

            // Light/dark squares
            if ((x + y) % 2 == 0)
                SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
            else
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderFillRect(renderer, &rect);

            // Draw piece
            if (board[y][x] == 'X' || board[y][x] == 'O') {
                SDL_SetRenderDrawColor(renderer,
                    board[y][x] == 'X' ? 255 : 0,
                    0,
                    board[y][x] == 'O' ? 255 : 0,
                    255);
                SDL_Rect piece = { x * CELL + 20, y * CELL + 20, CELL - 40, CELL - 40 };
                SDL_RenderFillRect(renderer, &piece);
            }
        }
    }

    // Draw column letters (A–H)
    for (int x = 0; x < SIZE; x++) {
        char label[2] = { 'A' + x, '\0' };
        draw_text(renderer, font, label, x * CELL + CELL / 2 - 10, SIZE * CELL + 10, (SDL_Color){0, 0, 0, 255});
    }

    // Draw row numbers (1–8)
    for (int y = 0; y < SIZE; y++) {
        char label[2] = { '0' + (SIZE - y), '\0' };
        draw_text(renderer, font, label, SIZE * CELL + 10, y * CELL + CELL / 2 - 10, (SDL_Color){0, 0, 0, 255});
    }

    // Show current move input
    char display[64];
    snprintf(display, sizeof(display), "Player %c - Move: %s", current_player, input);
    draw_text(renderer, font, display, 10, SIZE * CELL + 40, (SDL_Color){20, 20, 200, 255});

    SDL_RenderPresent(renderer);
}

int is_valid_move(int fx, int fy, int tx, int ty, char player) {
    if (tx < 0 || tx >= SIZE || ty < 0 || ty >= SIZE || board[ty][tx] != ' ')
        return 0;
    int dx = tx - fx;
    int dy = ty - fy;
    // Regular move (no jump)
    if (abs(dx) == 1 && ((player == 'X' && dy == -1) || (player == 'O' && dy == 1)))
        return 1;
    // Jump move (captures opponent's piece)
    if (abs(dx) == 2 && ((player == 'X' && dy == -2) || (player == 'O' && dy == 2))) {
        int mx = (fx + tx) / 2, my = (fy + ty) / 2;
        // Check if there is an opponent's piece to capture
        return board[my][mx] != ' ' && board[my][mx] != player ? 2 : 0;
    }
    return 0;
}

void make_move(int fx, int fy, int tx, int ty, char player) {
    int type = is_valid_move(fx, fy, tx, ty, player);
    if (!type) return;
    board[ty][tx] = player;
    board[fy][fx] = ' ';
    if (type == 2) {
        int mx = (fx + tx) / 2, my = (fy + ty) / 2;
        board[my][mx] = ' ';  // Remove captured piece
    }
    current_player = (current_player == 'X') ? 'O' : 'X';
}

int parse_move(const char *s, int *fx, int *fy, int *tx, int *ty) {
    if (strlen(s) != 4) return 0;
    if (!isalpha(s[0]) || !isdigit(s[1]) || !isalpha(s[2]) || !isdigit(s[3]))
        return 0;

    *fx = toupper(s[0]) - 'A';
    *fy = SIZE - (s[1] - '0');
    *tx = toupper(s[2]) - 'A';
    *ty = SIZE - (s[3] - '0');

    return (*fx >= 0 && *fx < SIZE && *fy >= 0 && *fy < SIZE &&
            *tx >= 0 && *tx < SIZE && *ty >= 0 && *ty < SIZE);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window *win = SDL_CreateWindow("Checkers SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH + 80, HEIGHT, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 24);

    if (!font) {
        printf("Failed to load font!\n");
        return 1;
    }

    init_board();
    int running = 1;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = 0;
            else if (e.type == SDL_KEYDOWN) {
                SDL_Keycode key = e.key.keysym.sym;

                if (key == SDLK_RETURN && input_pos == 4) {
                    int fx, fy, tx, ty;
                    if (parse_move(input, &fx, &fy, &tx, &ty) && board[fy][fx] == current_player) {
                        make_move(fx, fy, tx, ty, current_player);
                    } else {
                        printf("Invalid move: %s\n", input);
                    }
                    input_pos = 0;
                    input[0] = '\0';
                } else if (key == SDLK_BACKSPACE && input_pos > 0) {
                    input[--input_pos] = '\0';
                } else if (input_pos < 4) {
                    if ((key >= SDLK_a && key <= SDLK_z) || (key >= SDLK_0 && key <= SDLK_9)) {
                        input[input_pos++] = isalpha(key) ? toupper(key) : key;
                        input[input_pos] = '\0';
                    }
                }
            }
        }

        draw_board(ren, font);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
