#include <iostream>
#include <stdio.h>
#include "SearchTree.h"
using namespace std;

void instruct() {
	cout << "This is a demostration program for Binary Search Tree.\nHere're the available commands:" << endl;
	cout << "[P] preOrder" << endl
	     << "[I] inOrder" << endl
	     << "[Q] postOrder" << endl
	     << "[i] insert" << endl
	     << "[s] search" << endl
	     << "[r] remove" << endl
	     << "[d] destroy" << endl
	     << "[S] size" << endl
	     << "[h] help" << endl
	     << "[q] quit" << endl;
}

template <typename T>
void printer(T data) {
	cout << data << " ";
}

char getCommand() {
	cout << ">> ";
	char ch;
	ch = cin.get();
	while (ch == '\n') {
		ch = cin.get();
	}
	return ch;
}

int main() {
	instruct();
	char ch;
	int a, b, feedback;
	Node<int> *pback;
	BinaryTree<int> Tree;
	while ((ch = getCommand()) != 'q') {
		switch (ch) {
		case 'P':
			Tree.preOrder(printer);
			cout << "\nDone.\n";
			break;
		case 'I':
			Tree.inOrder(printer);
			cout << "\nDone.\n";
			break;
		case 'Q':
			Tree.postOrder(printer);
			cout << "\nDone.\n";
			break;
		case 'i':
			cout << "FORMAT: [KEY]" << endl;
			cin >> a;
			feedback = Tree.insert(a);
			if (feedback == EXISTED_VALUE) {
				cout << "This key already exists." << endl;
			} else {
				cout << "Done." << endl;
			}
			break;
		case 's':
			cout << "FORMAT: [KEY]" << endl;
			cin >> a;
			pback = Tree.search(a);
			if (pback != NULL) {
				printf("%d exists in the tree. (Address: %p)\n", a, pback);
			} else {
				printf("%d doesn't exist in the tree.\n", a);
			}
			break;
		case 'r':
			cout << "FORMAT: [KEY]" << endl;
			cin >> a;
			feedback = Tree.remove(a);
			if (feedback == NOT_FOUND) {
				printf("%d doesn't exist in the tree, can't be removed.\n", a);
			} else {
				printf("Done.\n");
			}
			break;
		case 'd':
			Tree.destroy();
			cout << "Done." << endl;
			break;
		case 'S':
			cout << "Size of the tree: " << Tree.getSize() << endl;
			break;
		case 'h':
			instruct();
			break;
		default:
			cout << "Unknown command. Please try again." << endl;
		}
	}
	cout << "Bye.<3" << endl;
	return 0;
}