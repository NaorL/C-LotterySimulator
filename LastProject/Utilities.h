#ifndef __UTILITIES_H__
#define __UTILITIES_H__

/***includes***/
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
/**************/

/***prototypes***/
//for list
int getMainMenuChoiceFromUser();
int getParticipantsNumber();
int getSubMenuChoice();
int **getManualCol();
int **getAutoCol();
void printCol(int *col, int numOfHits);
void printParticipantData(ColListNode **arr, int size, char *name);
BOOL checkColValidation(int **arr);
int *getWinningCol();
void printWinningCol(int *col);
int getNumOfHits(int *check, int *winningCol);
void mergeSort(ColListNode **arr, int size);
void Merge(ColListNode**arr, ColListNode**L, int lSize, ColListNode**R, int rSize);
int continueSavingMessage();





/***************/
#endif // !__UTILITIES_H__
