#include <stdio.h> //rezolvata deja pe ocw
#define BUFMAX 1005
 
int main(int argc, char **argv)
{
    FILE *pFile;
    char buffer[BUFMAX];
 
    pFile = fopen("myfile.txt" , "r");
    if (pFile == NULL)
        printf("Nu s-a putut deschide fisierul");
 
    while (fgets(buffer, BUFMAX, pFile) != NULL) {
		printf("%s", buffer);
    }
	fclose(pFile);
}