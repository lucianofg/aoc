#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

int process_line(char *line) {
    bool has_number = false;
    char tmp[10];
    int tmp_i = 0;
    int tmp_size = 10;
    int winning_numbers[MAX_SIZE] = {0};
    int your_numbers[MAX_SIZE] = {0};
    int *list = winning_numbers;
    int index = 0;
    int i = 0;

    while (line[i++] != ':')
        ;

    for (; line[i]; i++) {
        if (isdigit(line[i])) {
            tmp[tmp_i++] = line[i];
            has_number = true;
            continue;
        }

        switch (line[i]) {
        case '|':
        case ' ':
        case '\n':
            if (has_number) {
                tmp_i = 0;
                has_number = false;
                list[index++] = atoi(tmp);
                memset(tmp, 0, tmp_size);
            }

            if (line[i] == '|') {
                index = 0;
                list = your_numbers;
            }
            break;
        default:
            printf("Has symbol code: %d (%c)\n", (int)line[i], line[i]);
        }
    }

    int num = 1;
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < index; j++) {
            if (winning_numbers[i] == your_numbers[j]) {
                num *= 2;
            }
        }
    }
    return num / 2;
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

    char line[1024];
    int sum = 0;
    while (fgets(line, sizeof(line), input) != NULL) {
        sum += process_line(line);
    }

    printf("%d\n", sum);

    return 0;
}
