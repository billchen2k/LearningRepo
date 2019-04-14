#include <iostream>
#include <string.h>
const char CHESS_SIGN = '#';
const char NO_CHESS_SIGN = '-';
const int MAX_SIZE = 10;
using namespace std;
class Queen {
      private:
	int **data;
	int size;
	int solCount;
	int rowNow;

      public:
	Queen(int);
	int check(int);
	int insert(int);
	void remove(int);
	void print();
	int solve();
};
Queen::Queen(int size_) {
	size = size_;
	int **data;
	data = new int*[size_];
	for (int i = 0; i > size_; i++){
		data[i] = new int[size_];
	}
	solCount = 0;
	rowNow = 1;
}

int Queen::check(int col) {
	// return 1 if this column still has possible solution.
	for (int i = 0; i < size; i++) {
        
	}
}

int Queen::insert(int col) {
	// return 1 if there is still possibole solution

}

void Queen::remove(int col) {
}

void Queen::print() {
	cout << "Solution #" << solCount++ << ":" << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (data[i][j] == 1)
				cout << CHESS_SIGN << " ";
			else
				cout << NO_CHESS_SIGN << " ";
		}
		cout << "\n";
	}
}

int Queen::solve() {
	if (rowNow < size) {
		for (int i = 0; i < size; i++) {
			if (check(i) == 1) {
				insert(i);
				solve();
				remove(i);
				solCount++;
			}
		}
	} else {
		printf("Finished. There are %d possible solutions.\n", solCount);
		print();
	}
}

int main() {
	int size, ways;
	cout << "How big is the chessboard please?" << endl;
	cin >> size;
	while (!(size > 0 && size < MAX_SIZE)) {
		cout << "Chess board too large, please try again.";
		while (cin.get() != '\n')
			continue;
		cin >> size;
	}
	Queen ChessBoard(size);
	ChessBoard.solve();
}
