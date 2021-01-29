#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

void copie(FILE* original, int file_size);

int main()
{
		// Declaration des variables et pointeurs

	int file_size;

	int* buffer;

	FILE* original;
//	FILE* copie;


		// Ouverture des fichiers

	original = fopen("sample/attention.wav", "rb");
//	copie = fopen("result/copie_attention.wav", "wb");


		// Taille du fichier à copier

	fseek(original, 0, SEEK_END);
	file_size = ftell(original);
	fseek(original, 0, SEEK_SET);


		// Copie

	copie(original, file_size);

//	buffer = (int*)malloc(file_size);

//	fread(buffer, file_size, 1, original);

//	fwrite(buffer, file_size, 1, copie);


		//Fermeture des fichiers

	fclose(original);
//	fclose(copie);
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


