#include <stdio.h>
#include <pthread.h>

int DAYS_OF_A_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int counter = 0;
int y1 = 0, m1 = 0, d1 = 0;
int y2 = 0, m2 = 0, d2 = 0;

int isLeapYear(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return 1;
	}
	return 0;
}

int isEqual() {
	return y1 == y2 && m1 == m2 && d1 == d2;
}

void addOneDay() {
	if (isLeapYear(y1)) {
		DAYS_OF_A_MONTH[1] = 29;
	} else {
		DAYS_OF_A_MONTH[1] = 28;
	}
	if (d1 == DAYS_OF_A_MONTH[m1 - 1]) {
		d1 = 1;
		if (m1 == 12) {
			m1 = 1;
			y1++;
		} else {
			m1++;
		}
	} else {
		d1++;
	}
	counter++;
}

int main() {
	scanf("%d %d %d %d %d %d", &y1, &m1, &d1, &y2, &m2, &d2);
	while (!isEqual()) {
		addOneDay();
	}
	printf("采集时间为%d天", counter);
}
