#include <stdio.h>
char a[100] = "ppfasdf fasdf asdfa asdf afsd asdf asdf";
int main() {
	int add;
	char *p = a;
	char ch[10];
	while (sscanf(p, "%s%n", ch, &add) != EOF) {
		p = p + add;
		printf("%s %d\n", ch, add);
	}
	scanf("%d", &add);
}