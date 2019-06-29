#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n = 0, i;
	char aux;
	char * ar = (char *) malloc (sizeof(char));
	scanf("%[^\n]", ar);
	while( ar[n]!= '\0') n++;
	for(i = 0; i < n/2; i++)
	{
		aux = ar[i]; 
		ar[i] = ar[n-1-i]; 
		ar[n-1-i] = aux;
	}
	printf("%s", ar);
	return 0;
}