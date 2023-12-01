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
    int first_digit, last_digit;

    for (int i = 0; line[i]; i++) {
        char c = line[i];
        if (isdigit(c)) {
            if (need_first) {
                first_digit = char_to_int(c) * 10;
                need_first = false;
            }
            last_digit = char_to_int(c);
        }
    }

    return first_digit + last_digit;
}

int char_to_int(char ch) {
    return ch - '0';
}
