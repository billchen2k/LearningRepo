//
//  main.c
//  Playground_C
//
//  Created by Bill Chen on 2018/10/17.
//  Copyright © 2018 Bill Chen. All rights reserved.
//

#include <stdio.h>

int judging(int year){
   if(year % 400==0) return1;
   elseif (year % 4==0 && year % 100 != 0) return1;
   elsereturn0;
}

int main(){
   int endyear, mycount, otherscount, income, outcome;
   printf("P is born in 2000.2.29, he has birthday party only at leap years. Everytime he have a birthday, he recieves 100 dollars from his 7 friends who are all born in the other months. While when they have their birthday, P gives them 20 dollars each. Now let's do some calculations.\n");
   while(printf("Please input the end year:\n") && scanf("%d",&endyear) && endyear>=2000){
       int yearnow=2000;
       for (mycount=0,otherscount=0;yearnow<=endyear;yearnow++){
           if (judging(yearnow)==1) mycount ++;
           otherscount++;
       }
       income = 7 * 100 * mycount; outcome = 7 * 20 * (otherscount);
       printf("Sine born, P have only celebrated %d birthdays.\n",mycount);
       printf("He gave his friend %d dollars intotal,\n", outcome);
       printf("And %d dollars in return.\n\n", income);
   }
   return0;
}

