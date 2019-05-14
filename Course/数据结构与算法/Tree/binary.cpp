#include <iostream>
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

template <class type>
class Binary_Tree {
      public:
      private:
	bNode<type> root;
};

main() {
}