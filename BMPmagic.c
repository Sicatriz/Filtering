// gcc -Wall -pedantic BMPmagic.c -o run
// SEBBE run C:\Users\sebbe\Desktop\test.bmp
// MIGUEL run test.bmp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


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
		return 0;
	}
	else
	{
		path = fopen(argv[1], "rb");
		if(path == NULL) //Test of het open van de file gelukt is!
		{
			printf("Something went wrong while trying to open %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	}

	//printf("0\n");
	HeaderLezen(path, bmpHeader, hoogte, breedte);
	//printf("%d", *hoogte);
	*padding = 0 /**breedte *3 % 4*/;
	*imagesize = *hoogte**breedte*3;
	array = (unsigned char *) malloc(sizeof(imagesize));
	//printf("%d\n", *imagesize);
	//unsigned char image[*breedte*3][*hoogte];
	
	ImageLezen(path, breedte, hoogte, imagesize, padding, array /*, image*/);
	FilterBw(path, bmpHeader, breedte, hoogte, imagesize, padding, array /*, image*/);
	//FilterBlur(path, bmpHeader, breedte, hoogte, imagesize, padding, array);
	
	//4 - (*breedte *24 % 32);
	
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
	//printf("1\n");
	fread(header, 1, 54, filef);
	
	// haal de filetype, hoogte en breedte uit de header
	//printf("2\n");
	char filetype[2]="";

    *b =(header[21] << 24) | (header[20] << 16) | (header[19] << 8) | (header[18]);
	
    //printf("de breedte van mijn afbeeding is = %d \n", *b);
    *h = (header[25] << 24) | (header[24] << 16) | (header[23] << 8) | (header[22]);
    //printf("de breedte van mijn afbeeding is = %d \n", *h);

	//printf("%d \t %p\n", *b, b);
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
	/*for(int i=0; i<54; i++)
	{
		putchar(header[i]);
	}
	printf("\n3\n");*/
}

//test git

void ImageLezen(FILE* fp, int * bre, int * ho, int* grootte, int* pad, unsigned char *arr/*, unsigned char afbeelding[*bre*3][*ho]*/)
{
	
	//printf("\n\n%d\n\n",*pad);
	//char input =0;
	
	if(arr == NULL)
	{
		printf("mem alloc failed");
		exit(EXIT_FAILURE);
	}
	
	//printf("0\n");
	fread(arr, 1, *grootte, fp);
	//printf("1\n");
	//printf("%d", *grootte);
	for(int i=0; i<*grootte; i++)
	{
		printf("%x ", arr[i]);
	}
	printf("\n\n");
	
	for(int i=0; i<*ho; i++)
	{
		for(int j=0; j<*bre*3/*+*pad*/; j++)
		{
			if(j%3==0)
			{
				printf(" | ");
			}
			//afbeelding[i][j] = arr[(i**bre*3)+j];
			printf("%x ",arr[(i**bre*3)+j]);
		}
		printf("\n\n");
	}

/*	printf("\n\n");
	for(int i=0; i<*ho; i++)
	{
		for(int j=0; j<*bre*3; j++)
		{
			printf("%x ",afbeelding[i][j]);
		}
		printf("\n\n");
	}
	printf("\n\n");
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
	printf("BW				maak een zwart/wit afbeelding.\n");
	printf("SCALE#				schaal afbeelding naar gekozen factor tussen 1 en 4. (vervang # met een getal tussen 1 en 5)\n");
	printf("BLUE				pas blauwfilter toe.\n");
	printf("RED				pas roodfilter toe.\n");
	printf("GREEN				pas groenfilter toe.\n");
	printf("WH				pas WARHOLfilter toe.\n");
}



void FilterBw(FILE* fp, unsigned char* header, int * bre, int * ho, int* grootte, int* pad, unsigned char *arr/*, unsigned char afbeelding[*bre*3][*ho]*/)
{

//**************
	//BW filter
//**************

	int pixel = 0;
	FILE* output = fopen("outputBW.BMP", "wb");
	
	
	if(output == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", "outputBW.BMP");
        exit(EXIT_FAILURE);
    }

	for(int i=0; i<*ho; i++)
	{
		for(int j=0; j<*bre*3; j+=3)
		{
			pixel = pixel + arr[(i**bre*3)+j];
			pixel = pixel + arr[(i**bre*3)+j+1];
			pixel = pixel + arr[(i**bre*3)+j+2];
			
			printf("%x %x %x | ",arr[(i**bre*3)+j], arr[(i**bre*3)+j+1], arr[(i**bre*3)+j+2]);

			pixel = pixel / 3;

			arr[(i**bre*3)+j] = pixel;
			arr[(i**bre*3)+j+1] = pixel;
			arr[(i**bre*3)+j+2] = pixel;

			printf("%x %x %x | \n\n",arr[(i**bre*3)+j], arr[(i**bre*3)+j+1], arr[(i**bre*3)+j+2]);
			pixel = 0;
		}


		//printf("\n\n");
	}
	
	fwrite(header, 1, 54, output);
	fwrite(arr, 1, *grootte, output);
	
	fclose(output);

}


void FilterBlur(FILE* fp, unsigned char* header, int * bre, int * ho, int* grootte, int* pad, unsigned char *arr)
{
	int blauw = 0;
	int groen = 0;
	int rood = 0;
	FILE* output = fopen("outputBLUR.BMP", "wb");
	
	
	if(output == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", "outputBLUR.BMP");
        exit(EXIT_FAILURE);
    }
	
	for(int i=0; i<*ho; i++)
	{
		printf("\n\n");
		for(int j=0; j<*bre*3; j+=3)
		{
			
			blauw = 0;
			groen = 0;
			rood = 0;
			printf("%x %x %x | ",arr[(i**bre*3)+j], arr[(i**bre*3)+j+1], arr[(i**bre*3)+j+2]);
			
			//bovenste pixels
			if(i==0)
			{
				//linkerbovenhoek
				if(j==0)
				{
				
					//midden
					blauw += arr[(i**bre*3)+j];
					groen += arr[(i**bre*3)+j+1];
					rood  += arr[(i**bre*3)+j+2];
					
					//rechts
					blauw += arr[(i**bre*3)+j+3];
					groen += arr[(i**bre*3)+j+1+3];
					rood  += arr[(i**bre*3)+j+3+2];
					
					//onder
					blauw += arr[((i+1)**bre*3)+j];
					groen += arr[((i+1)**bre*3)+j+1];
					rood  += arr[((i+1)**bre*3)+j+2];
					
					//rechts onder
					blauw += arr[((i+1)**bre*3)+j+3];
					groen += arr[((i+1)**bre*3)+j+1+3];
					rood  += arr[((i+1)**bre*3)+j+3+2];
				
				
					blauw = blauw/4;
					groen = groen/4;
					rood  = rood/4;
				}
				
				//rechterbovenhoek
				else if(j==*bre*3-3)
				{
					//links
					blauw += arr[(i**bre*3)+j-3];
					groen += arr[(i**bre*3)+j-2];
					rood  += arr[(i**bre*3)+j-1];
					
					//midden
					blauw += arr[(i**bre*3)+j];
					groen += arr[(i**bre*3)+j+1];
					rood  += arr[(i**bre*3)+j+2];
					
					//links onder
					blauw += arr[((i+1)**bre*3)+j-3];
					groen += arr[((i+1)**bre*3)+j-2];
					rood  += arr[((i+1)**bre*3)+j-1];
					
					//onder
					blauw += arr[((i+1)**bre*3)+j];
					groen += arr[((i+1)**bre*3)+j+1];
					rood  += arr[((i+1)**bre*3)+j+2];
					
					
					blauw = blauw/4;
					groen = groen/4;
					rood  = rood/4;
				}
				//boven midden
				else
				{
					//links
					blauw += arr[(i**bre*3)+j-3];
					groen += arr[(i**bre*3)+j-2];
					rood  += arr[(i**bre*3)+j-1];
					
					//midden
					blauw += arr[(i**bre*3)+j];
					groen += arr[(i**bre*3)+j+1];
					rood  += arr[(i**bre*3)+j+2];
					
					//rechts
					blauw += arr[(i**bre*3)+j+3];
					groen += arr[(i**bre*3)+j+1+3];
					rood  += arr[(i**bre*3)+j+3+2];
					
					
					
					//links onder
					blauw += arr[((i+1)**bre*3)+j-3];
					groen += arr[((i+1)**bre*3)+j-2];
					rood  += arr[((i+1)**bre*3)+j-1];
					
					//onder
					blauw += arr[((i+1)**bre*3)+j];
					groen += arr[((i+1)**bre*3)+j+1];
					rood  += arr[((i+1)**bre*3)+j+2];
					
					//rechts onder
					blauw += arr[((i+1)**bre*3)+j+3];
					groen += arr[((i+1)**bre*3)+j+1+3];
					rood  += arr[((i+1)**bre*3)+j+3+2];
					
					
					
					blauw = blauw/6;
					groen = groen/6;
					rood  = rood/6;
				}
			}
			//onderste pixels
			else if(i==*ho-1)
			{
				//linkeronderhoek
				if(j==0)
				{
					//boven
					blauw += arr[((i-1)**bre*3)+j];
					groen += arr[((i-1)**bre*3)+j+1];
					rood  += arr[((i-1)**bre*3)+j+2];
					
					//rechts boven
					blauw += arr[((i-1)**bre*3)+j+3];
					groen += arr[((i-1)**bre*3)+j+1+3];
					rood  += arr[((i-1)**bre*3)+j+2+3];
					
					
					//midden
					blauw += arr[(i**bre*3)+j];
					groen += arr[(i**bre*3)+j+1];
					rood  += arr[(i**bre*3)+j+2];
					
					//rechts
					blauw += arr[(i**bre*3)+j+3];
					groen += arr[(i**bre*3)+j+1+3];
					rood  += arr[(i**bre*3)+j+2+3];
					
					
					blauw = blauw/4;
					groen = groen/4;
					rood  = rood/4;
				}
				
				//rechteronderhoek
				else if(j==*bre*3-3)
				{
					//links boven
					blauw += arr[((i-1)**bre*3)+j-3];
					groen += arr[((i-1)**bre*3)+j-2];
					rood  += arr[((i-1)**bre*3)+j-1];
					
					//boven
					blauw += arr[((i-1)**bre*3)+j];
					groen += arr[((i-1)**bre*3)+j+1];
					rood  += arr[((i-1)**bre*3)+j+2];
					
					//links
					blauw += arr[(i**bre*3)+j-3];
					groen += arr[(i**bre*3)+j-2];
					rood  += arr[(i**bre*3)+j-1];
					
					//midden
					blauw += arr[(i**bre*3)+j];
					groen += arr[(i**bre*3)+j+1];
					rood  += arr[(i**bre*3)+j+2];
					
					
					blauw = blauw/4;
					groen = groen/4;
					rood  = rood/4;
				
				}
				//ondermidden
				else
				{
					//links boven
					blauw += arr[((i-1)**bre*3)+j-3];
					groen += arr[((i-1)**bre*3)+j-2];
					rood  += arr[((i-1)**bre*3)+j-1];
					
					//boven
					blauw += arr[((i-1)**bre*3)+j];
					groen += arr[((i-1)**bre*3)+j+1];
					rood  += arr[((i-1)**bre*3)+j+2];
					
					//rechts boven
					blauw += arr[((i-1)**bre*3)+j+3];
					groen += arr[((i-1)**bre*3)+j+1+3];
					rood  += arr[((i-1)**bre*3)+j+3+2];
					
					//links
					blauw += arr[(i**bre*3)+j-3];
					groen += arr[(i**bre*3)+j-2];
					rood  += arr[(i**bre*3)+j-1];
					
					//midden
					blauw += arr[(i**bre*3)+j];
					groen += arr[(i**bre*3)+j+1];
					rood  += arr[(i**bre*3)+j+2];
					
					//rechts
					blauw += arr[(i**bre*3)+j+3];
					groen += arr[(i**bre*3)+j+1+3];
					rood  += arr[(i**bre*3)+j+3+2];
					
					blauw = blauw/6;
					groen = groen/6;
					rood  = rood/6;
				}
			}
			//midden
			else
			{
				//links
				if(j==0)
				{
					//boven
					blauw += arr[((i-1)**bre*3)+j];
					groen += arr[((i-1)**bre*3)+j+1];
					rood  += arr[((i-1)**bre*3)+j+2];
					
					//rechts boven
					blauw += arr[((i-1)**bre*3)+j+3];
					groen += arr[((i-1)**bre*3)+j+1+3];
					rood  += arr[((i-1)**bre*3)+j+3+2];
					
					
					//midden
					blauw += arr[(i**bre*3)+j];
					groen += arr[(i**bre*3)+j+1];
					rood  += arr[(i**bre*3)+j+2];
					
					//rechts
					blauw += arr[(i**bre*3)+j+3];
					groen += arr[(i**bre*3)+j+1+3];
					rood  += arr[(i**bre*3)+j+3+2];
					
					
					//onder
					blauw += arr[((i+1)**bre*3)+j];
					groen += arr[((i+1)**bre*3)+j+1];
					rood  += arr[((i+1)**bre*3)+j+2];
					
					//rechts onder
					blauw += arr[((i+1)**bre*3)+j+3];
					groen += arr[((i+1)**bre*3)+j+1+3];
					rood  += arr[((i+1)**bre*3)+j+3+2];
					
					
					
					
					blauw = blauw/6;
					groen = groen/6;
					rood  = rood/6;
				}
				//rechts
				else if(j==*bre*3-3)
				{
					//links boven
					blauw += arr[((i-1)**bre*3)+j-3];
					groen += arr[((i-1)**bre*3)+j-2];
					rood  += arr[((i-1)**bre*3)+j-1];
					
					//boven
					blauw += arr[((i-1)**bre*3)+j];
					groen += arr[((i-1)**bre*3)+j+1];
					rood  += arr[((i-1)**bre*3)+j+2];
					
					
					//links
					blauw += arr[(i**bre*3)+j-3];
					groen += arr[(i**bre*3)+j-2];
					rood  += arr[(i**bre*3)+j-1];
					
					//midden
					blauw += arr[(i**bre*3)+j];
					groen += arr[(i**bre*3)+j+1];
					rood  += arr[(i**bre*3)+j+2];
					
					
					//links onder
					blauw += arr[((i+1)**bre*3)+j-3];
					groen += arr[((i+1)**bre*3)+j-2];
					rood  += arr[((i+1)**bre*3)+j-1];
					
					//onder
					blauw += arr[((i+1)**bre*3)+j];
					groen += arr[((i+1)**bre*3)+j+1];
					rood  += arr[((i+1)**bre*3)+j+2];
					
					
					
					
					blauw = blauw/6;
					groen = groen/6;
					rood  = rood/6;
				}
				//normaal
				else
				{
					//links boven
					blauw += arr[((i-1)**bre*3)+j-3];
					groen += arr[((i-1)**bre*3)+j-2];
					rood  += arr[((i-1)**bre*3)+j-1];
					
					//boven
					blauw += arr[((i-1)**bre*3)+j];
					groen += arr[((i-1)**bre*3)+j+1];
					rood  += arr[((i-1)**bre*3)+j+2];
					
					//rechts boven
					blauw += arr[((i-1)**bre*3)+j+3];
					groen += arr[((i-1)**bre*3)+j+1+3];
					rood  += arr[((i-1)**bre*3)+j+3+2];
					
					//links
					blauw += arr[(i**bre*3)+j-3];
					groen += arr[(i**bre*3)+j-2];
					rood  += arr[(i**bre*3)+j-1];
					
					//midden
					blauw += arr[(i**bre*3)+j];
					groen += arr[(i**bre*3)+j+1];
					rood  += arr[(i**bre*3)+j+2];
					
					//rechts
					blauw += arr[(i**bre*3)+j+3];
					groen += arr[(i**bre*3)+j+1+3];
					rood  += arr[(i**bre*3)+j+3+2];
					
					//links onder
					blauw += arr[((i+1)**bre*3)+j-3];
					groen += arr[((i+1)**bre*3)+j-2];
					rood  += arr[((i+1)**bre*3)+j-1];
					
					//onder
					blauw += arr[((i+1)**bre*3)+j];
					groen += arr[((i+1)**bre*3)+j+1];
					rood  += arr[((i+1)**bre*3)+j+2];
					
					//rechts onder
					blauw += arr[((i+1)**bre*3)+j+3];
					groen += arr[((i+1)**bre*3)+j+1+3];
					rood  += arr[((i+1)**bre*3)+j+3+2];
					
					//gem berekenen
					blauw = blauw/9;
					groen = groen/9;
					rood  = rood/9;
				}
			}
			//gem toekenen
			arr[(i**bre*3)+j]   = blauw;
			arr[(i**bre*3)+j+1] = groen;
			arr[(i**bre*3)+j+2] = rood;
			
			printf("%x %x %x | \t",arr[(i**bre*3)+j], arr[(i**bre*3)+j+1], arr[(i**bre*3)+j+2]);
		}
	}	
	
	
	fwrite(header, 1, 54, output);
	fwrite(arr, 1, *grootte, output);
	
	printf("\n\n");
	
	fclose(output);
	
}
