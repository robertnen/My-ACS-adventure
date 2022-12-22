#include <stdio.h> //rezolvata deja pe ocw
#define BUFMAX 1005
 
int main(int argc, char *argv[])
{
	FILE *dest, *src;
	int i;
	char buffer[BUFMAX];
	dest = fopen(argv[1], "w");
	if (!dest)
	{
		fprintf(stderr, "Eroare! Nu am putut deschide fisierul destinatie!\n");
		return 0;
	}
	for (i = 2; i < argc; ++i)
	{
		src = fopen(argv[i], "r");
		if (!src)
		{
			fprintf(stderr, "Eroare! Nu am putut deschide fisierul sursa (%d)!\n", i);
			return 0;
		}
		while (fgets(buffer, BUFMAX, src) != NULL)
		        fputs(buffer, dest);
		fclose(src);
	}
	fclose(dest);
	return 0;
}