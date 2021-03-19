#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

void copie();
void grave();
void aigue();
void file_handle();
void slice();

typedef struct
{
    uint8_t FileTypeBlocID[4];
    uint32_t FileSize;
    uint8_t FileFormatID[4];
    uint8_t FormatBlocID[4];
    uint32_t BlocSize;
    uint16_t AudioFormat;
    uint16_t NbrCanaux;
    uint32_t Frequence;
    uint32_t BytePerSec;
    uint16_t BytePerBloc;
    uint16_t BitsPerSample;
    uint8_t DataBlocID[4];
    uint32_t DataSize;
  
}wav_h;

typedef struct
{
    FILE* File;

    wav_h Header;    

    uint8_t* Data;
    
}fichier_wav;


fichier_wav source;   


int main()
{
    file_handle();

            printf("FileTypeBlocID : %s\n", source.Header.FileTypeBlocID);
            printf("FileSize : %u \n", source.Header.FileSize);
            printf("FileFormatID : %s\n", source.Header.FileFormatID);
            printf("FormatBlocID : %s\n", source.Header.FormatBlocID);
            printf("BlocSize : %u\n", source.Header.BlocSize);
            printf("AudioFormat : %u\n", source.Header.AudioFormat);
            printf("NbrCanaux : %u\n", source.Header.NbrCanaux);
            printf("Frequence : %u\n", source.Header.Frequence);
            printf("BytePerSec : %u\n", source.Header.BytePerSec);
            printf("BytePerBloc : %u\n", source.Header.BytePerBloc);
            printf("BitsPerSample : %u\n", source.Header.BitsPerSample);
            printf("DataBlocID : %s\n", source.Header.DataBlocID);
            printf("DataSize : %u\n", source.Header.DataSize);


    
    copie(source.File);

    free(source.Data);

		
}

void copie()
{   
    fichier_wav copie; 
    
    uint32_t file_size = source.Header.FileSize;


                // Ouverture des fichiers

    copie.File = fopen("result/copie_attention.wav", "wb");


                // Copie

    int16_t* buffer = (int16_t*)malloc(file_size);

    fread(buffer, file_size, 1, source.File);

    fwrite(buffer, file_size, 1, copie.File);


                //Fermeture des fichiers

	free(buffer);

    fclose(copie.File);	

}

void grave8()
{        
            // Déclaration et initialisation de la structure grave
    
    fichier_wav grave;
    grave.File = fopen("result/grave.wav", "wb");
    grave.Header = source.Header;
    grave.Data = (uint8_t*)malloc(grave.Header.DataSize);    


    		// Duplication de chaque valeur
   
	uint8_t* buffer = (uint8_t*)malloc(grave.Header.DataSize * 2);

	for(int i=0, j=0; i < grave.Header.DataSize; i++, j++)
	{
		buffer[j] = source.Data[i];

 		buffer[++j] = source.Data[i];
	}


            // Mise à l'échelle  
    
    int k=0;

	int p = 1;		                                // durée d'un segment en ms

	int seg = grave.Header.Frequence*p/1000;	    //nombre d'échantillon dans un segment de durée p  

	for(int i=0; i < grave.Header.Datasize - seg; i=i+seg)
	{
		for(int j=0; j < seg; j++)
		{
			grave.Data[j+i] = (buffer[j+i+seg+k*(seg-1)] + buffer[j+i+seg+k*(seg-1)])/2;
		}
		k++;

	}  

    fwrite(grave.Data, grave.Header.Datasize, 1, grave.File);

	free(buffer);
    free(grave.Data);

	fclose(grave.File);

}

void grave16()
{        
            // Déclaration et initialisation de la structure grave
    
    fichier_wav grave;
    grave.File = fopen("result/grave.wav", "wb");
    grave.Header = source.Header;
    grave.Data = (uint8_t*)malloc(grave.Header.DataSize);    


    		// Duplication de chaque valeur
   
	uint8_t* buffer = (uint8_t*)malloc(grave.Header.DataSize * 2);

	for(int i=0, j=0; i < grave.Header.DataSize; i++, j++)
	{
		buffer[j] = source.Data[i];

 		buffer[++j] = source.Data[i];
	}


            // Mise à l'échelle  
    
    int k=0;

	int p = 1;		                                // durée d'un segment en ms

	int seg = grave.Header.Frequence*p/1000;	    //nombre d'échantillon dans un segment de durée p  

	for(int i=0; i < grave.Header.Datasize - seg; i=i+seg)
	{
		for(int j=0; j < seg; j++)
		{
			grave.Data[j+i] = (buffer[j+i+seg+k*(seg-1)] + buffer[j+i+seg+k*(seg-1)])/2;
		}
		k++;

	}  

    fwrite(grave.Data, grave.Header.Datasize, 1, grave.File);

	free(buffer);
    free(grave.Data);

	fclose(grave.File);

}

