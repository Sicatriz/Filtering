//gcc -Wall -pedantic BMPmagic.c -o run
//run C:\Users\sebbe\Desktop\Untitled.bmp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTPUT "output.BMP"

int main(int argc, char *argv[])
{
	FILE *path = fopen(argv[1], "r");
	FILE *newf = fopen(OUTPUT,"w+");
	
	if(path == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", path);
        exit(EXIT_FAILURE);
    }
	
	if(newf == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to create %s\n", newf);
        exit(EXIT_FAILURE);
    }
	
	char bmpHeader[54]; // voorzie een array van 54-bytes voor de BMP Header
    fread(bmpHeader, sizeof(unsigned char), 54, path); // lees de 54-bytes header

    // haal de filetype, hoogte en breedte uit de header
	char filetype[2]="";
    int breedte = *(int*)&bmpHeader[18];
    int hoogte = *(int*)&bmpHeader[22];
	int bitformat = *(int*)&bmpHeader[28];
	int padding = (breedte*hoogte)%4;
	strncpy(filetype, bmpHeader, 2);
	
	if(strncmp(filetype, "BM",2)!=0)
	{
		printf("file is geen bitmap file\n");
	}
	
	if(bitformat != 24)
	{
		printf("bitmapfile is niet 24 bits\n");
	}
	
	//skip paddings
	if(padding)
	{
		
	}
	//lees alles
	else
	{
		
	}
	
	
	fclose(path);
	fclose(newf);
	
	return 0;
}