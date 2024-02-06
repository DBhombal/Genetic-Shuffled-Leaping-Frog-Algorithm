#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable : 4996)
//Declare Variables
double pop[100];
double memeplex[5][20];

double x2, y2, f2, e, goldenFrog2 = 0, goldenFrogOld2 = 0, bestX = 0, bestXplus = 0;
int min, genCount2 = 0;


//In final
FILE* f;

//Assigns x to a random number between -2 and 2, decimals inclusive
void setX2()
{
	double nearest = min + ((double)rand()/(double)(RAND_MAX)) * 4;
	x2 = round(nearest * 10000000) / 10000000;

	//Closest negative number to 0
	if (x2 < bestX < 0)
		bestX = x2;

	//Closest positive number to 0
	if (0 < bestX < x2)
		bestXplus = x2;
}

double getX2()
{
	return x2;
}

//Assigns y to a random number between -2 and 2, decimals inclusive
void setY2()
{
	double nearest = min + ((double)rand() / (double)(RAND_MAX)) * 4;
	y2 = round(nearest * 10000000) / 10000000;
}

double getY2()
{
	return y2;
}


//Randomly distributes all the frogs across the 5 memeplexes
void distribute(int i)
{
	
	int count0 = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0;
	int r = rand() % 5;

	//Set to the first memeplex2
	if (r == 0)
	{
		memeplex[r][count0] = pop[i];
		count0++;
	}
	//Set to second memeplex2
	else if (r == 1)
	{
		memeplex[r][count1] = pop[i];
		count1++;
	}
	//Set to third memeplex2
	else if (r == 2)
	{
		memeplex[r][count2] = pop[i];
		count2++;
	}
	//Set to fourth memeplex2
	else if (r == 3)
	{
		memeplex[r][count3] = pop[i];
		count3++;
	}
	//Set to last memeplex2
	else if (r == 4)
	{
		memeplex[r][count4] = pop[i];
		count4++;
	}
	
}

double getPop(int i)
{
	return pop[i];
}

//Lower values are better

double setFitness2()
{
	double numerator, denominator, holder;
	e = 2.71828183;

	denominator = pow(e, (pow(x2, 2) + pow(y2, 2)));
	numerator = (7 * x2 * y2);

	if (denominator != 0)
	{
		holder = numerator / denominator;
		f2 = round(holder * 10000000) / 10000000;
	}
	return f2;
}

void setPop(int i)
{
	pop[i] = setFitness2();
}

void setGoldenFrog2()
{
	int i;

	//Sets the golden frog to the frog with the best fitness score in memeplex0
	for (i = 0; i < 5; i++)
	{
		if (memeplex[i][0] < goldenFrog2)
		{
			goldenFrogOld2 = goldenFrog2;
			goldenFrog2 = memeplex[i][0];

			printf( "New Golden Frog, Fitness value: %8.5f, Generation: %2d\n", memeplex[i][0], getGenCount2());
		}
	}
}

void setGoldenFrogV2(FILE* f)
{
	int i;

	//Sets the golden frog to the frog with the best fitness score in memeplex0
	for (i = 0; i < 5; i++)
	{
		if (memeplex[i][0] <= goldenFrog2)
		{
			 
			goldenFrogOld2 = goldenFrog2;
			goldenFrog2 = memeplex[i][0];

			fprintf(f, "New Golden Frog, Fitness value: %8.5f, Generation: %2d\n", memeplex[i][0], getGenCount2());
		}
	}
}

double getGoldenFrog2()
{
	goldenFrog2 = round(goldenFrog2 * 100000) / 100000;
	return goldenFrog2;
}

//Sorts all the memeplexes in ascending order
void sortMemeplex()
{
	int m, count, j;
	double temp;
	//Loop for the different memeplexes
	for (m = 0; m < 5; m++)
	{
		for (count = 0; count < 20; count++)
		{
			//Loop to sort through each memeplex2 individually
			for (j = 0; j < 20; j++)
			{
				//Will Sort memeplexes in ascending order
				if (memeplex[m][j] > memeplex[m][count])
				{
					temp = memeplex[m][count];
					memeplex[m][count] = memeplex[m][j];
					memeplex[m][j] = temp;
				}
			}	
		}
	}
}

void shuffleFrogs()
{
	int i, j;
	double temp1[8], temp2[8], temp3[8], temp4[8], temp5[8];
	for (i = 0; i < 5; i++)
	{
		//Gets the best 8 frogs and sends 2 to a different memeplex2
		for (j = 0; j < 8; j++)
		{
			//Best 8 frogs are stored in temp[j]
			temp1[j] = memeplex[0][j];
			temp2[j] = memeplex[1][j];
			temp3[j] = memeplex[2][j];
			temp4[j] = memeplex[3][j];
			temp5[j] = memeplex[4][j];
		}
		switch (i)
		{
			//Each case sends the frogs to different indexes in the target memeplexes but replaces the ones that were stored in temp array 
		case 0:

			memeplex[1][0] = temp1[0];
			memeplex[1][1] = temp1[1];

			memeplex[2][0] = temp1[2];
			memeplex[2][1] = temp1[3];

			memeplex[3][0] = temp1[4];
			memeplex[3][1] = temp1[5];

			memeplex[4][0] = temp1[6];
			memeplex[4][1] = temp1[7];

		case 1:

			memeplex[0][0] = temp2[0];
			memeplex[0][1] = temp2[1];

			memeplex[2][2] = temp2[2];
			memeplex[2][3] = temp2[3];

			memeplex[3][2] = temp2[4];
			memeplex[3][3] = temp2[5];

			memeplex[4][2] = temp2[6];
			memeplex[4][3] = temp2[7];

		case 2:

			memeplex[0][2] = temp3[0];
			memeplex[0][3] = temp3[1];

			memeplex[1][2] = temp3[2];
			memeplex[1][3] = temp3[3];

			memeplex[3][4] = temp3[4];
			memeplex[3][5] = temp3[5];

			memeplex[4][4] = temp3[6];
			memeplex[4][5] = temp3[7];

		case 3:

			memeplex[0][4] = temp4[0];
			memeplex[0][5] = temp4[1];

			memeplex[1][4] = temp4[2];
			memeplex[1][5] = temp4[3];

			memeplex[2][4] = temp4[4];
			memeplex[2][5] = temp4[5];

			memeplex[4][6] = temp4[6];
			memeplex[4][7] = temp4[7];

		case 4:

			memeplex[0][6] = temp5[0];
			memeplex[0][7] = temp5[1];

			memeplex[1][6] = temp5[2];
			memeplex[1][7] = temp5[3];

			memeplex[2][6] = temp5[4];
			memeplex[2][7] = temp5[5];

			memeplex[3][6] = temp5[6];
			memeplex[3][7] = temp5[7];
		}
	}
}

void resetMemeplexes()
{
	int i, j;
	for (i = 0; i < 5; i++)
	{
		for (j = 8; j < 20; j++)
		{
			setX2();
			setY2();

			memeplex[i][j] = setFitness2();
		}
	}
	genCount2++;
}

int getGenCount2()
{
	return genCount2;
}

int endCase2()
{
	//Algorithm stops when the change between golden frogs is less than 0.0005
	if ((goldenFrog2 < 0) && (goldenFrogOld2 < 0))
	{
		if ((goldenFrogOld2 - goldenFrog2) < 0.00005)
			return 1;
	}
	return 0;

}