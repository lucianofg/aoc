#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum colors {
    RED = 0,
    BLUE,
    GREEN,
};

int process_line(char *line);
int process_cubes(char *line);
char *get_id(char *line, int *id);

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
    int id;
    char *last = get_id(line, &id);
    int power_set_cubes = process_cubes(last);

    return power_set_cubes;
}

char *get_id(char *line, int *return_id) {
    // Skipping "Game_" (0 1 2 3 4)
    char *last = line + 5;
    char id[4] = "";
    int i = 0;
    while (last[0] != ':') {
        id[i] = last[0];
        last++;
        i++;
    }
    *return_id = atoi(id);
    // skipping ":_"
    last += 2;

    return last;
}

int process_cubes(char *line) {
    int total[3] = {
        [RED] = 0,
        [BLUE] = 0,
        [GREEN] = 0,
    };
    int max[3] = {
        [RED] = 0,
        [BLUE] = 0,
        [GREEN] = 0,
    };

    enum colors color;
    char tmp[5] = "";
    size_t tmp_size = 5;
    int value = 0;
    int j = 0;

    for (int i = 0; line[i]; i++) {
        if (isdigit(line[i])) {
            tmp[j++] = line[i];
            continue;
        }

        switch (line[i]) {
        case 'b':
            color = BLUE;
            i += 3;
            break;
        case 'r':
            color = RED;
            i += 2;
            break;
        case 'g':
            color = GREEN;
            i += 4;
            break;
        case ',':
        case ';':
        case '\n':
            value = atoi(tmp);
            j = 0;
            memset(tmp, 0, tmp_size);

            switch (color) {
            case RED:
                total[RED] += value;
                break;
            case BLUE:
                total[BLUE] += value;
                break;
            case GREEN:
                total[GREEN] += value;
                break;
            }

            if (line[i] == ';' || line[i] == '\n') {
                for (int k = 0; k < 3; k++) {
                    if (total[k] > max[k]) {
                        max[k] = total[k];
                    }
                    total[k] = 0;
                }
            }
            break;
        }
    }

    int power = 1;
    for (int i = 0; i < 3; i++) {
        power *= max[i];
    }
    return power;
}
