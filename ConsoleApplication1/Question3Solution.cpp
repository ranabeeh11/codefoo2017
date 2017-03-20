#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

//Rameal Nabeeh
//IGN Code Foo 2017 Question 3


//struct for the 3 by 3 grid
struct grid {
	int numb;
	struct grid *TL; //create a link for each direction a node can go
	struct grid *T;
	struct grid *TR;
	struct grid *L;
	struct grid *R;
	struct grid *BL;
	struct grid *B;
	struct grid *BR;
};

struct valid {
	int numb; //record the current valid link
	int taken[10] = {10,10,10,10,10,10,10,10,10,10}; //remember which paths have been taken
	struct valid *next; 
	struct valid *previous;
	struct grid* from; //jump back to a specific node
};

struct validHolder {
	struct valid *hold; //contains all valid links in one location
	struct validHolder *next;
	struct validHolder *previous;
};

struct returnDir {
	struct grid* current; //gridHold
	int plus; //plus for sum
	struct valid* vald; //vald for valid
};

struct arrHolder {
	int val[6] = {10,10,10,10,10,10};
	int count;
	struct arrHolder *next;
	struct arrHolder *previous;
};

//GRID PRINT FUNCTION 
void printGrid(struct grid *start)
{
	cout << start->numb << "---";
	cout << start->R->numb << "---";
	cout << start->R->R->numb << "\n";
	cout << "|   |   |\n";
	cout << start->B->numb << "---";
	cout << start->BR->numb << "---";
	cout << start->BR->R->numb << "\n";
	cout << "|   |   |\n";
	cout << start->B->B->numb << "---";
	cout << start->B->BR->numb << "---";
	cout << start->B->BR->R->numb << "\n\n";
}

//GRID CONSTRUCTION FUNCTION
struct grid *constructGrid(int init[])
{
	//LOCAL VARIABLES
	int count = 9;
	struct grid *gridNew, *gridTL, *gridTM, *gridTR, *gridML, *gridMM, *gridMR, *gridBL, *gridBM, *gridBR;
	gridTL = NULL; 
	gridTM = NULL;
	gridTR = NULL;
	gridML = NULL;
	gridMM = NULL;
	gridMR = NULL;
	gridBL = NULL;
	gridBM = NULL;
	gridBR = NULL;

	//KEEP CREATING NEW GRID NODES AND ADDING THEM TO THE GRID 9 TIMES
	while (count != -1)
	{
		gridNew = new grid();
		gridNew->numb = init[count];
		gridNew->TL = NULL;
		gridNew->T = NULL;
		gridNew->TR = NULL;
		gridNew->L = NULL;
		gridNew->R = NULL;
		gridNew->BL = NULL;
		gridNew->B = NULL;
		gridNew->BR = NULL;
		switch (count)//EACH NODE HAS UNIQUE CONNECTIONS AND NAMES
		{
		case(9)://GRID TOP LEFT
			gridTL = gridNew;
			break;
		case(8)://GRID MIDDLE LEFT
			gridML = gridNew;
			gridML->T = gridTL;
			gridTL->B = gridML;
			break;
		case(7)://GRID BOTTOM LEFT
			gridBL = gridNew;
			gridML->B = gridBL;
			gridBL->T = gridML;
			break;
		case(6)://GRID TOP MIDDLE
			gridTM = gridNew;
			gridTM->L = gridTL;
			gridTL->R = gridTM;
			gridTM->BL = gridML;
			gridML->TR = gridTM;
			break;
		case(5)://GRID MIDDLE MIDDLE
			gridMM = gridNew;
			gridMM->L = gridML;
			gridML->R = gridMM;
			gridMM->TL = gridTL;
			gridTL->BR = gridMM;
			gridMM->T = gridTM;
			gridTM->B = gridMM;
			gridMM->BL = gridBL;
			gridBL->TR = gridMM;
			break;
		case(4)://GRID BOTTOM MIDDLE
			gridBM = gridNew;
			gridBM->L = gridBL;
			gridBL->R = gridBM;
			gridBM->TL = gridML;
			gridML->BR = gridBM;
			gridBM->T = gridMM;
			gridMM->B = gridBM;
			break;
		case(3)://GRID TOP RIGHT
			gridTR = gridNew;
			gridTR->L = gridTM;
			gridTM->R = gridTR;
			gridTR->BL = gridMM;
			gridMM->TR = gridTR;
			break;
		case(2)://GRID MIDDLE RIGHT
			gridMR = gridNew;
			gridMR->L = gridMM;
			gridMM->R = gridMR;
			gridMR->T = gridTR;
			gridTR->B = gridMR;
			gridMR->TL = gridTM;
			gridTM->BR = gridMR;
			gridMR->BL = gridBM;
			gridBM->TR = gridMR;
			break;
		case(1)://GRID BOTTOM RIGHT
			gridBR = gridNew;
			gridBR->L = gridBM;
			gridBM->R = gridBR;
			gridBR->T = gridMR;
			gridMR->B = gridBR;
			gridBR->TL = gridMM;
			gridMM->BR = gridBR;
			break;
		default:
			count = 0;
			break;
		}
		count--;
	}
	return gridTL;
}

