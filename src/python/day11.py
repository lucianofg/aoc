#!/usr/bin/python
import sys


if len(sys.argv) < 2:
    print(f"Usage: {sys.argv[0]} input_file", file=sys.stderr)
    exit(1)

contents = open(sys.argv[1]).read().strip().split('\n')

galaxies = []
empty_lines = []
empty_cols = []

for i, line in enumerate(contents):
    empty = True
    for j, elem in enumerate(line):
        if elem == '#':
            galaxies.append((i, j))
            empty = False
    if empty:
        empty_lines.append(i)

asdf = {}
for g in galaxies:
    asdf[g[1]] = 1
for i in range(len(contents[0])):
    v = asdf.get(i, None)
    if v is None:
        empty_cols.append(i)
del asdf


def solve(expansion_value):
    soma = 0
    for i in range(len(galaxies)):
        for j in range(i + 1, len(galaxies)):
            x, y = galaxies[i]
            p, q = galaxies[j]
            soma += abs(x - p) + abs(y - q)

            count = 0
            for m in empty_lines:
                if x < m < p or x > m > p:
                    count += 1
            soma += count * (expansion_value - 1)

            count = 0
            for m in empty_cols:
                if y < m < q or y > m > q:
                    count += 1
            soma += count * (expansion_value - 1)

    return soma


print(solve(2), solve(1_000_000))
