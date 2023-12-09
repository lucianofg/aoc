#!/usr/bin/python
import sys
from numpy import lcm

if len(sys.argv) < 2:
    print(f"Usage: {sys.argv[0]} input_file", file=sys.stderr)
    exit(1)

contents = open(sys.argv[1]).readlines()

instructions = contents[0]
max_instructions = len(instructions[:-1])
values = {}
queue = []

for line in contents[2:]:
    a, tmp = line.split("=")
    b, c = tmp[2:-2].split(",")
    a, b, c = a.strip(), b.strip(), c.strip()
    values[a] = (b, c)

    if a.endswith("A"):
        queue.append(a)


z_index = []
for elem in queue:
    instruction_index = 0
    count = 0
    current = elem
    while not current.endswith("Z"):
        if instruction_index >= max_instructions:
            instruction_index = 0
        ch = instructions[instruction_index]
        count += 1
        instruction_index += 1
        if ch == 'L':
            current = values[current][0]
        elif ch == 'R':
            current = values[current][1]
    z_index.append(count)

print(lcm.reduce(z_index))
