#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// dimensions of the file:
#define ROWS 140
#define COLS 140
#define MAX_SIZE 1000

int has_numbers[ROWS][COLS];   // i if has number (i being index of list_numbers)
bool has_symbols[ROWS][COLS];  // true if has symbol

int list_numbers[MAX_SIZE];  // store numbers
size_t list_numbers_index = 0;

int list_gears[MAX_SIZE];
size_t list_gears_index = 0;

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
        }
    }
}

int do_sum() {
    int sum = 0;
    for (size_t i = 0; i < list_numbers_index; i++) {
        sum += list_gears[i];
    }
    return sum;
}

void add_gear(int n1, int n2) {
    int value = list_numbers[n1] * list_numbers[n2];
    list_gears[list_gears_index++] = value;
}

int get_has_number(int i, int j) {
    if (i < 0 || j < 0 || i >= ROWS || j >= COLS) {
        return -1;
    } else {
        return has_numbers[i][j];
    }
}

void find_gears() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (has_symbols[i][j]) {
                int nums[8] = {
                    get_has_number(i - 1, j - 1),
                    get_has_number(i - 1, j),
                    get_has_number(i - 1, j + 1),
                    get_has_number(i, j - 1),
                    get_has_number(i, j + 1),
                    get_has_number(i + 1, j - 1),
                    get_has_number(i + 1, j),
                    get_has_number(i + 1, j + 1),
                };

                int gear_numbers[8];
                memset(gear_numbers, -1, sizeof gear_numbers);
                int index = 0;
                for (int p = 0; p < 8; p++) {
                    if (nums[p] != -1) {
                        bool has_equal = false;
                        for (int k = 0; k < index; k++) {
                            if (nums[p] == gear_numbers[k]) {
                                has_equal = true;
                            }
                        }
                        if (!has_equal) {
                            gear_numbers[index++] = nums[p];
                        }
                    }
                }

                if (gear_numbers[0] != -1 && gear_numbers[1] != -1 && gear_numbers[2] == -1) {
                    add_gear(gear_numbers[0], gear_numbers[1]);
                }
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

    memset(has_numbers, -1, sizeof has_numbers);
    memset(has_symbols, false, sizeof has_symbols);
    memset(list_numbers, 0, sizeof list_numbers);
    memset(list_gears, 0, sizeof list_gears);

    int line_number = 0;
    char line[1024];
    while (fgets(line, sizeof(line), input) != NULL) {
        process_line(line, line_number);
        line_number++;
    }
    find_gears();
    int sum = do_sum();

    printf("%d\n", sum);

    return 0;
}
