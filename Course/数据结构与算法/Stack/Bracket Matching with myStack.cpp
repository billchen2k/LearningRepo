#include <iostream>
#include <string>
#include <stack>
const int MAXL = 1000;
using namespace std;
char left_bracket[5] = {'(', '[', '{', '<', '\0'};
char right_bracket[5] = {')', ']', '}', '>', '\0'};
class myStack{
    private:
        char data[1000];
        int pos = 0;
    public:
        void push(char ch){
            data[pos] = ch;
            pos++;
        }
        void pop(){
            pos--;
        }
        char top(){
            return data[pos-1];
        }
        int empty(){
            return pos == 0 ? 1 : 0;
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
        int flag = -1;
        //stack<char> data;
        myStack data;
        for (int i = 0; i < strlen(input); i++){
            if (is_subset(input[i], left_bracket)){
                data.push(input[i]);
            }
            else if (is_subset(input[i], right_bracket)){
                if (!data.empty()) {
                    if ((is_subset(data.top(), left_bracket)) == (is_subset(input[i], right_bracket))) {
                        flag = 1;
                        data.pop();
                    }
                    else{
                        flag = 0;
                        break;
                    }
             }
                else{
                    flag = 0;
                    break;
                }
            }
        }
        if (!data.empty())
            flag = 0;
        if (data.empty() && flag == -1)
            flag = 1;
        printer(flag);
    }
}