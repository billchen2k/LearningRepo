// 改算法不要留坑！！！！
// 4.14 03:02
#include <iostream>
#include <string.h>
#include <ctime>

const char CHESS_SIGN = '#';
const char NO_CHESS_SIGN = '-';
const int MAX_SIZE = 16;
using namespace std;
class Queen {
      private:
	int *columnFlag;
	int *leftAxisFlag;
	int *rightAxisFlag;
	int size;
	
	int count;
	

      public:
	Queen(int);
	int check(int);
	int insert(int);
	void remove(int);
	void print();
	int solve();
	unsigned long int solCount;
};

Queen::Queen(int size_) {
	size = size_;
	columnFlag = new int[size_ - 1];
	leftAxisFlag = new int[size_ * 2 - 1];
	rightAxisFlag = new int[size_ * 2 - 1];
	for (int i = 0; i < size;i++){
		columnFlag[i] = -1;
	}
	for (int i = 0; i < 2 * size - 1;i++){
		leftAxisFlag[i] = 0;
		rightAxisFlag[i] = 0;
	}
	solCount = 0;
	count = 0;
}

int Queen::check(int col) {
	// return 1 if the position [row][col] is free.
	int ret = !((columnFlag[col] + 1) || leftAxisFlag[col + count] || rightAxisFlag[count - col + size - 1]);
	return ret;
}

int Queen::insert(int col) {
	columnFlag[col] = count;
	leftAxisFlag[col + count] = 1;
	rightAxisFlag[count - col + size - 1] = 1;
	count++;
}

void Queen::remove(int col) {
	count--;
	columnFlag[col] = -1;
	leftAxisFlag[col + count] = 0;
	rightAxisFlag[count - col + size - 1] = 0;
}

void Queen::print() {
	solCount++;
	// cout << "Solution #" << ++solCount << ":" << endl;
	// for (int i = 0; i < size; i++) {
	// 	for (int j = 0; j < size; j++) {
	// 		if (columnFlag[j] == i)
	// 			cout << CHESS_SIGN << " ";
	// 		else
	// 			cout << NO_CHESS_SIGN << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
}

int Queen::solve() {
	if (count != size) {
		for (int i = 0; i < size; i++) {
			if (check(i) == 1) {
				int cowNow = i;
				insert(i);
				solve();
				remove(cowNow);

			}
		}
	} else {
		//printf("Finished. There are %d possible solutions.\n", solCount);
		print();
	}
}

int main() {
	int size, ways;
	cout << "How big is the chessboard please?" << endl;
	cin >> size;
	while (!(size > 0 && size <= MAX_SIZE)) {
		cout << "Chess board too large, please try again." << endl;
		while (cin.get() != '\n')
			continue;
		cin >> size;
	}
	int start = clock();
	Queen ChessBoard(size);
	ChessBoard.solve();
	int end = clock();
	if (ChessBoard.solCount == 0){
		cout << "No solution found." << endl;
	}
	cout << "Solved out " << ChessBoard.solCount << " solutions in " << double(end - start) / CLOCKS_PER_SEC << " s." << endl;
}