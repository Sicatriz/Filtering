//gcc -Wall -pedantic BMPmagic.c -o run
//run C:\Users\Administrator\Desktop\Untitled.bmp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTPUT "output.BMP"

void HeaderLezen(FILE *filef, unsigned char* Head, signed int *h, signed int *b );

int main(int argc, char *argv[])
{

	unsigned char bmpHeader[54] = "";
    char *image = NULL; 
	signed int *breedte = NULL;
    signed int *hoogte = NULL;
	int padding = 0;
	int imagesize = 0;
	FILE *path = NULL;
	
	if (argv[1]=="--help" || argv[1]== "--h")
	{
		/* code TO DO MIGUEL*/ 
	}
	else
	{
		path = fopen(argv[1], "rb");
	}

	if(path == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", argv[1]);
        return -1;
    }

	printf("0\n");
	HeaderLezen(path, bmpHeader, hoogte, breedte);
	printf("%d", *breedte);
	padding = *breedte %4;
	imagesize = *hoogte * *breedte;
	image = (char *) malloc(imagesize);
	
	if(image == NULL)
	{
		printf("mem alloc failed");
		return -2;
	}
	
	//skip paddings
	if(padding)
	{
		/*code TO DO MIGUEL*/
	}
	//lees alles
	else
	{
		fread(image, 1, imagesize, path);
	}

	fclose(path);
	free(image);
	
	return 0;
}

void HeaderLezen(FILE *filef, unsigned char* Head, signed int *h, signed int *b)
{
	//header inlezen
	printf("1\n");
	fread(Head, 1, 54, filef);
	
	// haal de filetype, hoogte en breedte uit de header
	printf("2\n");
	char filetype[2]="";
    b = (signed int*)&Head[18];
    h = (signed int*)&Head[22];
	printf("%d \t %p\n", *b, b);
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
	for(int i=0; i<54; i++)
	{
		putchar(Head[i]);
	}
	printf("\n3\n");
}






