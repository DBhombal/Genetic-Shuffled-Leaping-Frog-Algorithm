/***************************************************************
Muhammad Bhombal(T00662679) Final Project 
Enhanced Simplified Genetic Algorithm
Inspired by the frog algorithm from assignment 3
The same fitness function will be used but the range will differ
They also will not be sorted into memeplexes
***************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Bhombal_lab3_Frog_Modified.h"
#pragma warning(disable : 4996) //Allows my compiler to compile with fopen


//Global Declarations
double population[1000];
double x[1000];
double y[1000];
double f, e, bestF, goldenFrog, goldenFrogOld, gFrog, gFrogOld, xTemp, yTemp;
int min, genCount = 0, pMainComplete = 0, pChildComplete = 0;
char buffer[1000000000];
char buffer2[100000];

double pop2[100];
double memeplex2[5][20];

FILE* gF;
FILE* sF;
/*double temp1[8], temp2[8], temp3[8], temp4[8], temp5[8];
double x2, y2, f2, e, goldenFrog2 = 0, goldenFrogOld2 = 0, bestX = 0, bestXplus = 0;
int genCount2 = 0;
int count0 = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0;*/


/**************************************************************************************
Sets the X value
For future generations, the X value will be inherited, and the Y value will be rerolled
**************************************************************************************/
void setX(int i)
{
	/**********************************
	Setting to - 2 to 2 for a base case
	CHANGE LATER
	***********************************/
	double nearest = min + ((double)rand()/(double)(RAND_MAX))*4;
	x[i] = round(nearest * 100000) / 100000; //Rounds to 4 Decimal places
}

double setXTemp()
{
	double nearest = min + ((double)rand() / (double)(RAND_MAX)) * 4;
	xTemp = round(nearest * 100000) / 100000; //Rounds to 4 Decimal places
	return xTemp;
}

/***************************************************
Sets the Y value
For future generations, The Y value will be rerolled
***************************************************/
void setY(int i)
{
	/**********************************
	Setting to - 2 to 2 for a base case
	CHANGE LATER
	***********************************/
	double nearest = min + ((double)rand() / (double)(RAND_MAX)) * 4;
	y[i] = round(nearest * 100000) / 100000; //Rounds to 4 Decimal places
}

double setYTemp()
{
	double nearest = min + ((double)rand() / (double)(RAND_MAX)) * 4;
	yTemp = round(nearest * 100000) / 100000; //Rounds to 4 Decimal places

	return yTemp;
}

//Currently The same fitness function as assignment3
double setFitness(int i)
{
	double numerator, denominator, holder;
	e = 2.71828183;

	denominator = pow(e, (pow(x[i], 2) + pow(y[i], 2)));
	numerator = (7 * x[i] * y[i]);

	if (denominator != 0)
	{
		holder = numerator / denominator;
		f = round(holder * 100000) / 100000;
	}
	return f;
}

//C does not support Overloading so I must make a new method
double newFitness(double x, double y)
{
	double numerator, denominator, holder;
	e = 2.71828183;

	denominator = pow(e, (pow(x, 2) + pow(y, 2)));
	numerator = (7 * x * y);

	if (denominator != 0)
	{
		holder = numerator / denominator;
		f = round(holder * 100000) / 100000;
	}
	return f;
}

//Lower values are better
void setGoldenFrog()
{
	/********************************************************************************
	population[] should be sorted in ascending order when this is called
	sets the first 2 indexes as the golden frogs
	Should the change between golden frogs be less than 0.005, the program will end
	********************************************************************************/

	if (goldenFrog != population[0])
	{
		goldenFrog = population[0];
		goldenFrogOld = population[1];

		fprintf(gF, "New Golden Frog: %8.5f, Generation: %2d\n", goldenFrog, genCount);	
	}
}

//Sorts and keeps the best 50 frogs
//The remaining 950 will be replaced with future generations
void sortAscendingOrder()
{
	double temp, tempX, tempY;
	int j, count;

	//Sorts 1/10 of the population in ascending order
	for (count = 0; count < 100; count++)
	{
		for (j = 0; j < 1000; j++)
		{
			if (population[j] > population[count])
			{
				temp = population[count];
				tempX = x[count];
				tempY = y[count];

				x[count] = x[j];
				y[count] = y[j];

				population[count] = population[j];
				population[j] = temp;

				x[j] = tempX;
				y[j] = tempY;
			}
		}
	}
}