//FUNCTION TO PRINT VALIDS
void quickPrint(struct arrHolder *arrHead)
{
	struct arrHolder *arrHold;

	//QUICK PRINT
	arrHold = arrHead;
	while (arrHold != NULL)
	{
		for (int i = 0; i < sizeof(arrHold->val) / 4; i++)
		{
			if (arrHold->val[i] != 10)
			{
				if (arrHold->val[i + 1] == 10)
				{
					cout << arrHold->val[i] << " =" << " ";
				}
				else
				{
					cout << arrHold->val[i] << " +" << " ";
				}
			}
		}
		cout << "9 \n";
		arrHold = arrHold->next;
	}
}

//FUNCTION TO VALIDATE IF A PATH HAS BEEN TAKEN ALREADY
bool validateTaken(struct valid *val, int hold)
{
	int skip = 0;
	
	//IF A VALID ALREADY HAS A NUMBER IN ITS TAKEN PATH LIST THEN RETURN TRUE
	for (int i = 0; i < sizeof(val->taken) / 4; i++)
	{
		if (val->taken[i] == hold)
		{
			skip = 1;
		}
	}

	if (skip == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//CHANGE VALIDHOLDER TO A DIFFERENT DATA STRUCTURE TO MAKE REMOVING DUPLICATES EASIER
struct arrHolder *copyHolder(struct validHolder* holderHead)
{
	struct arrHolder *arrHead, *arrHold, *arrNew;
	struct validHolder *holderHold;
	struct valid *vHold;
	arrHead = NULL;
	arrNew = NULL;
	arrHold = NULL;
	int skip = 1;
	int count = 0;

	//LOOP THROUGH ALL VALIDS IN THE VALID HOLDER
	holderHold = holderHead;
	while (holderHold != NULL)
	{
		count = 0;
		skip = 1;
		arrNew = new arrHolder();
		arrNew->previous = NULL;
		arrNew->next = NULL;
		vHold = holderHold->hold;
		//COPY VALIDS TO ARRAY HOLDER
		while (vHold != NULL)
		{
			for (int i = 0; i < sizeof(arrNew->val) / 4; i++)
			{
				if (arrNew->val[i] == 10)
				{
					arrNew->val[i] = vHold->numb;
					break;
				}
			}
			vHold = vHold->next;
		}
		for (int i = 0; i < sizeof(arrNew->val) / 4; i++)
		{
			if (arrNew->val[i] != 10)
			{
				skip = 0;
				count++;
			}
		}
		arrNew->count = count;
		//SKIP IF THIS IS AN EMPTY VALID (IE ALL 10S)
		if (skip == 1)
		{
			free(arrNew);
		}
		//THIS WILL ONLY HAPPEN IF THE VALID IS JUST 9
		else if (count == 1)
		{
			free(arrNew);
		}
		//ELSE ADD SOMEWHERE IN THE LIST
		else if (arrHead == NULL)
		{
			arrHead = arrNew;
		}
		else
		{
			arrHold = arrHead;
			while (arrHold->next != NULL)
			{
				arrHold = arrHold->next;
			}
			arrHold->next = arrNew;
			arrNew->previous = arrHold;
		}

		holderHold = holderHold->next;
	}

	return arrHead;
}

//FUNCTION TO ORGANIZE THE ARRHOLDER BEFORE PRINTING
void organizeHolder(struct arrHolder* arrHead)
{
	struct arrHolder *arrHold, *ar2, *temp;
	int count = 0;
	int shift = 0;
	int numb;
	arrHold = arrHead;
	temp = NULL;

	//LOOK THROUGH EACH NODE IN THE ARRHOLDER AND COMPARE IT TO EVERYTHING DOWN THE LINE
	while (arrHold != NULL)
	{
		numb = arrHold->val[0];
		ar2 = arrHold->next;
		while (ar2!=NULL)
		{
			for (int i = 0; i < arrHold->count; i++)
			{
				if (numb == ar2->val[i])
				{
						count++;
						shift++;
						numb = arrHold->val[shift];
						i = -1;
				}
			}

			//THEY WILL BE THE SAME IF THE CHECK COUNT IS EQUAL TO THE SIZE OF THE NODE COUNT
			if (count == arrHold->count)
			{
				//SO THEN THIS IS A DUPLICATE SO RELINK
				if (ar2->next == NULL)
				{
					ar2->previous->next = NULL;
					temp = ar2;
					ar2 = ar2->previous;
					free(temp);
				}
				else
				{
					ar2->previous->next = ar2->next;
					ar2->next->previous = ar2->previous;
					ar2 = ar2->previous;
					free(temp);
				}
			}

			count = 0;
			shift = 0;
			numb = arrHold->val[shift];
			ar2 = ar2->next;
		}

		arrHold = arrHold->next;
	}

	//PRINT THE VALIDS IN THE RIGHT WAY
	quickPrint(arrHead);
	
}

//FUNCTION TO HANDLE ADDING DIRECTIONS TO A VALID LINK
struct returnDir *handleDir(struct grid* current, struct grid* dir, struct valid* val, int plus)
{
	//val = vhold, current = gridHold, gridHold->dir = dir

	//LOCAL VARIABLES
	int hold;
	struct returnDir *ret = new returnDir();
	struct valid *vNew;
	vNew = NULL;
	hold = dir->numb;

	//ADD IT TO THE VALID LL AND RETURN POINT OF REFERENCE
	plus += hold;
	vNew = new valid();
	vNew->next = NULL;
	vNew->previous = val;
	val->next = vNew;
	vNew->from = current;
	vNew->numb = hold;

	//COPY NEW NUMBER INTO TAKEN LIST
	for (int i = 0; i < sizeof(val->taken)/4; i++)
	{
		if (val->taken[i] == 10)
		{
			val->taken[i] = hold;
			break;
		}
	}
	//COPY ALL OF TAKEN LIST INTO NEW VALID
	for (int i = 0; i < sizeof(val->taken)/4; i++)
	{
		vNew->taken[i] = val->taken[i];
	}
	val = vNew;
	current = dir;

	//CREATE A RETURN
	ret->current = current;
	ret->vald = val;
	ret->plus = plus;
	return ret;
}

//FREE A VALID FROM VALIDHOLDER
struct validHolder *freeValid(struct validHolder* validHold, struct validHolder* holderHead)
{
	struct validHolder *holdTemp;
	//CASE 1: THIS IS THE ONLY VALIDHOLDER ENTRY THEREFORE IT IS THE HEAD
	if (validHold->next == NULL && validHold->previous == NULL)
	{
		holderHead = NULL;
		free(validHold);
		return holderHead;
	}
	else
	{
		//CASE 2 THIS ENTRY IS AT THE END
		if (validHold->next == NULL)
		{
			validHold->previous->next = NULL;
			free(validHold);
			return holderHead;
		}
		else if (validHold->previous == NULL)//CASE 3 THIS ENTRY IS THE HEAD AND WE NEED A NEW HEAD
		{
			holderHead = validHold->next;
			holderHead->previous = NULL;
			free(validHold);
			return holderHead;
		}
		else //CASE 4 THIS ENTRY IS SOMEWHERE IN THE MIDDLE
		{
			validHold->previous->next = validHold->next;
			validHold->next->previous = validHold->previous;
			free(validHold);
			return holderHead;
		}
	}
}

//COPY A VALID
struct returnDir *validCopy(struct valid* validHead, struct validHolder* holderHold)
{
	//LOCAL VARIABLES
	struct valid *newHead, *validHold, *newValid, *newHold;
	struct validHolder *newHolder = new validHolder();
	struct returnDir *ret = new returnDir();
	newHead = NULL;
	newHold = NULL;
	newValid = NULL;
	int s = 0;
	validHold = validHead;

	//CREATE A NEW VALID COPY WITH N-1 NODES
	while (validHold->next != NULL)
	{
		newValid = new valid();

		for (int i = 0; i < (sizeof(validHold->taken) / 4); i++)
		{
			newValid->taken[i] = validHold->taken[i];
		}

		newValid->from = validHold->from;
		newValid->numb = validHold->numb;
		newValid->previous = NULL;
		newValid->next = NULL;

		if (newHead == NULL)
		{
			newHead = newValid;
		}
		else
		{
			newHold = newHead;
			while (newHold->next != NULL)
			{
				newHold = newHold->next;
			}
			newHold->next = newValid;
			newValid->previous = newHold;
		}

		validHold = validHold->next;
	}

	holderHold->next = newHolder;
	newHolder->previous = holderHold;
	newHolder->next = NULL;
	newHolder->hold = newHead;

	//ADD TO THE VALID HOLDER THE NEW VALID
	if(newHold != NULL)
	{
		newHold = newHold->next;
	}
	else
	{
		newHold = newHead;
	}
	ret->current = validHold->from;
	validHold = newHead;
	while (validHold != NULL)
	{
		s += validHold->numb;
		validHold = validHold->next;
	}
	ret->plus = s;
	ret->vald = newHold;
	return ret;
}

int main() {

	//INTRO-------------------------------------------------------

	cout << "Hello whoever is reviewing this code =)\n"
		"This is my solution for the 9x9 grid\n"
		"Hope it's highly readable, have a great day!\n\n";
	
	//VARIABLES----------------------------------------------------

	int init[10] = { 0,1,2,3,4,5,6,7,8,9 }; //initial values for grid 0<=n<=9
	int count = 9; //keeps track of cube count
	int sum = 0; //keeps track of the sum of a link
	int exhausted = 0; //int as a binary to indicate when a link is completely done
	struct grid *gridTL, *gridTM, *gridTR, *gridML, *gridMM, *gridMR, *gridBL, *gridBM, *gridBR, *gridHold, *gridStart, *gridConstant; //necessary struct pointers
	struct valid *vHold, *vNew, *vHead, *vTemp;
	struct validHolder *holderHead, *holderNew, *holderHold;
	struct returnDir* ret;
	struct arrHolder *arrHead;
	gridTL = NULL; //initiate each section to null
	gridTM = NULL;
	gridTR = NULL;
	gridML = NULL;
	gridMM = NULL;
	gridMR = NULL;
	gridBL = NULL;
	gridBM = NULL;
	gridBR = NULL;
	holderHead = NULL;
	ret = NULL;
	
	//CREATE RANDOM INITIAL ARRAY-----------------------------------

	srand(time(0)); //change the seed(initial value) for random number generator to get different results from randshuffle

	random_shuffle(&init[0], &init[10]);
	//int init[10] = {4,8,3,9,7,1,2,0,6,5}; //GOOD TEST ARRAY

	//NOW CONSTRUCT A GRID BASED OFF OF THE RANDOM ARRAY
	
	gridStart= constructGrid(init);
	gridTL = gridStart;
	gridTM = gridStart->R;
	gridTR = gridStart->R->R;
	gridML = gridStart->B;
	gridMM = gridStart->BR;
	gridMR = gridStart->BR->R;
	gridBL = gridStart->B->B;
	gridBM = gridStart->BR->B;
	gridBR = gridStart->BR->BR;

	//PRINT THE GRID 
	
	printGrid(gridTL);

	//NOW ANALYZE GRID

	count = 9;
	while (count != -1)
	{
		if (count != 0)
		{
			//CREATE VALID FOR LATER
			vNew = new valid();
			vNew->next = NULL;
			vNew->previous = NULL;
			vNew->from = NULL;

			//CREATE VALIDHOLDER FOR LATER
			holderNew = new validHolder();
			holderNew->next = NULL;
			holderNew->previous = NULL;
		}

		switch (count)
		{
		case(9):
			gridHold = gridTL;
			break;
		case(8):
			gridHold = gridML;
			break;
		case(7):
			gridHold = gridBL;
			break;
		case(6):
			gridHold = gridTM;
			break;
		case(5):
			gridHold = gridMM;
			break;
		case(4):
			gridHold = gridBM;
			break;
		case(3):
			gridHold = gridTR;
			break;
		case(2):
			gridHold = gridMR;
			break;
		case(1):
			gridHold = gridBR;
			break;
		default:
			count = 0;
			exhausted = 1;
		}

		if (count != 0)
		{
			gridConstant = gridHold;
			vNew->numb = gridHold->numb;//the new valid has an value of it's grid position
			vNew->taken[0] = gridHold->numb; //it has taken itself to remove repeats
			sum = vNew->numb;//the sum starts off with this value
			vHead = vNew; //the start of this iteration is the valid head
			holderNew->hold = vHead; //validholder's first valid is validhead
			//holderHead = holderNew; //holdernew is the holderhead
			//vhhNew->hold = holderHead; //validholderholder's first validholder is holderhead
			vHold = vHead; //validhold starts at the head

			//ADD VALID TO VALIDHOLDER
			if (holderHead == NULL)
			{
				holderHead = holderNew;
			}
			else
			{
				holderHold = holderHead;
				while (holderHold->next != NULL)
				{
					holderHold = holderHold->next;
				}
				holderHold->next = holderNew;
				holderNew->previous = holderHold;
			}
		}

		//TEST LINK UNTIL ALL OPTIONS THAT LEAD TO 9 ARE EXHAUSTED
		while (exhausted != 1)
		{
			if (gridHold->R != NULL && (sum + gridHold->R->numb <= 9) && validateTaken(vHold, gridHold->R->numb) == false)
			{
				ret = handleDir(gridHold, gridHold->R, vHold, sum);
			}
			else if (gridHold->BR != NULL && (sum + gridHold->BR->numb <= 9) && validateTaken(vHold, gridHold->BR->numb) == false)
			{
				ret = handleDir(gridHold, gridHold->BR, vHold, sum);
			}
			else if (gridHold->B != NULL && (sum + gridHold->B->numb <= 9) && validateTaken(vHold, gridHold->B->numb) == false)
			{
				ret = handleDir(gridHold, gridHold->B, vHold, sum);
			}
			else if (gridHold->BL != NULL && (sum + gridHold->BL->numb <= 9) && validateTaken(vHold, gridHold->BL->numb) == false)
			{
				ret = handleDir(gridHold, gridHold->BL, vHold, sum);
			}
			else if (gridHold->L != NULL && (sum + gridHold->L->numb <= 9) && validateTaken(vHold, gridHold->L->numb) == false)
			{
				ret = handleDir(gridHold, gridHold->L, vHold, sum);
			}
			else if (gridHold->TL != NULL && (sum + gridHold->TL->numb <= 9) && validateTaken(vHold, gridHold->TL->numb) == false)
			{
				ret = handleDir(gridHold, gridHold->TL, vHold, sum);
			}
			else if (gridHold->T != NULL && (sum + gridHold->T->numb <= 9) && validateTaken(vHold, gridHold->T->numb) == false)
			{
				ret = handleDir(gridHold, gridHold->T, vHold, sum);
			}
			else if (gridHold->TR != NULL && (sum + gridHold->TR->numb <= 9) && validateTaken(vHold, gridHold->TR->numb) == false)
			{
				ret = handleDir(gridHold, gridHold->TR, vHold, sum);
			}
			else if (sum == 9)
			{
				//ADD VALID TO HOLDER AND CREATE A COPY WITH N-1 NODES
				holderHold = holderHead;
				while (holderHold->next != NULL)
				{
					holderHold = holderHold->next;
				}
				while (vHold->previous != NULL)
				{
					vHold = vHold->previous;
				}
				vHead = vHold;
				ret = validCopy(vHead, holderHold);
				while (vHold->next != NULL)
				{
					vHold = vHold->next;
				}
				//IF THERE IS NO PREVIOUS VALID LIST THEN THIS NODE HAS GONE THROUGH ALL ITERATIONS AND IS EXHAUSTED
				if (vHold->previous == NULL)
				{
					exhausted = 1;
				}
			}
			else {
				//DELETE VALID AND RELINK BECAUSE HEAD HAS NO POSSIBLE OPTIONS
				if (vHold->previous == NULL)
				{
					holderHold = holderHead;
					while (holderHold->next != NULL)
					{
						holderHold = holderHold->next;
					}
					while (vHold->previous != NULL)
					{
						vHold = vHold->previous;
					}
					vHead = vHold;
					//DELETE VALID FUNCTION
					holderHead = freeValid(holderHold, holderHead);
					while (vHold->next != NULL)
					{
						vHold = vHold->next;
					}
					exhausted = 1;
				}
				else
				{
					//IF IT ISN'T THE FIRST VALID THEN MAKE A NEW COPY AND DELETE THE CURRENT VALID FROM THE HOLDER
					holderHold = holderHead;
					while (holderHold->next != NULL)
					{
						holderHold = holderHold->next;
					}
					while (vHold->previous != NULL)
					{
						vHold = vHold->previous;
					}
					vHead = vHold;
					ret = validCopy(vHead, holderHold); //MAKE A COPY
					holderHead= freeValid(holderHold, holderHead); //THEN DELETE FROM HOLDER
					while (vHold->next != NULL)
					{
						vHold = vHold->next;
					}
					//GARBAGE COLLECTION
					vTemp = vHold;
					vHold = vHold->previous;
					free(vTemp);
					vHold->next = NULL;
				}
			}
			
			//SAVE NEW REFERENCE POINT LOCALLY
			if(ret!=NULL)
			{
				gridHold = ret->current;
				vHold = ret->vald;
				sum = ret->plus;
			}

			if (gridHold == NULL)
			{
				gridHold = gridConstant;
			}
		}

		exhausted = 0;
		sum = 0;
		count--;
	}

	arrHead = copyHolder(holderHead);
	//ORGANIZE THE VALIDHOLDER TO REMOVE DUPLICATES
	organizeHolder(arrHead);

	cout << "\nPress enter to end the program...";
	getchar();

	return 0;
}