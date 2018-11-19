#include "List.h"
#include "Utilities.h"
#include "files.h"

void main(int argc , char **argv)
{
	ParticipantList participants;
	FILE *file = NULL;
	int *winningCol = NULL;
	int choice = 0, i = 0;
	srand(time(NULL));
	choice = getMainMenuChoiceFromUser();

	switch (choice)
	{
	case 1:
		participants = startLottery();
		break;
	case 2:
		file = fopen(FILE_NAME, "rb");
		if (file == NULL)
			printf("\nThe lottery hasn't took place yet!\n");
		else
			printLastLotteryResults();
		break;
	case 3:
		printf("\nThanks for using the simulator!\n\n");
		exit(01);
		break;
	}
	
	//get winning col
	winningCol = getWinningCol();
	printWinningCol(winningCol);
	if (choice || file != NULL) {
		updateHits(&participants, winningCol);
		//print participant list as requested
		printParticipantList(&participants, participants.num_of_participants);
		choice = continueSavingMessage();
	}
		
	
	if (choice == 1)	
		saveLotteryToFile(&participants, participants.num_of_participants, winningCol);
	else
	{
		printf("\nExiting without saving...\n");
		exit(01);
	}
	
}