// CREDIT A MATHISZER HAHAHAHA C'EST LUI QUI A ECRIT CE CODE HAHAHAHA LE GOAT

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "ini.h"

#define NIGZIP int main(void)

char FILENAME[24];
char FINALNAME[24];
int PERCENT = 10; //default value
int KEEP = 1024; //default value
uint SEED = 0; //default value

static int handler(void* user, const char* sec, const char* name, const char* value){
    if(strcmp(name, "filename") == 0) strcpy(FILENAME, value);
    if(strcmp(name, "finalname") == 0) strcpy(FINALNAME, value);
    if(strcmp(name, "percentage") == 0) PERCENT = atoi(value);
    if(strcmp(name, "starting_byte") == 0) KEEP = atoi(value);
    if(strcmp(name, "seed") == 0) SEED = atoi(value);
}

NIGZIP{
    uint64_t size;
    char* buf;

    if(ini_parse("options.ini", handler, NULL) < 0) exit(1);

    srand(SEED);
    FILE* ficher = fopen(FILENAME, "rb");
    if(ficher == NULL) exit(1);
    fseek(ficher, 0, SEEK_END);
    size = ftell(ficher);
    fseek(ficher, 0, SEEK_SET);
    printf("Taille du fichier: %d bytes\n", size);
    buf = malloc(size);
    fread(buf, 1, size, ficher);
    fclose(ficher);

    for(int i = KEEP; i < size; i++){
        if(rand() % 100 > PERCENT){
            buf[i] = 0;
        }
    }

    FILE* ecrire = fopen(FINALNAME, "wb");
    if(ecrire == NULL) exit(1);
    fwrite(buf, 1, size, ecrire);
    free(buf);
    fclose(ecrire);
    
    printf("Réussi !\n");
    return 0;
}