#include "files.h"


void saveLotteryToFile(ParticipantList *lst, int num_of_participants, int *winningCol)
{
	FILE *fp;
	
	fp = createBinaryFile(FILE_NAME);

	writeLotteryResultsToFile(fp, lst, num_of_participants, winningCol);
}

FILE *createBinaryFile(char *fileName)
{
	FILE *fp;
	fp = fopen(fileName, "wb");
	if (fp == NULL)
		printf("ERROR: couldn't create file!\n");
	else
		return fp;
}

void writeLotteryResultsToFile(FILE *file, ParticipantList *lst, int num_of_participants, int* winningCol)
{
	int i, nameLen;
	ParticipantListNode *curr = lst->head;
	//write the number of participants
	fwrite(&num_of_participants, sizeof(int), 1, file);

	for (i = 0; i < num_of_participants; i++)
	{
		//get and write name lenght to file
		nameLen = strlen(curr->participant->name);
		fwrite(&nameLen, sizeof(int), 1, file);
		//write the name without '\0'
		fwrite(curr->participant->name, sizeof(char), nameLen, file);
		//write number of columns
		fwrite(&curr->participant->lst->num_of_cols, sizeof(int), 1, file);
		//compress each col of the participant
		compressAndWriteParticipantCols(file, curr->participant);
		curr = curr->next;
	}
	compressColToBytesAndWriteToFile(file, winningCol);
	//close & save changes
	fclose(file);
}

void compressAndWriteParticipantCols(FILE* file, Participant *participant)
{
	int i, size;
	//array to store the cols by hits numbers
	ColListNode **arr;
	ColListNode *pCol = participant->lst->head;
	//get num of columns
	size = participant->lst->num_of_cols;
	//allocate pointers to col list node array
	arr = (ColListNode**)malloc(size * sizeof(ColListNode*));
	//set the adresses in arr
	for (i = 0; i < size; i++)
	{
		arr[i] = pCol;
		pCol = pCol->next;
	}
	//sort arr by hits
	mergeSort(arr, size);
	//set pcol to start of col list
	pCol = participant->lst->head;
	for (i = 0; i < size; i++)
	{
		compressColToBytesAndWriteToFile(file, *arr[i]->pcols);
	}
}

void compressColToBytesAndWriteToFile(FILE *file, int *col)
{
	int i, count = 0;
	BYTE ch = 0, binValue;
	//array to store the compressed col
	BYTE *compressedCol = (BYTE*)malloc(COMPRESSED_COL_SIZE * sizeof(BYTE));
	for (i = 0; i < COL_SIZE; i++)
	{
		if (i % 2 == 0)
		{
			binValue = 0;
			binValue = binValue | col[i];
		}
		else
		{
			binValue = binValue << 4;
			binValue = binValue | col[i];
			compressedCol[count] = binValue;
			count++;
		}
	}
	fwrite(compressedCol, sizeof(BYTE), COMPRESSED_COL_SIZE, file);
}






void printLastLotteryResults()
{
	FILE *file;
	long int fileSize, pos;
	char ch;
	int num_of_participants, name_len, count = 0, num_of_cols;
	//open the file "lottery" we saved for reading
	file = fopen(FILE_NAME, "rb");
	if (file == NULL)
		printf("\nERROR: file does nor exist yet, please run lottery first.\n");
	//print winning col first (at similar way to the first printing as requested)
	//printWinningColFromFile(file);
	fileSize = getFileSize(file);
	//get the number of participants
	fread(&num_of_participants, sizeof(int), 1, file);
	//till winning col at the end of file (not included)
	while (ftell(file) < fileSize - (sizeof(BYTE) * COMPRESSED_COL_SIZE))
	{
		printName(file);
		//get number of columns filled by the participant
		fread(&num_of_cols, sizeof(int), 1, file);
		printColsFromFile(file, num_of_cols);
		
	}

	fclose(file);
}

long int getFileSize(FILE *file)
{
	long int saver, res;
	saver = ftell(file);
	fseek(file, 0, SEEK_END);
	res = ftell(file);
	fseek(file, saver, SEEK_SET);
	return res;
}

void printName(FILE *fp)
{
	char *name;
	int nameLen;
	fread(&nameLen, sizeof(int), 1, fp);
	name = (char*)malloc((nameLen + 1) * sizeof(char));
	fread(name, sizeof(char), nameLen, fp);
	name[nameLen] = '\0';
	printf("\nThe name of the participant is: %s\n", name);
}

void printColsFromFile(FILE *fp, int num_of_cols)
{
	int i;

	printf("The form filled by the participant is:\n");
	for (i = 0; i < num_of_cols; i++)
	{
		printSingleColFromFile(fp);
		printf("\n");
	}
}

void printSingleColFromFile(FILE *fp)
{
	int i;
	BYTE *arr;
	//arry to store the column - size of 3 chars
	arr = (BYTE*)malloc(COMPRESSED_COL_SIZE * sizeof(BYTE));
	//set array with values from file
	fread(arr, sizeof(BYTE), COMPRESSED_COL_SIZE, fp);
	for (i = 0; i < COMPRESSED_COL_SIZE; i++)
	{
		printByte(arr[i]);
	}
	free(arr);
}

void printByte(BYTE val)
{
	//mask1 will extrat the first number entered and mask2 the one after
	BYTE mask1 = 0xF0; // 11110000
	BYTE mask2 = 0x0F; // 00001111
	mask1 = (mask1 & val) >> 4;
	//extract the number inserted earlier
	printf("%d  ", mask1);
	printf("%d  ", mask2 & val);
}

void printWinningColFromFile(FILE *fp)
{
	long int winnnig_col_pos, saver;
	printf("The winning col is:\n");
	saver = ftell(fp);
	fseek(fp, -COMPRESSED_COL_SIZE, SEEK_END);
	winnnig_col_pos = ftell(fp);
	printSingleColFromFile(fp);
	fseek(fp, saver, SEEK_SET);
}