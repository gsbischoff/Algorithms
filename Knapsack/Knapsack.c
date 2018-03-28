#include <stdio.h>
#include <string.h>

//#define MAX(a,b) (a>b?a:b)

int
main(int argc, char **argv)
{
	if(argc != 3)
		return(0);

	//char *A = argv[1];
	//char *B = argv[2];



	int i = ;
	int p = ;

	int v[i], w[i];

	int S[i + 1][p + 1];
	int T[i + 1][p + 1];

	memset(S, 0, sizeof(int) * (i + 1) * (p + 1));
	memset(T, 0, sizeof(int) * (i + 1) * (p + 1));

	for (int k = 1; k <= i; ++k)
	{
		for (int j = 1; j <= p; ++j)
		{
			if (S[k-1][j] > S[k-1][j-w[k]] + v[k])
			{
				S[k][j] = S[k-1][j];
				T[k][j] = 0;
			}
			else
			{
				S[k][j] = S[k-1][j-w[k]] + v[k];
				T[k][j] = 1;
			}
		}
	}

	printf("Max value is %d\n", S[i][p]);

	return(0);
}