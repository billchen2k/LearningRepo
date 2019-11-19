#!/bin/bash

# 首行显示列表标题：List of Users
# 标题后输出分割线
# 每行只显示用户名、组名和使用的默认shell路径，并在最上方显示字段名称，如UserName，GroupName，Shell Path，注意字段名与内容要按列对齐
# 在列表下方输出分割线
# 在分割线下方输出带提示的统计信息，统计每种shell路径出现的次数

# groupNames=()
# groupNames=`cat /etc/group | sed '/^#/d' | awk -F ':' '{print ($1) }'`

cat /etc/passwd | sed '/^#/d' > temp.out
awk -F ':' '
    BEGIN{
        printf "List of Users\n";
        printf "--------------------------------------------------------------------------------------\n"
        printf "%-30s | %-30s | %-20s\n","USERNAME","GROUP NAME","SHELL PATH";
        printf "-------------------------------+--------------------------------+---------------------\n"
    } 
    NR==FNR {
        group[$3]=$1
    }
    NR>FNR {
        count[$7]++;
        printf "%-30s | %-30s | %-20s\n", $1, group[$4], $7
    }
    END{
        printf "--------------------------------------------------------------------------------------\n"
        printf "Shell Counter:\n"
        for (one in count) {
            printf "The shell [%s] appeared %s times.\n", one, count[one];
        }
    }
' /etc/group temp.out > awk1.out;
echo "Finished. See awk1.out."
rm temp.out