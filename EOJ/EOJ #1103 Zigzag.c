//2019.01.15 Tue
//Notes: case后常加入break
#include <stdio.h>
int main(){
	int count;
	scanf("%d", &count);
	int i = 0;
	enum direction {LEFT, RIGHT, UP, DOWN};
	for (i=0; i<count; i++){
		int len;
		enum direction dirc = RIGHT;
		scanf("%d", &len);
		int zig[len][len];
		int j = 0, k = 0, num = 1;
		int r = 0;
		for (r = 0; r < len * len;r++){
			zig[j][k] = num;
			num++;
			if (j==0 && k==0) dirc = RIGHT;
			else if(j==k && j % 2==1) dirc = LEFT;
			else if (j==k && j % 2==0) dirc = UP;
			else if ((k==0 && j % 2==0)|| (j==0 && k % 2==0)) dirc = RIGHT;
			else if ((k==0 && j % 2==1)|| (j==0 && k % 2==1)) dirc = DOWN;
			switch(dirc){
				case LEFT: k-=1; break;
				case RIGHT: k+= 1; break;
				case UP: j -= 1; break;
				case DOWN: j += 1; break;
			}
		}
		printf ("case #%d:\n", i);
		for (j=0;j<len;j++){
			for (k=0;k<len;k++){
				if (k<len-1) printf ("%d ", zig[j][k]);
				else printf ("%d\n", zig[j][k]);
			}
		}
	}
	return 0;
}
