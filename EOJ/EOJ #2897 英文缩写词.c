//2019.2.3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void remover(char * input, char * tocut){
	char * cutter;
	while((cutter=strstr(input, tocut))!=NULL){
		int i;
		for(i=0;i<strlen(tocut);i++){
			cutter[i]=' ';
		}
	}
}
int main(){
	char *input=  malloc(100 * sizeof(char));
	while(gets(input) && *input != '\0'){
		char *output = malloc(100 * sizeof(char));
		int i,n = (int)strlen(input), j;
		for(i=0; i<n; i++) input[i]=toupper(input[i]);
		output[0]=input[0];
		remover(input, " A ");
		remover(input, "A ");
		remover(input, " AN ");
		remover(input, "AN ");
		remover(input, " OF ");
		remover(input, "OF ");
		remover(input, " THE ");
		remover(input, "THE ");
		remover(input, " FOR ");
		remover(input, "FOR ");
		remover(input, " AND ");
		remover(input, "AND ");
		for(i=0, j=0, n=(int)strlen(input); i<n; i++){
			if (i==0){
				if(input[0]!=' ') {output[0]=input[0];j++;}
			}else{
				if((input[i]==' ' && input[i+1]!=' ') ||
				   (input[i]=='-' && input[i+1]!='-')){output[j]=input[i+1]; j++;}
			}
		}
		puts(output);
	}
	return 0;
}
