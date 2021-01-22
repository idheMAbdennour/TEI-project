#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

int main()
{
	int file_size;
	int *fsize = &file_size;

	int *buffer;

	FILE *original;
	FILE *copie;


	original = fopen("sample/attention.wav", "rb");
	copie = fopen("result/copie_attention.wav", "wb");

	buffer = (int*)malloc(lseek(original, 0L, SEEK_END));

	fread(buffer, lseek(original, 0L, SEEK_END), 1, original);
	fwrite(buffer, lseek(original, 0L, SEEK_END),1, copie);

	//printf("%d\n", file_size);

	return 0;
}
