import random

count = 10
with open("graph10.in", "w+") as f:
    for i in range(count):
        for j in range(count):
            if (i != j):
                f.write("{} {} {}\n".format(i, j, random.randint(1, 100)))
                f.write("{} {} {}\n".format(j, i, random.randint(1, 100)))

print("Generated map for {} nodes.".format(count))