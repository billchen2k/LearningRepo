# 生成地图的 Python 脚本

import random
import sys

def generate(count):
    count = int(count)
    with open("graph{}.in".format(count), "w+") as f:
        for i in range(count):
            for j in range(count):
                if (i != j):
                    f.write("{} {} {}\n".format(i, j, random.randint(1, 100)))
                    f.write("{} {} {}\n".format(j, i, random.randint(1, 100)))

    print("Generated map for {} nodes.".format(count))


if __name__ == "__main__":
    print(len(sys.argv))
    if (len(sys.argv) == 1):
        print("Used to generate map. Usage: generatemap.py <node count>.")
    else:
        generate(sys.argv[1])
