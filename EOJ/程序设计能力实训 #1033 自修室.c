//2019.2.18 1033
#include <stdio.h>
int main(){
	int len, i;
	while((scanf("%d", &len))!=EOF){
		int ID, Dis, R, C;
		//-1 indicates no solution and outputDis indicates the distance of the classroom.
		int output=-1, outputDis=2000000;
		for(i=0;i<len;i++){
			scanf("%d %d %d %d", &ID, &Dis, &R, &C);
			char class[17][17];
			int j, k;
			for(j=0;j<R;j++){
				scanf("%s", class[j+1]+1);
			}
			for(j=0;j<R+2;j++) {
				class[j][0]='0';
				class[j][C+1]='0';
			}
			for(j=0;j<C+2;j++){
				class[0][j]='0';
				class[R+1][j]='0';
			}
			//judging
			for(j=1;j<R+1;j++){
				for(k=1;k<C+1;k++){
					if(class[j][k]=='0' && class[j-1][k]=='0' &&
					   class[j][k-1]=='0' && class[j][k+1]=='0'){
						//judge the distance
						if(outputDis>Dis){
							outputDis = Dis;
							output=ID;
						}
					}
				}
			}
		}
		//output
		if(output!=-1) printf("%d\n", output);
		else printf("Bad Luck,Rocker!\n");
	}
	return 0;
}
