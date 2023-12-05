#!/usr/bin/python
import sys

if (len(sys.argv) < 2):
    print(f"Usage: {sys.argv[0]} input_file")
    exit(-1)

input = open(sys.argv[1]).readlines()

seeds = list(map(int, input[0][6:].split()))

origins = {}
destiny = {}
current_src, current_dst = "", ""

path = []

for line in input[1:]:
    first = line[0]
    if first.isspace():
        current_src, current_dst = "", ""
    if first.isalpha():
        category_index = line.find("map")
        category = line[:category_index].split('-')
        src, dst = category[0].strip(), category[2].strip()
        current_src, current_dst = src, dst
        origins[src] = []
        destiny[dst] = []
        path.append((src, dst))

    if first.isnumeric():
        numbers = list(map(int, line.split()))
        origins[current_src].append(range(numbers[1], numbers[1] + numbers[2]))
        destiny[current_dst].append(range(numbers[0], numbers[0] + numbers[2]))


locations = []
for seed in seeds:
    for (s, d) in path:
        old_seed = seed
        for i in range(len(origins[s])):
            a = origins[s][i].index(seed) if seed in origins[s][i] else None
            seed = seed if a is None else destiny[d][i][a]
            if a is not None:
                break

    locations.append(seed)

print(min(locations))
