#!/usr/bin/python
import sys
from math import floor

if (len(sys.argv) < 2):
    print(f"Usage: {sys.argv[0]} input_file")
    exit(-1)

input = open(sys.argv[1]).readlines()

timelimit = int("".join(input[0].split(":")[1].strip().split()))
distance = int("".join(input[1].split(":")[1].strip().split()))


def calc_distance(p, t):
    return p * (t - p)


ways = 0
for pressing in range(timelimit):
    if calc_distance(pressing, timelimit) > distance:
        ways += 1

print(ways)
