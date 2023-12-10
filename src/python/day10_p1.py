#!/usr/bin/python
import sys

check = {
    ('|', 's'): 's',
    ('|', 'n'): 'n',
    ('-', 'e'): 'e',
    ('-', 'w'): 'w',
    ('L', 's'): 'e',
    ('L', 'w'): 'n',
    ('J', 's'): 'w',
    ('J', 'e'): 'n',
    ('7', 'n'): 'w',
    ('7', 'e'): 's',
    ('F', 'n'): 'e',
    ('F', 'w'): 's',
}

coord = {
    'n': [-1, 0],
    's': [1, 0],
    'w': [0, -1],
    'e': [0, 1],
}


def find_loop(contents, i, j):
    assert contents[i][j] == 'S'

    current_path = [(i, j)]

    ret = False
    if contents[i + 1][j] in ['|', 'L', 'J']:
        ret += check_loop(contents, i + 1, j, 's', current_path)
    if not ret and contents[i - 1][j] in ['-', 'J', '7']:
        ret += check_loop(contents, i - 1, j, 'n', current_path)
    if not ret and contents[i][j+1] in ['|', '7', 'F']:
        ret += check_loop(contents, i, j+1, 'e', current_path)
    if not ret and contents[i][j-1] in ['-', 'L', 'F']:
        ret += check_loop(contents, i, j-1, 'w', current_path)

    print(ret)


def check_loop(contents, i, j, d, current_path):
    while True:
        ch = contents[i][j]
        if ch == 'S':
            return len(current_path) // 2
        if ch not in ['-', '|', 'J', 'F', 'L', '7']:
            return 0

        d = check.get((ch, d), None)
        if d is None:
            return 0
        x, y = coord[d]
        i += x
        j += y
        current_path.append((i, j))


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} input_file", file=sys.stderr)
        exit(1)

    contents = open(sys.argv[1]).readlines()
    for i in range(len(contents)):
        j = contents[i].find('S')
        if j != -1:
            find_loop(contents, i, j)
            break


if __name__ == "__main__":
    main()
