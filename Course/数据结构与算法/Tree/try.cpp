#include <iostream>
using namespace std;

int print(int a){
	printf("%d", a);
	return 0;
}

int caller(int input, int touch(int)){
	touch(input);
	return 0;
}

int main(){
	caller(3, print);
}