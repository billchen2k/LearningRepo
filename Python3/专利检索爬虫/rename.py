import os
import sys
fileList = os.listdir(sys.path[0] + '/output')
newList = []
for old in fileList:
    i = 0
    new = old
    while i <= 999:
        new = new.replace('PAGE' + str(i) + '.pickle', 'PAGE_%03d.pickle' % i)
        new = new.replace('PAGE%03d.pickle' % i, 'PAGE_%03d.pickle' % i)
        # print(new)
        newList.append(new)
        i = i + 1
    print('即将重命名：'  + old + ' => ' + new)
    os.renames(sys.path[0] + '/output/' + old, sys.path[0] + '/output/' + new)
