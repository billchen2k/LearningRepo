#!/bin/bash

# 若参数为普通文件，则显示其内容
# 若参数为压缩文件，则解压缩（如同目录下有同名文件则放弃）
# 若参数为目录，则将其归档并压缩（如已有同名压缩文件则放弃）
# 若参数不存在，给出错误提示并退出

if [ ! $# -eq 1 ]
    then 
        echo "Please input an argument."
    else
        if [ ! -e $1 ]
    then
        echo "File not exist."
    else
        if [ -d $1 ]
            then
                if [ -e ${1##*/}.zip ]
                        then
                            echo "Archived file already exists, operation abandoned."
                        else
                            echo "Creating ${1##*/}.zip..."
                            zip -q ${1##*/}.zip $1/*;
                            echo "Created."
                fi
            else
                if [ ${1##*.} = "zip" ]
                    then
                        echo "Unarchiving ${1##*/}..."
                        unzip $1
                        echo "Finished."
                    else
                        echo "------------------------ File content: ------------------------"
                        cat $1
                fi
        fi
    fi
fi