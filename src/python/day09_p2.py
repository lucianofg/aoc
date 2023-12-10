#!/usr/bin/python
import sys
from functools import reduce

if len(sys.argv) < 2:
    print(f"Usage: {sys.argv[0]} input_file", file=sys.stderr)
    exit(1)

contents = open(sys.argv[1]).readlines()


def all_zeros(tmp):
    for i in tmp:
        if i != 0:
            return False
    if len(tmp) == 0:
        False
    return True


soma = 0
for line in contents:
    numbers = list(map(int, line.split()))
    results = []
    firsts = []
    while not all_zeros(numbers):
        firsts.append(numbers[0])
        for i in range(0, len(numbers) - 1):
            results.append(numbers[i+1] - numbers[i])
        numbers = results
        results = []
    next = reduce(lambda x, y: y - x, reversed(firsts))
    soma += next

print(soma)
