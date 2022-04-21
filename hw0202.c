#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct array* row;
typedef struct array{
    int value;
    row col;
}array;

int distance(int a, int b){
    if (a>b){
        return a-b;
    }else{
        return b-a;
    }
}

int min(int a, int b, int c){
    if (a>b)
        a = b;
    else
        b = a;
    if (b>c)
        return c;
    else
        return b;
}

int readInput(char **str){
    int wordCount = 0, letr;
    char *string = (char*)malloc(6000*sizeof(char));
    *str = string;
    while ((letr = getchar()) != '\n'){
        *string =  (char)letr;
        string++;
        wordCount++;
    }
    return wordCount;
}

int chLock(char* oldStr, char* newStr, int insert, int delete, int rotate){

    int fpreR, fpreC, fpreRC;
    int oldLen = strlen(oldStr);
    int newLen = strlen(newStr);
    row costrow = (row)malloc((oldLen + 1)*sizeof(array));
    for (int z = 0; z < oldLen; z++){
        costrow[z].col = (row)malloc((newLen + 1)*sizeof(array));
    }

    for (int r = 0; r <= oldLen; r++){
        for (int c = 0; c <= newLen; c++){
            if (r == 0){
                costrow[r].col[c].value = c * insert;
            } else if (c == 0){
                costrow[r].col[c].value = r * delete; 
            } else {
                fpreR = costrow[r-1].col[c].value + delete;
                fpreC = costrow[r].col[c-1].value + insert;
                fpreRC = costrow[r-1].col[c-1].value + distance((int)(oldStr[r-1]), (int)(newStr[c-1])) * rotate;
                costrow[r].col[c].value = min(fpreR, fpreC, fpreRC);
            }
        }   
    }
    return costrow[oldLen].col[newLen].value;
}

int main(int argc, char const *argv[]){
    int adCost, delCost, roCost, inNum, outNum, result;
    char *before, *after;

    scanf("%d %d %d\n", &adCost, &delCost, &roCost);
    inNum = readInput(&before);
    outNum = readInput(&after);
    
    result = chLock(before, after, adCost, delCost, roCost);
    printf("%d\n",result);
    return 0;
}
