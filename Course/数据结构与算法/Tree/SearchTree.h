#ifndef NOT_FOUND
#define NOT_FOUND -1
#define SUCCESS 1
#define EXISTED_VALUE -2
#endif
typedef int feedback;
template <typename T>
struct Node {
	T entry;
	Node *left;
	Node *right;
	Node *parent;
	Node() {
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	Node(T _entry, Node<T> *_left = NULL, Node<T> *_right = NULL, Node<T> *_parent = NULL) {
		entry = _entry;
		left = _left;
		right = _right;
		parent = _parent;
	}
};

template <class T>
class BinaryTree {
      public:
	void preOrder(void touch(T));
	void preOrder(void touch(T), Node<T> *root);
	void inOrder(void touch(T));
	void inOrder(void touch(T), Node<T> *root);
	void postOrder(void touch(T));
	void postOrder(void touch(T), Node<T> *root);
	feedback insert(T key);
	feedback insert(T key, Node<T> *&root);
	Node<T> *search(T key);
	Node<T> *search(T key, Node<T> *root);
	feedback remove(T key);
	feedback remove(T key, Node<T> *&root);
	Node<T> *predecessor(Node<T> *root);
	Node<T> *successor(Node<T> *root);
	Node<T> *maximum(Node<T> *root);
	Node<T> *minimum(Node<T> *root);
	void destroy();
	void destroy(Node<T> *&root);
	int getSize();
	BinaryTree();
	~BinaryTree();

      private:
	int size;
	Node<T> *treeRoot;
};

template <class T>
BinaryTree<T>::BinaryTree() {
	size = 0;
	treeRoot = NULL;
}

template <class T>
void BinaryTree<T>::preOrder(void touch(T)) {
	preOrder(touch, treeRoot);
}

template <class T>
void BinaryTree<T>::preOrder(void touch(T), Node<T> *root) {
	if (root != NULL) {
		touch(root->entry);
		preOrder(touch, root->left);
		preOrder(touch, root->right);
	}
}

template <class T>
void BinaryTree<T>::inOrder(void touch(T)) {
	inOrder(touch, treeRoot);
}

template <class T>
void BinaryTree<T>::inOrder(void touch(T), Node<T> *root) {
	if (root != NULL) {
		inOrder(touch, root->left);
		touch(root->entry);
		inOrder(touch, root->right);
	}
}

template <class T>
void BinaryTree<T>::postOrder(void touch(T)) {
	postOrder(touch, treeRoot);
}

template <class T>
void BinaryTree<T>::postOrder(void touch(T), Node<T> *root) {
	if (root != NULL) {
		postOrder(touch, root->left);
		postOrder(touch, root->right);
		touch(root->entry);
	}
}

template <class T>
feedback BinaryTree<T>::insert(T key) {
	return insert(key, treeRoot);
}

template <class T>
feedback BinaryTree<T>::insert(T key, Node<T> *&root) {
	int height = 0;
	Node<T> *x = root;
	Node<T> *y = root;
	while (x != NULL) {
		height++;
		y = x;
		if (key > x->entry) {
			x = x->right;
		} else if (key < x->entry) {
			x = x->left;
		} else if (x->entry == key) {
			return EXISTED_VALUE;
		}
	}
	if (y == NULL) {
		treeRoot = new Node<T>(key, NULL, NULL, NULL);
	} else if (key > y->entry) {
		y->right = new Node<T>(key, NULL, NULL, y);
	} else if (key < y->entry) {
		y->left = new Node<T>(key, NULL, NULL, y);
	}
	size++;
	return SUCCESS;
}

template <class T>
Node<T> *BinaryTree<T>::search(T key) {
	return search(key, treeRoot);
}

template <class T>
Node<T> *BinaryTree<T>::search(T key, Node<T> *root) {
	if (root == NULL || root->entry == key) {
		return root;
	} else if (key > root->entry) {
		return search(key, root->right);
	} else if (key < root->entry) {
		return search(key, root->left);
	}
}

template <class T>
Node<T> *BinaryTree<T>::maximum(Node<T> *root) {
	Node<T> *x = root;
	Node<T> *y = root;
	if (x == NULL) {
		return x;
	} else {
		while (x != NULL) {
			y = x;
			x = x->right;
		}
		return y;
	}
}

template <class T>
Node<T> *BinaryTree<T>::minimum(Node<T> *root) {
	Node<T> *x = root;
	Node<T> *y = root;
	if (x == NULL) {
		return x;
	} else {
		while (x != NULL) {
			y = x;
			x = x->left;
		}
		return y;
	}
}

template <class T>
Node<T> *BinaryTree<T>::predecessor(Node<T> *root) {
	if (root == NULL || root->left == NULL)
		return root;
	else
		return maximum(root->left);
}

template <class T>
Node<T> *BinaryTree<T>::successor(Node<T> *root) {
	if (root == NULL || root->right == NULL)
		return root;
	else
		return minimum(root->right);
}

template <class T>
feedback BinaryTree<T>::remove(T key) {
	Node<T> *ans = search(key);
	if (ans == NULL) {
		return NOT_FOUND;
	} else {
		remove(key, ans);
		size--;
		return SUCCESS;
	}
}

template <class T>
feedback BinaryTree<T>::remove(T key, Node<T> *&root) {
	Node<T> *x = root;
	Node<T> *y = predecessor(x);
	if (root->right == NULL) {
		if (root->parent == NULL) {
			treeRoot = root->left;
		} else if (root->parent->left == root) {
			root->parent->left = root->left;
		} else if (root->parent->right == root) {
			root->parent->right = root->left;
		}
		delete root;
	} else if (root->left == NULL) {
		if (root->parent == NULL) {
			treeRoot = root->right;
		} else if (root->parent->left == root) {
			root->parent->left = root->right;
		} else if (root->parent->right == root) {
			root->parent->right = root->right;
		}
		delete y;
	} else {
		root->entry = y->entry;
		if (y->parent == root) {
			root->left = y->left;
		} else {
			y->parent->right = y->left;
		}
		delete y;
	}

	return SUCCESS;
}

template <class T>
void BinaryTree<T>::destroy() {
	destroy(treeRoot);
	size = 0;
}

template <class T>
void BinaryTree<T>::destroy(Node<T> *&root) {
	if (root == NULL) {
		return;
	}
	if (root->left != NULL) {
		destroy(root->left);
	}
	if (root->right != NULL) {
		destroy(root->right);
	}
	delete root;
	root = NULL;
}

template <class T>
int BinaryTree<T>::getSize() {
	return size;
}

template <class T>
BinaryTree<T>::~BinaryTree() {
	destroy();
}
