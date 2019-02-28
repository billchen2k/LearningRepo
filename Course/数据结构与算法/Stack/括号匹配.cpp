#include <iostream>
#include <string>
#include <stack>
const int MAXL = 1000;
using namespace std;
class myStack
{
  private:
    int data[1000];
    int position;
  public:
};
int main()
{
    cout << "Please type one line including brackets(Eg. ()[]{}),\n and we weill verify if these brackets are correctly matched." << endl
         << endl
         << "input Q or q or an empty line to quit." << endl;
    char input[1000];
    while (cin.getline(input, MAXL) && input[0] != '\0')
    {
        if (toupper(input[0] == 'q' && input[1] == '\0'))
            break;
        stack<char> data;
        int i;
        for (i = 0; i < strlen(input); i++)
        {
            if (input[i] == '(' || input[i] == ')' || input[i] == '[' || input[i] == ']' || input[i] == '{' || input[i] == '}')
            {
                data.push(input[i]);
            }
        }
        int a = 0, b = 0, c = 0;
        while (!data.empty())
        {
            if (data.top() == ')')
                a++;
            if (data.top() == '(')
                a--;
            if (data.top() == ']')
                b++;
            if (data.top() == '[')
                b--;
            if (data.top() == '{')
                c++;
            if (data.top() == '}')
                c++;
            data.pop();
        }
        if (a == 0 && b == 0 && c == 0)
            cout << "Matched." << endl;
        else
            cout << "Not Matched." << endl;
    }
    return 0;
}
