#include <iostream>
#include <string.h>
using namespace std;
int order[5] = {0, 2, 4, 3, 1};
void alter(char * toalter){
    char temp[6];
    strcpy(temp, toalter);
    for (int i = 0; i < 5; i++)
    {
        *(toalter + i) = temp[order[i]];
    }
    toalter[5] = '\0';
}
char * process(char * toprocess){
    long int temp = atoi(toprocess);
    long int output = 1;
    for (int i = 0; i < 5; i++)    {
        output = output * temp % 100000;
    }
    char coutput[6] = {0};
    
}
int main(){
    int len;
    char input[6];
    cin >> len;
    for (int i = 0; i < len;i++){
        cin >> input;
        alter(input);
        cout << "case #" << i << ":" << endl;
        printf("%5d\n", process(input));
    }
    return 0;
}
/* BROKEN PART
int main()
{
    int len, i = 0;
    cin >> len;
    for (; i < len; i++)
    {
        char input[6];
        cin >> input;
        char process1[6], process3[20], process4[7], process6[6], process7[6];
        process1[0] = input[0];
        process1[1] = input[2];
        process1[2] = input[4];
        process1[3] = input[3];
        process1[4] = input[1];
        process1[5] = '\0';
        long int process2, process5;
        process2 = (long)atoi(process1) * (long)atoi(process1) * (long)atoi(process1);
        sprintf(process3, "%ld", process2);
        int j, k;
        for (j = (int)strlen(process3) - 6, k = 0; j < strlen(process3); j++, k++)
        {
            process4[k] = process3[j];
        }
        process4[6] = '\0';
        process5 = (long)atoi(process4) * (long)atoi(process1) * (long)atoi(process1);
        sprintf(process6, "%ld", process5);
        for (j = (int)strlen(process6) - 5, k = 0; j < strlen(process6); j++, k++)
        {
            process7[k] = process6[j];
        }
        process7[5] = '\0';
        cout << "case #" << i << ":" << endl;
        cout << process7 << endl;
    }
    return 0;
}
*/