# Calculate k-mean of given points.

import math

x = [[0, 2], [0, 0], [1, 0], [5, 0], [5, 2]]
c1 = [2, 2]
c2 = [5, 5]
round = 10
x = [[3, 1], [3, 2], [4, 1], [4, 2], [1, 3], [1, 4], [2, 3], [2, 4]]
c1 = [0, 4]
c2 = [0, 3]
for r in range(round):
    d1 = []
    d2 = []
    s1 = []
    s2 = []
    for i in range(len(x)):
        d1.append(math.sqrt((x[i][0] - c1[0]) ** 2) + math.sqrt((x[i][1] - c1[1]) ** 2))
        d2.append(math.sqrt((x[i][0] - c2[0]) ** 2) + math.sqrt((x[i][1] - c2[1]) ** 2))
    for i in range(len(x)):
        if (d1[i] < d2[i]):
            s1.append(i)
        else:
            s2.append(i)
    c1x = 0
    c1y = 0
    for i in range(len(s1)):
        c1x = c1x + x[s1[i]][0]
        c1y = c1y + x[s1[i]][1]
    c1x = c1x / len(s1)
    c1y = c1y / len(s1)
    c2x = 0
    c2y = 0
    for i in range(len(s2)):
        c2x = c2x + x[s2[i]][0]
        c2y = c2y + x[s2[i]][1]
    c2x = c2x / len(s2)
    c2y = c2y / len(s2)
    c1 = [c1x, c1y]
    c2 = [c2x, c2y]
    print("ROUND {}: \n\t S1 = [{}], S2 = [{}], !c1 = ({}), !c2 = ({})\n\t d1 = [{}], d2= [{}]"
          .format(str(r), ", ".join(str(v) for v in s1), ", ".join(str(v) for v in s2),
                  ", ".join(str(v) for v in c1), ", ".join(str(v) for v in c2),
                  ", ".join(str(v) for v in d1), ", ".join(str(v) for v in d2)))
