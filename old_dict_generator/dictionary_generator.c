#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "tags.h"
#include "../lib/hashmap.h"

#define KEY_MAX_LENGTH (256)
#define KEY_PREFIX ("somekey")
#define KEY_COUNT (1024*1024)



typedef struct data_struct_s
{
    char key_string[KEY_MAX_LENGTH];
    int number;
} data_struct_t;

void updateTags(char* word, struct tagcounts_t *val, char* tag);
unsigned long hash(char *str);
void printMap(map_t mymap, char* name);

map_t generate_dictionary(char *filepath)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    int index;
    int error;
    map_t mymap;
    char key_string[KEY_MAX_LENGTH];
    data_struct_t* value;
    char* val;
    
    char *buffer[3];
    
    mymap = hashmap_new();

    fp = fopen(filepath, "r");
    char *saveptr;
    char *word;
    char *tag;
    tagcounts_t tags;
    
    
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int counter = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
      
        word = strtok_r(line, " ", &saveptr);
        tag = strtok_r(NULL, " ", &saveptr);
        if(word[read-1] == '\n') word[read-1] = '\0';
        if(tag[read-1] == '\n') tag[read-1] = '\0';
        
         char* newword = malloc(strlen(word) + 1);
         char* newtag = malloc(strlen(tag) + 1);
        
        strcpy(newword, word);
        strcpy(newtag, tag);
       
      
        
        
        //Get the current tagset

        if(hashmap_get(mymap, word, (void **)&tags) == MAP_MISSING){
            
            struct tagcounts_t *newtags = malloc (sizeof (struct tagcounts_t));

            memset(newtags, 0, sizeof(struct tagcounts_t));
            updateTags(newword, newtags, newtag);
            
           // printf("The word being put into the map is: %s\nThe tag is: %s\nThe hash of the key is %lu\n", newword, newtag, hash(word));
            hashmap_put(mymap, newword, newtags);
           // printf("Here is the value of APPGE: %d\n", newtags.APPGE);

        }
        else{
            struct tagcounts_t *curtags = malloc (sizeof (struct tagcounts_t));

            hashmap_get(mymap, newword, (void **)&curtags);
           // printf("The word being updated in the map is: %s\nThe tag is: %s\nThe hash of it is %lu\n", newword, newtag, hash(tag));
         //   printf("The value of the ZZ2 before updating is: %d\n", curtags->ZZ2);
            updateTags(newword,curtags, newtag);
       //     printf("The value of the APPGE after updating is: %d\n", curtags->APPGE);
            hashmap_remove(mymap, newword);
            hashmap_put(mymap, newword, curtags);
        }

    }
    
    printf("Size of map is: %d\n",hashmap_length(mymap) );


    
    
    
    
    
    /* Now, destroy the map */
   // hashmap_free(mymap);
    //free(newword);
    //free(newtag);

    return mymap;
}


