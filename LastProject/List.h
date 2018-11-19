#ifndef __LIST_H__
#define __LIST_H__
#define _CRT_SECURE_NO_WARNINGS

/***includes***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/**************/

#define COL_SIZE 6
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define MANUAL -1
#define AUTO -2
#define RAND_MAX 15

/***structs***/
typedef struct colListNode{
	int **pcols;
	int num_of_hits;
	struct colListNode *next;
}ColListNode;

typedef struct colList{
	ColListNode *head;
	ColListNode *tail;
	int num_of_cols;
}ColList;

typedef struct participant{
	char *name;
	ColList *lst;
}Participant;

typedef struct paticipantListNode{
	Participant *participant;
	struct paticipantListNode *next;
}ParticipantListNode;

typedef struct participantList{
	ParticipantListNode *head;
	ParticipantListNode *tail;
	int num_of_participants;
}ParticipantList;
/*************/

/***prototypes***/
ParticipantList startLottery();
void makeEmptyParticipantList(ParticipantList* lst);
ParticipantList buildParticipantList(int num_of_participants);
void insertDataToEndOfParticipantList(ParticipantList *lst, Participant *newParticipant);
Participant *allocateNewParticipantNode();
void makeEmptyColList(ColList *lst);
char *getParticipantName(int index);
void getManualForm(Participant *p, int flag, int num_of_cols);
void insertDataToEndOfColList(ColList *lst, int flag, int index);
ColListNode *allocateColListNode(ColListNode *next);
void insertNodeToEndOfColList(ColList *lst, ColListNode *newTail);
BOOL isEmptyColList(ColList *lst);
void printColList(ColList *lst);
ParticipantListNode *allocatePaticipantListNode(Participant *newParticipant, ParticipantListNode *next);
void insertNodeToEndOfParticipantList(ParticipantList *lst, ColListNode *newTail);
BOOL isEmptyParticipantList(ParticipantList *lst);
void printParticipantList(ParticipantList **lst, int num_of_participants);
void getAutoForm(Participant *p, int flag, int num_of_cols);
int getColsNum(Participant *p);
void updateHits(ParticipantList* lst, int *winningCol);
void printParticipantColsByHits(Participant *participant);
void updateHitsStatistics(Participant *participant, int *bucket);
int getTotalHits(Participant *participant);
int getHighAvgIndex(double *arr, int size);



#endif // !__LIST_H__
