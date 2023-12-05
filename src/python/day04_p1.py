#!/usr/bin/python3
import sys

if (len(sys.argv) < 2):
    print(f"Usage: {sys.argv[0]} input_file")
    exit(-1)

input = open(sys.argv[1]).readlines()

sum = 0

for line in input:
    index = line.find(':')
    card_id = line[:index]

    winning, yours = line[index + 1:].split('|')
    winning_set = set(list(map(int, winning.split())))
    yours_set = set(list(map(int, yours.split())))
    exponent = len(winning_set & yours_set)
    if (exponent > 0):
        sum += 2**(exponent-1)

print(int(sum))
