#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	FILE *path = fopen(argv[1], "r");
	//printf("Something went wrong while trying to open %s\n", path);
	if(path == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", path);
        exit(EXIT_FAILURE);
    }
	
	
	
	
	
	
	return 0;
}