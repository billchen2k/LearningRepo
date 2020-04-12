#include <iostream>

using namespace std;

class template {
      private:
	/* data */
      public:
	template(/* args */);
	~template();
};

template ::template(/* args */) {
}

template ::~template() {
}

template <class T>
class Data {

      private:
	T element;

      public:
	Data(T _element) {
		element = _element;
	}
	void print() {
		cout << element << endl;
	}
};

int main() {
	Data<string> data = Data(string("Hello!"));
	data.print();
}

template <class T>
T get() {
}