void updateTags(char* word, struct tagcounts_t *val, char* tag){
    
    unsigned long hash_value = hash(tag);
    if(strcmp(tag, "vd0")) hash_value+=1;
    switch(hash_value){
        case 210706734482: val->APPGE+=1; break;
        case 5863226: val->AT+=1; break;
        case 193486507: val->AT1+=1; break;
        case 193487094: val->BCL+=1; break;
        case 5863275: val->CC+=1; break;
        case 193488173: val->CCB+=1; break;
        case 5863291: val->CS+=1; break;
        case 193488700: val->CSA+=1; break;
        case 193488713: val->CSN+=1; break;
        case 193488719: val->CST+=1; break;
        case 193488722: val->CSW+=1; break;
        case 5863306: val->DA+=1; break;
        case 193489147: val->DA1+=1; break;
        case 193489148: val->DA2+=1; break;
        case 193489212: val->DAR+=1; break;
        case 193489214: val->DAT+=1; break;
        case 5863307: val->DB+=1; break;
        case 193489181: val->DB2+=1; break;
        case 5863309: val->DD+=1; break;
        case 193489246: val->DD1+=1; break;
        case 193489247: val->DD2+=1; break;
        case 193489310: val->DDQ+=1; break;
        case 210709862090: val->DDQGE+=1; break;
        case 6385147348: val->DDQV+=1; break;
        case 5863362: val->EX+=1; break;
        case 5863386: val->FO+=1; break;
        case 5863392: val->FU+=1; break;
        case 5863394: val->FW+=1; break;
        case 5863409: val->GE+=1; break;
        case 5863476: val->IF+=1; break;
        case 5863479: val->II+=1; break;
        case 5863485: val->IO+=1; break;
        case 5863493: val->IW+=1; break;
        case 5863513: val->JJ+=1; break;
        case 193496043: val->JJR+=1; break;
        case 193496045: val->JJT+=1; break;
        case 5863514: val->JK+=1; break;
        case 5863605: val->MC+=1; break;
        case 193499014: val->MC1+=1; break;
        case 193499015: val->MC2+=1; break;
        case 6385469345: val->MCGE+=1; break;
        case 6385469541: val->MCMC+=1; break;
        case 5863606: val->MD+=1; break;
        case 5863608: val->MF+=1; break;
        case 193500136: val->ND1+=1; break;
        case 5863649: val->NN+=1; break;
        case 193500466: val->NN1+=1; break;
        case 193500467: val->NN2+=1; break;
        case 193500514: val->NNA+=1; break;
        case 193500515: val->NNB+=1; break;
        case 6385517374: val->NNL1+=1; break;
        case 6385517375: val->NNL2+=1; break;
        case 193500528: val->NNO+=1; break;
        case 6385517474: val->NNO2+=1; break;
        case 6385517638: val->NNT1+=1; break;
        case 6385517639: val->NNT2+=1; break;
        case 193500534: val->NNU+=1; break;
        case 6385517671: val->NNU1+=1; break;
        case 6385517672: val->NNU2+=1; break;
        case 5863651: val->NP+=1; break;
        case 193500532: val->NP1+=1; break;
        case 193500533: val->NP2+=1; break;
        case 6385519288: val->NPD1+=1; break;
        case 6385519289: val->NPD2+=1; break;
        case 6385519585: val->NPM1+=1; break;
        case 6385519586: val->NPM2+=1; break;
        case 5863715: val->PN+=1; break;
        case 193502644: val->PN1+=1; break;
        case 6385589475: val->PNQO+=1; break;
        case 6385589479: val->PNQS+=1; break;
        case 6385589482: val->PNQV+=1; break;
        case 6385589644: val->PNX1+=1; break;
        case 6385591313: val->PPGE+=1; break;
        case 6385591294: val->PPH1+=1; break;
        case 210724514797: val->PPHO1+=1; break;
        case 210724514798: val->PPHO2+=1; break;
        case 210724514929: val->PPHS1+=1; break;
        case 210724514930: val->PPHS2+=1; break;
        case 210724515886: val->PPIO1+=1; break;
        case 210724515887: val->PPIO2+=1; break;
        case 210724516018: val->PPIS1+=1; break;
        case 210724516019: val->PPIS2+=1; break;
        case 6385591822: val->PPX1+=1; break;
        case 6385591823: val->PPX2+=1; break;
        case 193502782: val->PPY+=1; break;
        case 5863768: val->RA+=1; break;
        case 193504596: val->REX+=1; break;
        case 5863774: val->RG+=1; break;
        case 193504655: val->RGQ+=1; break;
        case 6385653733: val->RGQV+=1; break;
        case 193504656: val->RGR+=1; break;
        case 193504658: val->RGT+=1; break;
        case 5863779: val->RL+=1; break;
        case 5863783: val->RP+=1; break;
        case 193504946: val->RPK+=1; break;
        case 5863785: val->RR+=1; break;
        case 193505018: val->RRQ+=1; break;
        case 6385665712: val->RRQV+=1; break;
        case 193505019: val->RRR+=1; break;
        case 193505021: val->RRT+=1; break;
        case 5863787: val->RT+=1; break;
        case 5863848: val->TO+=1; break;
        case 5863874: val->UH+=1; break;
        case 193508781: val->VB0+=1; break;
        case 6385791603: val->VBDR+=1; break;
        case 6385791611: val->VBDZ+=1; break;
        case 193508836: val->VBG+=1; break;
        case 193508838: val->VBI+=1; break;
        case 193508842: val->VBM+=1; break;
        case 193508843: val->VBN+=1; break;
        case 193508847: val->VBR+=1; break;
        case 193508855: val->VBZ+=1; break;
        case 193508848: val->VD0+=1; break;
        case 193508899: val->VDD+=1; break;
        case 193508902: val->VDG+=1; break;
        case 193508904: val->VDI+=1; break;
        case 193508909: val->VDN+=1; break;
        case 193508921: val->VDZ+=1; break;
        case 193508979: val->VH0+=1; break;
        case 193509031: val->VHD+=1; break;
        case 193509034: val->VHG+=1; break;
        case 193509036: val->VHI+=1; break;
        case 193509041: val->VHN+=1; break;
        case 193509053: val->VHZ+=1; break;
        case 5863912: val->VM+=1; break;
        case 193509203: val->VMK+=1; break;
        case 193509441: val->VV0+=1; break;
        case 193509493: val->VVD+=1; break;
        case 193509496: val->VVG+=1; break;
        case 6385813475: val->VVGK+=1; break;
        case 193509498: val->VVI+=1; break;
        case 193509503: val->VVN+=1; break;
        case 6385813706: val->VVNK+=1; break;
        case 193509515: val->VVZ+=1; break;
        case 5863989: val->XX+=1; break;
        case 193513930: val->ZZ1+=1; break;
        case 193513931: val->ZZ2+=1; break;
    }
    
}

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    
    return hash;
}

void printMap(map_t mymap, char* name){
  struct tagcounts_t *finalval = malloc (sizeof (struct tagcounts_t));
   if(hashmap_get(mymap, name, (void **)&finalval) == MAP_OK)
    printf("Key: %s\nValues: APPGE=%d\tZZ1=%d\tZZ2=%d\n", name, finalval->APPGE, finalval->ZZ1, finalval->ZZ2);

}
          

