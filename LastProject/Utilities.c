#define _CRT_SECURE_NO_WARNINGS
#include "Utilities.h"
#include "List.h"
#include "files.h"



int getMainMenuChoiceFromUser()
{
	int choice;
	printf("Welcome to the lottery simulator!\nPlease enter 1-3 to select one of the following:\n");
	printf("1. Enter the number of contestants in the lottery\n");
	printf("2. Show last lottery results\n");
	printf("3. Exit\n");
	scanf("%d", &choice);
	return choice;
}

int getParticipantsNumber()
{
	int num;
	printf("Please enter the number of participants in the lottery:\n");
	scanf("%d", &num);
	return num;
}

int getSubMenuChoice()
{
	int choice;
	printf("Please choose one of the two options below:\n");
	printf("1)Manual lottery\n");
	printf("2)Automatic lottery\n");
	scanf("%d", &choice);
	return choice;
}

int **getManualCol()
{
	int **res;
	int *col;
	int i;
	res = (int**)malloc(sizeof(int*));
	col = (int*)malloc(COL_SIZE * sizeof(int));
	for (i = 0; i < COL_SIZE; i++)
		scanf("%d", &col[i]);
	*res = col;
	return res;
}

void printCol(int *col, int numOfHits)
{
	int i;
	for (i = 0; i < COL_SIZE; i++)
		printf("%2d  ", col[i]);
	printf("\tThe number of Hits is: %d", numOfHits);
	printf("\n");

}

void printParticipantData(ColListNode **arr, int size, char *name)
{
	int i;
	printf("\nThe name of the participant is: %s\n", name);
	printf("The form filled by %s is:\n", name);
	for (i = 0; i < size; i++)
		printCol(*(arr[i])->pcols, arr[i]->num_of_hits);

}

int **getAutoCol()
{
	int **res;
	int *col;
	int i;
	BOOL isColValid = FALSE;
	//makes sure of getting different numbers each run
	res = (int**)malloc(sizeof(int*));
	col = (int*)malloc(COL_SIZE * sizeof(int));
	while (isColValid == FALSE)
	{
		for (i = 0; i < COL_SIZE; i++)
			col[i] = ((unsigned)rand() % RAND_MAX) + 1;
		//make sure the column we got is valid
		isColValid = checkColValidation(&col);
	}
	*res = col;
	return res;
}

BOOL checkColValidation(int **arr)
{
	int i, j;
	BOOL res = TRUE;
	for (i = 0; i < COL_SIZE - 1; i++)
	{
		for (j = i + 1; j < COL_SIZE; j++)
			if ((*arr)[i] == (*arr)[j] || (*arr)[i] < 1 || (*arr)[i]>15 || (*arr)[j]<1 || (*arr)[j]>15)
			{
				return FALSE;
			}
	}
	return TRUE;
}

int *getWinningCol()
{
	int i;
	int *res;
	BOOL isColValid = FALSE;
	res = (int*)malloc(COL_SIZE * sizeof(int));
	while (isColValid == FALSE)
	{
		for (i = 0; i < COL_SIZE; i++)
			res[i] = (rand() % RAND_MAX) + 1;
		//make sure the column we got is valid
		isColValid = checkColValidation(&res);
	}
	return res;
}

void printWinningCol(int *col)
{
	int i;
	printf("\nThe winning col is:\n");
	for (i = 0; i < COL_SIZE; i++)
		printf("%d ", col[i]);
	printf("\n");
}

int getNumOfHits(int *check, int *winningCol)
{
	int res = 0, i;
	//from 0-15
	int bucketArr[16] = { 0 };
	//update bucket array with the winning col
	for (i = 0; i < COL_SIZE; i++)
	{
		bucketArr[winningCol[i]] = 1;
	}
	//check for 1's in the bucket array - get positions from check array filled by the user/automatically
	for (i = 0; i < COL_SIZE; i++)
	{
		if (bucketArr[check[i]] == 1)
			res++;
	}
	return res;
}

void mergeSort(ColListNode **arr, int size)
{
	ColListNode **L, **R;
	int i, mid;

	if (size < 2)
		return;

	mid = size / 2;

	L = (ColListNode**)malloc(mid * sizeof(ColListNode*));
	R = (ColListNode**)malloc((size - mid) * sizeof(ColListNode*));
	//left subarray
	for (i = 0; i < mid; i++)
	{
		L[i] = arr[i];
	}
	//right subarray
	for (i = mid; i < size; i++)
	{
		R[i - mid] = arr[i];
	}

	mergeSort(L, mid);
	mergeSort(R, size - mid);
	Merge(arr, L, mid, R, size - mid);
	
	free(L);
	free(R);
}

void Merge(ColListNode**arr, ColListNode**L, int lSize, ColListNode**R, int rSize)
{
	//i-left index, j-right index, k-sorted array index
	int i = 0, j = 0, k = 0;

	while (i < lSize && j < rSize)
	{
		if (L[i]->num_of_hits > R[j]->num_of_hits)
		{
			arr[k] = L[i];
			k++;
			i++;
		}
		else
		{
			arr[k] = R[j];
			k++;
			j++;
		}
	}

	while (i < lSize)
	{
		arr[k] = L[i];
		k++;
		i++;
	}

	while (j < rSize)
	{
		arr[k] = R[j];
		k++;
		j++;
	}
}

int continueSavingMessage()
{
	int choice;
	printf("Please enter 1 in order to continue and saving the lottery, or any other number to exit without saving.\n");
	scanf("%d", &choice);
	return choice;
}

