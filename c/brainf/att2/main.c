#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 20

typedef struct {
    unsigned char *subcells;
    int subcell_count;
} Cell;

Cell memory[MEMORY_SIZE];
int current_cell = 0;
int current_subcell = 0;

unsigned char* get_current_value_ptr(Cell *cell) {
    if (cell->subcell_count == 0) {
        // No subcells: single cell value is stored in subcells[0] implicitly
        // We'll treat this as an internal value (use a dummy 1-byte buffer)
        static unsigned char single_value = 0;
        return &single_value;
    } else {
        return &cell->subcells[current_subcell];
    }
}

void add_subcell(Cell *cell) {
    cell->subcells = realloc(cell->subcells, (cell->subcell_count + 1) * sizeof(unsigned char));
    cell->subcells[cell->subcell_count] = 0;
    cell->subcell_count++;
    current_subcell = cell->subcell_count - 1;
}

void remove_subcell(Cell *cell) {
    if (cell->subcell_count > 0) {
        cell->subcell_count--;
        cell->subcells = realloc(cell->subcells, cell->subcell_count * sizeof(unsigned char));
        if (current_subcell >= cell->subcell_count)
            current_subcell = cell->subcell_count - 1;
        if (cell->subcell_count == 0) current_subcell = 0;
    }
}

void move_subcell_right(Cell *cell) {
    if (cell->subcell_count == 0) return;
    if (current_subcell < cell->subcell_count - 1) current_subcell++;
}

void move_subcell_left(Cell *cell) {
    if (cell->subcell_count == 0) return;
    if (current_subcell > 0) current_subcell--;
}

void print_memory_state(int window_size, int pointer_pos) {
    printf("\nMemory State:\n");
    int start = pointer_pos - window_size / 2;
    if (start < 0) start = 0;
    int end = start + window_size;
    if (end > MEMORY_SIZE) {
        end = MEMORY_SIZE;
        start = end - window_size;
        if (start < 0) start = 0;
    }

    // Print cell values and subcells
    for (int i = start; i < end; i++) {
        printf("[");
        if (memory[i].subcell_count == 0) {
            // single cell, print 1 value (simulate subcell 0)
            unsigned char val = 0;
            if (i == current_cell && current_subcell == 0) {
                // if pointer here, use dynamic single_value (tricky, so we read from a dummy)
                // We use get_current_value_ptr with a temp pointer for current cell.
                // But for other cells with no subcells, just print 0 (initialized)
                if (i == current_cell) val = *get_current_value_ptr(&memory[i]);
            }
            printf("%3d", val);
        } else {
            for (int j = 0; j < memory[i].subcell_count; j++) {
                printf("%3d", memory[i].subcells[j]);
                if (j != memory[i].subcell_count - 1) printf(",");
            }
        }
        printf("]");
    }
    printf("\n");

    // Print pointer indicators under cells
    for (int i = start; i < end; i++) {
        if (i == current_cell) {
            printf("  ^");
            if (memory[i].subcell_count > 0)
                printf("  | (subcell %d)", current_subcell);
        } else {
            printf("    ");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int debug = 0;
    char *filename = NULL;

    if (argc < 2) {
        printf("Usage: %s [-D] filename.bf\n", argv[0]);
        return 1;
    }

    int arg_index = 1;
    if (strcmp(argv[1], "-D") == 0) {
        debug = 1;
        if (argc < 3) {
            printf("Usage: %s [-D] filename.bf\n", argv[0]);
            return 1;
        }
        filename = argv[2];
    } else {
        filename = argv[1];
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File open failed");
        return 1;
    }

    // Init memory cells
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].subcells = NULL;
        memory[i].subcell_count = 0;
    }

    int c;
    int display_window_size = 10;
    int paused = 0;

    while ((c = fgetc(file)) != EOF) {
        int recognized = 0;

        // Skip comments/non-commands silently except recognized commands:
        switch (c) {
            case '+':
                (*get_current_value_ptr(&memory[current_cell]))++;
                recognized = 1;
                break;
            case '-':
                (*get_current_value_ptr(&memory[current_cell]))--;
                recognized = 1;
                break;
            case '>':
                if (current_cell < MEMORY_SIZE - 1) {
                    current_cell++;
                    current_subcell = 0;
                }
                recognized = 1;
                break;
            case '<':
                if (current_cell > 0) {
                    current_cell--;
                    current_subcell = 0;
                }
                recognized = 1;
                break;
            case '^':
                add_subcell(&memory[current_cell]);
                recognized = 1;
                break;
            case '$':
                remove_subcell(&memory[current_cell]);
                recognized = 1;
                break;
            case '/':
                move_subcell_right(&memory[current_cell]);
                recognized = 1;
                break;
            case '\\':
                move_subcell_left(&memory[current_cell]);
                recognized = 1;
                break;
            case ',':
                {
                    int inp = getchar();
                    if (inp != EOF) {
                        *get_current_value_ptr(&memory[current_cell]) = inp;
                    }
                }
                recognized = 1;
                break;
            case '.':
                putchar(*get_current_value_ptr(&memory[current_cell]));
                fflush(stdout);
                recognized = 1;
                break;
            default:
                recognized = 0;
                break;
        }

        if (debug && recognized) {
            print_memory_state(display_window_size, current_cell);
            printf("Current instruction: '%c'\n", c);
            printf("Controls: '=' pause/resume, '+' show more cells, '-' show fewer cells, 'q' quit debug\n");
            paused = 1;
            while (paused) {
                int input = getchar();
                if (input == '=') {
                    paused = !paused;
                } else if (input == '+') {
                    if (display_window_size < MEMORY_SIZE)
                        display_window_size++;
                    print_memory_state(display_window_size, current_cell);
                } else if (input == '-') {
                    if (display_window_size > 1)
                        display_window_size--;
                    print_memory_state(display_window_size, current_cell);
                } else if (input == 'q') {
                    fclose(file);
                    for (int i = 0; i < MEMORY_SIZE; i++) {
                        if (memory[i].subcells != NULL)
                            free(memory[i].subcells);
                    }
                    return 0;
                }
            }
        }
    }

    fclose(file);
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].subcells != NULL) free(memory[i].subcells);
    }

    return 0;
}

