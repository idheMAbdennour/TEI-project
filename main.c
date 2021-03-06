#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

void copie(FILE* original, int file_size);
void dilater(FILE* original, int file_size);
void compresser(FILE* original, int file_size);
void grave(int16_t* buffer, int file_size, int new_file_size);
void aigue(int16_t* buffer, int file_size, int new_file_size);


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

	int16_t* buffer_old;
	int16_t* buffer_new;

	int count_noise = 0;
	int count_speech = 0;

    FILE* res;

	fseek(original, 44, SEEK_SET);


                // Ouverture des fichiers

    res = fopen("result/dilatation_attention.raw", "wb");


                // Mise en tampon de l'original

    buffer_old = (int16_t*)malloc((file_size - 44)*sizeof(int16_t));


    fread(buffer_old, file_size - 44, 1, original);



		// Duplication de chaque valeur

	buffer_new = (int16_t*)malloc(new_file_size*sizeof(int16_t));

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

	grave(buffer_new, file_size, new_file_size);

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

	aigue(buffer_new, file_size, new_file_size);

    fwrite(buffer_new, new_file_size, 1, res);


                //Fermeture des fichiers

	free(buffer_old);

	free(buffer_new);

    fclose(res);

}

void grave(int16_t* buffer, int file_size, int new_file_size)
{
	int16_t* buffer_final = (int16_t*)malloc((file_size-44)*sizeof(int16_t));
	int k=0;

	int p = 1;		// durée d'un segment en ms

	int seg = 44100*p/1000;	//nombre d'échantillon dans un segment de durée p

	FILE* final;

    final = fopen("result/grave.raw", "wb");

	for(int i=0; i < file_size-44-seg; i=i+seg)
	{
		for(int j=0; j < seg; j++)
		{
			buffer_final[j+i] = (buffer[j+i+k*(seg-1)] + buffer[j+i+seg+k*(seg-1)])/2;
		}
		k++;

	}

    fwrite(buffer_final, file_size-44, 1, final);

	free(buffer_final);

	fclose(final);
}

void aigue(int16_t* buffer, int file_size, int new_file_size)
{
    int16_t* buffer_final = (int16_t*)malloc((file_size-44)*sizeof(int16_t));
	int k=0;

	int p = 1;		// durée d'un segment en ms

	int seg = 44100*p/1000;	//nombre d'échantillon dans un segment de durée p

	FILE* final;

    final = fopen("result/aigue.raw", "wb");

	for(int i=0; i < new_file_size-seg; i=i+seg)
	{
		for(int j=0; j < seg; j++)
		{
			buffer_final[j+i+k*(seg-1)] = buffer[j+i];
			buffer_final[j+i+seg+k*(seg-1)] = buffer[j+i];
		}
		k++;
	}

    fwrite(buffer_final, file_size-44, 1, final);

	free(buffer_final);

	fclose(final);
}

