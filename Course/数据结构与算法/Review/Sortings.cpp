// Sortings.
// Written By @BillChen2000, 2019.6.22

#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

clock_t BubbleSort(vector<int> entry, vector<int> &newdata, int &moves) {
	clock_t start = clock();
	int count = entry.size();
	int isShifted = 0, pos = 0;
	do {
		isShifted = 0;
		for (pos = 0; pos < count - 1; pos++) {
			if (entry[pos] > entry[pos + 1]) {
				swap(entry[pos], entry[pos + 1]);
				// int temp = entry[pos];
				// entry[pos] = entry[pos + 1];
				// entry[pos + 1] = temp;
				isShifted = 1;
				moves++;
			}
		}
	} while (isShifted);
	newdata = entry;
	return clock() - start;
}

clock_t SelectionSort(vector<int> entry, vector<int> &newdata, int &moves) {
	clock_t start = clock();
	for (int i = 0; i < entry.size(); i++) {
		for (int j = i; j < entry.size(); j++) {
			int swapp = i;
			if (entry[j] < entry[swapp]) {
				swapp = j;
			}
			if (i != swapp) {
				swap(entry[i], entry[swapp]);
				moves++;
			}
		}
	}

	newdata = entry;
	return clock() - start;
}

clock_t InsertionSort(vector<int> entry, vector<int> &newdata, int &moves) {
	clock_t start = clock();
	for (int i = 1; i < entry.size(); i++) {
		for (int j = i;;) {
			if (entry[j] < entry[j - 1]) {
				swap(entry[j], entry[j - 1]);
				j--;
				moves++;
			}
			if (j == 0)
				break;
			if (entry[j] >= entry[j - 1]) {
				break;
			}
		}
	}
	newdata = entry;
	return clock() - start;
}

clock_t ShellSort(vector<int> entry, vector<int> &newdata, int &moves) {
	clock_t start = clock();
	int increment = entry.size();
	do {
		increment = increment / 3 + 1;
		for (int k = 0; k < increment; k++) {
			for (int i = increment + k; i < entry.size(); i += increment) {
				for (int j = i;;) {
					if (entry[j] < entry[j - increment]) {
						swap(entry[j], entry[j - increment]);
						j -= increment;
						moves++;
					}
					if (j - increment < 0)
						break;
					if (entry[j] >= entry[j - increment]) {
						break;
					}
				}
			}
		}
	} while (increment != 1);
	newdata = entry;
	return clock() - start;
}

clock_t ShellSort7321(vector<int> entry, vector<int> &newdata, int &moves) {
	clock_t start = clock();
	int increments[4] = {7,3,2,1};
	int increment, k = 0;
	do {
		increment = increments[k];
		for (int k = 0; k < increment; k++) {
			for (int i = increment + k; i < entry.size(); i += increment) {
				for (int j = i;;) {
					if (entry[j] < entry[j - increment]) {
						swap(entry[j], entry[j - increment]);
						j -= increment;
						moves++;
					}
					if (j - increment < 0)
						break;
					if (entry[j] >= entry[j - increment]) {
						break;
					}
				}
			}
		}
		k++;
	} while (increment != 1);

	newdata = entry;
	return clock() - start;
}

clock_t xSort(vector<int> entry, vector<int> &newdata, int &moves) {
	clock_t start = clock();

	/*
		Put your code here...
	 */

	newdata = entry;
	return clock() - start;
}

bool isSorted(vector<int> entry) {
	for (int i = 0; i < entry.size() - 1; i++) {
		if (entry[i] > entry[i + 1])
			return false;
	}
	return true;
}

void Generate(int count) {
	FILE *fp = fopen("/Users/billchen/OneDrive/Workspace/LearningRepo/Course/数据结构与算法/Review/datain.txt", "w+");
	srand(clock());
	for (int i = 0; i < count - 1; i++) {
		fprintf(fp, "%6d\n", rand() % count);
	}
	fprintf(fp, "%6d", rand() % count);
	fclose(fp);
}

int main() {
begin:
	int count;
	cout << "Data Source Count: ";
	cin >> count;
	Generate(count);
	ofstream fout("/Users/billchen/OneDrive/Workspace/LearningRepo/Course/数据结构与算法/Review/dataout.txt", ios::out);
	ifstream fin("/Users/billchen/OneDrive/Workspace/LearningRepo/Course/数据结构与算法/Review/datain.txt", ios::in);
	vector<int> data, out;
	for (int i = 0; !fin.eof(); i++) {
		int temp;
		fin >> temp;
		data.push_back(temp);
	}
	int moves = 0;
	
	cout << "Generated " << data.size() << " Numbers." << endl;
	cout << "SORTING          |TIME USAGE (s)  |Moves         |Correctness" << endl;
	cout << "-----------------|----------------|--------------|--------------" << endl;
	printf("%-17s|%-16f|%-14d|%s\n", "Bubble Sort", BubbleSort(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	moves = 0;
	printf("%-17s|%-16f|%-14d|%s\n", "Selection Sort", SelectionSort(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	moves = 0;
	printf("%-17s|%-16f|%-14d|%s\n", "Insertion Sort", InsertionSort(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	moves = 0;
	printf("%-17s|%-16f|%-14d|%s\n", "Shell Sort (%3)", ShellSort(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	moves = 0;
	printf("%-17s|%-16f|%-14d|%s\n", "Shell Sort (7321)", ShellSort7321(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	moves = 0;

	int i = 100;

	// while(i--){
	// 	vector<int> data1;
	// 	vector<int> out1;
	// 	srand(clock());
	// 	for (int j = 0; j < count; j++) {
	// 		data1.push_back(rand() % count);
	// 	}
	// 	int moves1 = 0;
	// 	printf("%-17s|%-16f|%-14d|%s\n", "Shell Sort", ShellSort7321(data1, out1, moves1) / double(CLOCKS_PER_SEC), moves1, isSorted(out1) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	// }


	// for (int i = 0; i < out.size();i++){
	// 	cout << out[i] << endl;
	// }
	fin.close();
	fout.close();

	cout << "\nRestart? ([r] to restart, any other key to exit...)" << endl;
	char ch;
	while(cin.get()!='\n')
		continue;
	ch = cin.get();
	if (tolower(ch) == 'r')
		goto begin;
	return 0;

}