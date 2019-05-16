#include <iostream>
#include <ctime>

int main(){
	long start = clock();
	float a[5][5] = {{1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}, {4, 5, 6, 7, 8}, {5, 6, 7, 8, 9}};
	float sum = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5;j++){
			sum += a[j][i];
		}
	}
	long end = clock();
	std::cout << end - start << std::endl;
}