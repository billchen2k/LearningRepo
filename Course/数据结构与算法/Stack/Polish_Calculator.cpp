#include <iostream>
#include <stack>
#include <string.h>
const int NO_ERROR = 0;
const int ERROR_UNDERFLOW = 1;
const int ERROR_OVERFLOW = 2;
const int ERROR_MAXNUMBER = 3;
const int ERROR_UNKNOWNCOMMAND = 4;
const int ERROR_INVALIDINPUT = 5;
using namespace std;
int isNumber(char * ch){
    bool flag=true;
    int pointCount = 0;
    for (int i = 0; i < strlen(ch); i++){
        if (!((ch[i]>= '0' && ch[i] <='9' )|| ch[i] == '.'))
            flag = false;
        if (ch[i] == '.')
            pointCount++;
        if (pointCount>1){
            flag = false;
        }
    }
    return flag;
}
int operate(char command, stack<double> &num){
    double tempA, tempB;
    int errorStatus;
    switch (command){
        case '+':
            if (num.size() >= 1){
                tempA = num.top();
                num.pop();
                tempB = num.top();
                num.pop();
                num.push(tempA + tempB);
            }
            else{
                return ERROR_UNDERFLOW;
            }
            break;
        case '-':
            if (num.size() >= 1){
                tempA = num.top();
                num.pop();
                tempB = num.top();
                num.pop();
                num.push(tempA - tempB);
            }
            else{
                return ERROR_UNDERFLOW;
            }
            break;
        case '*':
            if (num.size() >= 1){
                tempA = num.top();
                num.pop();
                tempB = num.top();
                num.pop();
                num.push(tempA * tempB);
            }
            else{
                return ERROR_UNDERFLOW;
            }
            break;
        case '/':
            if (num.size() >= 1){
                tempA = num.top();
                num.pop();
                tempB = num.top();
                num.pop();
                num.push(tempA / tempB);
            }
            else{
                return ERROR_UNDERFLOW;
            }
            break;
        case '=':
            if (num.size() != 0)
                cout << num.top() << endl;
            else{
                return ERROR_UNDERFLOW;
            }
            break;
        default:
            return ERROR_UNKNOWNCOMMAND;
    }
    return 0;
}
void instruct(){
    cout << "Welcome to the Polish Calculator." << endl
         << "Now you can enter a line of valid command, press <enter> to operate." << endl
         << "Valid commands are [+] [-] [*] [/] [=] and numbers."
         << "Enter x or X to clean the stack, Q or q to quit." << endl;
}
void sayError(int errorCode){
    switch (errorCode){
        case ERROR_UNDERFLOW:
            cout << "Error: Stack underflow." << endl;
            break;
        case ERROR_OVERFLOW:
            cout << "Error: Stack overflow." << endl;
            break;
        case ERROR_MAXNUMBER:
            cout << "Error: Numbers are too large." << endl;
            break;
        case ERROR_UNKNOWNCOMMAND:
            cout << "Error: Unknown operator." << endl;
            break;
        case ERROR_INVALIDINPUT:
            cout << "Error: Invalid input." << endl;
            break;
        default:
            break;
    }
}
int main(){
    instruct();
    stack<double> numbers;
    bool stopflag = false;
    char tempCommand[1000];
    char tempNumber[30];
    while (cin >> tempCommand && !stopflag){
        if (isNumber(tempCommand)){
            numbers.push(atof(tempCommand));
        }
        else{
            if (strlen(tempCommand)!=1){
                sayError(ERROR_INVALIDINPUT);
            }
            else if (toupper(tempCommand[0]) == 'X'){
                while (!numbers.empty())
                    numbers.pop();
            }
            else if (int status = operate(tempCommand[0], numbers) != 0)
                sayError(status);
        }
    }
}