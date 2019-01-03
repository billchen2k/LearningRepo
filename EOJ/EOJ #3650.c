#include <stdio.h>

int main() {
    char input1[100001], input2[100001];
    int i = 0;
    while ((input1[i] = getchar()) != '\n') i++;
    input1[i] = '\0';    i = 0;
    while ((input2[i] = getchar()) != '\n') i++;
    input2[i] = '\0';
    int length = i - 1, biggerflag = 2;
    for (i = 0; i <=length; i++) {
        if (input1[i] > input2[i]) biggerflag = 1;
        else if (input1[i] < input2[i]) break;
    }
    if (biggerflag == 1) {
        char temp[100001];
        for (i = 0; i <= length; i++) {
            temp[i] = input1[i]; input1[i] = input2[i]; input2[i] = temp[i];
        }
        
    }
    for (i = length; i >= 0; i--) {
        if (input1[i] != 'Z') {
            (input1[i])++; break;
        }
        else if (input1[i] == 'Z') {
            input1[i] = 'A';
        }
    }
    printf("%s", input1);
    getchar();
}


