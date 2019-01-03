//
//  main.c
//  Playground_C
//
//  Created by Bill Chen on 2018/10/17.
//  Copyright © 2018 Bill Chen. All rights reserved.
//

#include <stdio.h>

int convert(int weight, char unit){
    switch(unit){
        case 'g':return weight;
        case 'G':return weight;
        case 'K':return weight * 1000;
        case 'k':return weight * 1000;
        case 'O':return weight * 454.0 /16.0;
        case 'o':return weight * 454.0 /16.0;
        case 'P':return weight * 454;
        case 'p':return weight * 454;
        default:return -1;
        
    }
}

int main(){
    int i=0;
    int weight[4];
    char unit[4];
    int conweight[4];
    printf("欢迎来到货物质量单位换算系统。1千克=1000克，1镑=16盎司，1镑=454克。\n");
    for (i=0; i<4;i++){
        char c;
        printf("请输入货物的质量数（正整数）：");
        scanf("%d", &weight[i]);
        printf("请输入货物的质量单位（G g-克，K k-千克，O o-盎司，P p-镑，输入x程序退出）：");
       
        scanf("%c", &c);
        unit[i]=c;
        conweight[i] = convert(weight[i],unit[i]);
        if (unit[i]=='x' || conweight[i]==-1) return 0;
        printf("第 %d 个货物的重量为：%d克\n\n", i+1, conweight[i]);
    }
    int max = conweight[0], min = conweight[0], sum = 0, ave;
    for (i=0; i<4; i++){
        if (max < conweight[i]) max = conweight[i];
    }
    for (i=0; i<4; i++){
        if (min > conweight[i]) min = conweight[i];
    }
    for (i=0; i<4; i++) sum += conweight[i];
    ave = sum/4;
    printf("最重的货物为%d克\n最轻的货物为%d克\n总共有%d克\n平均质量为%d克\n", max, min, sum, ave);
    return 0;
}

