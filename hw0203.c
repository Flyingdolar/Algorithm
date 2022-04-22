#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ROUTE(x,y) Route[x%2][y]

typedef struct node* list;
typedef struct node{
    int row_x;
    int col_y;
    int LENGTH;
    list NEXROW;
    list NEXCOL;
}node;

void printList(list DATA){

    if (DATA->NEXROW){
        list COLLIST;
        while ((DATA = DATA->NEXROW)){
            printf("ROW %03d :",DATA->row_x);
            COLLIST = DATA;
            while ((COLLIST = COLLIST->NEXCOL)){
                printf(" (%d,%d)", COLLIST->row_x, COLLIST->col_y);
            }
            printf("\n");
        }
    } else if (DATA->NEXCOL){
        printf("COL :");
        while ((DATA = DATA->NEXCOL)){
            printf(" %d", DATA->col_y);
        }
        printf("\n");
    }

    return;
}

int MAX(int valueA, int valueB){
    if (valueA > valueB){
        return valueA;
    } else {
        return valueB;
    }   
}

// Create New Header of the List
list newList(int n){

    list HEADER = (list)malloc(n*sizeof(node));

    HEADER->row_x = -1;
    HEADER->col_y = -1;
    HEADER->LENGTH = 0;

    return HEADER;
}

// Create New Row in the List
list newRow(list HEAD, list PREVROW, int nodeX, int nodeY){

    list ROWHEAD = (list)malloc(sizeof(node));
    list newNode = (list)malloc(sizeof(node));

    HEAD->LENGTH++;
    ROWHEAD->NEXROW = PREVROW->NEXROW;
    ROWHEAD->NEXCOL = newNode;
    PREVROW->NEXROW = ROWHEAD;

    ROWHEAD->row_x = nodeX;
    ROWHEAD->col_y = -1;
    ROWHEAD->LENGTH = 1;

    newNode->row_x = nodeX;
    newNode->col_y = nodeY;
    newNode->LENGTH = -1;

    return ROWHEAD;
}

// Create New Column in the List
list newCol(list ROWHEAD, int nodeX, int nodeY){

    list HEADER = ROWHEAD;
    list newNode = (list)malloc(sizeof(node));

    while (ROWHEAD->NEXCOL && ROWHEAD->NEXCOL->col_y <= nodeY){
        ROWHEAD = ROWHEAD->NEXCOL;
    }
    if (ROWHEAD->col_y == nodeY){
        return HEADER;
    }
    HEADER->LENGTH++;
    newNode->NEXCOL = ROWHEAD->NEXCOL;
    ROWHEAD->NEXCOL = newNode;

    newNode->row_x = nodeX;
    newNode->col_y = nodeY;
    newNode->LENGTH = -1;

    return HEADER;
}

// Add (x,y) to the List
void addNode(list DATA, int nodeX, int nodeY){

    list dataHead = DATA;

    // Let ListPtr stop at "row_X <= nodeX", or the "last Node" of List
    while (DATA->NEXROW && DATA->NEXROW->row_x <= nodeX){
        DATA = DATA->NEXROW;
    }

    if (DATA->row_x == nodeX) {
        // If the row exist -> create "NEW COLUMN"
        newCol(DATA, nodeX, nodeY);
    } else {
        // If row not exist -> create "NEW ROW"
        newRow(dataHead, DATA, nodeX, nodeY);
    }
    return;
}

// Main Process : Get the Max Value of Treasure
int MAX_GAIN(list MAP, list COLLIST){

    int GAIN = 0;
    list rowPtr, colPtr;
    int Route[3][COLLIST->LENGTH];
    
    colPtr = COLLIST->NEXCOL;
    for (int y = 0; y < COLLIST->LENGTH; y++, colPtr = colPtr->NEXCOL){
        Route[2][y] = colPtr->col_y;
    }

    rowPtr = MAP->NEXROW;
    for (int x = 0; x < MAP->LENGTH; x++, rowPtr = rowPtr->NEXROW){
        // printf("when X = %02d\n",x);

        colPtr = rowPtr->NEXCOL;
        for (int y = 0; y < COLLIST->LENGTH; y++){
            if (Route[2][y] == (colPtr->col_y)){
                Route[x%2][y] = 1;
                if (colPtr->NEXCOL)
                    colPtr = colPtr->NEXCOL;
            } else {
                Route[x%2][y] = 0;
            }
            // printf(" %02d",Route[x%2][y]);
        }
        // printf("\n");

        colPtr = rowPtr->NEXCOL;
        for (int y = 0; y < COLLIST->LENGTH; y++){
            if (x && y){
                Route[x%2][y] += MAX(Route[(x-1)%2][y], Route[x%2][y-1]);
            } else if (x){
                Route[x%2][y] += Route[(x-1)%2][y];
            } else if (y){
                Route[x%2][y] += Route[x%2][y-1];
            }
            // printf(" %02d",Route[x%2][y]);
        }
        // printf("\n");
    }
    GAIN = Route[(MAP->LENGTH-1)%2][(COLLIST->LENGTH-1)];
    return GAIN;
}

// Input & Output
int main(int argc, char const *argv[]){
    
    int num = 0, result, PtX, PtY;
    list treasure = newList(1);
    list yAxisList = newList(1);

    scanf("%d",&num);
    for (int i = 0; i < num; i++){
        scanf("%d %d", &PtX, &PtY);
        addNode(treasure, PtX, PtY);
        newCol(yAxisList, PtX, PtY);
    }

    // printf("--- Treasure ---\n");
    // printList(treasure);
    // printf("--- YAxisList ---\n");
    // printList(yAxisList);

    result = MAX_GAIN(treasure, yAxisList);
    printf("%d\n", result);

    return 0;
}
