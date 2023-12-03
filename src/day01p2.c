#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int process_line(char *line);
int char_to_int(char c);

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

    int sum = 0;
    char line[1024];
    while (fgets(line, sizeof(line), input) != NULL) {
        int value = process_line(line);
        sum += value;
    }

    printf("%d\n", sum);

    return 0;
}

int process_line(char *line) {
    bool need_first = true;
    int first_digit = 0;
    int last_digit = 0;

    for (int i = 0; line[i]; i++) {
        int number = 0;
        if (isdigit(line[i])) {
            number = char_to_int(line[i]);
        } else {
            switch (line[i]) {
            case 'o':
                if (strncmp(line + i, "one", 3) == 0) {
                    number = 1;
                }
                break;
            case 't':
                if (strncmp(line + i, "two", 3) == 0) {
                    number = 2;
                } else if (strncmp(line + i, "three", 5) == 0) {
                    number = 3;
                }
                break;
            case 'f':
                if (strncmp(line + i, "four", 4) == 0) {
                    number = 4;
                } else if (strncmp(line + i, "five", 4) == 0) {
                    number = 5;
                }
                break;
            case 's':
                if (strncmp(line + i, "six", 3) == 0) {
                    number = 6;
                } else if (strncmp(line + i, "seven", 5) == 0) {
                    number = 7;
                }
                break;
            case 'e':
                if (strncmp(line + i, "eight", 5) == 0) {
                    number = 8;
                }
                break;
            case 'n':
                if (strncmp(line + i, "nine", 4) == 0) {
                    number = 9;
                }
                break;
            }
        }
        if (need_first && number) {
            first_digit = number * 10;
            need_first = false;
        }
        if (number) {
            last_digit = number;
        }
    }

    return first_digit + last_digit;
}

int char_to_int(char ch) {
    return ch - '0';
}
