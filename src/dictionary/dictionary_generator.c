#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "../tagger/tags.h"
#include "dictionary_generator.h"
#include "../lib/hashmap.h"

map_t generate_dictionary(char *filepath)
{
    //Used for file reading
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    //Used for various placeholders
    int index;
    int error;
    map_t mymap;
    char key_string[KEY_MAX_LENGTH];
    data_struct_t* value;
    char* val;
    
    //Instantiate a new hashmap
    mymap = hashmap_new();

    //Use these variables to parse and prepare words for tagset updating.
    fp = fopen(filepath, "r");
    char *saveptr;
    char *word;
    char *tag;
    tagcounts_t tags;
    
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    //Continue reading until the end of the file
    while ((read = getline(&line, &len, fp)) != -1) {
      
        word = strtok_r(line, " ", &saveptr);
        tag = strtok_r(NULL, " ", &saveptr);
        if(word[read-1] == '\n') word[read-1] = '\0';
        if(tag[read-1] == '\n') tag[read-1] = '\0';
        
         char* newword = malloc(strlen(word) + 1);
         char* newtag = malloc(strlen(tag) + 1);
        
        strcpy(newword, word);
        strcpy(newtag, tag);

        //See if the word is already used as a key value.
        //If it is not, we allocate a new structure to store as the keyword's value
        //and call updateTags, this will set the initial tag to 1.
        //Finally, we put this keyword and value into the hashmap.
        
        if(hashmap_get(mymap, word, (void **)&tags) == MAP_MISSING){
            struct tagcounts_t *newtags = malloc (sizeof (struct tagcounts_t));
            memset(newtags, 0, sizeof(struct tagcounts_t));
            updateTags(newword, newtags, newtag);
            hashmap_put(mymap, newword, newtags);
        }
        
        //If the word already exists, get the current tagset values of the keyword.
        //Update it's contents to reflect the new tag (increment the correct value)
        //and finally remove the old version from the map and put the new version in.
        else{
            struct tagcounts_t *curtags = malloc (sizeof (struct tagcounts_t));
            hashmap_get(mymap, newword, (void **)&curtags);
            updateTags(newword,curtags, newtag);
            hashmap_remove(mymap, newword);
            hashmap_put(mymap, newword, curtags);
        }

    }
    //return the finished map
    return mymap;
}
void updateTags(char* word, struct tagcounts_t *val, char* tag){
    
    //Hash the tag value to save time in the future
    int hash_value = tag_to_hash(tag);
    
    /*auto generated switch statement*/
    //Switch statement is passed the hashed tag value. The corresponding cases
    //are enumerated types described in ../tagger/tags.h
    
    switch(hash_value){
        case APPGE: val->APPGE+=1; break;
        case AT: val->AT+=1; break;
        case AT1: val->AT1+=1; break;
        case BCL: val->BCL+=1; break;
        case CC: val->CC+=1; break;
        case CCB: val->CCB+=1; break;
        case CS: val->CS+=1; break;
        case CSA: val->CSA+=1; break;
        case CSN: val->CSN+=1; break;
        case CST: val->CST+=1; break;
        case CSW: val->CSW+=1; break;
        case DA: val->DA+=1; break;
        case DA1: val->DA1+=1; break;
        case DA2: val->DA2+=1; break;
        case DAR: val->DAR+=1; break;
        case DAT: val->DAT+=1; break;
        case DB: val->DB+=1; break;
        case DB2: val->DB2+=1; break;
        case DD: val->DD+=1; break;
        case DD1: val->DD1+=1; break;
        case DD2: val->DD2+=1; break;
        case DDQ: val->DDQ+=1; break;
        case DDQGE: val->DDQGE+=1; break;
        case DDQV: val->DDQV+=1; break;
        case EX: val->EX+=1; break;
        case FO: val->FO+=1; break;
        case FU: val->FU+=1; break;
        case FW: val->FW+=1; break;
        case GE: val->GE+=1; break;
        case IF: val->IF+=1; break;
        case II: val->II+=1; break;
        case IO: val->IO+=1; break;
        case IW: val->IW+=1; break;
        case JJ: val->JJ+=1; break;
        case JJR: val->JJR+=1; break;
        case JJT: val->JJT+=1; break;
        case JK: val->JK+=1; break;
        case MC: val->MC+=1; break;
        case MC1: val->MC1+=1; break;
        case MC2: val->MC2+=1; break;
        case MCGE: val->MCGE+=1; break;
        case MCMC: val->MCMC+=1; break;
        case MD: val->MD+=1; break;
        case MF: val->MF+=1; break;
        case ND1: val->ND1+=1; break;
        case NN: val->NN+=1; break;
        case NN1: val->NN1+=1; break;
        case NN2: val->NN2+=1; break;
        case NNA: val->NNA+=1; break;
        case NNB: val->NNB+=1; break;
        case NNL1: val->NNL1+=1; break;
        case NNL2: val->NNL2+=1; break;
        case NNO: val->NNO+=1; break;
        case NNO2: val->NNO2+=1; break;
        case NNT1: val->NNT1+=1; break;
        case NNT2: val->NNT2+=1; break;
        case NNU: val->NNU+=1; break;
        case NNU1: val->NNU1+=1; break;
        case NNU2: val->NNU2+=1; break;
        case NP: val->NP+=1; break;
        case NP1: val->NP1+=1; break;
        case NP2: val->NP2+=1; break;
        case NPD1: val->NPD1+=1; break;
        case NPD2: val->NPD2+=1; break;
        case NPM1: val->NPM1+=1; break;
        case NPM2: val->NPM2+=1; break;
        case PN: val->PN+=1; break;
        case PN1: val->PN1+=1; break;
        case PNQO: val->PNQO+=1; break;
        case PNQS: val->PNQS+=1; break;
        case PNQV: val->PNQV+=1; break;
        case PNX1: val->PNX1+=1; break;
        case PPGE: val->PPGE+=1; break;
        case PPH1: val->PPH1+=1; break;
        case PPHO1: val->PPHO1+=1; break;
        case PPHO2: val->PPHO2+=1; break;
        case PPHS1: val->PPHS1+=1; break;
        case PPHS2: val->PPHS2+=1; break;
        case PPIO1: val->PPIO1+=1; break;
        case PPIO2: val->PPIO2+=1; break;
        case PPIS1: val->PPIS1+=1; break;
        case PPIS2: val->PPIS2+=1; break;
        case PPX1: val->PPX1+=1; break;
        case PPX2: val->PPX2+=1; break;
        case PPY: val->PPY+=1; break;
        case RA: val->RA+=1; break;
        case REX: val->REX+=1; break;
        case RG: val->RG+=1; break;
        case RGQ: val->RGQ+=1; break;
        case RGQV: val->RGQV+=1; break;
        case RGR: val->RGR+=1; break;
        case RGT: val->RGT+=1; break;
        case RL: val->RL+=1; break;
        case RP: val->RP+=1; break;
        case RPK: val->RPK+=1; break;
        case RR: val->RR+=1; break;
        case RRQ: val->RRQ+=1; break;
        case RRQV: val->RRQV+=1; break;
        case RRR: val->RRR+=1; break;
        case RRT: val->RRT+=1; break;
        case RT: val->RT+=1; break;
        case TO: val->TO+=1; break;
        case UH: val->UH+=1; break;
        case VB0: val->VB0+=1; break;
        case VBDR: val->VBDR+=1; break;
        case VBDZ: val->VBDZ+=1; break;
        case VBG: val->VBG+=1; break;
        case VBI: val->VBI+=1; break;
        case VBM: val->VBM+=1; break;
        case VBN: val->VBN+=1; break;
        case VBR: val->VBR+=1; break;
        case VBZ: val->VBZ+=1; break;
        case VD0: val->VD0+=1; break;
        case VDD: val->VDD+=1; break;
        case VDG: val->VDG+=1; break;
        case VDI: val->VDI+=1; break;
        case VDN: val->VDN+=1; break;
        case VDZ: val->VDZ+=1; break;
        case VH0: val->VH0+=1; break;
        case VHD: val->VHD+=1; break;
        case VHG: val->VHG+=1; break;
        case VHI: val->VHI+=1; break;
        case VHN: val->VHN+=1; break;
        case VHZ: val->VHZ+=1; break;
        case VM: val->VM+=1; break;
        case VMK: val->VMK+=1; break;
        case VV0: val->VV0+=1; break;
        case VVD: val->VVD+=1; break;
        case VVG: val->VVG+=1; break;
        case VVGK: val->VVGK+=1; break;
        case VVI: val->VVI+=1; break;
        case VVN: val->VVN+=1; break;
        case VVNK: val->VVNK+=1; break;
        case VVZ: val->VVZ+=1; break;
        case XX: val->XX+=1; break;
        case ZZ1: val->ZZ1+=1; break;
        case ZZ2: val->ZZ2+=1; break;
        default: printf("Illegal input tag\n");
        /* punctuation not included because 
        these tags are known up front */
    }
}

//Simple helper method used to test certain inputs. Showed correct output for the corresponding text file
//used to test
void printMap(map_t mymap, char* name){
    struct tagcounts_t *finalval = malloc (sizeof (struct tagcounts_t));
    if(hashmap_get(mymap, name, (void **)&finalval) == MAP_OK)
        printf("Key: %s\nValues: APPGE=%d\tZZ1=%d\tZZ2=%d\n",
             name, finalval->APPGE, finalval->ZZ1, finalval->ZZ2);
}
          

