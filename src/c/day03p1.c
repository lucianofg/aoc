#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// dimensions of the file:
#define ROWS 140
#define COLS 140
#define MAX_SIZE 1000

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

int get_has_number(int i, int j) {
    if (i < 0 || j < 0 || i >= ROWS || j >= COLS) {
        return -1;
    } else {
        return has_numbers[i][j];
    }
}


void find_adjacent_numbers() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (has_symbols[i][j]) {
                if_number_add_adjacent(get_has_number(i - 1, j - 1));
                if_number_add_adjacent(get_has_number(i - 1, j));
                if_number_add_adjacent(get_has_number(i - 1, j + 1));
                if_number_add_adjacent(get_has_number(i, j - 1));
                if_number_add_adjacent(get_has_number(i, j + 1));
                if_number_add_adjacent(get_has_number(i + 1, j - 1));
                if_number_add_adjacent(get_has_number(i + 1, j));
                if_number_add_adjacent(get_has_number(i + 1, j + 1));
            }
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
    find_adjacent_numbers();
    int sum = do_sum();

    printf("%d\n", sum);

    return 0;
}
