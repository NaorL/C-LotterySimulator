#ifndef FILES__H__
#define FILES__H__

#include "List.h"
#include "Utilities.h"

typedef unsigned char BYTE;

#define COMPRESSED_COL_SIZE 3
#define FILE_NAME "lottery"


void saveLotteryToFile(ParticipantList *lst, int num_of_participants, int *winningCol);
FILE *createBinaryFile(char *fileName);
void writeLotteryResultsToFile(FILE *file, ParticipantList *lst, int num_of_participants, int* winningCol);
void compressAndWriteParticipantCols(FILE* file, Participant *participant);
void compressColToBytesAndWriteToFile(FILE *file, int *col);

void printLastLotteryResults();
long int getFileSize(FILE *file);

void printName(FILE *fp);
void printColsFromFile(FILE *fp, int num_of_cols);
void printSingleColFromFile(FILE *fp);
void printByte(BYTE val);
void printWinningColFromFile(FILE *fp);

#endif // !FILES__H__
