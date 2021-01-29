#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

void copie(FILE* original, int file_size);
void dilater(FILE* original, int file_size);

int main()
{
		// Declaration des variables et pointeurs

	int file_size;

	FILE* original;


		// Ouverture des fichiers

	original = fopen("sample/attention.wav", "rb");


		// Taille du fichier à copier

	fseek(original, 0, SEEK_END);
	file_size = ftell(original);
	fseek(original, 0, SEEK_SET);


		// Copie

//	copie(original, file_size);

		// Dilater

	dilater(original, file_size);
printf("4 ");

		//Fermeture des fichiers

	fclose(original);

	return 0;
}

void copie(FILE* original, int file_size)
{
	int* buffer;

        FILE* copie;


                // Ouverture des fichiers

        copie = fopen("result/copie_attention.wav", "wb");


                // Copie

        buffer = (int*)malloc(file_size);

        fread(buffer, file_size, 1, original);

        fwrite(buffer, file_size, 1, copie);


                //Fermeture des fichiers

        fclose(copie);

}

void dilater(FILE* original, int file_size)
{
	int new_file_size = 2 * (file_size - 44);

	char* buffer_old;
	char* buffer_new;

        FILE* res;
printf("0000 ");

	fseek(original, 44, SEEK_SET);

                // Ouverture des fichiers
printf("000 ");
        res = fopen("result/dilatation_attention.raw", "wb");


                // Mise en tampon de l'original
printf("00 ");
        buffer_old = (char*)malloc(file_size - 44);
printf("0 ");

        fread(buffer_old, file_size - 44, 1, original);
printf("1 ");


		// Duplication de chaque valeur

	buffer_new = (char*)malloc(new_file_size);
printf("2 ");

	for(int i = 0, j = 0; i < file_size - 44; i++)
	{
		buffer_new[j] = buffer_old[i];
			j=j+1;
		buffer_new[j] = buffer_old[i];
			j=j+1;
	}
printf("3 ");
        fwrite(buffer_new, new_file_size, 1, res);
printf("4 ");

                //Fermeture des fichiers

        fclose(res);

}


