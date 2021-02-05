#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "main.h"

void copie(FILE* original, int file_size);
void dilater(FILE* original, int file_size);
void compresser(FILE* original, int file_size);
void grave(FILE* original, int16_t* buffer, int file_size);


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


		// Copier

	copie(original, file_size);

		// Dilater

	dilater(original, file_size);

		// Compresser

	compresser(original, file_size);

		//Fermeture des fichiers

	fclose(original);

	return 0;
}

void copie(FILE* original, int file_size)
{
	int16_t* buffer;

        FILE* copie;


                // Ouverture des fichiers

        copie = fopen("result/copie_attention.wav", "wb");


                // Copie

        buffer = (int16_t*)malloc(file_size);

        fread(buffer, file_size, 1, original);

        fwrite(buffer, file_size, 1, copie);


                //Fermeture des fichiers

	free(buffer);

        fclose(copie);

}

void dilater(FILE* original, int file_size)
{
	int new_file_size = 2 * (file_size - 44);

	int* buffer_old;
	int* buffer_new;

        FILE* res;

	fseek(original, 44, SEEK_SET);


                // Ouverture des fichiers

        res = fopen("result/dilatation_attention.raw", "wb");


                // Mise en tampon de l'original

        buffer_old = (int*)malloc((file_size - 44)*sizeof(int));


        fread(buffer_old, file_size - 44, 1, original);



		// Duplication de chaque valeur

	buffer_new = (int*)malloc(new_file_size*sizeof(int));

	for(int i=0, j=0; i < file_size-44; i++, j++)
	{
		buffer_new[j] = buffer_old[i];

 		buffer_new[++j] = buffer_old[i];
		//printf("|%d %d", i, j);
	}

/*	for(int i=0; i<40; i++)
	{
		printf("%d ", buffer_old[i]);
	}

	printf("\n");

	for(int i=0; i<40; i++)
	{
		printf("%d ", buffer_new[i]);
	}
	printf("\n");
*/
        fwrite(buffer_new, new_file_size, 1, res);

                //Fermeture des fichiers

	free(buffer_old);

	free(buffer_new);

        fclose(res);

}


void compresser(FILE* original, int file_size)
{
	int new_file_size = (file_size - 44)/2;

	int16_t* buffer_old;
	int16_t* buffer_new;

        FILE* res;

	fseek(original, 44, SEEK_SET);


                // Ouverture des fichiers

        res = fopen("result/compression_attention.raw", "wb");


                // Mise en tampon de l'original

        buffer_old = (int16_t*)malloc((file_size-44)*sizeof(int16_t));


        fread(buffer_old, file_size - 44, 1, original);



		// Supression d'une valeur sur deux

	buffer_new = (int16_t*)malloc(new_file_size*sizeof(int16_t));

	for(int i=0, j=0; (i < new_file_size)&&(j < file_size-44) ; i++, j+=2)
	{
		buffer_new[i] = buffer_old[j];
		//printf("|%d %d", i, j);
	}

/*	for(int i=0; i<40; i++)
	{
		printf("%d ", buffer_old[i]);
	}

	printf("\n");

	for(int i=0; i<40; i++)
	{
		printf("%d ", buffer_new[i]);
	}
	printf("\n");
*/
        fwrite(buffer_new, new_file_size, 1, res);


                //Fermeture des fichiers

	free(buffer_old);

	free(buffer_new);

        fclose(res);

}

void grave(FILE* original, int16_t* buffer, int file_size)
{





}


