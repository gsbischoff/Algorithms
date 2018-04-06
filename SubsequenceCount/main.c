#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
C(char *X, char *Y)
{
	if(X[0] == '\0' || Y[0] == '\0')
		return 0;
	if(X[1] == '\0' && X[0] == Y[0])
		return 1 + C(&X[0], &Y[1]);
	if(X[0] == Y[0])
		return C(&X[1], &Y[1]) + C(&X[0], &Y[1]);
	else
		return C(&X[0], &Y[1]);
}

void
printa(int x, int y, int S[x][y])
{
	for(int i = 0; i < x; i++)
	{
		for(int j = 0; j < y; j++)
		{
			//S[i][j] = y*i + j;
			printf("%d\t", S[i][j]);
			
		}
		printf("\n");
	}
	printf("\n");
}

int
CDynamic(char *X, char *Y)
{
	int xlen = strlen(X);
	int ylen = strlen(Y);

	int S[xlen + 1][ylen + 1];

	memset(&S[0][0], 0, sizeof(int) * (xlen + 1) * (ylen + 1));
	for(int i = 0; i < ylen + 1; i++)
		S[xlen][i] = 1;

	for(int i = xlen - 1; i >= 0; i--)
	{
		for(int j = ylen - 1; j >= 0; j--)
		{
			if(X[i] == Y[j])
				S[i][j] = S[i][j + 1] + S[i + 1][j + 1];
			else
				S[i][j] = S[i][j + 1];
		}
	}

	return S[0][0];
}

int
main(int argc, char **argv)
{
	char *X, *Y;

	if(argc == 3)
	{
		X = argv[1];
		Y = argv[2];
	}
	else
		return(0);

	int result = CDynamic(X, Y);

	printf("The number of times the subsequence \"%s\" appears in \"%s\" is %d.\n", X, Y, result);


	


	
	return(0);
}