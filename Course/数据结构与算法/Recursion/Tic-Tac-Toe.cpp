#include <iostream>
#include <random>
#include <stack>
#include <unistd.h>

#define SINGLE_PLAYER 0
#define TWO_PLAYERS 1
using namespace std;
void cleanstream();
int get_int(int lower, int uppe);
class Chess {
      private:
	int chessData[9];
	int mode;
	int level;
	int placedCount;
	int winner;
	int playerNow;

      public:
	bool done() {
		return (placedCount == 9 || decideWinner() != 0) ? true : false;
	}
	int decideWinner() {
		// Player 1: Player;
		// Player 2: AI.
		for (int i = 0; i < 3; i++) {
			if ((chessData[0 + i] == chessData[3 + i] && chessData[3 + i] == chessData[6 + i]) && chessData[0 + i] != 0) {
				return chessData[0 + i];
			}
			if (chessData[0 + 3 * i] == chessData[1 + 3 * i] && chessData[1 + 3 * i] == chessData[2 + 3 * i] && chessData[0 + 3 * i] != 0) {
				return chessData[0 + 3 * i];
			}
		}
		if ((chessData[0] == chessData[4] && chessData[4] == chessData[8] && chessData[0] != 0) ||
		    (chessData[2] == chessData[4] && chessData[4] == chessData[6] && chessData[2] != 0)) {
			return chessData[4];
		}
		return 0;
	}

	void place(int pos){
		switch(placedCount%2){
			case 1:
				if (chessData[pos - 1] == 0) {
					chessData[pos - 1] = 2;
					placedCount++;
					playerNow = 1;
				} else {
					cout << "该位置已有棋子。请重新输入：" << endl
					     << ">> ";
					place(get_int(1, 9));
				}
				break;
			case 0:
				if (chessData[pos - 1] == 0) {
					chessData[pos - 1] = 1;
					placedCount++;
					playerNow = 2;
				} else {
					cout << "该位置已有棋子。请重新输入：" << endl
					     << ">> ";
					place(get_int(1, 9));
				}
		}
	}
	int possibleMoves(stack<int> &moves) {
		for (int i = 0; i < 9; i++) {
			if (chessData[i] == 0) {
				moves.push(i);
			}
		}
		return 0;
	}
	bool isBetter(int a, int b){
		return placedCount % 2 ? (a <= b) : (a >= b);
	}
	int rating() {
		// rating: > 0 if the winner is Player 1, < 0 if the winner is Player 2
		// |mark| the bigger, this case is better.
		if (decideWinner() == 1) {
			return 10 - placedCount;
		} else if (decideWinner() == 2) {
			return -10 + placedCount;
		} else {
			return 0;
		}
	}

	int lookAhead(const Chess &GameNow, int depth, int &recommend) {
		if (depth == 0 || done() == true) {
			return rating();
		} else {
			stack<int> allMoves;
			possibleMoves(allMoves);
			while(!allMoves.empty()){

			}
			Chess newGame = GameNow;
				}
		return rating();
	}
	void printer() {
		string printData[9];
		for (int i = 0; i < 9; i++) {
			if (chessData[i] == 0) {
				printData[i] = "\033[2m" + to_string(i + 1) + "\033[0m";
			} else if (chessData[i] == 1) {
				printData[i] = "●";
			} else if (chessData[i] == 2) {
				printData[i] = "×";
			}
		}
		cout << "	┏━━━┳━━━┳━━━┓" << endl
		     << "	┃ " << printData[0] << " ┃ " << printData[1] << " ┃ " << printData[2] << " ┃" << endl
		     << "	┣━━━╋━━━╋━━━┫" << endl
		     << "	┃ " << printData[3] << " ┃ " << printData[4] << " ┃ " << printData[5] << " ┃" << endl
		     << "	┣━━━╋━━━╋━━━┫" << endl
		     << "	┃ " << printData[6] << " ┃ " << printData[7] << " ┃ " << printData[8] << " ┃" << endl
		     << "	┗━━━┻━━━┻━━━┛" << endl;
	}
	void start() {
		switch (mode) {
		case SINGLE_PLAYER:
			printer();
			while (!done()) {
				cout << "输入落子位置：" << endl
				     << ">> ";
				place(get_int(1, 9));
				printer();
				/*计算机下子
					 /
					 /*/
				printf("\033[7A");
				printer();
			}
			break;
		case TWO_PLAYERS:
			printer();
			while (!done()) {
				cout << "输入 Player 1 的落子位置：" << endl
				     << ">> ";
				place(get_int(1, 9));
				printer();
				if (done())
					break;
				cout << "输入 Player 2 的落子位置：" << endl
				     << ">> ";
				place(get_int(1, 9));
				printer();
			}
			if (decideWinner() == 0)
				cout << "游戏结束，平局。" << endl;
			else
				cout << "\033[1m游戏结束，Player " << decideWinner() << " 获胜。\033[0m" << endl;
			break;
		}
	}
	Chess(int mode_) {
		mode = mode_ == -1 ? TWO_PLAYERS : SINGLE_PLAYER;
		if (mode == SINGLE_PLAYER)
			level = mode_;
		placedCount = 0;
		for (int i = 0; i < 9; i++) {
			chessData[i] = 0;
		}
	}
};
void cleanstream() {
	cin.sync();
	cin.clear();
	while (cin.get() != '\n')
		continue;
}
int instruct() {
	//返回值：-1为双人对战，0-9的数字为人机对战，数字越大难度越高。
	cout << "这是一个简单的井字棋游戏。你会看到如下棋盘，输入对应的数字来在相应位置丢下旗子。" << endl
	     << "	┏━━━┳━━━┳━━━┓" << endl
	     << "	┃ \033[2m1\033[0m ┃ \033[2m2\033[0m ┃ \033[2m3\033[0m ┃" << endl
	     << "	┣━━━╋━━━╋━━━┫" << endl
	     << "	┃ \033[2m4\033[0m ┃ \033[2m5\033[0m ┃ \033[2m6\033[0m ┃" << endl
	     << "	┣━━━╋━━━╋━━━┫" << endl
	     << "	┃ \033[2m7\033[0m ┃ \033[2m8\033[0m ┃ \033[2m9\033[0m ┃" << endl
	     << "	┗━━━┻━━━┻━━━┛" << endl;
	cout << "为了开始游戏，请选择你的游戏模式：" << endl;
	char ch;
	cout << "a. 人机对战" << endl
	     << "b. 双人对战" << endl
	     << ">> ";
	cin.get(ch);
	while ((ch != 'a' && ch != 'b') || cin.fail()) {
		cout << "输入无效，请重试。" << endl
		     << ">> ";
		cleanstream();
		cin.get(ch);
	}
	if (ch == 'a') {
		cout << "接下来请设置游戏难度。0 = 最低难度，9 = 最高难度。" << endl
		     << ">> ";
		int lev = get_int(0, 9);
		return lev;
	} else {
		return -1;
	}
}
int get_int(int lower, int upper) {
	int ret;
	cin >> ret;
	while (cin.fail() || !(ret >= lower && ret <= upper)) {
		cleanstream();
		cout << "输入无效，请输入一个介于 " << lower << " 至 " << upper << " 之间的整数。" << endl
		     << ">> ";
		cin >> ret;
	}
	return ret;
}
int main() {
beginning:
	int mode = instruct();
	Chess Gamer(mode);
	Gamer.start();
	cout << "输入 [r] 来开始新的一局，其他任何内容来退出。" << endl
	     << ">> ";
	cleanstream();
	char ch;
	cin.get(ch);
	if (ch == 'r') {
		goto beginning;
	} else
		return 0;
}
