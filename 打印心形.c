#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int i, j;
	for (i = 1; i <= 3; i++) {
		for (j = 1; j <= 4 - i; j++) {
			printf(" ");
		}
		for (j = 1; j <= 2*i+1; j++) {
			if(j%2==1) printf(" ");
			else printf("*");
		}
		for (j = 1; j <= 9 - 2 * i; j++) {
			printf(" ");
		}
		for (j = 1; j <= 2 * i + 1; j++) {
			if (j % 2 == 1) printf(" ");
			else printf("*");
		}
		printf("\n");
	}

	return 0;
}
