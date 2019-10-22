#!/bin/bash

# 由用户输入一组数（以end表示输入结束），输出这些数的和，结果保留2位小数。要求使用函数做输入类型检查，并给出错误提示信息。

let sum=0;
for arg in $*                                          
do
    if [ $arg = "end" ];
        then break;
    else
        if grep -q '^[[:digit:]]*$' <<< "${arg/./}";then 
            sum=$(echo "scale=2;$sum+$arg" | bc)
            # echo $sum 
        else 
            echo $arg is not a number.;
        fi 
    fi
done
echo "SUM: $sum"