#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stuff* stuffPtr;
typedef struct stuff{
    int weight;
    int value;
    int amount;
}stuff;

typedef struct count* countPtr;
typedef struct count{
    int value;
    countPtr nextD;
}count;


int MaxValue(stuffPtr Data, int type, int ability){
    int *list = (int*)malloc((ability+1)*sizeof(int));
    countPtr remain = (countPtr)malloc((ability+1)*sizeof(count));
    for (int index = 0; index < ability+1; index++){
        remain[index].nextD = (countPtr)malloc((type)*sizeof(count));
    }

    for (int i = 0; i < ability+1; i++){
        for (int j = 0; j < type; j++){
            remain[i].nextD[j].value = 0;
        }  
    }
    int record;
    list[0] = 0;
    for (int wei = 1; wei <= ability; wei++){
        record = -1;
        list[wei] = list[wei-1];
        for (int obj = 0; obj < type; obj++){
            remain[wei].nextD[obj].value = remain[wei-1].nextD[obj].value;
        }

        for (int obj = 0; obj < type; obj++){
            if(wei >= Data[obj].weight && Data[obj].amount > remain[wei - Data[obj].weight].nextD[obj].value){
                if ((list[wei - Data[obj].weight] + Data[obj].value) > list[wei]){
                    list[wei] = list[wei - Data[obj].weight] + Data[obj].value;
                    record = obj;
                }
            }
        }
        if(record >= 0){
            for (int obj = 0; obj < type; obj++){
                remain[wei].nextD[obj].value = remain[wei - Data[record].weight].nextD[obj].value;
            }
            remain[wei].nextD[record].value++;
        }
        // debug
        printf("%d %d", wei, list[wei]);
        for (int i = 0; i < type; i++){
            for (int j = 0; j < remain[wei].nextD[i].value; j++){
                printf(" %d", Data[i].weight);
            }  
        }
        printf(" record = %d\n",record);
    }
    return list[ability]; 
}

int main(int argc, char const *argv[]){
    int Ntrs, BobStand, output;
    scanf("%d %d", &Ntrs, &BobStand);
    stuffPtr treasure = (stuff*)malloc(Ntrs * sizeof(stuff));
    for (int index=0; index<Ntrs; index++){
        scanf("%d %d %d", &(treasure[index].weight), &(treasure[index].value), &(treasure[index].amount));
    }
    output = MaxValue(treasure, Ntrs, BobStand);
    printf("%d\n", output);
    return 0;
}