#include <iostream>
#include <stdio.h>
using namespace std;
template <class type>
struct bNode{
	type entry;
	bNode *left;
	bNOde *right;
    bNode(){
	    left = NULL;
	    right = NULL;
    }
    bNode(type _entry, bNode* _left = NULL, bNode* _right = NULL){
	    entry = _entry;
	    left = left;
	    right = _right;
    }
};

template <typename T>
class Binary_Tree {
      public:
      private:
	bNode<type> root;
};

main() {
}