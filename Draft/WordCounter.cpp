#include <stdio.h>
#include <string.h>

int main(){
	int totalWords = 1, pos = 0;
	char temp[100];
	char c;
	while ((c = getchar()) != '\n'){
		if (c != ' '){
			temp[pos] = c;
			pos++;
		} else {
			temp[pos] = '\0';
			totalWords++;
			printf("第%d个单词：%s", totalWords, temp);
		}
    }
    printf("共有%d个单词。");
}