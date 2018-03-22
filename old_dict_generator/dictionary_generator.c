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

void updateTasks(char* word, struct tagset *val, char* tag);
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
    tagset tags;
    
    
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
            
            struct tagset *newtags = malloc (sizeof (struct tagset));

            memset(newtags, 0, sizeof(struct tagset));
            updateTasks(newword, newtags, newtag);
            
           // printf("The word being put into the map is: %s\nThe tag is: %s\nThe hash of the key is %lu\n", newword, newtag, hash(word));
            hashmap_put(mymap, newword, newtags);
           // printf("Here is the value of APPGE: %d\n", newtags.APPGE);

        }
        else{
            struct tagset *curtags = malloc (sizeof (struct tagset));

            hashmap_get(mymap, newword, (void **)&curtags);
           // printf("The word being updated in the map is: %s\nThe tag is: %s\nThe hash of it is %lu\n", newword, newtag, hash(tag));
         //   printf("The value of the ZZ2 before updating is: %d\n", curtags->ZZ2);
            updateTasks(newword,curtags, newtag);
       //     printf("The value of the APPGE after updating is: %d\n", curtags->APPGE);
            hashmap_remove(mymap, newword);
            hashmap_put(mymap, newword, curtags);
        }

    }
    
    printf("Size of map is: %d\n",hashmap_length(mymap) );
 //   tagset* finalval;
  //  printf("Trying to find value James with hash %lu\n", hash("James"));
    
        printMap(mymap, "James");
        printMap(mymap, "Uni");
        printMap(mymap, "Gary");
        printMap(mymap, "Paul");

    
    
    
    
    
    /* Now, destroy the map */
   // hashmap_free(mymap);
    //free(newword);
    //free(newtag);

    return mymap;
}


