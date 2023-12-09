#!/usr/bin/python
import sys
from collections import Counter
from functools import cmp_to_key

if len(sys.argv) < 2:
    print(f"Usage: {sys.argv[0]} input_file", file=sys.stderr)
    exit(1)

lines = open(sys.argv[1]).readlines()


def get_stregth(hand):
    values = Counter(hand)
    values = sorted(values.items(), reverse=True, key=lambda x: x[1])

    if values[0][1] == 5:
        return 6
    elif values[0][1] == 4:
        return 5
    elif values[0][1] == 3 and values[1][1] == 2:
        return 4
    elif values[0][1] == 3:
        return 3
    elif values[0][1] == 2 and values[1][1] == 2:
        return 2
    elif values[0][1] == 2:
        return 1
    else:
        return 0


def compare_same_stregth(hand, other):
    for i in range(5):
        if hand[0][i] != other[0][i]:
            return cards_values[hand[0][i]] - cards_values[other[0][i]]
    return 0


cards_values = {
    'A': 12,
    'K': 11,
    'Q': 10,
    'J': 9,
    'T': 8,
    '9': 7,
    '8': 6,
    '7': 5,
    '6': 4,
    '5': 3,
    '4': 2,
    '3': 1,
    '2': 0,
}

hands_values = {
    0: [],
    1: [],
    2: [],
    3: [],
    4: [],
    5: [],
    6: [],
}

for line in lines:
    hand, bind = line.split()
    stregth = get_stregth(hand)
    hands_values[stregth].append((hand, int(bind)))


soma = 0
rank = 1
for key, value in hands_values.items():
    value = sorted(value, key=cmp_to_key(compare_same_stregth))

    for v in value:
        soma += rank * v[1]
        rank += 1


print(soma)
