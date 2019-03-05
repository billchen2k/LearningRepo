#include <iostream>
#include <stack>
#include <string.h>
const int NO_ERROR = 0;
const int ERROR_UNDERFLOW = 1;
const int ERROR_OVERFLOW = 2;
const int ERROR_MAXNUMBER = 3;
const int ERROR_UNKNOWNCOMMAND = 4;
using namespace std;
bool isOperator(char * ch){
    
}
int operate(char command, stack<double> &num){
    double tempA, tempB;
    int errorStatus;
    switch (command){
        case '=':
            cout << num.top() << endl;
            break;
        case '+':
            if (num.size() >= 1){
                tempA = num.top();
                num.pop();
                tempB = num.top(); 
                num.push()
            }
            else{
                cout << "ERROR: STACK UNDERFLOW.";
                return ERROR_UNDERFLOW;
            }
        case default:
            return ERROR_UNKNOWNCOMMAND;
    }
    void instruct()
    {
        cout << "Welcome to the Polish Calculator." << endl
             << "Now you can enter a line of valid command, press <enter> to operate." << endl
             << "Valid commands are [+] [-] [*] [/] [=] and numbers."
             << "Enter Q or q to quit.";
}
int main(){
    instruct();
    stack<double> numbers;
    bool stopflag = false;
    char tempCommand[30];
    while (cin >> tempCommand && !stopflag){
        if (isOperator(tempCommand)){
            int status = operate(tempCommand[0], numbers);
            case status
        }
        else{
            numbers.push(atof(tempCommand));
        }
    }
}