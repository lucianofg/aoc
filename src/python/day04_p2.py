#!/usr/bin/python3
import sys

if (len(sys.argv) < 2):
    print(f"Usage: {sys.argv[0]} input_file")
    exit(-1)

input = open(sys.argv[1]).readlines()

cards = [0 for _ in range(1000)]
cards[0] = 1
for line_number, line in enumerate(input):
    cards[line_number + 1] += 1
    index = line.find(':')

    winning, yours = line[index + 1:].split('|')
    set_winning = set(list(map(int, winning.split())))
    set_yours = set(list(map(int, yours.split())))
    number_winning_cards = len(set_winning & set_yours)
    for i in range(number_winning_cards):
        cards[line_number + 1 + i] += cards[line_number]


print(sum(cards) - 1)
