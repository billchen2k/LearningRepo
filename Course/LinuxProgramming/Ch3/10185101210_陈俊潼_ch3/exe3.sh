#!/bin/bash

# 对比两个目录dir1和dir2（通过参数给出），将dir2中符合下列条件的文件复制到dir1，并将每一条复制记录存储到文件record中：
# 该文件不在dir1中
# 该文件比dir1中的同名文件更新

if [ ! $# -eq 2 ]
    then 
        echo "Please input two argument."
    else
        if [[ ! -d $1  || ! -d $2 ]]
    then
        echo "Directory do not exist or this is not a directory."
    else
        for onefile in `ls -R $2`   
        do
            if [[ $onefile =~ : ]]
            then
                continue
            else
                if [ ! -e $1/$onefile ]
                then
                    cp $2/${onefile} $1/${onefile}
                    echo Copied ${2}/${onefile} to ${1}/${onefile}. >> record
                    echo Copied ${2}/${onefile} to ${1}/${onefile}.
                else
                    if [ $2/$onefile -nt $1/$onefile ]
                    then
                        cp $2/$onefile $1/$onefile
                        echo Copied ${2}/${onefile} to ${1}/${onefile}. >> record
                        echo Copied ${2}/${onefile} to ${1}/${onefile}.
                    fi
                fi

            fi
        done
    fi
fi