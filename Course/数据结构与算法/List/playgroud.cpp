#include <iostream>
#include <stack>
#include <list>
typedef int errorCode;
using namespace std;
struct node{
    char entry;
    node *next;
    node();
    node(char item, node *add_on = NULL);
};
node::node(){
    next = NULL;
}
node::node(char item, node *add_on){
    entry = item;
    next = add_on;
}
int main()
{
    node first_node('a');         // node first_node stores data 'a' .
    node *p0 = &first_node;       // p0 points to first node .
    node *p1 = new node('b');     // A second node storing 'b' is created.
    p0->next = p1;                // The secondnode is linked after first node .
    node *p2 = new node('c', p0); // A thirdnode storing 'c' is created.
                                  // The thirdnode links back to the first node,*p0 .
    p1->next = p2;                // The thirdnode is linked after the secondnode
    cout << "The char p0 points to is:" << p0->entry << endl;
    cout << "The char p1 points to is:" << p0->next->entry << endl;
    cout << "The char p2 points to is:" << p0->next->next->entry << endl;
    return 0;
}
