#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

enum State {NEW, READY, RUNNING, EXIT, BLOCKED};

/*contains information about processes*/
struct PCB {
	int processId;
	int userId;
	int arrivalTime;
	int priority;
	int expectedTimeRemaining;
	int expectedMemoryNeed;
	int expectedPctCPU;
	bool realTime;
	enum State processState;
	int currentPriority;
	int timeWaitingSoFar;
	int timeProcessingLastRun;
	int timeProcessingSoFar;
	struct PCB* nextPtr;
	

};

/*function prototypes*/
void fillPCB(struct PCB* currPCB, int arr[]);

void priorityLevelDisplay(int priority, struct PCB arr[]);

void displayPCB(struct PCB currPCB);


int main() {
	//array of PCBs with room for 600 PCBs
	struct PCB PCBs[600];
	struct PCB currPCB;

	//used to open file and store the name
	FILE* fptr;
	char filename[23];
	int y = 0;
	errno_t err;
	
	//used for information from file for PCBs
	int fromFile[8];
	size_t fr0, fr1, fr2, fr3, fr4, fr5, fr6, fr7;
	int pcbNum = 0;

	//user entered priority number
	int getPri;
	

	/*initializes filename array*/
	for (int x = 0; x < 20; x++) {
		filename[x] = '\0';
	}

	/*initialize PCB array*/
	for (int z = 0; z < 600; z++) {
		currPCB = PCBs[z];
		//z + 1 since process ids start at 1 and array starts at 0
		currPCB.processId = z + 1;
	}

	/*intializes fromFile array*/
	for (int r = 0; r < 8; r++) {
		fromFile[r] = 0;
	}


	/*initial promt for user input*/
	printf("The files available are: \n");
	printf("\t1) processes.txt \n");
	printf("\t2) allprocesses.txt \n");
	printf("Enter the file to be opened: ");

	/*scans in the string for the filename*/
	while (y < 22) {
		scanf_s("%c", &filename[y]);
		if (filename[y] != '\n') {
			y++;
		}
		else {
			filename[y] = '\0';
			break;
		}
		
	}
	

	/*open the file and output potential error*/
	err = fopen_s(&fptr, filename, "r");
	printf("err: %d\n", err);
	if (err != 0) {
		perror("error");
		printf("Can't open the file %s\n", filename);
		getchar();
		return 1;
	}	
	printf("file opened \n");

	
	/*reads in file and fills pcbs*/
	while (1) {
		fr0 = fscanf_s(fptr, "%d", &fromFile[0]);
		fr1 = fscanf_s(fptr, "%d", &fromFile[1]);
		fr2 = fscanf_s(fptr, "%d", &fromFile[2]);
		fr3 = fscanf_s(fptr, "%d", &fromFile[3]);
		fr4 = fscanf_s(fptr, "%d", &fromFile[4]);
		fr5 = fscanf_s(fptr, "%d", &fromFile[5]);
		fr6 = fscanf_s(fptr, "%d", &fromFile[6]);
		fr7 = fscanf_s(fptr, "%d", &fromFile[7]);

		if ((fr0 == 1) && (fr1 == 1) && (fr2 == 1) && (fr3 == 1) && (fr4 == 1) && (fr5 == 1) && (fr6 == 1) && (fr7 == 1)) {
			fillPCB(&PCBs[pcbNum], fromFile);
			displayPCB(PCBs[pcbNum]);
			pcbNum++;
			
		}
		else {
			break;
		}
	}

	/*closes file after everything is read*/
	fclose(fptr);
	
	//prompts user for priority number
	printf("Enter a priority number:\t");
	scanf_s("%d", &getPri);
	priorityLevelDisplay(getPri, PCBs);

	printf("press enter to exit");

	getchar();
	
}
/*function to fill PCB struct whose pointer is passed with info from the array*/
void fillPCB(struct PCB* currPCB, int arr[]) {
	currPCB->processId = arr[0];
	currPCB->userId = arr[1];
	currPCB->arrivalTime = arr[2];
	currPCB->priority = arr[3];
	currPCB->expectedTimeRemaining = arr[4];
	currPCB->expectedMemoryNeed = arr[5];
	currPCB->expectedPctCPU = arr[6];
	currPCB->realTime = arr[7];
	currPCB->processState = NEW;
	currPCB->currentPriority = arr[3];
	currPCB->timeWaitingSoFar = 0;
	currPCB->timeProcessingLastRun = 0;
	currPCB->timeProcessingSoFar = 0;
	//currPCB->nextPtr is not used in this program

}

/*searches array of PCBs and finds/displays PCBs of given priority level*/
void priorityLevelDisplay(int pri, struct PCB arr[]) {
	//sort array unless linear search is used
	struct PCB curr;
	int total = 0;

	
	/*linear search version*/
	for (int x = 0; x < 600; x++) {
		//makes use of us knowing exactly how many PCBs are in the file (500)
		//if processId is over 500, we know data in following spots is invalid because of initialization of array in main
		curr = arr[x];
		if ((curr.priority == pri) && (curr.processId <= 500)) {			
			displayPCB(curr);
			total++;
		}
	}

	if (total == 0) {
		printf("No processes have the entered priority level\n");
	}
	getchar();
}

/*displays PCB struct that is passed*/
void displayPCB(struct PCB currPCB) {
	//reads in and prints values for the PCB
	printf("ID: %d Usr: %d Arr: %d pri: %d Remain: %d Mem: %d CPU: %d\n", currPCB.processId, currPCB.userId, 
		currPCB.arrivalTime, currPCB.priority,
		currPCB.expectedTimeRemaining, currPCB.expectedMemoryNeed, currPCB.expectedPctCPU);
}