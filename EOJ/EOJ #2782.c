#include <stdio.h>
#include <string.h>
int main(){
     int line, i;
     scanf("%d", &line);
     char outE[] = "Excellent\n", outA[] = "Accept More\n", outI[] = "I'm possible\n";
     char outC[] = "Cheer\n", outN[]="Nice\n", outU[]="Ultimate\n";
     for (i=0;i<line;i++){
          char input[11];
          scanf("%s", input);
          if (strcmp(input, "E")==0) printf("%s", outE);
          elseif (strcmp(input, "C")==0) printf("%s", outC);
          elseif (strcmp(input, "N")==0) printf("%s", outN);
          elseif (strcmp(input, "U")==0) printf("%s", outU);
          elseif (strcmp(input, "ACM")==0) printf("%s", outA);
          elseif (strcmp(input, "Impossible")==0) printf("%s", outI);
     }
     return 0;
}

