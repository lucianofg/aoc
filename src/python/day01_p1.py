import sys

if (len(sys.argv) < 2):
    print(f"Usage: {sys.argv[0]} input_file")
    exit(-1)

input = open(sys.argv[1]).readlines()

sum = 0
for line in input:
    numbers = []
    for ch in line:
        if ch.isdigit():
            numbers.append(int(ch))

    sum += numbers[0] * 10 + numbers[-1]

print(sum)
