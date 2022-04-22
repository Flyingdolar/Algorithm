#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define map(x,y) Map[x%2].col[y].num

#ifdef _DEBUG_
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif

typedef struct array* arr;
typedef struct array{
    int16_t num;
    arr col;
}array;

typedef struct list* lt;
typedef struct list{
    int x,y;
    lt next;
}list;

typedef struct multilist* mlt;
typedef struct multilist{
    int32_t lead;
    lt child;
    mlt next;
}multilist;

void printPoint(mlt Data){
    lt kid;
    DEBUG_PRINT(("-----------------------------\n"));
    while (Data->next){
        Data = Data->next;
        DEBUG_PRINT(("Lead( %d )\n",Data->lead));
        kid = Data->child;
        while ((kid = kid->next)){
            DEBUG_PRINT(("-- Record : %d %d\n", kid->x, kid->y));
        }
    }
    DEBUG_PRINT(("-----------------------------\n"));
    return;
}

int32_t min(int32_t input_A, int32_t input_B){
    if (input_A > input_B){
        return input_B;
    } else {
        return input_A;
    }   
}

int32_t max(int32_t input_A, int32_t input_B){
    if (input_A > input_B){
        return input_A;
    } else {
        return input_B;
    }   
}

void lt_Store(int32_t input_X, int32_t input_Y, lt out_Data){

    while (out_Data->next){
        out_Data = out_Data->next;
    }

    lt newNode = (lt)malloc(sizeof(list));
    newNode->next = out_Data->next;
    out_Data->next = newNode;
    newNode->x = input_X;
    newNode->y = input_Y;

    return;
}

void mlt_Store(int32_t input_X, int32_t input_Y, mlt out_Data){

    while (out_Data->next && out_Data->next->lead <= input_X){
        out_Data = out_Data->next;
    }

    if (out_Data->lead == input_X){
        // DEBUG_PRINT(("(%d,%d)save in old one\n", input_X, input_Y));
        lt_Store(input_X, input_Y, out_Data->child);
    } else {
        // DEBUG_PRINT(("(%d,%d)save in new one\n", input_X, input_Y));
        mlt newNode = (mlt)malloc(sizeof(multilist));
        newNode->next = out_Data->next;
        out_Data->next = newNode;
        newNode->lead = input_X;
        newNode->child = (lt)malloc(sizeof(list));
        lt_Store(input_X, input_Y, newNode->child);
    }

    return;
}

void mark_Treasure(mlt trs_Info, arr col_Map, int32_t line){

    while (trs_Info->next && trs_Info->lead != line)
        trs_Info = trs_Info->next;
    
    if (trs_Info->lead == line) {
        DEBUG_PRINT(("--There's Treasure on %d--\n", line));
        lt kid = trs_Info->child;
        while ((kid = kid->next)) {
            DEBUG_PRINT(("KID = %d  ",kid->y));
            col_Map[(kid->y) - 1].num = 1;
            DEBUG_PRINT(("SUCCESS!\n"));
        }
    } else {
        DEBUG_PRINT(("--No Treasure in this row--\n"));
    }

    DEBUG_PRINT(("Marked Done!\n"));
    return;
}

int16_t gain_Treasure(mlt Key, int32_t baseX, int32_t baseY, int32_t upper_X, int32_t upper_Y){

    int32_t lenX = upper_X - baseX + 1;
    int32_t lenY = upper_Y - baseY + 1;

    DEBUG_PRINT(("MapSize = (%d,%d)\n", lenX, lenY));

    arr Map = (arr)malloc(2*sizeof(array));
    Map[0].col = (arr)malloc((lenY)*sizeof(array));
    Map[1].col = (arr)malloc((lenY)*sizeof(array));

    DEBUG_PRINT(("\n\n"));
    for (int32_t ptX = 0; ptX < lenX; ptX++){

        DEBUG_PRINT(("\nROW( %d )\n",ptX));
        for (int32_t ptY = 0; ptY < lenY; map(ptX, ptY) = 0,ptY++);
        mark_Treasure(Key, Map[ptX%2].col, baseX + ptX);
        
        for (int32_t ptY = 0; ptY < lenY; ptY++){

            if ((ptY % 10) == 0){
                DEBUG_PRINT(("\n<%03d>  ", ptY));
            }

            printf("C%02d->",ptY);
            
            DEBUG_PRINT(("(%d)",map(ptX, ptY)));
            if (ptX != 0 && ptY != 0){
                map(ptX, ptY) += max(map((ptX-1), ptY), map(ptX, (ptY-1)));
            } else if (ptX != 0){
                map(ptX, ptY) += map((ptX-1), ptY);
            } else if (ptY != 0){
                map(ptX, ptY) += map(ptX, (ptY-1));
            }
            DEBUG_PRINT(("%d ", map(ptX, ptY)));
        }
        DEBUG_PRINT(("\n"));
    }
    // DEBUG_PRINT(("MapSize = (%d,%d)\n", lenX, lenY));
    DEBUG_PRINT(("\n"));
    return map((lenX-1), (lenY-1));
}

int main(int argc, char const *argv[]){
    
    int Points, Gains;
    int32_t pos_X, pos_Y, min_X = 10000000, min_Y = 10000000, max_X = 0, max_Y = 0;
    mlt pos_Treasure =  (mlt)malloc(sizeof(multilist));
    pos_Treasure->lead = -1;
    
    scanf("%d",&Points);
    for (int16_t i = 0; i < Points; i++){
        scanf("%d %d", &pos_X, &pos_Y);
        mlt_Store(pos_X, pos_Y, pos_Treasure);
        min_X = min(pos_X, min_X);
        min_Y = min(pos_Y, min_Y);
        max_X = max(pos_X, max_X);
        max_Y = max(pos_Y, max_Y);
    }

    DEBUG_PRINT(("\n"));
    printPoint(pos_Treasure);
    DEBUG_PRINT(("\nmin(x,y) = (%d,%d)\nmax(x,y) = (%d,%d)\n", min_X, min_Y, max_X, max_Y));
    DEBUG_PRINT(("\n"));

    Gains = gain_Treasure(pos_Treasure, min_X, min_Y, max_X, max_Y);
    printf("%d\n", Gains);
    
    return 0;
}