void newGeneration()
{
	int i;
	//Only the best 50 frogs are kept and the rest replaced with crossovers from new generations
	for (i = 5; i < 1000; i++)
	{
		/**************************************************************
		Mutations and crossovers
		The newFitness() function is called inside of a if statement
		It is checked with one inherited value, and one random value
		Depending on which one has a lower value, either the value of
		x[j] or y[j] is replaced with tempX or tempY, the other is kept
		**************************************************************/



		/****************************************************************************************
		* This Code Segment somehow forces the program to terminate after 24 generations
		* It also stops at the same point every time -1.2807 instead of -1.2870(+- 0.0005)
		* I am not sure why but thought it was interesting so I kept it
		* The golden frog before the last one is always the same aswell, -1.2802 at generation 18
		*****************************************************************************************
		* 
		if ((newFitness(x[i], setYTemp()) > (newFitness(setXTemp(), y[i]))))
			y[i] = yTemp;

		else if ((newFitness(x[i], setYTemp())) < (newFitness(setXTemp(), y[i])))
			x[i] = xTemp;
		*/
		
		
		if ((newFitness(x[0], setYTemp()) > (newFitness(setXTemp(), y[0]))))
		{
			y[i] = y[0];
			x[i] = xTemp;
		}

		else if ((newFitness(x[0], setYTemp())) < (newFitness(setXTemp(), y[0])))
		{
			x[i] = x[0];
			y[i] = yTemp;
		}

		else
			setY(i); 
		
		population[i] = newFitness(x[i], y[i]);
	}
	genCount++;
}

//Returns 1 to end the program
//Returns 0 to keep running
int endCase()
{
	//Case Both Negative
	if ((goldenFrog < 0) && (goldenFrogOld < 0))
	{
		if ((goldenFrogOld - goldenFrog) < 0.00005)
			return 1;
	}
	return 0;
}



void main()
{
	int end, end2;
	int i, j, k, id;

	int msec = 0, msec2 = 0;
	clock_t before = clock(), before2 = clock();
	clock_t difference;
	clock_t difference2;

	gF = fopen("geneticOut.txt", "w+");
	sF = fopen("shuffledOut.txt", "w+");

	if (gF == NULL)
		exit(-1);

	if (sF == NULL)
		exit(-1);

	goldenFrog = 0;
	goldenFrogOld = 0;
	min = -2;
	id = fork();
	srand(time(NULL));
	
	if (id == 0)
	{
	//Child
	//loops 100 times

	for (k = 0; k < 100; k++)
	{
		setX2();
		setY2();

		//Assigns the fitness value of each frog to pop[i]
		setPop(k);
		distribute(k);

		//	fprintf(sF,"Frog #%3d, X = %8.5f, Y = %8.5f, F = %8.5f\n", k + 1, getX2(), getY2(), getPop(k)); Limiting needless print statements to limit fileSize
	}
	fprintf(sF, "\n\n");

	//Loops Steps 3 - 5 100 times
	do
	{
		sortMemeplex();
		setGoldenFrogV2(sF);
		shuffleFrogs();
		resetMemeplexes();
		end2 = endCase2();

		difference2 = clock() - before2;
		msec2 = difference2 * 1000 / CLOCKS_PER_SEC;
	} while (end2 != 1);

	fprintf(sF, "Shuffling frog algorithm time taken: %d seconds %d milliseconds, Generations: %d\n", msec2 / 1000, msec2 % 1000, getGenCount2() - 1);
	pChildComplete = 1;

	}
	else
	{
	//Main
	//Initial Pop of 100
	for (i = 0; i < 1000; i++)
	{
		setX(i);
		setY(i);
		population[i] = setFitness(i);

		fprintf(gF, "Frog #%4d, X = %8.5f, Y = %8.5f, F = %8.5f\n", i + 1, x[i], y[i], population[i]);  //This line made the file too large to read fully but, it does not work without this line of code
	}

	//	fprintf(gF, "\n\n");

	sortAscendingOrder();
	setGoldenFrog();

	//Continues looping until the change in new golden frogs is negligible
	do
	{
		newGeneration();
		sortAscendingOrder();
		setGoldenFrog();
		end = endCase();

		//Tracks how long the program has been running
		difference = clock() - before;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (end != 1);
	pMainComplete = 1;
	fprintf(gF, "Genetic algorithm time taken: %d seconds %d milliseconds, Generations: %d\n", msec / 1000, msec % 1000, genCount);
	}
	
	if ((id > 0) && (pMainComplete == 1) && (pChildComplete == 1))
	{
		if (msec < msec2)
		{
			printf("The Genetic algorithm was faster, by %d seconds and %d milliseconds, Generations: %d", (msec2 - msec) / 1000, (msec2 - msec) % 1000, genCount);
			fread(buffer, sizeof(buffer), 1, gF);
		}
		else if (msec > msec2)
		{
			printf("The Shuffled algorithm was faster, by %d seconds and %d milliseconds, Generations: %d", (msec - msec2) / 1000, (msec - msec2) % 1000, genCount);
			fread(buffer, sizeof(buffer), 1, sF);	
		}
		else if (msec == msec2)
			printf("Both programs took exactly the same amount of time");
	printf("%s", buffer);
	}
	fclose(gF);
	fclose(sF);
}
