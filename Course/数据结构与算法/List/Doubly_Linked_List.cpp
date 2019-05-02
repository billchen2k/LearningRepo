#include <iostream>
#define MAXL 1000
using namespace std;

const int success = 0;
const int overflow = 1;
const int underflow = 2;
const int rangeerror = 3;
typedef int Error_code;

template <class Node_entry>
struct Node {
	//  data members
	Node_entry entry;
	Node<Node_entry> *back;
	Node<Node_entry> *next;
	//  constructors
	Node();
	Node(Node_entry input, Node<Node_entry> *link_back = NULL,
	     Node<Node_entry> *link_next = NULL) {
		entry = input;
		back = link_back;
		next = link_next;
	}
};

template <class List_entry>
class DList {
      public:
	//  Add specifications for methods of the list ADT.
	//  Add methods to replace compiler generated defaults.
	DList() {
		count = 0;
		current_position = 0;
		current = NULL;
	}
	int size() const {
		return count;
	}
	bool full() const {
		if (count == MAXL)
			return true;
		else
			return false;
	}
	bool empty() const {
		return count == 0 ? true : false;
	}
	void clear() {
		count = 0;
		set_position(0);
	}
	void traverse(void (*visit)(List_entry &)) {
		int originPos = current_position;
		for (int i = 0; i < count; i++) {
			set_position(i);
			(*visit)(current->entry);
		}
		set_position(originPos);
	}
	Error_code retrieve(int position, List_entry &x) const {
		if (position < 0 || position > count - 1)
			return rangeerror;
		set_position(position);
		x = current->entry;
		return success;
	}
	Error_code replace(int position, const List_entry &x) {
		if (position < 0 || position > count - 1)
			return rangeerror;
		set_position(position);
		current->entry = x;
	}
	Error_code remove(int position) {
		if (position < 0 || position > count - 1)
			return rangeerror;
		if (count == 0) {
			return underflow;
		}
		set_position(position);
		Node<List_entry> *preceding, *following;
		if (position == 0) {
			current->next->back = NULL;
		} else if (position == count - 1) {
			current->back->next = NULL;
		} else {
			preceding = current->back;
			following = current->next;
			preceding->next = following;
			following->back = preceding;
		}
		count--;
		return success;
	}
	Error_code insert(int position, const List_entry &x) {
		Node<List_entry> *new_node, *following, *preceding;
		if (position < 0 || position > count - 1)
			return rangeerror;
		if (count == MAXL)
			return overflow;
		if (position == 0) {
			if (count == 0)
				following = NULL;
			else {
				set_position(0);
				following = current;
			}
			preceding = NULL;
		} else {
			set_position(position - 1);
			preceding = current;
			following = preceding->next;
		}
		new_node = new Node<List_entry>(x, preceding, following);
		if (new_node == NULL)
			return overflow;
		if (preceding != NULL)
			preceding->next = new_node;
		if (following != NULL)
			following->back = new_node;
		current = new_node;
		current_position = position;
		count++;
		return success;
	}

      private:
	//  The auxiliary function to locate list positions follows:
	void set_position(int position) const {
		if (current_position <= position)
			for (; current_position != position; current_position++)
				current = current->next;
		else
			for (; current_position != position; current_position--)
				current = current->back;
	}

      protected:
	//  Data members for the doubly-linked list implementation follow:
	int count;
	mutable int current_position;
	mutable Node<List_entry> *current;
};

template <class entry>
void printer(entry x) {
	std::cout << x << " ";
}

char getCommand() {
	cout << ">> ";
	char ch;
	ch = cin.get();
	while(ch == '\n'){
		ch = cin.get();
	}
	return ch;
}

void response(int code) {
	switch (code) {
	case success:
		cout << "Done." << endl;
		break;
	case rangeerror:
		cout << "Error: Range error." << endl;
		break;
	case underflow:
		cout << "Error: Underflow." << endl;
		break;
	case overflow:
		cout << "Error: Overflow." << endl;
		break;
	default:
		cout << "Done." << endl;
	}
}

void instruct(){
	cout << "This is a demostration program for doubly linked list." << endl
	     << "Here're the available commands:" << endl
	     << endl
	     << "[c] clear" << endl
	     << "[s] size" << endl
	     << "[e] empty" << endl
	     << "[f] full" << endl
	     << "[r] retrieve" << endl
	     << "[R] replace" << endl
	     << "[d] delete " << endl
	     << "[i] insert" << endl
	     << "[t] traverse (pointed to func printer)" << endl
	     << "[h] help" << endl
	     << "[q] quit" << endl;
}
int main() {
	DList<int> mylist;
	int x = 3;
	char ch;
	instruct();
	while ((ch = getCommand()) != 'q') {
		int a, b;
		switch (ch) {
		case 'c':
			mylist.clear();
			cout << "Done." << endl;
			break;
		case 's':
			cout << mylist.size() << endl;
			break;
		case 'e':
			cout << (mylist.empty() ? "True." : "False.") << endl;
			break;
		case 'f':
			cout << (mylist.full() ? "True." : "False.") << endl;
			break;
		case 'r':
			cout << "Input format: [POSITION]" << endl
			     << ">> ";
			cin >> a;
			if (!cin.fail()) {
				int feedback = mylist.retrieve(a, b);
				if (feedback == success) {
					cout << b << endl;
					break;
				} else {
					response(feedback);
					break;
				}
			} else {
				cout << "Invalid input.";
				break;
			}
		case 'R':
			cout << "Input format: [POSITION] [VALUE]" << endl
			     << ">> ";
			cin >> a >> b;

			if (!cin.fail()) {
				int feedback = mylist.replace(a, b);
				response(feedback);
				break;
			} else {
				cout << "Invalid input.";
				break;
			}
		case 'd':
			cout << "Input format: [POSITION]" << endl
			     << ">> ";
			cin >> a;
			if (!cin.fail()) {
				int feedback = mylist.remove(a);
				response(feedback);
				break;
			} else {
				cout << "Invalid input.";
				break;
			}
		case 'i':
			cout << "Input format: [POSITION] [VALUE]" << endl
			     << ">> ";
			cin >> a >> b;
			if (!cin.fail()) {
				int feedback = mylist.insert(a, b);
				response(feedback);
				break;
			} else {
				cout << "Invalid input.";
				break;
			}
		case 't':
			mylist.traverse(printer);
			cout << endl
			     << "Done. - mylist.traverse(printer)" << endl;
			break;
		case 'x':
			cout << "Bye." << endl;
			return 0;
		case 'h':
			instruct();
			break;
		default:
			cout << "Unknown Command." << endl;
		}
	}
	return 0;
}