#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
print(int n, int m, char S[n][m], char *X, char *Y)
{
	for(int a = 0; a < n; ++a)
	{
		for(int b = 0; b < m; ++b)
		{
			if(a < 1 && b < 1)
				printf("  ");
			else if(a < 1)
				printf("%c ", Y[b]);
			else if(b < 1)
				printf("%c ", X[a]);
			else
				printf("%1d ", S[a][b]);
		}
		putc('\n', stdout);
	}
}
//   yyy
// x|---
// x|
// x|
int
main(int argc, char **argv)
{
	if(argc != 4)
		return(0);

	// X[i], Y[j], Z[i + j]
	// Interleave(i,j)
	//  Returns whether two strings are interleaved
	// 	I(i,j) = (Z[i + j] == X[i] && I(i-1,j))
	//		  || (Z[i + j] == Y[j] && I(i,j-1))
	char *X = argv[1];
	char *Y = argv[2];
	char *Z = argv[3];

	int n = strlen(X);
	int m = strlen(Y);

	char S[n + 1][m + 1];

	memset(S, 1, sizeof(char) * (n + 1) * (m + 1));
	S[0][1] = 1;
	S[1][0] = 1;

	for(int a = 0; a < n; ++a)
	{
		for(int b = 0; b < m; ++b)
		{
			printf("%c == %c or %c == %c\n", Z[a + b], X[a], Z[a + b], Y[b]);
			S[a + 1][b + 1] = (Z[a + b] == X[a] && S[a - 1][b])
				   || (Z[a + b] == Y[b] && S[a][b - 1]);
			printf("\tS[%d][%d] = %d\n", a + 1, b + 1, S[a + 1][b + 1]);
		}
	}

	print(n + 1, m + 1, S, X, Y);

	printf("\"%s\" %s an interleaving of \"%s\" and \"%s\".\n", Z, S[n][m]? "IS": "IS NOT", X , Y);

	return(0);
}