#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct array* row;
typedef struct array{
    int32_t value;
    row col;
}array;

int16_t absPos(int16_t a, int16_t b){
    if (a>b){
        return a-b;
    }else{
        return b-a;
    }
}

int16_t distance(int16_t a, int16_t b){
    int16_t ret = absPos(a,b);
    if (ret>13)
        ret = 26 - ret;
    return ret;
}

int32_t min(int32_t a, int32_t b, int32_t c){
    if (a>b)
        a = b;
    else
        b = a;
    if (b>c)
        return c;
    else
        return b;
}

int16_t readInput(char **str){
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

int32_t chLock(char* oldStr, char* newStr, int16_t insert, int16_t delete, int16_t rotate, int16_t oldLen, int16_t newLen){

    int32_t fpreR, fpreC, fpreRC;
    // int16_t oldLen = strlen(oldStr);
    // int16_t newLen = strlen(newStr);
    row costrow = (row)malloc(2*sizeof(array));
    costrow[0].col = (row)malloc((newLen + 1)*sizeof(array));
    costrow[1].col = (row)malloc((newLen + 1)*sizeof(array));

    for (int16_t r = 0; r <= oldLen; r++){
        for (int16_t c = 0; c <= newLen; c++){
            if (r == 0){
                costrow[r%2].col[c].value = c * insert;
            } else if (c == 0){
                costrow[r%2].col[c].value = r * delete; 
            } else {
                fpreR = costrow[(r-1)%2].col[c].value + delete;
                fpreC = costrow[r%2].col[c-1].value + insert;
                fpreRC = costrow[(r-1)%2].col[c-1].value + distance((int16_t)(oldStr[r-1]), (int16_t)(newStr[c-1])) * rotate;
                costrow[r%2].col[c].value = min(fpreR, fpreC, fpreRC);
            }
            // Debug
            // printf("r = %d, c = %d, value = %d\n", r, c, costrow[r].col[c].value);
        }   
    }
    return costrow[oldLen%2].col[newLen].value;
}

int main(int argc, char const *argv[]){
    int adCost, delCost, roCost;
    int16_t inNum, outNum;
    int32_t result;
    char *before, *after;

    scanf("%d %d %d\n", &adCost, &delCost, &roCost);
    inNum = readInput(&before);
    outNum = readInput(&after);

    result = chLock(before, after, adCost, delCost, roCost, inNum, outNum);
    printf("%d\n",result);
    return 0;
}
