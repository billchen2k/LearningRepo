#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count[101];
int main() {
	char str[101];
	scanf("%s", str);
	for (int k = 0; k < 101; k++) {
		count[k] = 0;
	}
	//大写转小写
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] + 32;
		}
	}
	//首字母大写
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] = str[i] - 32;
			break;
		}
	}
	int flag = 0;
	//输出字母
	for (int i = 0; str[i] != '\0'; i++) {
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
			printf("%c", str[i]);
			count[i] = 1;
			flag = 1;
		}
	}
	//输出数字
    if(flag) printf("\n");
    flag = 0;
    for (int i = 0; str[i] != '\0'; i++) {
	    if (str[i] >= '0' && (str[i] <= '9')) {
		    printf("%c", str[i]);
		    count[i] = 1;
		    flag = 1;
	    }
    }
	//输出其他符号
    if(flag) printf("\n");
	for (int i = 0; str[i] != '\0'; i++) {
		if (count[i] == 0) {
			printf("%c", str[i]);
		}
	}
	return 0;
}