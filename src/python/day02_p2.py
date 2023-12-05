#!/usr/bin/python3
import sys

if (len(sys.argv) < 2):
    print(f"Usage: {sys.argv[0]} input_file")
    exit(-1)

input = open(sys.argv[1]).readlines()

sum = 0

for line in input:
    max_colors = {
        "red": 1,
        "green": 1,
        "blue": 1,
    }
    index = line.find(':')
    game_id = int(line[:index].split()[1])

    for play in line[index + 1:-1].split(";"):
        for cubes in play.split(','):
            num, color = cubes.split()
            if (int(num) > max_colors[color]):
                max_colors[color] = int(num)

    sum += max_colors["red"] * max_colors["green"] * max_colors["blue"]

print(sum)