void updateTasks(char* word, struct tagset *val, char* tag){
    
    unsigned long hash_value = hash(tag);
    switch(hash_value){
        case 210667599090: val->APPGE
            +=1; break;
        case 193450564: val->AT
            +=1; break;
        case 6383869909: val->AT1
            +=1; break;
        case 6383888224: val->BCL
            +=1; break;
        case 193452181: val->CC
            +=1; break;
        case 6383923831: val->CCB
            +=1; break;
        case 193452709: val->CS
            +=1; break;
        case 6383941222: val->CSA
            +=1; break;
        case 6383941651: val->CSN
            +=1; break;
        case 6383941849: val->CST
            +=1; break;
        case 6383941948: val->CSW
            +=1; break;
        case 193453204: val->DA
            +=1; break;
        case 6383957029: val->DA1
            +=1; break;
        case 6383957062: val->DA2
            +=1; break;
        case 6383958118: val->DAR
            +=1; break;
        case 6383958184: val->DAT
            +=1; break;
        case 193453237: val->DB
            +=1; break;
        case 6383958151: val->DB2
            +=1; break;
        case 193453303: val->DD
            +=1; break;
        case 6383960296: val->DD1
            +=1; break;
        case 6383960329: val->DD2
            +=1; break;
        case 6383961352: val->DDQ
            +=1; break;
        case 6952133981044: val->DDQGE
            +=1; break;
        case 210670727134: val->DDQV
            +=1; break;
        case 193455052: val->EX
            +=1; break;
        case 193455844: val->FO
            +=1; break;
        case 193456042: val->FU
            +=1; break;
        case 193456108: val->FW
            +=1; break;
        case 193456603: val->GE
            +=1; break;
        case 193458814: val->IF
            +=1; break;
        case 193458913: val->II
            +=1; break;
        case 193459111: val->IO
            +=1; break;
        case 193459375: val->IW
            +=1; break;
        case 193460035: val->JJ
            +=1; break;
        case 6384183541: val->JJR
            +=1; break;
        case 6384183607: val->JJT
            +=1; break;
        case 193460068: val->JK
            +=1; break;
        case 193463071: val->MC
            +=1; break;
        case 6384282640: val->MC1
            +=1; break;
        case 6384282673: val->MC2
            +=1; break;
        case 210681353035: val->MCGE
            +=1; break;
        case 210681359503: val->MCMC
            +=1; break;
        case 193463104: val->MD
            +=1; break;
        case 193463170: val->MF
            +=1; break;
        case 6384319666: val->ND1
            +=1; break;
        case 193464523: val->NN
            +=1; break;
        case 6384330556: val->NN1
            +=1; break;
        case 6384330589: val->NN2
            +=1; break;
        case 6384331084: val->NNA
            +=1; break;
        case 6384331117: val->NNB
            +=1; break;
        case 210682939048: val->NNL1
            +=1; break;
        case 210682939081: val->NNL2
            +=1; break;
        case 6384331546: val->NNO
            +=1; break;
        case 210682942348: val->NNO2
            +=1; break;
        case 210682947760: val->NNT1
            +=1; break;
        case 210682947793: val->NNT2
            +=1; break;
        case 6384331744: val->NNU
            +=1; break;
        case 210682948849: val->NNU1
            +=1; break;
        case 210682948882: val->NNU2
            +=1; break;
        case 193464589: val->NP
            +=1; break;
        case 6384332734: val->NP1
            +=1; break;
        case 6384332767: val->NP2
            +=1; break;
        case 210683002210: val->NPD1
            +=1; break;
        case 210683002243: val->NPD2
            +=1; break;
        case 210683012011: val->NPM1
            +=1; break;
        case 210683012044: val->NPM2
            +=1; break;
        case 193466701: val->PN
            +=1; break;
        case 6384402430: val->PN1
            +=1; break;
        case 210685317325: val->PNQO
            +=1; break;
        case 210685317457: val->PNQS
            +=1; break;
        case 210685317556: val->PNQV
            +=1; break;
        case 210685323958: val->PNX1
            +=1; break;
        case 210685377979: val->PPGE
            +=1; break;
        case 210685378408: val->PPH1
            +=1; break;
        case 6952617521431: val->PPHO1
            +=1; break;
        case 6952617521464: val->PPHO2
            +=1; break;
        case 6952617525787: val->PPHS1
            +=1; break;
        case 6952617525820: val->PPHS2
            +=1; break;
        case 6952617557368: val->PPIO1
            +=1; break;
        case 6952617557401: val->PPIO2
            +=1; break;
        case 6952617561724: val->PPIS1
            +=1; break;
        case 6952617561757: val->PPIS2
            +=1; break;
        case 210685395832: val->PPX1
            +=1; break;
        case 210685395865: val->PPX2
            +=1; break;
        case 6384405928: val->PPY
            +=1; break;
        case 193468450: val->RA
            +=1; break;
        case 6384465790: val->REX
            +=1; break;
        case 193468648: val->RG
            +=1; break;
        case 6384467737: val->RGQ
            +=1; break;
        case 210687437839: val->RGQV
            +=1; break;
        case 6384467770: val->RGR
            +=1; break;
        case 6384467836: val->RGT
            +=1; break;
        case 193468813: val->RL
            +=1; break;
        case 193468945: val->RP
            +=1; break;
        case 6384477340: val->RPK
            +=1; break;
        case 193469011: val->RR
            +=1; break;
        case 6384479716: val->RRQ
            +=1; break;
        case 210687833146: val->RRQV
            +=1; break;
        case 6384479749: val->RRR
            +=1; break;
        case 6384479815: val->RRT
            +=1; break;
        case 193469077: val->RT
            +=1; break;
        case 193471090: val->TO
            +=1; break;
        case 193471948: val->UH
            +=1; break;
        case 6384604951: val->VB0
            +=1; break;
        case 210691987549: val->VBDR
            +=1; break;
        case 210691987813: val->VBDZ
            +=1; break;
        case 6384605710: val->VBG
            +=1; break;
        case 6384605776: val->VBI
            +=1; break;
        case 6384605908: val->VBM
            +=1; break;
        case 6384605941: val->VBN
            +=1; break;
        case 6384606073: val->VBR
            +=1; break;
        case 6384606337: val->VBZ
            +=1; break;
        case 6384607129: val->VD0
            +=1; break;
        case 6384607789: val->VDD
            +=1; break;
        case 6384607888: val->VDG
            +=1; break;
        case 6384607954: val->VDI
            +=1; break;
        case 6384608119: val->VDN
            +=1; break;
        case 6384608515: val->VDZ
            +=1; break;
        case 6384611485: val->VH0
            +=1; break;
        case 6384612145: val->VHD
            +=1; break;
        case 6384612244: val->VHG
            +=1; break;
        case 6384612310: val->VHI
            +=1; break;
        case 6384612475: val->VHN
            +=1; break;
        case 6384612871: val->VHZ
            +=1; break;
        case 193473202: val->VM
            +=1; break;
        case 6384617821: val->VMK
            +=1; break;
        case 6384626731: val->VV0
            +=1; break;
        case 6384627391: val->VVD
            +=1; break;
        case 6384627490: val->VVG
            +=1; break;
        case 210692709325: val->VVGK
            +=1; break;
        case 6384627556: val->VVI
            +=1; break;
        case 6384627721: val->VVN
            +=1; break;
        case 210692716948: val->VVNK
            +=1; break;
        case 6384628117: val->VVZ
            +=1; break;
        case 193475743: val->XX
            +=1; break;
        case 193478026: val->ZZ1
            +=1; break;
        case 193478027: val->ZZ2+=1; break;
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
  struct tagset *finalval = malloc (sizeof (struct tagset));
   if(hashmap_get(mymap, name, (void **)&finalval) == MAP_OK)
    printf("Key: %s\nValues: APPGE=%d\tZZ1=%d\tZZ2=%d\n", name, finalval->APPGE, finalval->ZZ1, finalval->ZZ2);

}
          

