#include <iostream>
using namespace std;
void bubble_sort(int entry[], int count) {
	int isShifted = 0, pos = 0;
	do {
		isShifted = 0;
		for (pos = 0; pos < count - 1; pos++) {
			if (entry[pos] > entry[pos + 1]) {
				int temp = entry[pos];
				entry[pos] = entry[pos + 1];
				entry[pos + 1] = temp;
				isShifted = 1;
			}
		}
	} while (isShifted);
}

int main(){
	int a[10] = {1, 3, 6, 9, 2, 7, 4, 8, 5, 0};
	bubble_sort(a, 10);
	for (int i = 0; i < 10;i++){
		cout << a[i] << " ";
	}
	return 0;
}