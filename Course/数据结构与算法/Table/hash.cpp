#include <vector>
#include <iostream>
using namespace std;

class MyHashSet {
      public:
	/** Initialize your data structure here. */
	MyHashSet() {
		buckets = new vector<int>[1000];
	}

	void add(int key) {
		buckets[key % 1000].push_back(key);
	}

	void remove(int key) {
		for (int i = 0; i < buckets[key % 1000].size(); i++) {
			if (buckets[key % 1000][i] == key) {
				buckets[key % 1000].erase(buckets[key % 1000].begin() + i);
			}
		}
	}

	/** Returns true if this set contains the specified element */
	bool contains(int key) {
		for (int i = 0; i < buckets[key % 1000].size(); i++) {
			if (buckets[key % 1000][i] == key) {
				return true;
			}
		}
		return false;
	}

      private:
	vector<int> *buckets;
};

int main(){
	MyHashSet *obj = new MyHashSet();
	obj->add(1);
	obj->add(2);
	obj->add(3);
	printf("%d ", obj->contains(2));
	obj->remove(2);
	printf("%d ", obj->contains(2));
	;
}
/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */