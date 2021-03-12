#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

void copie(FILE* original);
void grave();
void aigue();
void file_handle();
void slice();

typedef struct
{
    unsigned long FileTypeBlocID;
    unsigned long FileSize;
    unsigned long FileFormatID;
    unsigned long FormatBlocID;
    unsigned long BlocSize;
    uint16_t AudioFormat;
    uint16_t NbrCanaux;
    unsigned long Frequence;
    unsigned long BytePerSec;
    uint16_t BytePerBloc;
    uint16_t BitsPerSample;
    unsigned long DataBlocID;
    unsigned long DataSize;
  
}wav_h;

typedef struct
{
    FILE* File;

    wav_h Header;    

    char* Data;
    
}fichier_wav;


fichier_wav source;   


int main()
{
    file_handle();
    
    copie(source.File);

    free(source.Data);

		
}

void copie(FILE* original)
{   
    unsigned long file_size = source.Header.FileSize;
	int16_t* buffer;
    

    fichier_wav copie;


                // Ouverture des fichiers

    copie.File = fopen("result/copie_attention.wav", "wb");


                // Copie

    buffer = (int16_t*)malloc(file_size);

    fread(buffer, file_size, 1, original);

    fwrite(buffer, file_size, 1, copie);


                //Fermeture des fichiers

	free(buffer);

    fclose(copie);	

}

void grave()
{
	fichier_wav grave;
   
}

void aigue()
{
   
	
}

void file_handle()
{
    int i=0;     
    int file_size;

    source.File = fopen("sample/attention.wav", "rb");

    fseek(source.File, 0, SEEK_END);
	file_size = ftell(source.File);
	fseek(source.File, 0, SEEK_SET);

    char* buffer;
    buffer = malloc(file_size);    

    fread(buffer, file_size, 1, source.File);
    
    source.Header.FileTypeBlocID = buffer[i];
        i=i+4;
    source.Header.FileSize = buffer[i];
        i=i+4;
    source.Header.FileFormatID = buffer[i];
        i=i+4;
    source.Header.FormatBlocID = buffer[i];
        i=i+4;    
    source.Header.BlocSize = buffer[i];
        i=i+4;
    source.Header.AudioFormat = buffer[i];
        i=i+2;
    source.Header.NbrCanaux = buffer[i];
        i=i+2;
    source.Header.Frequence = buffer[i];
        i=i+4;
    source.Header.BytePerSec = buffer[i];
        i=i+4;
    source.Header.BytePerBloc = buffer[i];
        i=i+2;
    source.Header.BitsPerSample = buffer[i];
        i=i+2;
    source.Header.DataBlocID = buffer[i];
        i=i+4;
    source.Header.DataSize = buffer[i]; 

    free(buffer);

    slice();         
}

void slice()
{
    unsigned long data_size = source.Header.DataSize;
    
    source.Data = malloc(data_size);

    fseek(source.File, 44, SEEK_SET);

    fread(source.Data, data_size, 1, source.File);  
}

