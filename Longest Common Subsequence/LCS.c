#include <stdio.h>
#include <string.h>

#define MAX(a,b) (a>b?a:b)

int
main(int argc, char **argv)
{
	if(argc != 3)
		return(0);

	char *A = argv[1];
	char *B = argv[2];

	int n = strlen(A);
	int m = strlen(B);

	int S[n + 1][m + 1];

	memset(S, 0, sizeof(int) * (n + 1) * (m + 1));

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			if (A[i-1] == B[j-1])
				S[i][j] = S[i-1][j-1] + 1;
			else
				S[i][j] = MAX( S[i-1][j], S[i][j-1] );
		}
	}

	char str[S[n][m] + 1];
	int z = 0;

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			int t = S[i][j] - 1;
			if(S[i-1][j-1] == t
				&& S[i][j-1] == t
				&& S[i-1][j] == t)
			{
				str[z] = A[i-1];
				z++;
			}
				
		}
	}
	str[z] = '\0';

	printf("LCS is len %d; \"%s\"\n", S[n][m], str);

	return(0);
}