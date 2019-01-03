#include <stdio.h>
#include <string.h>
#define MAXL 100000
int replace(char * origin, char * source, char * target, int lenO) {
	char * pt;
	int lenS = (int)strlen(source);
	int lenT = (int)strlen(target);
	int position = 0, gap = 0;
	if (strstr(origin, source) == NULL) return 0; //未查找到异常处理
	while ((pt = strstr(origin + gap, source)) != NULL) {
		lenO = (int)strlen(origin);
		int i = 0;
		position = pt - origin;
		for (i = 0; i < lenS; i++) *(pt + i) = '\1';
		//判断在相应位置应该右移还是左移
		if (lenS >= lenT) {
			strncpy(pt, target, lenT);
			for (i = 0; i < lenO - position; i++) *(pt + lenT + i) = *(pt + i + lenS);
		}
		else {
			if (lenO - lenS + lenT >= MAXL) return -1; //超限异常处理
			for (i = lenO - position; i >= 0; i--) *(pt + lenT + i) = *(pt + i + lenS);
			strncpy(pt, target, lenT);
		}
		gap = position + lenT;//gap用于防止循环替换，使第二次搜索从替换之后的位置开始
	}
	return (int)strlen(origin);
}
int main() {
	//读入数据
	char s1[MAXL], s2[MAXL], s3[MAXL];
	int len1, len2, len3;
	printf("即将查找s1中的所有子串并替换，替换前后的长度限度为%d字节。\n", MAXL);
	puts("请输入原串s1：");
	fgets(s1, MAXL, stdin);
	len1 = (int)strlen(s1) - 1;
	s1[len1] = '\0';
	printf("原串s1的长度是%d，内容是：%s\n", len1, s1);
	puts("请输入查找串s2：");
	fgets(s2, MAXL, stdin);
	len2 = (int)strlen(s2) - 1;
	s2[len2] = '\0';
	printf("查找串s2的长度为%d，内容是：%s\n", len2, s2);
	puts("请输入替换串s3：");
	fgets(s3, MAXL, stdin);
	len3 = (int)strlen(s3) - 1;
	s3[len3] = '\0';
	printf("替换串s3的长度是%d，内容是：%s\n", len3, s3);
	//替换并计算新长度
	char snew[MAXL];
	int lennew;
	strncpy(snew, s1, len1);
	lennew = replace(s1, s2, s3, len1);
	if (!lennew)
		puts("未能查找到匹配结果，请重试。");
	else if (lennew == -1)
		puts("替换后超出长度限制，请重试。");
	else
		printf("替换后的s1长度为%d，内容是：%s\n", lennew, s1);
	system("pause");
	return 0;
}
