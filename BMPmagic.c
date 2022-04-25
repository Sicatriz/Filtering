//gcc -Wall -pedantic BMPmagic.c -o run
// SEBBE run C:\Users\Administrator\Desktop\Untitled.bmp
// MIGUEL run test.bmp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTPUT "output.BMP"

void HeaderLezen();

int main(int argc, char *argv[])
{

	unsigned char bmpHeader[54] = {0};
    unsigned char *image = NULL; 
	signed int *breedte = NULL;
    signed int *hoogte = NULL;
	int padding = 0;
	int imagesize = 0;
	FILE *path = NULL;
	FILE *output = NULL;
	
	if (argv[1]=="--help" || argv[1]== "--h")
	{
		/* code TO DO MIGUEL*/ 
	}
	else
	{
		path = fopen(argv[1], "rb");
		output = fopen(OUTPUT, "wb");
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
	image = (unsigned char *) malloc(imagesize);
	
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
	fclose(output);
	fclose(path);
	free(image);
	
	return 0;
}

void HeaderLezen(FILE *filef, unsigned char* header, signed int *h, signed int *b)
{
	//header inlezen
	printf("1\n");
	fread(header, 1, 54, filef);
	
	// haal de filetype, hoogte en breedte uit de header
	printf("2\n");
	char filetype[2]="";


	int breedte = 0;

    breedte = (header[21] << 24) | (header[20] << 16) | (header[19] << 8) | (header[18]);
	b = &breedte;
    printf("de breedte van mijn afbeeding is = %d \n", *b);
/*    *h = (*header[25] << 24) | (*header[24] << 16) | (*header[23] << 8) | (*header[22]);
    printf("de breedte van mijn afbeeding is = %d \n", *h);
*/
	printf("%d \t %p\n", *b, b);
	int bitformat = *(int*)&header[28];
	
	strncpy(filetype, header, 2);
	
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
		putchar(header[i]);
	}
	printf("\n3\n");
}






