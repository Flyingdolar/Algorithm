#include <stdio.h>
#include <stdlib.h>

int readInput(const char **string){
    int wordCount = 0;
    char *buffer = (char*)malloc(2*sizeof(char));
    if (fgets(buffer)){
        /* code */
    }
    for (int letr = 0; letr != 10 && letr != 0; wordCount++){
        fgets(string, 1, stdin);
        letr = atoi(&(string[wordCount]));
    }
    return wordCount;
}

int main(int argc, char const *argv[])
{
    int adCost, delCost, roCost, inNum, outNum;
    char *before = (char*)malloc(6000*sizeof(int));
    char *after = (char*)malloc(6000*sizeof(int));

    scanf("%d %d %d", &adCost, &delCost, &roCost);
    inNum = readInput(before);
    outNum = readInput(after);

    printf("%d %d\n", inNum, outNum);
    printf("%s\n",before);
    printf("%s\n",after);
    
    return 0;
}
