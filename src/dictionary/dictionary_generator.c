#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "../tagger/tags.h"
#include "dictionary_generator.h"
#include "../lib/hashmap.h"

void shorten_tag_struct(map_t map);
void get_highest_frequency(tagscount_t* tags, *int hash);

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

void shorten_tag_struct(map_t map){
    PFany p;
    any_t a;
    hashmap_iterate(map, p, a);
    
    int i;
    
    /* Cast the hashmap */
    hashmap_map* m = (hashmap_map*) map;
    
    /* On empty hashmap, return immediately */
    if (hashmap_length(m) <= 0)
        return MAP_MISSING;
    
    /* Linear probing */
    for(i = 0; i< m->table_size; i++)
        if(m->data[i].in_use != 0) {
            int highest = malloc(sizeof(int));
            char* key = m->data[i].key;
            
            get_highest_frequency((tagscount_t)&m->data[i].data, &highest);
            
            free(m->data[i].data);
            hashmap_remove(map, m->data[i].key);
            
            hashmap_put(map, key, highest);
            
        }
    
    
}

void get_highest_frequency(tagscount_t* tags, *int hash){
    
    int highest = -1;
    
    if(tags->APPGE > highest) highest = tags->APPGE;
    if(tags->AT > highest) highest = tags->AT;
    if(tags->AT1 > highest) highest = tags->AT1;
    if(tags->BCL > highest) highest = tags->BCL;
    if(tags->CC > highest) highest = tags->CC;
    if(tags->CCB > highest) highest = tags->CCB;
    if(tags->CS > highest) highest = tags->CS;
    if(tags->CSA > highest) highest = tags->CSA;
    if(tags->CSN > highest) highest = tags->CSN;
    if(tags->CST > highest) highest = tags->CST;
    if(tags->CSW > highest) highest = tags->CSW;
    if(tags->DA > highest) highest = tags->DA;
    if(tags->DA1 > highest) highest = tags->DA1;
    if(tags->DA2 > highest) highest = tags->DA2;
    if(tags->DAR > highest) highest = tags->DAR;
    if(tags->DAT > highest) highest = tags->DAT;
    if(tags->DB > highest) highest = tags->DB;
    if(tags->DB2 > highest) highest = tags->DB2;
    if(tags->DD > highest) highest = tags->DD;
    if(tags->DD1 > highest) highest = tags->DD1;
    if(tags->DD2 > highest) highest = tags->DD2;
    if(tags->DDQ > highest) highest = tags->DDQ;
    if(tags->DDQGE > highest) highest = tags->DDQGE;
    if(tags->DDQV > highest) highest = tags->DDQV;
    if(tags->EX > highest) highest = tags->EX;
    if(tags->FO > highest) highest = tags->FO;
    if(tags->FU > highest) highest = tags->FU;
    if(tags->FW > highest) highest = tags->FW;
    if(tags->GE > highest) highest = tags->GE;
    if(tags->IF > highest) highest = tags->IF;
    if(tags->II > highest) highest = tags->II;
    if(tags->IO > highest) highest = tags->IO;
    if(tags->IW > highest) highest = tags->IW;
    if(tags->JJ > highest) highest = tags->JJ;
    if(tags->JJR > highest) highest = tags->JJR;
    if(tags->JJT > highest) highest = tags->JJT;
    if(tags->JK > highest) highest = tags->JK;
    if(tags->MC > highest) highest = tags->MC;
    if(tags->MC1 > highest) highest = tags->MC1;
    if(tags->MC2 > highest) highest = tags->MC2;
    if(tags->MCGE > highest) highest = tags->MCGE;
    if(tags->MCMC > highest) highest = tags->MCMC;
    if(tags->MD > highest) highest = tags->MD;
    if(tags->MF > highest) highest = tags->MF;
    if(tags->ND1 > highest) highest = tags->ND1;
    if(tags->NN > highest) highest = tags->NN;
    if(tags->NN1 > highest) highest = tags->NN1;
    if(tags->NN2 > highest) highest = tags->NN2;
    if(tags->NNA > highest) highest = tags->NNA;
    if(tags->NNB > highest) highest = tags->NNB;
    if(tags->NNL1 > highest) highest = tags->NNL1;
    if(tags->NNL2 > highest) highest = tags->NNL2;
    if(tags->NNO > highest) highest = tags->NNO;
    if(tags->NNO2 > highest) highest = tags->NNO2;
    if(tags->NNT1 > highest) highest = tags->NNT1;
    if(tags->NNT2 > highest) highest = tags->NNT2;
    if(tags->NNU > highest) highest = tags->NNU;
    if(tags->NNU1 > highest) highest = tags->NNU1;
    if(tags->NNU2 > highest) highest = tags->NNU2;
    if(tags->NP > highest) highest = tags->NP;
    if(tags->NP1 > highest) highest = tags->NP1;
    if(tags->NP2 > highest) highest = tags->NP2;
    if(tags->NPD1 > highest) highest = tags->NPD1;
    if(tags->NPD2 > highest) highest = tags->NPD2;
    if(tags->NPM1 > highest) highest = tags->NPM1;
    if(tags->NPM2 > highest) highest = tags->NPM2;
    if(tags->PN > highest) highest = tags->PN;
    if(tags->PN1 > highest) highest = tags->PN1;
    if(tags->PNQO > highest) highest = tags->PNQO;
    if(tags->PNQS > highest) highest = tags->PNQS;
    if(tags->PNQV > highest) highest = tags->PNQV;
    if(tags->PNX1 > highest) highest = tags->PNX1;
    if(tags->PPGE > highest) highest = tags->PPGE;
    if(tags->PPH1 > highest) highest = tags->PPH1;
    if(tags->PPHO1 > highest) highest = tags->PPHO1;
    if(tags->PPHO2 > highest) highest = tags->PPHO2;
    if(tags->PPHS1 > highest) highest = tags->PPHS1;
    if(tags->PPHS2 > highest) highest = tags->PPHS2;
    if(tags->PPIO1 > highest) highest = tags->PPIO1;
    if(tags->PPIO2 > highest) highest = tags->PPIO2;
    if(tags->PPIS1 > highest) highest = tags->PPIS1;
    if(tags->PPIS2 > highest) highest = tags->PPIS2;
    if(tags->PPX1 > highest) highest = tags->PPX1;
    if(tags->PPX2 > highest) highest = tags->PPX2;
    if(tags->PPY > highest) highest = tags->PPY;
    if(tags->RA > highest) highest = tags->RA;
    if(tags->REX > highest) highest = tags->REX;
    if(tags->RG > highest) highest = tags->RG;
    if(tags->RGQ > highest) highest = tags->RGQ;
    if(tags->RGQV > highest) highest = tags->RGQV;
    if(tags->RGR > highest) highest = tags->RGR;
    if(tags->RGT > highest) highest = tags->RGT;
    if(tags->RL > highest) highest = tags->RL;
    if(tags->RP > highest) highest = tags->RP;
    if(tags->RPK > highest) highest = tags->RPK;
    if(tags->RR > highest) highest = tags->RR;
    if(tags->RRQ > highest) highest = tags->RRQ;
    if(tags->RRQV > highest) highest = tags->RRQV;
    if(tags->RRR > highest) highest = tags->RRR;
    if(tags->RRT > highest) highest = tags->RRT;
    if(tags->RT > highest) highest = tags->RT;
    if(tags->TO > highest) highest = tags->TO;
    if(tags->UH > highest) highest = tags->UH;
    if(tags->VB0 > highest) highest = tags->VB0;
    if(tags->VBDR > highest) highest = tags->VBDR;
    if(tags->VBDZ > highest) highest = tags->VBDZ;
    if(tags->VBG > highest) highest = tags->VBG;
    if(tags->VBI > highest) highest = tags->VBI;
    if(tags->VBM > highest) highest = tags->VBM;
    if(tags->VBN > highest) highest = tags->VBN;
    if(tags->VBR > highest) highest = tags->VBR;
    if(tags->VBZ > highest) highest = tags->VBZ;
    if(tags->VD0 > highest) highest = tags->VD0;
    if(tags->VDD > highest) highest = tags->VDD;
    if(tags->VDG > highest) highest = tags->VDG;
    if(tags->VDI > highest) highest = tags->VDI;
    if(tags->VDN > highest) highest = tags->VDN;
    if(tags->VDZ > highest) highest = tags->VDZ;
    if(tags->VH0 > highest) highest = tags->VH0;
    if(tags->VHD > highest) highest = tags->VHD;
    if(tags->VHG > highest) highest = tags->VHG;
    if(tags->VHI > highest) highest = tags->VHI;
    if(tags->VHN > highest) highest = tags->VHN;
    if(tags->VHZ > highest) highest = tags->VHZ;
    if(tags->VM > highest) highest = tags->VM;
    if(tags->VMK > highest) highest = tags->VMK;
    if(tags->VV0 > highest) highest = tags->VV0;
    if(tags->VVD > highest) highest = tags->VVD;
    if(tags->VVG > highest) highest = tags->VVG;
    if(tags->VVGK > highest) highest = tags->VVGK;
    if(tags->VVI > highest) highest = tags->VVI;
    if(tags->VVN > highest) highest = tags->VVN;
    if(tags->VVNK > highest) highest = tags->VVNK;
    if(tags->VVZ > highest) highest = tags->VVZ;
    if(tags->XX > highest) highest = tags->XX;
    if(tags->ZZ1 > highest) highest = tags->ZZ1;
    if(tags->ZZ2 > highest) highest = tags->ZZ2;
    
    *hash = highest;
}



