#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char *args[]) {
	if (argc != 3) {
		cout << "这是一个参考志愿值计算器。" << endl
		     << "    使用公式：(5 * (2 * real - top) * ln(real - top)) / top;" << endl;
		cout << endl
		     << "使用方式：howmany [上限人数] [实选人数]" << endl;
		return 0;
	}
	int top = atoi(args[1]);
	int real = atoi(args[2]);
	if (top <= 0 || real <= 0) {
		printf("无效的参数。\n");
	}
	if (top >= real) {
		printf("参考志愿值：0\n");
	} else {
		double score = (5 * (2 * real - top) * log(real - top)) / (double)top;
		if (score >= 100) {
			printf("参考志愿值：100 (%.2f)。\n", score);
		} else {
			printf("参考志愿值：%.2f\n", score);
		}
	}
	return 0;
}