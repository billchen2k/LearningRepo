//编译环境：macOS /clang
#include <iostream>
using namespace std;
//定义链表
typedef struct node{
    int entry;
    node *next;
    node();
    node(int _entry, node *_next = NULL);
};
node::node(){
    next = NULL;
}
node::node(int _entry, node *_next){
    entry = _entry;
    next = _next;
}
//初始化循环链表，并返回结尾一个的指针
node *initialize(int n, int m){
    node *h = new node();
    node *p = h;
    for (int i = 1; i <= n - 1; i++){
        p->entry = i;
        p->next = new node();
        p = p->next;
    }
    p->entry = n;
    p->next = h;
    return p;
}
//处理函数
node *process(node *h, int m){
    node *p = h;
    while(m---1){
        p = p->next;
    }
    cout <<"\033[31m编号为" << p->next->entry << "的人很不幸，他被扔到了海里。\033[0m" << endl;
    p->next = p->next->next;
    return p;
}
int main(int argc, char *args[]){
    cout << "\033[32m本程序用于求解残忍的约瑟夫问题。\n请输入船上的总人数 n 和他们报的数 m，并用空格分隔：\033[0m\n";
    int n, m;
    cin >> n >> m;
    while (cin.fail() || n == m)
    {
        cout << "\033[41m这样的规则玩不了这个游戏，请重新输入。\033[0m\n";
        while (cin.get() != '\n')
            ;
        cin.clear();
        cin >> n >> m;
    }
    node *p = initialize(n, m);
    node *h = p -> next;
    while(n---1){
        p = process(p, m);
    }
    cout << endl
         << "\033[46m编号为" << p->entry << "的人成功活到了最后。\nBravissimo!\033[0m";
    return 0;
}