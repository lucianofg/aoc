#!/usr/bin/python3
import sys

if (len(sys.argv) < 2):
    print(f"Usage: {sys.argv[0]} input_file")
    exit(-1)

input = open(sys.argv[1]).readlines()

sum = 0

for line in input:
    max_colors = {
        "red": 12,
        "green": 13,
        "blue": 14,
    }
    should_count = True
    index = line.find(':')
    game_id = int(line[:index].split()[1])

    for play in line[index + 1:-1].split(";"):
        for cubes in play.split(','):
            num, color = cubes.split()
            if (int(num) > max_colors[color]):
                should_count = False

    if should_count:
        sum += game_id

print(sum)
