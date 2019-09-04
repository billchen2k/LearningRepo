#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

int main(){
	cout << "Now we are starting to roll the coins." << endl;
	cout << "How many coins do you have?" << endl;
	int totalnum;
	int c1 = 0, c2 = 0;
	cin >> totalnum;
	cout << "Ding... Ding..." << endl;
	srand((unsigned)time(NULL));
	for (int i = 0; i < totalnum; i++) {
		if (rand() % 2 == 0)
			c1++;
		else
			c2++;
	}
	printf("Head: %d, Tail: %d\nHead ratio: %f\n", c1, c2, (float)c1 / (float)totalnum);
	return 0;
}