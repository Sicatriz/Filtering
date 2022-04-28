//gcc -Wall -pedantic BMPmagicMenu.c -o run
// SEBBE run C:\Users\Administrator\Desktop\Untitled.bmp
// MIGUEL run test.bmp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTPUT "output.BMP"

// Declaratie finite State Machine
typedef enum
{
	Start_State,
	FilterKeuze_State,
	BronSelectie_State,
    DoelSelectie_State,
    End_State
}fsmState;

void HeaderLezen();
void intro();
void help();

int main(int argc, char *argv[])
{

	unsigned char bmpHeader[54] = {0};
    unsigned char *image = NULL; 
	signed int *breedte = NULL;
    signed int *hoogte = NULL;
	int padding = 0;
	int imagesize = 0;
    int menuKeuze = 0;
	FILE *path = NULL;
	FILE *output = NULL;
    fsmState nextState = Start_State;

    if (strncmp(argv[1],"--help", 6) || strncmp(argv[1], "--h", 3))
	{
		intro();
		help();
	}
    else if (strncmp(argv[1],"", 0))
    {
        while (1)
        {
            switch (nextState)
            {
            case Start_State:
                intro();
                menuKeuze = 0;
                printf("[1]  Filtertype kiezen\n");
                printf("[2]  Programma beeindigen\n");
                scanf("%d", &menuKeuze);
                if (menuKeuze == 1)
                {
                    nextState = FilterKeuze_State;
                    break;
                }
                else if (menuKeuze == 2)
                {
                    nextState = End_State;
                    break;
                }
                else
                {
                    nextState = Start_State;
                    break;
                }
                break;
            case FilterKeuze_State:
                /* code */
                break;
            case BronSelectie_State:
                /* code */
                break;
            case DoelSelectie_State:
                /* code */
                break;
            case End_State:
                system("cls");
                printf("\n\n\n\n- - - - - - - - - - - - - - - - -\n");
                printf("Bedankt om BMPmagic te gebruiken!\n");

                break;

            default:
                break;
            }
        }
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
	//printf("%d \t %p\n", *b, b);
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

void intro()
{
    system("cls");
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


