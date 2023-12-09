#!/usr/bin/python
import sys

if len(sys.argv) < 2:
    print(f"Usage: {sys.argv[0]} input_file", file=sys.stderr)
    exit(1)

contents = open(sys.argv[1]).readlines()

instructions = contents[0]

values = {}

for line in contents[2:]:
    a, tmp = line.split("=")
    b, c = tmp[2:-2].split(",")
    a, b, c = a.strip(), b.strip(), c.strip()

    values[a] = (b, c)

count = 0
max_lines = len(instructions[:-1])
current = "AAA"
i = 0

while True:
    if i >= max_lines:
        i = 0
    ch = instructions[i]
    if current == "ZZZ":
        break
    if ch == 'L':
        current = values[current][0]
    elif ch == 'R':
        current = values[current][1]

    count += 1
    i += 1


print(count)
