#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "main.h"

int main()
{
	int file_size;
	int *fsize = &file_size;

	int *buffer;

//	printf("0");

	FILE *original;
	FILE *copie;

	original = fopen("sample/attention.wav", "rb"); 
//	printf("1");
	copie = fopen("result/copie_attention.wav", "wb");
//	printf("2");

	fseek(original, 0, SEEK_END);
	file_size = ftell(original);
	fseek(original, 0, SEEK_SET);


	buffer = (int*)malloc(file_size);
//	printf("3");

	fread(buffer, file_size, 1, original);
//	printf("4");
	fwrite(buffer, file_size, 1, copie);
//	printf("5");
	//printf("%d\n", file_size);

	return 0;
}
