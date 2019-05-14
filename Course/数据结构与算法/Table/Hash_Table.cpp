#include <cstdlib>
#include <iostream>
using namespace std;
const int hash_size = 1000;

class Hash_table {
      public:
	Hash_table() {
		for (int i = 0; i < hash_size; i++) {
			vals[i] = -1;
			keys[i] = -1;
		}
		stored = 0;
	}
	void clear() {
		for (int i = 0; i < hash_size; i++) {
			vals[i] = -1;
			keys[i] = -1;
		}
		stored = 0;
	}

	int hash(int key) {
		return key % 1000;
	}

	int insert(const int &key, const int &value) {
		int pos = hash(key);
		bool cycled = false;
		if (keys[pos] != -1 && keys[pos] == key) {
			vals[pos] = value;
			cout << "Previous value has been overwritten." << endl;
			return -1;
		}
		for (pos = hash(key); vals[pos] != -1; pos++) {
			if (pos == hash_size) {
				pos = 0;
				cycled = true;
			}
			if (pos == hash(key) && cycled == true) {
				cout << "Overflow." << endl;
				return -1;
			}
		}

		vals[pos] = value;
		keys[pos] = key;
		stored++;
		return 0;
	}

	int retrieve(const int &key) {
		int pos;
		bool cycled = false;
		for (pos = hash(key); keys[pos] != key; pos++) {
			if (pos == hash_size) {
				pos = 0;
				cycled = true;
			}
			if (cycled == true && pos == hash(key)) {
				cout << "Overflow." << endl;
				return -1;
			}
			if (vals[pos] == -1)
				break;
		}

		if (vals[pos] == -1) {
			cout << "Value not found." << endl;
			return -1;
		} else {
			return vals[pos];
		}
	}

	int remove(const int &key) {
		int pos;
		bool cycled = false;
		for (pos = hash(key);keys[pos] != key; pos++) {
			if (pos == hash_size) {
				pos = 0;
				cycled = true;
			}
			if (cycled == true && pos == hash(key)) {
				cout << "Overflow." << endl;
				return -1;
			}
			if (vals[pos] == -1)
				break;
		}
		if (vals[pos] == -1) {
			cout << "This key haven't store any values." << endl;
			return -1;
		} else {
			vals[pos] = -1;
			keys[pos] = -1;
			stored--;
		}
		return 0;
	}

	void print() {
		cout << "NO.   |KEY      |VALUE    |HASH ADDRESS" << endl;
		cout << "------+---------+---------+------------" << endl;
		for (int i = 0, printed = 0; printed < stored; i++) {
			if (keys[i] != -1) {
				printf("%-6d|%-9d|%-9d|%-6d\n", printed, keys[i], vals[i], i);
				printed++;
			}
		}
	}

      private:
	int vals[hash_size];
	int keys[hash_size];
	int stored;
};

void instruct() {
	cout << "This is a demostration program of the hash table. Here're the available commands:" << endl;
	cout << "[i] insert" << endl
	     << "[r] remove" << endl
	     << "[g] get" << endl
	     << "[c] clear" << endl
	     << "[p] print" << endl
	     << "[h] help" << endl
	     << "[q] quit" << endl;
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
	Hash_table mytable;
	char ch;
	int a, b, feedback;
	while ((ch = getCommand()) != 'q') {
		switch (ch) {
		case 'i':
			cout << "Format: [KEY] [VALUE]" << endl;
			cin >> a >> b;
			feedback = mytable.insert(a, b);
			if (feedback == 0)
				cout << "Done." << endl;
			break;
		case 'r':
			cout << "Format: [KEY]" << endl;
			cin >> a;
			feedback = mytable.remove(a);
			if (feedback == 0)
				cout << "Done." << endl;
			break;
		case 'g':
			cout << "Format: [KEY]" << endl;
			cin >> a;
			feedback = mytable.retrieve(a);
			if (feedback != -1)
				cout << "The value of key " << a << " is " << feedback << "." << endl;
			break;
		case 'c':
			mytable.clear();
			cout << "Done." << endl;
			break;
		case 'p':
			mytable.print();
			break;
		case 'h':
			instruct();
			break;
		default:
			cout << "Unknown command." << endl;
		}
	}
	cout << "Bye.<3" << endl;
	return 0;
}