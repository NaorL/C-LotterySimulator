#include "List.h"
#include "Utilities.h"

ParticipantList startLottery()
{
	ParticipantList res;
	int i;
	
	int num_of_participants;
	num_of_participants = getParticipantsNumber();
	res = buildParticipantList(num_of_participants);
	
	return res;
}
//set empty res list
void makeEmptyParticipantList(ParticipantList* lst)
{
	lst->head = lst->tail = NULL;
	lst->num_of_participants = 0;
}

ParticipantList buildParticipantList(int num_of_participants)
{
	ParticipantList res;
	Participant *participant_to_add;
	
	int i;
	makeEmptyParticipantList(&res);

	for (i = 0; i < num_of_participants; i++)
	{
		int sub_menu_choice, num_of_cols;
		participant_to_add = allocateNewParticipantNode();
		participant_to_add->name = getParticipantName(i);
		sub_menu_choice = getSubMenuChoice();
		num_of_cols = getColsNum(participant_to_add);

		if (sub_menu_choice == 1)
			getManualForm(participant_to_add, MANUAL, num_of_cols);
		else
			getAutoForm(participant_to_add, AUTO, num_of_cols);

		//after make sure that the data entered for each participant is valid, enter the participant to participant list
		insertDataToEndOfParticipantList(&res, participant_to_add);
	}
	res.num_of_participants = num_of_participants;
	return res;
}

Participant *allocateNewParticipantNode()
{
	Participant* newP;
	ColList *cols;
	cols = (ColList*)malloc(sizeof(ColList));
	newP = (Participant*)malloc(sizeof(Participant));
	newP->name = NULL;
	makeEmptyColList(cols);
	newP->lst = cols;
	return newP;
}

void makeEmptyColList(ColList *lst)
{
	lst->head = lst->tail = NULL;
	lst->num_of_cols = 0;
}

char *getParticipantName(int index)
{
	char *res;
	char ch;
	int logSize = 0, realSize = 1;
	res = (char*)malloc(realSize * sizeof(char));
	printf("Please enter the first name of  participant number %d:\n", index + 1);
	//for being able to continue with the name input
	ch = getchar();
	ch = getchar();

	//till end of input
	while (ch != '\n')
	{
		res[logSize] = ch;
		logSize++;
		if (realSize == logSize)
		{
			realSize = realSize * 2;
			res = (char*)realloc(res, realSize * sizeof(char));
		}
		ch = getchar();
	}
	res = (char*)realloc(res, logSize + 1 * sizeof(char));
	res[logSize] = '\0';
	return res;
}

void getManualForm(Participant *p, int flag, int num_of_cols)
{
	int  i;
	
	//till finish get the cols from user
	for (i = 0; i < num_of_cols; i++)
	{
		insertDataToEndOfColList(p->lst, flag, i + 1);
	}
}

void insertDataToEndOfColList(ColList *lst, int flag, int index)
{
	ColListNode *newTail;
	BOOL isColValid = FALSE;
	int failure = 0;
	newTail = allocateColListNode(NULL);
	if (flag == MANUAL)
	{

		while (isColValid == FALSE)
		{
			if (failure == 0)
				printf("\nPlease enter the values for column number %d:\n", index);
			else
			{
				printf("ERROR: Illegal col inserted!\nPlease make sure to enter numbers between 1-15, and that all the numbers are different from each other.\n");
				printf("Please re-insert values for the current col:\n");
			}
			failure++;
			newTail->pcols = getManualCol();
			//verify there is not duplications in the array or illegal number (not between 1-15)
			isColValid = checkColValidation(newTail->pcols);
		}
	}
	else
		newTail->pcols = getAutoCol();

	insertNodeToEndOfColList(lst, newTail);
}

ColListNode *allocateColListNode(ColListNode *next)
{
	ColListNode *res;
	res = (ColListNode*)malloc(sizeof(ColListNode));
	res->next = next;
	res->num_of_hits = 0;
	res->pcols = NULL;
	return res;
}

