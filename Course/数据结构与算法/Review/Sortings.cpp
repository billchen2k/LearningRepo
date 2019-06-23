// Sortings.
// Written By @BillChen2000, 2019.6.22
#include <algorithm>
#include <climits>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <unistd.h>
#include <vector>
using namespace std;

clock_t BubbleSort(vector<int> entry, vector<int> &newdata, int &moves) {
	moves = 0;
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
	moves = 0;
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
	moves = 0;
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
	moves = 0;
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
	moves = 0;
	clock_t start = clock();
	int increments[4] = {7, 3, 2, 1};
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

clock_t BucketSort(vector<int> entry, vector<int> &newdata, int &moves) {
	moves = 0;
	clock_t start = clock();
	newdata.clear();
	int max = entry[0];
	for (int i = 0; i < entry.size(); i++) {
		if (entry[i] > max)
			max = entry[i];
		moves++;
	}
	int *bucket = new int[max + 1]();
	for (int i = 0; i < entry.size(); i++) {
		bucket[entry[i]]++;
		moves++;
	}
	//	for (int i = 0; i < max;i++){
	//		int count = 0;
	//		for (int j = 0; j < entry.size();j++){
	//			if(entry[j] == i){
	//				count++;
	//				entry.erase(entry.begin() + j);
	//				j--;
	//
	//			}
	//
	//		}
	//		bucket[i] = count;
	//	}
	for (int i = 0; i <= max; i++) {
		for (int j = 0; j < bucket[i]; j++) {
			newdata.push_back(i);
			moves++;
		}
	}
	return clock() - start;
}

void _Merge(vector<int> &data, int front, int mid, int end, int &moves) {
	int li = 0, ri = 0;
	vector<int> left(data.begin() + front, data.begin() + mid + 1);
	vector<int> right(data.begin() + mid + 1, data.begin() + end + 1);
	left.push_back(INT_MAX);
	right.push_back(INT_MAX);
	for (int i = front; i <= end; i++) {
		if (left[li] <= right[ri]) {
			data[i] = left[li];
			li++;
		} else {
			data[i] = right[ri];
			ri++;
		}
		moves++;
	}
}

void _MergeSort(vector<int> &data, int front, int end, int &moves) {
	if (front >= end)
		return;
	int mid = front + (end - front) / 2;
	_MergeSort(data, front, mid, moves);
	_MergeSort(data, mid + 1, end, moves);
	_Merge(data, front, mid, end, moves);
}

clock_t MergeSort(vector<int> entry, vector<int> &newdata, int &moves) {
	moves = 0;
	clock_t start = clock();
	newdata = entry;
	_MergeSort(newdata, 0, newdata.size() - 1, moves);
	return clock() - start;
}

void _QuickSort(vector<int> &data, int front, int end, int &moves) {
	if (front >= end)
		return;
	int pivot = front + (end - front) / 2;
	swap(data[front], data[pivot]);
	moves++;
	int pos;
	for (pos = front + 1, pivot = front + 1; pos <= end; pos++) {
		if (data[pos] < data[front]) {
			swap(data[pos], data[pivot]);
			moves++;
			pivot++;
		}
	}

	swap(data[front], data[--pivot]);
	moves++;
	if (pos != pivot) {
		_QuickSort(data, front, pivot - 1, moves);
	}
	_QuickSort(data, pivot + 1, end, moves);
}

clock_t QuickSort(vector<int> entry, vector<int> &newdata, int &moves) {
	moves = 0;
	clock_t start = clock();
	newdata = entry;
	_QuickSort(newdata, 0, newdata.size() - 1, moves);
	return clock() - start;
}

void _Heapify(vector<int> &data, int begin, int end, int &moves) {
	int dad = begin;
	int son = dad * 2 + 1;
	while (son <= end) {
		if (son + 1 <= end && data[son + 1] > data[son])
			son++;
		if (data[dad] > data[son])
			return;
		else {
			swap(data[dad], data[son]);
			moves++;
			dad = son;
			son = son * 2 + 1;
		}
	}
}

clock_t HeapSort(vector<int> entry, vector<int> &newdata, int &moves) {
	moves = 0;
	clock_t start = clock();
	newdata = entry;
	for (int i = newdata.size() / 2 - 1; i >= 0; i--) {
		_Heapify(newdata, i, newdata.size() - 1, moves);
	}
	for (int i = newdata.size() - 1; i >= 0; i--) {
		swap(newdata[0], newdata[i]);
		moves++;
		_Heapify(newdata, 0, i - 1, moves);
	}
	return clock() - start;
}

clock_t xSort(vector<int> entry, vector<int> &newdata, int &moves) {
	moves = 0;
	clock_t start = clock();

	/*
	 Put your code here...
	 */

	newdata = entry;
	return clock() - start;
}

bool isSorted_old(vector<int> entry) {
	for (int i = 0; i < entry.size() - 1; i++) {
		if (entry[i] > entry[i + 1])
			return false;
	}
	return true;
}

bool isSorted(vector<int> origin, vector<int> entry) {
	if (origin.size() != entry.size())
		return false;
	sort(origin.begin(), origin.end());
	for (int i = 0; i < entry.size(); i++) {
		if (origin[i] != entry[i])
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
	printf("%-17s|%-16f|%-14d|%s\n", "Bubble Sort", BubbleSort(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(data, out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	printf("%-17s|%-16f|%-14d|%s\n", "Selection Sort", SelectionSort(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(data, out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	printf("%-17s|%-16f|%-14d|%s\n", "Insertion Sort", InsertionSort(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(data, out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	printf("%-17s|%-16f|%-14d|%s\n", "Shell Sort (/3)", ShellSort(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(data, out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	printf("%-17s|%-16f|%-14d|%s\n", "Shell Sort (7321)", ShellSort7321(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(data, out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	printf("%-17s|%-16f|%-14d|%s\n", "Bucket Sort", BucketSort(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(data, out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	printf("%-17s|%-16f|%-14d|%s\n", "Merge Sort", MergeSort(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(data, out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	printf("%-17s|%-16f|%-14d|%s\n", "Quick Sort", QuickSort(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(data, out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	printf("%-17s|%-16f|%-14d|%s\n", "Heap Sort", HeapSort(data, out, moves) / double(CLOCKS_PER_SEC), moves, isSorted(data, out) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");

	clock_t start = clock();
	vector<int> sorted = data;
	sort(sorted.begin(), sorted.end());
	printf("-----------------|----------------|--------------|--------------\n");
	printf("%-17s|%-16f|%-14s|%s\n", "sort() from C++", (clock() - start) / double(CLOCKS_PER_SEC), "---", "---");

	//	int i = 1000;
	//	 while(i--){
	//	 	vector<int> data1;
	//	 	vector<int> out1;
	//	 	srand(clock());
	//	 	for (int j = 0; j < count; j++) {
	//	 		data1.push_back(rand() % count);
	//	 	}
	//	 	int moves1 = 0;
	//	 	printf("%-17s|%-16f|%-14d|%s\n", "Shell Sort", ShellSort(data1, out1, moves1) / double(CLOCKS_PER_SEC), moves1, isSorted(data1, out1) ? "\033[42mCorrect\033[0m" : "\033[41mIncorrect\033[0m");
	//	 }

	//	 for (int i = 0; i < out.size();i++){
	//	 	cout << out[i] << endl;
	//	 }

	fin.close();
	fout.close();

	cout << "\nRestart? ([r] to restart, any other key to exit...)" << endl;
	char ch;
	while (cin.get() != '\n')
		continue;
	ch = cin.get();
	if (tolower(ch) == 'r')
		goto begin;
	return 0;
}
