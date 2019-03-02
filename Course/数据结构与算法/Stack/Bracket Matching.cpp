#include <iostream>
#include <string>
#include <stack>
const int MAXL = 1000;
using namespace std;
// class myStack
// {
//   private:
//     int data[1000];
//     int position;

//   public:
// };
int main()
{
    cout << "Please type one line including brackets(Eg. ()[]{}),\n and we weill verify if these brackets are correctly matched." << endl
         << endl
         << "input Q or q or an empty line to quit." << endl;
    char input[1000];
    char c;
    while ((c = cin.get()) != '\n')
    {
        if (toupper(c) == 'Q')
            break;
        stack<char> data;
        if (c == '(' || c == '[' || c == '{' || c == '<')
            data.push(c);
        if (c == ')' || c == ']' || c == '}' || c == '>')
        {
            if (!data.empty())
            {
                if (c - (char)data.top() != 1 && c - (char)data.top() != 2)
                {
                    cout << "Not Matched." << endl;
                    break;
                }
                else
                    data.pop();
            }
        }
        cout << "Matched." << endl;
    }
    return 0;
}
