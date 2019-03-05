#include <iostream>
#include <string>
const int MAXL = 1000;
const int ERROR_OVERFLOW = 1;
const int ERROR_UNDERFLOW = 2;
using namespace std;
char left_bracket[5] = "([{<";
char right_bracket[5] = ")]}>";
class myStack{
  private:
    char data[MAXL];
    int pos = 0;
  public:
    int push(char ch){
        if (pos == MAXL){
            cout << "ERROR: OVERFLOW." << endl;
            return ERROR_OVERFLOW;
        }
        else{
            data[pos] = ch;
            pos++;
            return 0;
        }
    }
    int pop(){
        if (pos == 0){
            cout << "ERROR: UNDERFLOW." << endl;
            return ERROR_UNDERFLOW;
        }
        else{
            pos--;
            return 0;
        }
    }
    char top(){
        if (pos == 0){
            cout << "ERROR: UNDERFLOW." << endl;
            return ERROR_UNDERFLOW;
        }
        else
            return data[pos - 1];
    }
    int empty(){
        return pos == 0 ? 1 : 0;
    }
    int size(){
        return pos;
    }
    void clear(){
        pos = 0;
    }
};
int is_subset(char src, char *dst)
{
    int i;
    for (i = 0; i < strlen(dst); i++){
        if (src == dst[i])
            return i + 1;
    }
    return 0;
}
void printer(int flag){
    cout << (flag ? "Matched.\n" : "Not Matched.\n");
}
int main(){
    cout << "Please type one line including brackets(Eg. ()[]{} & <>),\n and we weill verify if these brackets are correctly matched." << endl
         << endl
         << "input Q or q or an empty line to quit." << endl;
    char input[MAXL];
    while (cin.getline(input, MAXL) && !cin.fail() 
            && !((toupper(input[0]) == 'Q' && input[1] == '\0') || input[0] == '\0')) {
        int flag = -1, flagFinal = 1;
        //stack<char> data;
        myStack data;
        myStack wrong;
        for (int i = 0; i < strlen(input); i++){
            if (is_subset(input[i], left_bracket)){
                data.push(input[i]);
                wrong.push(i + 1);
            }
            else if (is_subset(input[i], right_bracket)){
                if (!data.empty()) {
                    if ((is_subset(data.top(), left_bracket)) == (is_subset(input[i], right_bracket))) {
                        flag = 1;
                        data.pop();
                        wrong.pop();
                    }
                    else{
                        flagFinal = 0;
                        wrong.push(i + 1);
                    }
             }
                else{
                    flagFinal = 0;
                    wrong.push(i + 1);
                }
            }
        }
        if (!data.empty()){
            flag = 0;
        }
        if (data.empty() && flag == -1)
            flag = 1;
        if(flag==1 && flagFinal!=0){
            cout << "Matched." << endl;
        }
        else{
            cout << "Not Matched." << endl
                 << "Dismatched Position: ";
            while (!wrong.empty()){
                printf("%d ", wrong.top());
                wrong.pop();
            }
            cout << endl;
        }
    }
    return 0;
}