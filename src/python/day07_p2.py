#!/usr/bin/python
import sys
from collections import Counter
from functools import cmp_to_key

if len(sys.argv) < 2:
    print(f"Usage: {sys.argv[0]} input_file")
    exit(1)

lines = open(sys.argv[1]).readlines()


def get_stregth(hand):
    values = Counter(hand)
    jokers = values.pop('J', 0)
    values = sorted(values.items(), reverse=True, key=lambda x: x[1])

    val = values[0][1] + jokers if len(values) > 0 else jokers
    if val == 5:
        return 6
    elif val == 4:
        return 5
    elif val == 3 and values[1][1] == 2:
        return 4
    elif val == 3:
        return 3
    elif val == 2 and values[1][1] == 2:
        return 2
    elif val == 2:
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
    'T': 9,
    '9': 8,
    '8': 7,
    '7': 6,
    '6': 5,
    '5': 4,
    '4': 3,
    '3': 2,
    '2': 1,
    'J': 0,
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
