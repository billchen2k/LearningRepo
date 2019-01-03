#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAXL 1000
int main() {
	char input[MAXL];
	puts("输入一个字符串，将有效的16进制数转换为10进制");
	while (printf("请输入一个字符串 (输入END退出)：\n") && gets_s(input, MAXL) && strcmp(input, "END")) {
		int i, len = strlen(input);
		bool available = false;
		int hex;
		if (input[0] == '0' && (input[1] == 'x' || input[1] == 'X')) {
			if (sscanf(input, "%x", &hex)) {
				available = true;
			}
		}
		printf("字符串s1的长度是%d，内容是%s\n", len, input);
		if (available == true) printf("转换后的十进制数为%d\n", hex);
		else printf("非法的16进制数值\n");
	}
	return 0;
}