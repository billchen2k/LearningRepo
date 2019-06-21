#include <iostream>
#include <fstream>
#include <cstdlib>

int main(){
	FILE *fp = fopen("/Users/billchen/OneDrive/Workspace/LearningRepo/Course/数据结构与算法/Review/datain.txt", "r+");
	for (int i = 0; i < 50000;i++){
		fprintf(fp, "%5d\n", rand() % 50000 + 10000);
	}
	return 0;
}