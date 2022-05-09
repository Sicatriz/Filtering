/*
* Author(s): Sebbe Gerits & Miguel Nunez
* Date: 6/12/2021
* Description: *** BMP MAGIC || FILTERS *** taak C-programeren2 1EAIC 2021-2022
*/

// cls
// SEBBE run C:\Users\sebbe\Desktop\test.bmp
// MIGUEL run test.bmp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define OUTPUT_Name "output.BMP"

/*
* Omschrijving: Introductiescherm
* @param:   nvt
* @param: nvt
* @return:  nvt
*/

void intro();

void help();
void HeaderLezen();
void ImageLezen();
void FilterBw();
void FilterBlur();


int main(int argc, char *argv[])
{
	unsigned char bmpHeader[54] = {0};
	unsigned char *array =NULL;
	signed int *breedte = (int*) malloc(sizeof(int));
    signed int *hoogte = (int*) malloc(sizeof(int));
	int *padding = (int*) malloc(sizeof(int));
	int *imagesize = (int*) malloc(sizeof(int));
	FILE *path = NULL;
	
	intro();

	if (strncmp(argv[1],"--help", 6)==0 || strncmp(argv[1], "--h", 3)==0)
	{
		system("cls");
		intro();
		help();
		exit(EXIT_FAILURE);
	}
	else
	{
		path = fopen(argv[1], "rb");
		if(path == NULL) //Test of het open van de file gelukt is!
		{
			printf("Something went wrong while trying to open %s\n", argv[1]);
			return -1;
		}
	}
	
	HeaderLezen(path, bmpHeader, hoogte, breedte);
	*padding = 0;
	*imagesize = *hoogte**breedte*3;
	array = (unsigned char *) malloc(*imagesize);
	
	
	if(array == NULL)
	{
		printf("mem alloc failed");
		exit(EXIT_FAILURE);
	}
	
	ImageLezen(path, breedte, hoogte, imagesize, padding, array);
	
	FilterBw(path, bmpHeader, breedte, hoogte, imagesize, padding, array);
	FilterBlur(path, bmpHeader, breedte, hoogte, imagesize, padding, array);
	
	free(breedte);
	free(hoogte);
	free(padding);
	free(imagesize);
	free(array);
	
	fclose(path);
	
	return 0;
}

void HeaderLezen(FILE *filef, unsigned char* header, signed int *h, signed int *b)
{
	//header inlezen
	fread(header, 1, 54, filef);
	
	// haal de filetype, hoogte en breedte uit de header
	char filetype[2]="";

	//breedte nemen
    *b =(header[21] << 24) | (header[20] << 16) | (header[19] << 8) | (header[18]);
	
	//hoogte nemen
    *h = (header[25] << 24) | (header[24] << 16) | (header[23] << 8) | (header[22]);
    
	
	int bitformat = *(int*)&header[28];
	
	strncpy(filetype,(char *)   header, 2);
	
	if(strncmp(filetype, "BM",2)!=0)
	{
		printf("file is geen bitmap file\n");
	}
	
	if(bitformat != 24)
	{
		printf("bitmapfile is niet 24 bits\n");
	}
}


void ImageLezen(FILE* fp, int * bre, int * ho, int* grootte, int* pad, unsigned char *arr)
{
	if(arr == NULL)
	{
		printf("mem alloc failed");
		exit(EXIT_FAILURE);
	}
	
	
	fread(arr, 1, *grootte, fp);
	
/*	
	for(int i=0; i<*grootte; i++)
	{
		printf("%x ", arr[i]);
	}
	printf("\n\n");
	
	for(int i=0; i<*ho; i++)
	{
		for(int j=0; j<*bre*3; j++)
		{
			if(j%3==0)
			{
				printf(" | ");
			}
			printf("%x ",arr[(i**bre*3)+j]);
		}
		printf("\n\n");
	}
*/
}


