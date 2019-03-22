
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;
typedef struct NODE{
    int entry;
    NODE *next;
    NODE *prev;
    NODE();
    NODE(int _entry, NODE *_next = NULL, NODE *_prev = NULL);
};
NODE::NODE(){
    prev = NULL;
    prev = NULL;
}
NODE::NODE(int _entry, NODE *_next, NODE *_prev){
    entry = _entry;
    next = _next;
    prev = _prev;
}
int main(int argc, char *args[])
{
    cout << "\033[42m本程序用于求解约瑟夫问题。请输入n和m并用空格分隔：\033[0m\n";
    int n, m;
    cin >> n >> m;
    while (cin.fail()){
        cout << "\033[31m输入无效，请重试。\033[0m\n";
        while(cin.get()!='\n')
            ;
        cin >> n >> m;
    }
    NODE *h = new NODE('0');
    for (int i = 0; i < n; i++)
    {
        p->next = new NODE;
        p->next->prev = p;
        p = p->next;
    }
    p->next = h;
    h->prev = p;
}