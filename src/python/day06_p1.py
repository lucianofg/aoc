#!/usr/bin/python
import sys

if (len(sys.argv) < 2):
    print(f"Usage: {sys.argv[0]} input_file")
    exit(-1)

input = open(sys.argv[1]).readlines()

times = list(map(int, input[0].split(":")[1].strip().split()))
distances = list(map(int, input[1].split(":")[1].strip().split()))


def calc_distance(pressing, timelimit):
    return pressing * (timelimit - pressing)


ways = []
for i, timelimit in enumerate(times):
    count = 0
    for pressing in range(timelimit):
        if calc_distance(pressing, timelimit) > distances[i]:
            count += 1
    ways.append(count)

total = 1
for i in ways:
    total *= i

print(total)