void grave32()
{        
            // Déclaration et initialisation de la structure grave
    
    fichier_wav grave;
    grave.File = fopen("result/grave.wav", "wb");
    grave.Header = source.Header;
    grave.Data = (uint8_t*)malloc(grave.Header.DataSize);    


    		// Duplication de chaque valeur
   
	uint8_t* buffer = (uint8_t*)malloc(grave.Header.DataSize * 2);

	for(int i=0, j=0; i < grave.Header.DataSize; i++, j++)
	{
		buffer[j] = source.Data[i];

 		buffer[++j] = source.Data[i];
	}


            // Mise à l'échelle  
    
    int k=0;

	int p = 1;		                                // durée d'un segment en ms

	int seg = grave.Header.Frequence*p/1000;	    //nombre d'échantillon dans un segment de durée p  

	for(int i=0; i < grave.Header.Datasize - seg; i=i+seg)
	{
		for(int j=0; j < seg; j++)
		{
			grave.Data[j+i] = (buffer[j+i+seg+k*(seg-1)] + buffer[j+i+seg+k*(seg-1)])/2;
		}
		k++;

	}  

    fwrite(grave.Data, grave.Header.Datasize, 1, grave.File);

	free(buffer);
    free(grave.Data);

	fclose(grave.File);

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

    uint8_t* buffer;
    buffer = malloc(file_size);    

    fread(buffer, file_size, 1, source.File);
    
    *((uint32_t*)source.Header.FileTypeBlocID) = *((uint32_t*)(buffer+i));
        i=i+4;
    
    source.Header.FileSize = *((uint32_t*)(buffer+i));
        i=i+4;
    
    source.Header.FileFormatID[0] = *(buffer+i);
        i=i+1;
    source.Header.FileFormatID[1] = *(buffer+i);
        i=i+1;
    source.Header.FileFormatID[2] = *(buffer+i);
        i=i+1;
    source.Header.FileFormatID[3] = *(buffer+i);
        i=i+1;

    source.Header.FormatBlocID[0] = *(buffer+i);
        i=i+1;    
    source.Header.FormatBlocID[1] = *(buffer+i);
        i=i+1; 
    source.Header.FormatBlocID[2] = *(buffer+i);
        i=i+1; 
    source.Header.FormatBlocID[3] = *(buffer+i);
        i=i+1; 
    
    source.Header.BlocSize = *((uint32_t*)(buffer+i));
        i=i+4;

    source.Header.AudioFormat = *((uint16_t*)(buffer+i));
        i=i+2;

    source.Header.NbrCanaux = *((uint16_t*)(buffer+i));
        i=i+2;

    source.Header.Frequence = *((uint32_t*)(buffer+i));
        i=i+4;

    source.Header.BytePerSec = *((uint32_t*)(buffer+i));
        i=i+4;

    source.Header.BytePerBloc = *((uint16_t*)(buffer+i));
        i=i+2;

    source.Header.BitsPerSample = *((uint16_t*)(buffer+i));
        i=i+2;

    source.Header.DataBlocID[0] = *(buffer+i);
        i=i+1;
    source.Header.DataBlocID[1] = *(buffer+i);
        i=i+1;
    source.Header.DataBlocID[2] = *(buffer+i);
        i=i+1;
    source.Header.DataBlocID[3] = *(buffer+i);
        i=i+1;

    source.Header.DataSize = *((uint32_t*)(buffer+i)); 

    free(buffer);

    slice();         
}

void slice()
{    
    source.Data = (uint8_t*)malloc(source.Header.DataSize);

    fseek(source.File, 44, SEEK_SET);

    fread(source.Data, source.Header.DataSize, 1, source.File);  
}

