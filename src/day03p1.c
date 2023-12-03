#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// dimensions of the file:
#define ROWS 140
#define COLS 140
#define MAX_SIZE 20000

int has_numbers[ROWS][COLS];  // i if has number (i being index of list_numbers)
bool has_symbols[ROWS][COLS];  // true if has symbol

int list_numbers[MAX_SIZE];  // store numbers
size_t list_numbers_index = 0;

int adjacent[MAX_SIZE];
int adjacent_index = 0;

void process_line(char *line, int line_number) {
    bool has_number = false;
    char tmp[10];
    int tmp_i = 0;
    int tmp_size = 10;

    for (int i = 0; line[i]; i++) {
        if (isdigit(line[i])) {
            tmp[tmp_i++] = line[i];
            has_number = true;
            has_numbers[line_number][i] = list_numbers_index;
            continue;
        }

        switch (line[i]) {
        case '*':
        case '/':
        case '+':
        case '%':
        case '&':
        case '-':
        case '=':
        case '$':
        case '@':
        case '#':
            has_symbols[line_number][i] = true;
        case '.':
        case '\n':
            if (has_number) {
                tmp_i = 0;
                has_number = false;
                list_numbers[list_numbers_index++] = atoi(tmp);
                memset(tmp, 0, tmp_size);
            }
            break;
        default:
            printf("Has symbol code: %d (%c)\n", (int)line[i], line[i]);
        }
    }
}

int do_sum() {
    int sum = 0;
    for (int i = 0; i < adjacent_index; i++) {
        int index = adjacent[i];
        sum += list_numbers[index];
        list_numbers[index] = 0;
    }
    return sum;
}

void if_number_add_adjacent(int i) {
    if (i != -1) {
        adjacent[adjacent_index++] = i;
    }
}

void create_adjacent_numbers() {
    // check most cases
    for (int i = 1; i < ROWS - 1; i++) {
        for (int j = 1; j < COLS - 1; j++) {
            if (has_symbols[i][j]) {
                if_number_add_adjacent(has_numbers[i - 1][j - 1]);
                if_number_add_adjacent(has_numbers[i - 1][j]);
                if_number_add_adjacent(has_numbers[i - 1][j + 1]);
                if_number_add_adjacent(has_numbers[i][j - 1]);
                if_number_add_adjacent(has_numbers[i][j + 1]);
                if_number_add_adjacent(has_numbers[i + 1][j - 1]);
                if_number_add_adjacent(has_numbers[i + 1][j]);
                if_number_add_adjacent(has_numbers[i + 1][j + 1]);
            }
        }
    }

    // check very specific cases
    if (has_symbols[0][0]) {
        if_number_add_adjacent(has_numbers[0][1]);
        if_number_add_adjacent(has_numbers[1][0]);
        if_number_add_adjacent(has_numbers[1][1]);
    }
    if (has_symbols[ROWS - 1][COLS - 1]) {
        if_number_add_adjacent(has_numbers[ROWS - 1][COLS - 2]);
        if_number_add_adjacent(has_numbers[ROWS - 2][COLS - 1]);
        if_number_add_adjacent(has_numbers[ROWS - 2][COLS - 2]);
    }
    if (has_symbols[0][COLS - 1]) {
        if_number_add_adjacent(has_numbers[0][COLS - 2]);
        if_number_add_adjacent(has_numbers[1][COLS - 1]);
        if_number_add_adjacent(has_numbers[1][COLS - 2]);
    }
    if (has_symbols[ROWS - 1][0]) {
        if_number_add_adjacent(has_numbers[ROWS - 1][1]);
        if_number_add_adjacent(has_numbers[ROWS - 2][0]);
        if_number_add_adjacent(has_numbers[ROWS - 2][1]);
    }

    // check first line
    for (int i = 0, j = 0; j < COLS - 1; j++) {
        if (has_symbols[i][j]) {
            if_number_add_adjacent(has_numbers[i][j - 1]);
            if_number_add_adjacent(has_numbers[i][j + 1]);
            if_number_add_adjacent(has_numbers[i + 1][j - 1]);
            if_number_add_adjacent(has_numbers[i+ 1][j]);
            if_number_add_adjacent(has_numbers[i + 1][j + 1]);
        }
    }
    // check last line
    for (int i = ROWS - 1, j = 0; j < COLS - 1; j++) {
        if (has_symbols[i][j]) {
            if_number_add_adjacent(has_numbers[i][j - 1]);
            if_number_add_adjacent(has_numbers[i][j + 1]);
            if_number_add_adjacent(has_numbers[i - 1][j - 1]);
            if_number_add_adjacent(has_numbers[i - 1][j]);
            if_number_add_adjacent(has_numbers[i - 1][j + 1]);
        }
    }
    // check first column
    for (int i = 0, j = 0; i < ROWS - 1; i++) {
        if (has_symbols[i][j]) {
            if_number_add_adjacent(has_numbers[i][j + 1]);
            if_number_add_adjacent(has_numbers[i - 1][j]);
            if_number_add_adjacent(has_numbers[i - 1][j + 1]);
            if_number_add_adjacent(has_numbers[i + 1][j]);
            if_number_add_adjacent(has_numbers[i + 1][j + 1]);
        }
    }
    // check last column
    for (int i = 0, j = COLS - 1; i < ROWS - 1; i++) {
        if (has_symbols[i][j]) {
            if_number_add_adjacent(has_numbers[i][j - 1]);
            if_number_add_adjacent(has_numbers[i - 1][j]);
            if_number_add_adjacent(has_numbers[i - 1][j - 1]);
            if_number_add_adjacent(has_numbers[i + 1][j]);
            if_number_add_adjacent(has_numbers[i + 1][j - 1]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        return -1;
    }
    char *filename = argv[1];
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        fprintf(stderr, "Could not open input file\n");
        return -1;
    }

    /* The part that matters */

    memset(has_numbers, -1, sizeof has_numbers); // Set to -1 cause we have 0 index!
    memset(has_symbols, false, sizeof has_symbols);
    memset(list_numbers, 0, sizeof list_numbers);
    memset(adjacent, 0, sizeof adjacent);

    int line_number = 0;
    char line[1024];
    while (fgets(line, sizeof(line), input) != NULL) {
        process_line(line, line_number);
        line_number++;
    }
    create_adjacent_numbers();
    int sum = do_sum();

    printf("%d\n", sum);

    return 0;
}