void intro()
{
	system("color a");
	printf("____________________________________________________________________________________________________________________________________________________________________________________\n");
	printf(" ____________________________________________________________________________________________________________________________________________________________________________________\n");
	printf("  ____________________________________________________________________________________________________________________________________________________________________________________\n");
	printf("   __/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\_\n");
	printf("    _\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////__\n");
	printf("     ____________________________________________________________________________________________________________________________________________________________________________________\n");
	printf("       ____________________________________________________________________________________________________________________________________________________________________________________\n");
	printf("        ____________________________________________________________________________________________________________________________________________________________________________________\n");
	printf(" _____________/\\\\\\\\\\\\\\\\\\\\\\\\\\_____/\\\\\\\\____________/\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\\\\\________________/\\\\\\\\____________/\\\\\\\\______/\\\\\\\\\\\\\\\\\\_________/\\\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\_________/\\\\\\\\\\\\\\\\\\____________\n");
	printf("  ____________\\/\\\\\\/////////\\\\\\__\\/\\\\\\\\\\\\________/\\\\\\\\\\\\__\\/\\\\\\/////////\\\\\\_____________\\/\\\\\\\\\\\\________/\\\\\\\\\\\\____/\\\\\\\\\\\\\\\\\\\\\\\\\\_____/\\\\\\//////////___\\/////\\\\\\///_______/\\\\\\////////_____________\n");
	printf("   ____________\\/\\\\\\_______\\/\\\\\\__\\/\\\\\\//\\\\\\____/\\\\\\//\\\\\\__\\/\\\\\\_______\\/\\\\\\_____________\\/\\\\\\//\\\\\\____/\\\\\\//\\\\\\___/\\\\\\/////////\\\\\\___/\\\\\\__________________\\/\\\\\\________/\\\\\\/______________________\n");
	printf("    ____________\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\___\\/\\\\\\\\///\\\\\\/\\\\\\/_\\/\\\\\\__\\/\\\\\\\\\\\\\\\\\\\\\\\\\\/______________\\/\\\\\\\\///\\\\\\/\\\\\\/_\\/\\\\\\__\\/\\\\\\_______\\/\\\\\\__\\/\\\\\\____/\\\\\\\\\\\\\\______\\/\\\\\\_______/\\\\\\________________________\n");
	printf("     ____________\\/\\\\\\/////////\\\\\\__\\/\\\\\\__\\///\\\\\\/___\\/\\\\\\__\\/\\\\\\/////////________________\\/\\\\\\__\\///\\\\\\/___\\/\\\\\\__\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\__\\/\\\\\\___\\/////\\\\\\______\\/\\\\\\______\\/\\\\\\________________________\n");
	printf("      ____________\\/\\\\\\_______\\/\\\\\\__\\/\\\\\\____\\///_____\\/\\\\\\__\\/\\\\\\_________________________\\/\\\\\\____\\///_____\\/\\\\\\__\\/\\\\\\/////////\\\\\\__\\/\\\\\\_______\\/\\\\\\______\\/\\\\\\______\\//\\\\\\_______________________\n");
	printf("       ____________\\/\\\\\\_______\\/\\\\\\__\\/\\\\\\_____________\\/\\\\\\__\\/\\\\\\_________________________\\/\\\\\\_____________\\/\\\\\\__\\/\\\\\\_______\\/\\\\\\__\\/\\\\\\_______\\/\\\\\\______\\/\\\\\\_______\\///\\\\\\_____________________\n");
	printf("        ____________\\/\\\\\\\\\\\\\\\\\\\\\\\\\\/___\\/\\\\\\_____________\\/\\\\\\__\\/\\\\\\_________________________\\/\\\\\\_____________\\/\\\\\\__\\/\\\\\\_______\\/\\\\\\__\\//\\\\\\\\\\\\\\\\\\\\\\\\/____/\\\\\\\\\\\\\\\\\\\\\\_____\\////\\\\\\\\\\\\\\\\\\____________\n");
	printf("         ____________\\/////////////_____\\///______________\\///___\\///__________________________\\///______________\\///___\\///________\\///____\\////////////_____\\///////////_________\\/////////_____________\n");
	printf("___________________________________________________________________________________________________________________________________________________________________________________________________\n");
	printf("  ___________________________________________________________________________________________________________________________________________________________________________________________________\n");
	printf("   __/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\_\n");
	printf("    _\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////___\\///////////__\n");
	printf("     ___________________________________________________________________________________________________________________________________________________________________________________________________\n");
	printf("      ___________________________________________________________________________________________________________________________________________________________________________________________________\n");
	printf("       ___________________________________________________________________________________________________________________________________________________________________________________________________\n");
	printf("        ___________________________________________________________________________________________________________________________________________________________________________________________________\n");

}

void help()
{
	printf("\n\n********************************************\n\n");
	printf("COMMANDO'S BMP MAGIC:\n");
	printf("\n\n********************************************\n\n");
	printf("\nRUN		Start het programma in normale modus.\n\n");
	printf("Om een snelle actie vanuit de prompt zonder menu:\n\n");
	printf("RUN [inputfile.bmp] -o [outputfile] -f [filtertype]\n\n");
	printf("FILTER COMMANDO'S\n"); 
	printf("SMOOTH				vervaag afbeelding.\n");
	printf("BW					maak een zwart/wit afbeelding.\n");
	printf("SCALE#				schaal afbeelding naar gekozen factor tussen 1 en 4. (vervang # met een getal tussen 1 en 5)\n");
	printf("BLUE				pas blauwfilter toe.\n");
	printf("RED				pas roodfilter toe.\n");
	printf("GREEN				pas groenfilter toe.\n");
	printf("WH				    pas WARHOLfilter toe.\n");
}

