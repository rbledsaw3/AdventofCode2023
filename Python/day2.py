import sys
from collections import defaultdict
inputFile = open(sys.argv[1]).read().strip()

def part1():
    totalSum = 0
    for line in inputFile.split('\n'):
        isGamePossible = True
        id_, line = line.split(':')
        for event in line.split(';'):
            for cubes in event.split(','):
                n, color = cubes.split()
                if int(n) > {'red': 12, 'green': 13, 'blue': 14}.get(color, 0):
                    isGamePossible = False
        if isGamePossible:
            totalSum += int(id_.split()[-1])
    return totalSum

def part2():
    totalSum = 0
    for line in inputFile.split('\n'):
        id_, line = line.split(':')
        vec = defaultdict(int)
        for event in line.split(';'):
            for cubes in event.split(','):
                n, color = cubes.split()
                n = int(n)
                vec[color] = max(vec[color], n)
        print(vec)
        score = 1
        for v in vec.values():
            score *= v
        totalSum += score
    return totalSum

print(part1())
print(part2())
