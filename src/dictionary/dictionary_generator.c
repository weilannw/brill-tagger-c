#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "tags.h"
#include "dictionary_generator.h"
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
            updateTags(newword, newtags, newtag);
            hashmap_put(mymap, newword, newtags);
        }
        else{
            struct tagset *curtags = malloc (sizeof (struct tagset));
            hashmap_get(mymap, newword, (void **)&curtags);
            updateTags(newword,curtags, newtag);
            hashmap_remove(mymap, newword);
            hashmap_put(mymap, newword, curtags);
        }

    }
    return mymap;
}

void updateTags(char* word, struct tagset *val, char* tag){
    unsigned long hash_value = hash(tag);
    switch(hash_value){
        case APPGE: val->APPGE++; 
            break;
        case AT: val->AT++; 
            break;
        case AT1: val->AT1++; 
            break;
        case BCL: val->BCL++; 
            break;
        case CC: val->CC++; 
            break;
        case CCB: val->CCB++; 
            break;
        case CS: val->CS++; 
            break;
        case CSA: val->CSA++; 
            break;
        case CSN: val->CSN++; 
            break;
        case CST: val->CST++; 
            break;
        case CSW: val->CSW++; 
            break;
        case DA: val->DA++; 
            break;
        case DA1: val->DA1++; 
            break;
        case DA2: val->DA2++; 
            break;
        case DAR: val->DAR++; 
            break;
        case DAT: val->DAT++; 
            break;
        case DB: val->DB++; 
            break;
        case DB2: val->DB2++; 
            break;
        case DD: val->DD++; 
            break;
        case DD1: val->DD1++; 
            break;
        case DD2: val->DD2++; 
            break;
        case DDQ: val->DDQ++; 
            break;
        case DDQGE: val->DDQGE++; 
            break;
        case DDQV: val->DDQV++; 
            break;
        case EX: val->EX++; 
            break;
        case FO: val->FO++; 
            break;
        case FU: val->FU++; 
            break;
        case FW: val->FW++; 
            break;
        case GE: val->GE++; 
            break;
        case IF: val->IF++; 
            break;
        case II: val->II++; 
            break;
        case IO: val->IO++; 
            break;
        case IW: val->IW++; 
            break;
        case JJ: val->JJ++; 
            break;
        case JJR: val->JJR++; 
            break;
        case JJT: val->JJT++; 
            break;
        case JK: val->JK++; 
            break;
        case MC: val->MC++; 
            break;
        case MC1: val->MC1++; 
            break;
        case MC2: val->MC2++; 
            break;
        case MCGE: val->MCGE++; 
            break;
        case MCMC: val->MCMC++; 
            break;
        case MD: val->MD++; 
            break;
        case MF: val->MF++; 
            break;
        case ND1: val->ND1++; 
            break;
        case NN: val->NN++; 
            break;
        case NN1: val->NN1++; 
            break;
        case NN2: val->NN2++; 
            break;
        case NNA: val->NNA++; 
            break;
        case NNB: val->NNB++; 
            break;
        case NNL1: val->NNL1++; 
            break;
        case NNL2: val->NNL2++; 
            break;
        case NNO: val->NNO++; 
            break;
        case NNO2: val->NNO2++; 
            break;
        case NNT1: val->NNT1++; 
            break;
        case NNT2: val->NNT2++; 
            break;
        case NNU: val->NNU++; 
            break;
        case NNU1: val->NNU1++; 
            break;
        case NNU2: val->NNU2++; 
            break;
        case NP: val->NP++; 
            break;
        case NP1: val->NP1++; 
            break;
        case NP2: val->NP2++; 
            break;
        case NPD1: val->NPD1++; 
            break;
        case NPD2: val->NPD2++; 
            break;
        case NPM1: val->NPM1++; 
            break;
        case NPM2: val->NPM2++; 
            break;
        case PN: val->PN++; 
            break;
        case PN1: val->PN1++; 
            break;
        case PNQO: val->PNQO++; 
            break;
        case PNQS: val->PNQS++; 
            break;
        case PNQV: val->PNQV++; 
            break;
        case PNX1: val->PNX1++; 
            break;
        case PPGE: val->PPGE++; 
            break;
        case PPH1: val->PPH1++; 
            break;
        case PPHO1: val->PPHO1++; 
            break;
        case PPHO2: val->PPHO2++; 
            break;
        case PPHS1: val->PPHS1++; 
            break;
        case PPHS2: val->PPHS2++; 
            break;
        case PPIO1: val->PPIO1++; 
            break;
        case PPIO2: val->PPIO2++; 
            break;
        case PPIS1: val->PPIS1++; 
            break;
        case PPIS2: val->PPIS2++; 
            break;
        case PPX1: val->PPX1++; 
            break;
        case PPX2: val->PPX2++; 
            break;
        case PPY: val->PPY++; 
            break;
        case RA: val->RA++; 
            break;
        case REX: val->REX++; 
            break;
        case RG: val->RG++; 
            break;
        case RGQ: val->RGQ++; 
            break;
        case RGQV: val->RGQV++; 
            break;
        case RGR: val->RGR++; 
            break;
        case RGT: val->RGT++; 
            break;
        case RL: val->RL++; 
            break;
        case RP: val->RP++; 
            break;
        case RPK: val->RPK++; 
            break;
        case RR: val->RR++; 
            break;
        case RRQ: val->RRQ++; 
            break;
        case RRQV: val->RRQV++; 
            break;
        case RRR: val->RRR++; 
            break;
        case RRT: val->RRT++; 
            break;
        case RT: val->RT++; 
            break;
        case TO: val->TO++; 
            break;
        case UH: val->UH++; 
            break;
        case VB0: val->VB0++; 
            break;
        case VBDR: val->VBDR++; 
            break;
        case VBDZ: val->VBDZ++; 
            break;
        case VBG: val->VBG++; 
            break;
        case VBI: val->VBI++; 
            break;
        case VBM: val->VBM++; 
            break;
        case VBN: val->VBN++; 
            break;
        case VBR: val->VBR++; 
            break;
        case VBZ: val->VBZ++; 
            break;
        case VD0: val->VD0++; 
            break;
        case VDD: val->VDD++; 
            break;
        case VDG: val->VDG++; 
            break;
        case VDI: val->VDI++; 
            break;
        case VDN: val->VDN++; 
            break;
        case VDZ: val->VDZ++; 
            break;
        case VH0: val->VH0++; 
            break;
        case VHD: val->VHD++; 
            break;
        case VHG: val->VHG++; 
            break;
        case VHI: val->VHI++; 
            break;
        case VHN: val->VHN++; 
            break;
        case VHZ: val->VHZ++; 
            break;
        case VM: val->VM++; 
            break;
        case VMK: val->VMK++; 
            break;
        case VV0: val->VV0++; 
            break;
        case VVD: val->VVD++; 
            break;
        case VVG: val->VVG++; 
            break;
        case VVGK: val->VVGK++; 
            break;
        case VVI: val->VVI++; 
            break;
        case VVN: val->VVN++; 
            break;
        case VVNK: val->VVNK++; 
            break;
        case VVZ: val->VVZ++; 
            break;
        case XX: val->XX++; 
            break;
        case ZZ1: val->ZZ1++; 
            break;
        case ZZ2: val->ZZ2++; 
            break;
    }
}
unsigned long hash(char *tag)
{
    unsigned long hash = 5381;
    int c;
    
    while ((c = *tag++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    
    return hash;
}

void printMap(map_t mymap, char* name){
  struct tagset *finalval = malloc (sizeof (struct tagset));
   if(hashmap_get(mymap, name, (void **)&finalval) == MAP_OK)
    printf("Key: %s\nValues: APPGE=%d\tZZ1=%d\tZZ2=%d\n", name, finalval->APPGE, finalval->ZZ1, finalval->ZZ2);

}
          

