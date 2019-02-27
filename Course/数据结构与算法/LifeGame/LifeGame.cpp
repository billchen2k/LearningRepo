#include "pch.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
constexpr int FIRST_INTRODUCTION = 0;
constexpr int MANIPUNATE_INSTRUCTION = 1;
constexpr int WITH_GENERATION_INFO = 1;
constexpr int NO_GENERATION_INFO = 0;
//Define rules;
int BOTTOM_LIMIT = 1;
int UPPER_LIMIT = 4;
int REBIRTH_NUM = 3;
//define characters to print
const char LIVEC = '#';
const char DIEC = '.';
const int MAXL = 101;
using namespace std;
class LifeMap {
public:
	int width;
	int height;
	int matrix[MAXL][MAXL] = { 0 };
	int surround[MAXL][MAXL] = { 0 };
	int generation = 0;
	void instructor(int type) {
		switch (type) {
		case FIRST_INTRODUCTION:
			cout << "Welcome to the Game of Life!" << endl << endl <<
				"生命游戏是一个零玩家游戏，它包括一个二维矩形世界，这个世界中的每个方格居住着一个活着的或死了的细胞。一个细胞在下一个时刻生死取决于相邻八个方格中活着的或死了的细胞的数量。如果相邻方格活着的细胞数量过多，这个细胞会因为资源匮乏而在下一个时刻死去；相反，如果周围活细胞过少，这个细胞会因太孤单而死去。"
				<< endl << "实际中，你可以设定周围活细胞的数目怎样时才适宜该细胞的生存。如果这个数目设定过低，世界中的大部分细胞会因为找不到太多的活的邻居而死去，直到整个世界都没有生命；如果这个数目设定过高，世界中又会被生命充满而没有什么变化。所以我们把这个数目选取为2或者3；这样整个生命世界才不至于太过荒凉或拥挤，而是一种动态的平衡。"
				<< endl << "这样的话，游戏的规则就是：当一个方格周围有2或3个活细胞时，方格中的活细胞在下一个时刻继续存活；即使这个时刻方格中没有活细胞，在下一个时刻也会“诞生”活细胞。在这个游戏中，还可以设定一些更加复杂的规则，例如当前方格的状况不仅由父一代决定，而且还考虑祖父一代的情况。"
				<< endl << "你作为这个世界的上帝，随意设定某个方格细胞的死活，以观察对世界的影响。在游戏的进行中，杂乱无序的细胞会逐渐演化出各种精致、有形的结构；这些结构往往有很好的对称性，而且每一代都在变化形状。一些形状已经锁定，不会逐代变化。有时，一些已经成形的结构会因为一些无序细胞的“入侵”而被破坏。但是形状和秩序经常能从杂乱中产生出来。"
				<< endl << endl << " Please insert the width AND the height of the grid:" << endl << "(Max Length is " << MAXL - 2 << ")" << endl;
			break;
		case MANIPUNATE_INSTRUCTION:
			cout << endl << "Now you can insert \"L X Y\" (eg. L 2 3 or l 2 3 to set the cell located in the 2nd row, 3rd column) to set a cell to live,"
				<< endl << "insert \"D X Y\" to set a cell to die. insert \"P\" to print the current status."
				<< endl << "\"N\" for simply jump tp the next generation.\nN (optional)GENERATIONS (optional)INTERVAL_TIME for evolve multiple generation at a time."
				<< endl << "Insert \"R\" to reset your gird and \"Q\" to quit." << endl
				<< "Inset X to define rules."
				<< "Most interstingly, you can radomlize every cell by insert \"!\"" << endl << "You can set multiple cells' status in one line." << endl;
			break;
		}

	}
	void initialize(int W, int H) {
		int i, j;
		for (i = 0; i < MAXL; i++) {
			for (j = 0; j < MAXL; j++) {
				matrix[i][j] = 0;
				surround[i][j] = 0;
			}
		}
		width = W;
		height = H;
		generation = 0;
	}
	void printer(int gen) {
		//gen = 1 for printing with generation info.
		if (gen == 1) {
			cout << "\n   Generation No." << generation << ":" << endl;
		}
		cout << endl;
		int i, j;
		cout << "  ";
		for (i = 0; i < width; i++) {
			printf("%2d ", i + 1);
		}
		cout << endl;
		for (i = 0; i < height; i++) {
			printf("%2d ", i + 1);
			for (j = 0; j < width; j++) {
				if (matrix[i + 1][j + 1] == 0) printf("%c  ", DIEC);
				else if (matrix[i + 1][j + 1] == 1) printf("%c  ", LIVEC);
			}
			cout << endl;
		}
		cout << endl;
		//print ratio
		if (gen == 1) {
			int liveCells = 0;
			for (i = 0; i < height; i++) {
				for (j = 0; j < width; j++) {
					if (matrix[i + 1][j + 1] == 1) liveCells++;
				}
			}
			cout << "   Live cell ratio: " << (double)liveCells / (double)(width*height) * 100.0
				<< "% (" << liveCells << "/" << width * height << ")" << endl << endl;
		}
	}
	void SetLiving(int W, int H) {
		if (W <= 0 || W > width || H <= 0 || H > height)
			cout << "Unvalid input, please try again.\n";
		else {
			matrix[W][H] = 1;
			cout << "Cell (" << W << " ," << H << ") came alive." << endl;
		}

	}
	void SetDying(int W, int H) {
		if (W <= 0 || W > width || H <= 0 || H > height)
			cout << "Unvalid input, please try again.\n";
		else {
			matrix[W][H] = 0;
			cout << "Cell (" << W << " ," << H << ") has been dead." << endl;
		}

	}
	void Radomlize() {
		int i, j;
		cout << "Randomlizing cell status..." << endl;
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				//srand(time(NULL));
				if ((rand() % 2) == 1) matrix[i + 1][j + 1] = 0;
				else {
					matrix[i + 1][j + 1] = 1;
					cout << "Cell (" << i + 1 << " ," << j + 1 << ") came alive." << endl;
				}
			}
		}
	}
	void Next() {
		int i, j;
		//Initialize the surround matrix.
		for (i = 0; i < MAXL; i++) {
			for (j = 0; j < MAXL; j++) {
				surround[i][j] = 0;
			}
		}
		//Calculate the surrounded live cells
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				if (matrix[i][j] == 1) surround[i + 1][j + 1]++;
				if (matrix[i][j + 1] == 1) surround[i + 1][j + 1]++;
				if (matrix[i][j + 2] == 1) surround[i + 1][j + 1]++;
				if (matrix[i + 1][j] == 1) surround[i + 1][j + 1]++;
				if (matrix[i + 1][j + 2] == 1) surround[i + 1][j + 1]++;
				if (matrix[i + 2][j] == 1) surround[i + 1][j + 1]++;
				if (matrix[i + 2][j + 1] == 1) surround[i + 1][j + 1]++;
				if (matrix[i + 2][j + 2] == 1) surround[i + 1][j + 1]++;
			}
		}
		//Rules
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				if (surround[i + 1][j + 1] >= UPPER_LIMIT) matrix[i + 1][j + 1] = 0;
				if (surround[i + 1][j + 1] <= BOTTOM_LIMIT) matrix[i + 1][j + 1] = 0;
				if (surround[i + 1][j + 1] == REBIRTH_NUM) matrix[i + 1][j + 1] = 1;
			}
		}
		generation++;
	}
	void Definer() {
		int i, j, k;
		cout << "Please insert three value to define the rules: (Defaul Configuration:1 4 3)" << endl
			<< "BOTTOM_LIMIT UPPER_LIMIT REBIRTH_NUM" << endl;
	inputrule: cout << ">> "; cin >> i >> j >> k;
		if (cin.fail() || i >= 8 || j >= 8 || k >= 8 || i < 0 || j < 0 || k < 0) {
			cout << "Invalid input, please input three positive integers smaller than 8." << endl;
			cin.clear();
			while (cin.get() != '\n');
			goto inputrule;
		}
		else {
			BOTTOM_LIMIT = i;
			UPPER_LIMIT = j;
			REBIRTH_NUM = k;
			printf("Rules have been defined to %d %d %d.\n", i, j, k);
		}
	}
};
int main()
{
	LifeMap Map;
	//These variables are used for manipunating.
	int X, Y;
	//these two labels are used for jumping for input that's too large and the reset command.
start: Map.instructor(FIRST_INTRODUCTION);
input: cin >> X >> Y;
	while (cin.fail()) {
		cout << "Unvalid input, please try again. Pleas type two integers." << endl;
		cin.clear();
		while (cin.get() != '\n') continue;
		cin >> X >> Y;
	}
	while (X >= 100 || Y >= 100) {
		cout << "Too long." << endl;
		cin.clear();
		goto input;
	}
	Map.instructor(MANIPUNATE_INSTRUCTION);
	cout << "This is all the cells you have." << endl;
	Map.initialize(X, Y);
	Map.printer(NO_GENERATION_INFO);
	cin.clear();
	while (cin.get() != '\n') continue; // Clear datas in the cache.
	char command;
	while ((command = toupper(cin.get())) != 'Q') {
		switch (command) {
		case 'L':
			cin >> X >> Y;
			if (cin.fail()) {
				cout << "Unvalid input, please try again." << endl;
				cin.clear();
				while (cin.get() != '\n') continue;
			}
			else
				Map.SetLiving(X, Y);
			break;
		case 'D':
			cin >> X >> Y;
			if (cin.fail()) {
				cout << "Unvalid input, please try again." << endl;
				cin.clear();
				while (cin.get() != '\n') continue;
			}
			else
				Map.SetDying(X, Y);
			break;
		case 'P':
			Map.printer(WITH_GENERATION_INFO);
			break;
		case 'N':
			//gens mens the number of generations to evolve
			//interval means the interval times between two evolutions
			int i, gens, interval;
			if (cin.get() != '\n') {
				cin >> gens;
				if (cin.get() == '\n') interval = 0;
				else cin >> interval;
				if (gens <= 0 || interval < 0) {
					cout << "Unvalid input, please enter positive integers." << endl;
					cin.clear();
					while (cin.get() != '\n') continue;
				}
				else {
					for (i = 0; i < gens; i++) {
						system("cls");
						Map.instructor(MANIPUNATE_INSTRUCTION);
						Map.Next();
						Map.printer(WITH_GENERATION_INFO);
						Sleep(interval);
					}
				}
			}
			else {
				system("cls");
				Map.instructor(MANIPUNATE_INSTRUCTION);
				Map.Next();
				Map.printer(WITH_GENERATION_INFO);
			}
			break;
		case 'R':
			system("cls");
			goto start;
			break;
		case '!':
			Map.Radomlize();
			cout << "OK, now it's just chaos." << endl;
			Map.printer(WITH_GENERATION_INFO);
			break;
		case 'X':
			Map.Definer();
		case '\n': break;
		case ' ': break;
		default:
			cout << "Unknown Command:(" << endl;
			//while (cin.get() != '\n') continue;
		}
	}
	cout << "See you:)\n\n";
	system("pause");
	return 0;
}
