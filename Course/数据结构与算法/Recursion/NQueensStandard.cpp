#include <iostream>
using namespace std;

const int max_board = 30;

class Queens {
      public:
	Queens(int size);

	bool unguarded(int col) const;
	void insert(int col);
	void remove(int col);
	bool is_solved() const;
	void print() const;
	int board_size;

      protected:
      private:
	int count;
	bool col_free[max_board];	      // 存储列是否被占据
	bool upward_free[2 * max_board - 1];   // 存储自左下到右上的对角线是否被占据
	bool downward_free[2 * max_board - 1]; // 存储自右下到左上的对角线是否被占据
	int queen_in_row[max_board];	   // 存储每一行queen的列号
	static int success;
};
int Queens::success = 1;

Queens::Queens(int size)
/*Post: 初始化一个Queens类的对象.
*/
{
	board_size = size;
	count = 0;
	int i;
	for (i = 0; i < board_size; i++)
		col_free[i] = true;
	for (i = 0; i < (board_size * 2 - 1); i++)
		upward_free[i] = true;
	for (i = 0; i < (board_size * 2 - 1); i++)
		downward_free[i] = true;
	for (i = 0; i < board_size; i++)
		queen_in_row[i] = -1;
}

bool Queens::unguarded(int col) const
/*Post: 检查第一个空行(count)的col列是否未被皇后守卫, 若是返回true否则返回false
*/
{
	return col_free[col] && upward_free[count + col] && downward_free[count - col + board_size - 1];
}

void Queens::insert(int col)
/*Post: 向第一个空行的col列添加皇后, 并设置列及对角线被守卫.
*/
{
	queen_in_row[count] = col; // 第一个空行的索引为count
	col_free[col] = false;
	upward_free[count + col] = false;
	downward_free[count - col + board_size - 1] = false;
	count++;
}

void Queens::remove(int col)
/*Post: 移除最后一个非空行col列的皇后, 并重新设置列及对角线未被守卫.
*/
{
	count--;
	queen_in_row[count] = -1;
	col_free[col] = true;
	upward_free[count + col] = true;
	downward_free[count - col + board_size - 1] = true;
}

bool Queens::is_solved() const
/*Post: 若填入的皇后数等于棋盘大小返回true, 否则返回false.
*/
{
	return count == board_size;
}

void Queens::print() const
/*Post: 打印出皇后在棋盘上的分布图.
*/
{
	cout << "case #" << success++ << ":" << endl;
	for (int row = 0; row < board_size; row++) {
		for (int col = 0; col < board_size; col++) {
			if (queen_in_row[row] == col)
				cout << "*";
			else
				cout << "-";
		}
		cout << endl;
	}
	cout << endl;
}

void solve_from(Queens &configuration)
//Post: 对于大小为board_size的棋盘, 通过插入和移除回溯的方法寻找可行的棋盘配置并打印.
  //Uses: Queens类和回溯的方法.
{
	if (configuration.is_solved())
		configuration.print();
        
	else
		for (int col = 0; col < configuration.board_size; col++)
			if (configuration.unguarded(col)) {
				configuration.insert(col);
				solve_from(configuration);
				configuration.remove(col);
			}
}

int main() {
	int board_size;
	cin >> board_size;
	if (board_size < 0 || board_size > max_board)
		cout << "The number is out of range!" << endl;
	else {
		Queens configuration(board_size);
		solve_from(configuration);
	}

	return 0;
}