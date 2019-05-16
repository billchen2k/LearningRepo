// HashTable.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
using namespace std;

struct key_value {
	int key; //默认权限是public
	string value;
	key_value() { //初始值选取不太好
		key = 0;
		value = "0";
	}
};

class Batch { //类设计不完善，应该是可以动态添加桶的长度，所以用链表最好。我这里懒，直接用数组模拟。
      public:
	Batch() {
		current_batchsize = -1;
	}
	int current_batchsize;

      public:
	key_value k_v[50];
};

class HashTable {
      public:
	HashTable() {
		init();
	}
	Batch *batch[10];

      public:
	void init();
	int hash(int);
	key_value lookup(int);
	void insert(int, string);
};
void HashTable::init() {
	for (int i = 0; i < 10; ++i) {
		batch[i] = new Batch();
	}
}
int HashTable::hash(int input) {
	return input % 10;
}
key_value HashTable::lookup(int key) {
	int batch_num = hash(key);
	for (int i = 0; i < 50; ++i) {
		if (batch[batch_num]->k_v[i].key == key) {
			return batch[batch_num]->k_v[i];
		}
	}
}
void HashTable::insert(int key, string value) {
	int batch_num = hash(key);
	int current_batchsize = batch[batch_num]->current_batchsize;
	//有问题,若是有相同的key，应该是改变他的value
	batch[batch_num]->k_v[current_batchsize + 1].key = key;
	batch[batch_num]->k_v[current_batchsize + 1].value = value;
	batch[batch_num]->current_batchsize++;
}

int main() {

	HashTable my_hash_table;
	int a = 1, b = 2, c = 3, d = 11;
	my_hash_table.insert(a, "a");
	my_hash_table.insert(b, "b");
	my_hash_table.insert(c, "c");
	my_hash_table.insert(d, "d");
	cout << "batch_num:" << my_hash_table.hash(a) << "	key:" << my_hash_table.lookup(a).key << "	value:" << my_hash_table.lookup(a).value << endl;
	cout << "batch_num:" << my_hash_table.hash(b) << "	key:" << my_hash_table.lookup(b).key << "	value:" << my_hash_table.lookup(b).value << endl;
	cout << "batch_num:" << my_hash_table.hash(c) << "	key:" << my_hash_table.lookup(c).key << "	value:" << my_hash_table.lookup(c).value << endl;
	cout << "batch_num:" << my_hash_table.hash(d) << "	key:" << my_hash_table.lookup(d).key << "	value:" << my_hash_table.lookup(d).value << endl;
	return 0;
}
