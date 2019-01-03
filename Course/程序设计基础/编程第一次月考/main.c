#include <stdio.h>
#include <math.h>
int primesum(int, int);
int main() {
	int key, i, length;
	key = primesum(100, 200) % 10;
	printf("100到200所有质数的和为：%d\n由此求出key值为：%d\n", primesum(100, 200), key);
	char code[]= "P^ pbee aZo^ ma^ l^\hg] fhgmaer m^lm hg Gho^f[^k 27, 2037.";
	printf("密文为：%s\n", code);
	for (length = 0; code[length] != '\0'; length++);	//求字符串长度
	for (i = 0; i <= length; i++) {
		if (code[i]+7 >= 'a' && code[i]+7 <= 'z' || code[i]+7 >= 'A' && code[i]+7 <= 'Z')
			code[i] += 7;
	}
	printf("原文为：%s\n", code);
	getchar();
}
//该函数用于求lower到upper之间所有质数的和
int primesum(int lower, int upper) {
	int i, j, sum=0, flag;
	for (i = lower; i <= upper; i++) {
		flag = 1;
		for (j = 2; j < sqrt(i); j++) {
			if (i%j == 0) flag = 0;
		}
		if (flag == 1) sum += i;
	}
	return sum;
}
