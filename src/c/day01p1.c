#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
    char number[3] = "";

    for (int i = 0; line[i]; i++) {
        if (isdigit(line[i])) {
            if (need_first) {
                number[0] = line[i];
                need_first = false;
            }
            number[1] = line[i];
        }
    }

    return atoi(number);
}

int char_to_int(char ch) {
    return ch - '0';
}
