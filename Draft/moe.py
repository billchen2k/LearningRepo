lenth = input()
grades = []
ave = 0
for i in range(int(lenth)):
    info = input()
    grades.append(int(info.split(' ')[1]))
ave = sum(grades) / len(grades)
s = 0
for one in grades:
    s = s + ((ave - one) ** 2)
s = s / (len(grades)-1)
print('%.2f %.2f\n' % (ave, s ** 0.5))