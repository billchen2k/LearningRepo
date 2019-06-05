#include <climits>
#include <cmath>
#include <ctime>
#include <iostream>
using namespace std;

class Random {
      public:
	Random() {
		seed = time(NULL) % INT_MAX;
		mlt = 2643;
		addon = 3746;
	}
	double Random_real() {
		double max = INT_MAX + 1.0;
		double temp = reseed();
		if (temp < 0)
			temp = temp + max;
		return temp / max;
	}

	int Poisson(double mean) {
		double limit = exp(-mean);
		double product = Random_real();
		int count = 0;
		while (product > limit) {
			count++;
			product *= Random_real();
		}
		return count;
	}

      private:
	int seed, mlt, addon;
	int reseed() {
		seed = seed * mlt + addon;
		return seed;
	}
};

int main() {
	double E;
	int n;
	cout << "请输入概率均值：" << endl;
	cin >> E;
	cout << "请输入产生的随机整数的个数：" << endl;
	cin >> n;
	Random random;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		int temp = random.Poisson(E);
		cout << random.Poisson(E) << " ";
		sum += temp;
	}
	cout << "整个数列平均值为 " << (double)sum / (double)n << "。 "<< endl;
	return 0;
}