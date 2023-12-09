#!/usr/bin/python
import sys

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
    lasts = []
    while not all_zeros(numbers):
        lasts.append(numbers[-1])
        for i in range(0, len(numbers) - 1):
            results.append(numbers[i+1] - numbers[i])
        numbers = results
        results = []
    soma += sum(lasts)

print(soma)
