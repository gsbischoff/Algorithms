#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define MAX(a,b) (a>b?a:b)

int
main(int argc, char **argv)
{
	if(argc % 2 != 0 && argc > 2)
		return(0);

	int i = (argc - 2) / 2;		// number of items [value-weight pairs]
	int p = atoi(argv[1]);

	printf("i: %d, p: %d\n", i, p);

	int v[i], w[i];

	for (int k = 0; k < i; ++k)
	{
		v[k] = atoi(argv[2*k + 2]);
		w[k] = atoi(argv[2*k + 3]);

		printf("v[%d] = %d, w[%d] = %d\n", k, v[k], k, w[k]);
	}	

	int S[i + 1][p + 1];
	int T[i + 1][p + 1];	// truth values, for 'added'

	memset(S, 0, sizeof(int) * (i + 1) * (p + 1));
	memset(T, 0, sizeof(int) * (i + 1) * (p + 1));
	printf("S[i][p] = %d\n", S[i][p]);

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