void insertNodeToEndOfColList(ColList *lst, ColListNode *newTail)
{
	if (isEmptyColList(lst))
	{
		lst->head = newTail;
		lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
	newTail->next = NULL;
}

BOOL isEmptyColList(ColList *lst)
{
	if (lst->head == NULL)
		return TRUE;
	else
		return FALSE;
}

void insertDataToEndOfParticipantList(ParticipantList *lst, Participant *newParticipant)
{
	ParticipantListNode *newTail;
	newTail = allocatePaticipantListNode(newParticipant, NULL);
	
	insertNodeToEndOfParticipantList(lst, newTail);
}

ParticipantListNode *allocatePaticipantListNode(Participant *newParticipant, ParticipantListNode *next)
{
	ParticipantListNode *newP;
	newP = (ParticipantListNode*)malloc(sizeof(ParticipantListNode));
	newP->next = next;
	newP->participant = newParticipant;
	return newP;
}

void insertNodeToEndOfParticipantList(ParticipantList *lst, ColListNode *newTail)
{
	if (isEmptyParticipantList(lst))
	{
		lst->head = newTail;
		lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
	newTail->next = NULL;
}

BOOL isEmptyParticipantList(ParticipantList *lst)
{
	if (lst->head == NULL)
		return TRUE;
	else
		return FALSE;
}

void printParticipantList(ParticipantList *lst, int num_of_participants)
{
	ParticipantListNode *pParticipant = lst->head;
	ParticipantListNode *bestAvgHits = NULL;
	double *avgHitsArr, highAvg = 0;
	int hitsBucket[7] = { 0 };
	int i, num_of_hits, highAvgIndex;
	//print by number of hits
	while (pParticipant)
	{
		printParticipantColsByHits(pParticipant->participant);
		pParticipant = pParticipant->next;
	}
	//print cols statistics 
	pParticipant = lst->head;
	while (pParticipant)
	{
		updateHitsStatistics(pParticipant->participant, hitsBucket);
		pParticipant = pParticipant->next;
	}
	//print to screen hits statistics
	for (i = 1; i <= COL_SIZE; i++)
	{
		printf("The number of %d hits is: %d\n", i, hitsBucket[i]);
	}
	//get the participant with best average hits
	pParticipant = lst->head;
	avgHitsArr = (double*)calloc(num_of_participants, sizeof(double));
	//build average array
	for (i = 0; i < num_of_participants; i++)
	{
		num_of_hits = getTotalHits(pParticipant->participant);
		avgHitsArr[i] = (double)(num_of_hits) / (double)(pParticipant->participant->lst->num_of_cols);
		pParticipant = pParticipant->next;
	}
	highAvgIndex = getHighAvgIndex(avgHitsArr, num_of_participants);
	//get the participant name
	pParticipant = lst->head;
	for (i = highAvgIndex; i > 0; i--)
	{
		pParticipant = pParticipant->next;
	}
	printf("\nThe participant with the best average hits is: %s\n", pParticipant->participant->name);
	free(avgHitsArr);
}

void printParticipantColsByHits(Participant *participant)
{
	ColListNode **arr;
	ColListNode *p = participant->lst->head;
	int size, i;
	size = participant->lst->num_of_cols;
	//allocate pointers to col list node array
	arr = (ColListNode**)malloc(size * sizeof(ColListNode*));
	//sortArr = (ColListNode**)malloc(size * sizeof(ColListNode*));
	//set the array with addresses
	for (i = 0; i < size; i++)
	{
		arr[i] = p;
		p = p->next;
	}

	mergeSort(arr, size);


	printParticipantData(arr, size, participant->name);
}

void getAutoForm(Participant *p, int flag, int num_of_cols)
{
	int i;
	//till finish get the cols from user
	for (i = 0; i < num_of_cols; i++)
	{
		insertDataToEndOfColList(p->lst, flag, i + 1);
	}
}

int getColsNum(Participant *p)
{
	int colsNum;
	printf("\nPlease enter the number of columns to fill:\n");
	scanf("%d", &colsNum);
	p->lst->num_of_cols = colsNum;
	return colsNum;
}

void updateHits(ParticipantList* lst, int *winningCol)
{
	ParticipantListNode *pParticipant = lst->head;
	ColListNode *pCol;
	
	//scan the list
	while (pParticipant)
	{
		pCol = pParticipant->participant->lst->head;
		//scan the list of cols per participant
		while (pCol)
		{
			int num;
			num = getNumOfHits(*pCol->pcols, winningCol);
			pCol->num_of_hits = num;
			pCol = pCol->next;
		}
		
		pParticipant = pParticipant->next;

	}
}

void updateHitsStatistics(Participant *participant, int *bucket)
{
	ColListNode *curr = participant->lst->head;
	//going over the col list
	while (curr)
	{
		bucket[curr->num_of_hits]++;
		curr = curr->next;
	}
}

int getTotalHits(Participant *participant)
{
	ColListNode *curr = participant->lst->head;	
	int res = 0;
	while (curr)
	{
		res = res + (curr->num_of_hits);
		curr = curr->next;
	}
	return res;
}

int getHighAvgIndex(double *arr, int size)
{
	int i, loc = 0;
	double max = arr[0];
	for (i = 1; i < size; i++)
	{
		if (arr[i]>max)
		{
			max = arr[i];
			loc = i;
		}	
	}
	return loc;
}
