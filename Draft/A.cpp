#include <iostream>
using namespace std;
struct Node {
	int data;
	Node *next;
	Node();
	Node(int item, Node *address = NULL); //initialize
};
Node::Node() {
	next = NULL;
}
Node::Node(int item, Node *address) {
	data = item;
	next = address;
}

Node *deletesame(Node *h) {
	Node *cur = h;
	while (cur != NULL) {
		Node *r = cur;

		while (r->next != NULL) {
			if (r->next->data == cur->data)
				r->next = r->next->next;
			else
				r = r->next;
		}
		cur = cur->next;
	}
	return h;
}

int main() {
	int n, num;
	cin >> n;
    cin >> num;
	Node *head = new Node(num);
	Node *p = head;

	for (int i = 1; i < n; i++) {
		cin >> num;
		Node *newptr = new Node(num);
		p->next = newptr;
		p = newptr;
	}
	p->next = NULL;
	Node *v = deletesame(head);
	while (v != NULL) {
		cout << v->data << " ";
		v = v->next;
	}
	// while (head) {
	// 	Node *t = head;
	// 	head = head->next;
	// 	delete t;
	// }
	// free(head);
	// //delete p;
	// delete v;
    while(head->next != NULL){
	    Node *p = head;
	    p = head->next;
	    free(head);
	    head = p;
    }
	return 0;
}