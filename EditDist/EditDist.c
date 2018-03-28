#include <stdio.h>
#include <string.h>

#define MIN(a,b) a<b?a:b

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

	//printf("%s %s\n", A, B);

	for (int x = 0; x <= m; ++x) S[0][x] = x;
	for (int y = 0; y <= n; ++y) S[y][0] = y;

	for (int i = 1; i <= n; ++i)
	{
		
		for (int j = 1; j <= m; ++j)
		{
			//printf("%c = %c\n", A[i-1], B[i-1]);
			if (A[i-1] == B[j-1])
			{
				//printf("S[%d][%d] = %d\n", i, j, S[i-1][j-1]);
				S[i][j] = S[i-1][j-1];
			}
			else
			{
				int q = S[i-1][j]+1;
				int r = S[i][j-1]+1;
				int s = S[i-1][j-1]+1;

				int t = MIN(q,r);
				//printf("S[%d][%d] = %d\n", i, j, MIN(t,s));
				S[i][j] = MIN(t,s);
			}
		}
	}

	//return S[n,m];
	printf("EditDist is %d\n", S[n][m]);
//*/
	return(0);
}