void FilterBw(FILE* fp, unsigned char *header, int * bre, int * ho, int* grootte, int* pad, unsigned char *arr)
{

//**************
	//BW filter
//**************

	unsigned char filtered[*grootte];
	
	FILE  * out = fopen("bw.bmp", "wb");
	
	printf("2");
	
	if(out == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", "Bw.BMP");
        exit(EXIT_FAILURE);
    }


	int pixel = 0;

	for(int i=0; i<*ho; i++)
	{
		for(int j=0; j<*bre*3; j+=3)
		{
			pixel = pixel + arr[(i**bre*3)+j];
			pixel = pixel + arr[(i**bre*3)+j+1];
			pixel = pixel + arr[(i**bre*3)+j+2];
		//	printf("%x %x %x | ",arr[(i**bre*3)+j], arr[(i**bre*3)+j+1], arr[(i**bre*3)+j+2]);

			pixel = pixel / 3;

			filtered[(i**bre*3)+j] = pixel;
			filtered[(i**bre*3)+j+1] = pixel;
			filtered[(i**bre*3)+j+2] = pixel;

		//	printf("%x %x %x | \n\n",filtered[(i**bre*3)+j], filtered[(i**bre*3)+j+1], filtered[(i**bre*3)+j+2]);
			pixel =0;
		}
	}
	
	fwrite(header, 1, 54, out); 
	fwrite(filtered, 1, *grootte, out);
	fclose(out);
}


void FilterBlur(FILE* fp, unsigned char* head, int * bre, int * ho, int* grootte, int* pad, unsigned char *arr)
{
	int blauw = 0;
	int groen = 0;
	int rood = 0;
	int gem =0;
	unsigned char filtered[*grootte];
	printf("0");
	
	//fclose(out);
	
	printf("1");
	
	FILE * out = fopen("Blur.BMP", "wb+");
	
	printf("2");
	
	if(out == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", "Blur.BMP");
        exit(EXIT_FAILURE);
    }
	
	for(int i=0; i<*ho; i++)
	{
	//	printf("\n\n");
		for(int j=0; j<*bre*3; j+=3)
		{
			
			blauw = 0;
			groen = 0;
			rood = 0;
<<<<<<< HEAD
			gem = 1;
			printf("%x %x %x | ",arr[(i**bre*3)+j], arr[(i**bre*3)+j+1], arr[(i**bre*3)+j+2]);
=======
		//	printf("%x %x %x | ",arr[(i**bre*3)+j], arr[(i**bre*3)+j+1], arr[(i**bre*3)+j+2]);
>>>>>>> main
			
			//midden
			blauw += arr[(i**bre*3)+j];
			groen += arr[(i**bre*3)+j+1];
			rood  += arr[(i**bre*3)+j+2];
			
			//rechts
			if(j!=*bre*3-3)
			{
				blauw += arr[(i**bre*3)+j+3];
				groen += arr[(i**bre*3)+j+1+3];
				rood  += arr[(i**bre*3)+j+3+2];
				gem++;
			}
			
			//onder
			if(i!=*ho-1)
			{
				blauw += arr[((i+1)**bre*3)+j];
				groen += arr[((i+1)**bre*3)+j+1];
				rood  += arr[((i+1)**bre*3)+j+2];		
				gem++;				
			}
			
			//rechts onder
			if(j!=*bre*3-3&&i!=*ho-1)
			{						
				blauw += arr[((i+1)**bre*3)+j+3];
				groen += arr[((i+1)**bre*3)+j+1+3];
				rood  += arr[((i+1)**bre*3)+j+3+2];
				gem++;
			}
		
			//links
			if(j!=0)
			{
				blauw += arr[(i**bre*3)+j-3];
				groen += arr[(i**bre*3)+j-2];
				rood  += arr[(i**bre*3)+j-1];
				gem++;
			}
			
			//links onder
			if(i!=*ho-1&&j!=*bre*3-3)
			{
				blauw += arr[((i+1)**bre*3)+j-3];
				groen += arr[((i+1)**bre*3)+j-2];
				rood  += arr[((i+1)**bre*3)+j-1];
				gem++;
			}
			
			//links boven
			if(i!=0&&j!=0)
			{
				blauw += arr[((i-1)**bre*3)+j-3];
				groen += arr[((i-1)**bre*3)+j-2];
				rood  += arr[((i-1)**bre*3)+j-1];
				gem++;
			}
			
			//boven
			if(i!=0)
			{
				blauw += arr[((i-1)**bre*3)+j];
				groen += arr[((i-1)**bre*3)+j+1];
				rood  += arr[((i-1)**bre*3)+j+2];
				gem++;
			}
			
			//rechts boven
			if(i!=0&&j!=*bre*3-3)
			{
				blauw += arr[((i-1)**bre*3)+j+3];
				groen += arr[((i-1)**bre*3)+j+1+3];
				rood  += arr[((i-1)**bre*3)+j+3+2];	
				gem++;
			}
			
			//gem berekenen
			blauw = blauw/gem;
			groen = groen/gem;
			rood  = rood/gem;
			
			//gem toekenen
			filtered[(i**bre*3)+j]   = blauw;
			filtered[(i**bre*3)+j+1] = groen;
			filtered[(i**bre*3)+j+2] = rood;
			
		//	printf("%x %x %x | \t",filtered[(i**bre*3)+j], filtered[(i**bre*3)+j+1], filtered[(i**bre*3)+j+2]);
		}
	}	
	
	printf("\n\n");
	printf("2");
	fwrite(head, 1, 54, out); 
	fwrite(filtered, 1, *grootte, out);
	
	fclose(out);
	
}
