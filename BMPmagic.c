//gcc -Wall -pedantic BMPmagic.c -o run
//run C:\Users\sebbe\Desktop\Untitled.bmp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTPUT "output.BMP"

void HeaderLezen(FILE *file, char* Head, int *h, int *b );

int main(int argc, char *argv[])
{
	char *bmpHeader = "";
    char *image = NULL; 
	int *breedte = NULL;
    int *hoogte = NULL;
	int padding = 0;
	int imagesize = 0;
	
	
	
	
	
	FILE *path = NULL;
	if (argv[1]=="--help" || argv[1]== "--h")
	{
		/* code TO DO MIGUEL*/ 
	}
	else
	{
		path = fopen(argv[1], "r");
	}
	
	HeaderLezen(path, bmpHeader, hoogte, breedte);
	padding = *breedte %4;
	imagesize = *hoogte * *breedte;
	image = (char *) malloc(imagesize);
	

	//FILE *newf = fopen(OUTPUT,"wb+");
	
	if(path == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", path);
        exit(EXIT_FAILURE);
    }
	
	/*if(newf == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to create %s\n", newf);
        exit(EXIT_FAILURE);
    }*/
	
		
	//skip paddings
	if(padding)
	{
		/*code TO DO MIGUEL*/
	}
	//lees alles
	else
	{
		fread(image, sizeof(unsigned char), imagesize, path);
	}
	
	
	fclose(path);
	/*if(newf != NULL)
	{
		fclose(newf);
	}*/
	
	
	return 0;
}

void HeaderLezen(FILE *file, char* Head, int *h, int *b)
{
	//header inlezen
	fread(Head, sizeof(unsigned char), 54, file);
	
	// haal de filetype, hoogte en breedte uit de header
	
	char filetype[2]="";
    b = (int*)&Head[18];
    h = (int*)&Head[22];
	int bitformat = *(int*)&Head[28];
	
	strncpy(filetype, Head, 2);
	
	if(strncmp(filetype, "BM",2)!=0)
	{
		printf("file is geen bitmap file\n");
	}
	
	if(bitformat != 24)
	{
		printf("bitmapfile is niet 24 bits\n");
	}
	
}






