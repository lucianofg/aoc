import sys

if (len(sys.argv) < 2):
    print(f"Usage: {sys.argv[0]} input_file")
    exit(-1)

input = open(sys.argv[1]).readlines()

sum = 0
for line in input:
    numbers = []
    numbers_set = {
        1: "one",
        2: "two",
        3: "three",
        4: "four",
        5: "five",
        6: "six",
        7: "seven",
        8: "eight",
        9: "nine",
    }
    for i, ch in enumerate(line):
        if ch.isdigit():
            numbers.append(int(ch))
            continue
        for key, value in numbers_set.items():
            if line[i:].startswith(value):
                numbers.append(key)

    sum += numbers[0] * 10 + numbers[-1]

print(sum)
