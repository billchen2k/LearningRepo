#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED

#define maxRow 20
#define maxCol 60

class Life{
		private:
	int row;
	int col;
	int board[maxRow + 2][maxCol + 2];

      public:
	void initialize();
	void show();
	void judge();
	Life(int, int);
};

#endif

