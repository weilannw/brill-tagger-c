#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "../tagger/tags.h"
#include "dictionary_generator.h"
#include "../lib/hashmap.h"

void shorten_tag_struct(map_t map);
void get_highest_frequency(tagcounts_t *tags, int *hash);

tagcounts_t frequency_count;
//call in generate dict = malloc (sizeof (struct tagcounts_t));
int most_common_tag;
 // call in generate dict= malloc (sizeof(int));


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
    
    //Placeholder values that aren't needed but are passed into the hashmaps function
    PFany p;
    any_t t;
    
    hashmap_iterate(mymap, p, t);
    
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
        case APPGE: val->APPGE+=1; frequency_count.APPGE+=1; break;
        case AT: val->AT+=1; frequency_count.AT+=1; break;
        case AT1: val->AT1+=1; frequency_count.AT1+=1; break;
        case BCL: val->BCL+=1; frequency_count.BCL+=1; break;
        case CC: val->CC+=1; frequency_count.CC+=1; break;
        case CCB: val->CCB+=1; frequency_count.CCB+=1; break;
        case CS: val->CS+=1; frequency_count.CS+=1; break;
        case CSA: val->CSA+=1; frequency_count.CSA+=1; break;
        case CSN: val->CSN+=1; frequency_count.CSN+=1; break;
        case CST: val->CST+=1; frequency_count.CST+=1; break;
        case CSW: val->CSW+=1; frequency_count.CSW+=1; break;
        case DA: val->DA+=1; frequency_count.DA+=1; break;
        case DA1: val->DA1+=1; frequency_count.DA1+=1; break;
        case DA2: val->DA2+=1; frequency_count.DA2+=1; break;
        case DAR: val->DAR+=1; frequency_count.DAR+=1; break;
        case DAT: val->DAT+=1; frequency_count.DAT+=1; break;
        case DB: val->DB+=1; frequency_count.DB+=1; break;
        case DB2: val->DB2+=1; frequency_count.DB2+=1; break;
        case DD: val->DD+=1; frequency_count.DD+=1; break;
        case DD1: val->DD1+=1; frequency_count.DD1+=1; break;
        case DD2: val->DD2+=1; frequency_count.DD2+=1; break;
        case DDQ: val->DDQ+=1; frequency_count.DDQ+=1; break;
        case DDQGE: val->DDQGE+=1; frequency_count.DDQGE+=1; break;
        case DDQV: val->DDQV+=1; frequency_count.DDQV+=1; break;
        case EX: val->EX+=1; frequency_count.EX+=1; break;
        case FO: val->FO+=1; frequency_count.FO+=1; break;
        case FU: val->FU+=1; frequency_count.FU+=1; break;
        case FW: val->FW+=1; frequency_count.FW+=1; break;
        case GE: val->GE+=1; frequency_count.GE+=1; break;
        case IF: val->IF+=1; frequency_count.IF+=1; break;
        case II: val->II+=1; frequency_count.II+=1; break;
        case IO: val->IO+=1; frequency_count.IO+=1; break;
        case IW: val->IW+=1; frequency_count.IW+=1; break;
        case JJ: val->JJ+=1; frequency_count.JJ+=1; break;
        case JJR: val->JJR+=1; frequency_count.JJR+=1; break;
        case JJT: val->JJT+=1; frequency_count.JJT+=1; break;
        case JK: val->JK+=1; frequency_count.JK+=1; break;
        case MC: val->MC+=1; frequency_count.MC+=1; break;
        case MC1: val->MC1+=1; frequency_count.MC1+=1; break;
        case MC2: val->MC2+=1; frequency_count.MC2+=1; break;
        case MCGE: val->MCGE+=1; frequency_count.MCGE+=1; break;
        case MCMC: val->MCMC+=1; frequency_count.MCMC+=1; break;
        case MD: val->MD+=1; frequency_count.MD+=1; break;
        case MF: val->MF+=1; frequency_count.MF+=1; break;
        case ND1: val->ND1+=1; frequency_count.ND1+=1; break;
        case NN: val->NN+=1; frequency_count.NN+=1; break;
        case NN1: val->NN1+=1; frequency_count.NN1+=1; break;
        case NN2: val->NN2+=1; frequency_count.NN2+=1; break;
        case NNA: val->NNA+=1; frequency_count.NNA+=1; break;
        case NNB: val->NNB+=1; frequency_count.NNB+=1; break;
        case NNL1: val->NNL1+=1; frequency_count.NNL1+=1; break;
        case NNL2: val->NNL2+=1; frequency_count.NNL2+=1; break;
        case NNO: val->NNO+=1; frequency_count.NNO+=1; break;
        case NNO2: val->NNO2+=1; frequency_count.NNO2+=1; break;
        case NNT1: val->NNT1+=1; frequency_count.NNT1+=1; break;
        case NNT2: val->NNT2+=1; frequency_count.NNT2+=1; break;
        case NNU: val->NNU+=1; frequency_count.NNU+=1; break;
        case NNU1: val->NNU1+=1; frequency_count.NNU1+=1; break;
        case NNU2: val->NNU2+=1; frequency_count.NNU2+=1; break;
        case NP: val->NP+=1; frequency_count.NP+=1; break;
        case NP1: val->NP1+=1; frequency_count.NP1+=1; break;
        case NP2: val->NP2+=1; frequency_count.NP2+=1; break;
        case NPD1: val->NPD1+=1; frequency_count.NPD1+=1; break;
        case NPD2: val->NPD2+=1; frequency_count.NPD2+=1; break;
        case NPM1: val->NPM1+=1; frequency_count.NPM1+=1; break;
        case NPM2: val->NPM2+=1; frequency_count.NPM2+=1; break;
        case PN: val->PN+=1; frequency_count.PN+=1; break;
        case PN1: val->PN1+=1; frequency_count.PN1+=1; break;
        case PNQO: val->PNQO+=1; frequency_count.PNQO+=1; break;
        case PNQS: val->PNQS+=1; frequency_count.PNQS+=1; break;
        case PNQV: val->PNQV+=1; frequency_count.PNQV+=1; break;
        case PNX1: val->PNX1+=1; frequency_count.PNX1+=1; break;
        case PPGE: val->PPGE+=1; frequency_count.PPGE+=1; break;
        case PPH1: val->PPH1+=1; frequency_count.PPH1+=1; break;
        case PPHO1: val->PPHO1+=1; frequency_count.PPHO1+=1; break;
        case PPHO2: val->PPHO2+=1; frequency_count.PPHO2+=1; break;
        case PPHS1: val->PPHS1+=1; frequency_count.PPHS1+=1; break;
        case PPHS2: val->PPHS2+=1; frequency_count.PPHS2+=1; break;
        case PPIO1: val->PPIO1+=1; frequency_count.PPIO1+=1; break;
        case PPIO2: val->PPIO2+=1; frequency_count.PPIO2+=1; break;
        case PPIS1: val->PPIS1+=1; frequency_count.PPIS1+=1; break;
        case PPIS2: val->PPIS2+=1; frequency_count.PPIS2+=1; break;
        case PPX1: val->PPX1+=1; frequency_count.PPX1+=1; break;
        case PPX2: val->PPX2+=1; frequency_count.PPX2+=1; break;
        case PPY: val->PPY+=1; frequency_count.PPY+=1; break;
        case RA: val->RA+=1; frequency_count.RA+=1; break;
        case REX: val->REX+=1; frequency_count.REX+=1; break;
        case RG: val->RG+=1; frequency_count.RG+=1; break;
        case RGQ: val->RGQ+=1; frequency_count.RGQ+=1; break;
        case RGQV: val->RGQV+=1; frequency_count.RGQV+=1; break;
        case RGR: val->RGR+=1; frequency_count.RGR+=1; break;
        case RGT: val->RGT+=1; frequency_count.RGT+=1; break;
        case RL: val->RL+=1; frequency_count.RL+=1; break;
        case RP: val->RP+=1; frequency_count.RP+=1; break;
        case RPK: val->RPK+=1; frequency_count.RPK+=1; break;
        case RR: val->RR+=1; frequency_count.RR+=1; break;
        case RRQ: val->RRQ+=1; frequency_count.RRQ+=1; break;
        case RRQV: val->RRQV+=1; frequency_count.RRQV+=1; break;
        case RRR: val->RRR+=1; frequency_count.RRR+=1; break;
        case RRT: val->RRT+=1; frequency_count.RRT+=1; break;
        case RT: val->RT+=1; frequency_count.RT+=1; break;
        case TO: val->TO+=1; frequency_count.TO+=1; break;
        case UH: val->UH+=1; frequency_count.UH+=1; break;
        case VB0: val->VB0+=1; frequency_count.VB0+=1; break;
        case VBDR: val->VBDR+=1; frequency_count.VBDR+=1; break;
        case VBDZ: val->VBDZ+=1; frequency_count.VBDZ+=1; break;
        case VBG: val->VBG+=1; frequency_count.VBG+=1; break;
        case VBI: val->VBI+=1; frequency_count.VBI+=1; break;
        case VBM: val->VBM+=1; frequency_count.VBM+=1; break;
        case VBN: val->VBN+=1; frequency_count.VBN+=1; break;
        case VBR: val->VBR+=1; frequency_count.VBR+=1; break;
        case VBZ: val->VBZ+=1; frequency_count.VBZ+=1; break;
        case VD0: val->VD0+=1; frequency_count.VD0+=1; break;
        case VDD: val->VDD+=1; frequency_count.VDD+=1; break;
        case VDG: val->VDG+=1; frequency_count.VDG+=1; break;
        case VDI: val->VDI+=1; frequency_count.VDI+=1; break;
        case VDN: val->VDN+=1; frequency_count.VDN+=1; break;
        case VDZ: val->VDZ+=1; frequency_count.VDZ+=1; break;
        case VH0: val->VH0+=1; frequency_count.VH0+=1; break;
        case VHD: val->VHD+=1; frequency_count.VHD+=1; break;
        case VHG: val->VHG+=1; frequency_count.VHG+=1; break;
        case VHI: val->VHI+=1; frequency_count.VHI+=1; break;
        case VHN: val->VHN+=1; frequency_count.VHN+=1; break;
        case VHZ: val->VHZ+=1; frequency_count.VHZ+=1; break;
        case VM: val->VM+=1; frequency_count.VM+=1; break;
        case VMK: val->VMK+=1; frequency_count.VMK+=1; break;
        case VV0: val->VV0+=1; frequency_count.VV0+=1; break;
        case VVD: val->VVD+=1; frequency_count.VVD+=1; break;
        case VVG: val->VVG+=1; frequency_count.VVG+=1; break;
        case VVGK: val->VVGK+=1; frequency_count.VVGK+=1; break;
        case VVI: val->VVI+=1; frequency_count.VVI+=1; break;
        case VVN: val->VVN+=1; frequency_count.VVN+=1; break;
        case VVNK: val->VVNK+=1; frequency_count.VVNK+=1; break;
        case VVZ: val->VVZ+=1; frequency_count.VVZ+=1; break;
        case XX: val->XX+=1; frequency_count.XX+=1; break;
        case ZZ1: val->ZZ1+=1; frequency_count.ZZ1+=1; break;
        case ZZ2: val->ZZ2+=1; frequency_count.ZZ2+=1; break;
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


//This method takes in a tag structure along with an allocated integer.
//The method stores the most frequent value's hash into the address of the passed in int pointer
void get_highest_frequency(tagcounts_t* tags, int *hash){
    int highest = -1;
    
    if(tags->APPGE > highest) highest = APPGE;
    if(tags->AT > highest) highest = AT;
    if(tags->AT1 > highest) highest = AT1;
    if(tags->BCL > highest) highest = BCL;
    if(tags->CC > highest) highest = CC;
    if(tags->CCB > highest) highest = CCB;
    if(tags->CS > highest) highest = CS;
    if(tags->CSA > highest) highest = CSA;
    if(tags->CSN > highest) highest = CSN;
    if(tags->CST > highest) highest = CST;
    if(tags->CSW > highest) highest = CSW;
    if(tags->DA > highest) highest = DA;
    if(tags->DA1 > highest) highest = DA1;
    if(tags->DA2 > highest) highest = DA2;
    if(tags->DAR > highest) highest = DAR;
    if(tags->DAT > highest) highest = DAT;
    if(tags->DB > highest) highest = DB;
    if(tags->DB2 > highest) highest = DB2;
    if(tags->DD > highest) highest = DD;
    if(tags->DD1 > highest) highest = DD1;
    if(tags->DD2 > highest) highest = DD2;
    if(tags->DDQ > highest) highest = DDQ;
    if(tags->DDQGE > highest) highest = DDQGE;
    if(tags->DDQV > highest) highest = DDQV;
    if(tags->EX > highest) highest = EX;
    if(tags->FO > highest) highest = FO;
    if(tags->FU > highest) highest = FU;
    if(tags->FW > highest) highest = FW;
    if(tags->GE > highest) highest = GE;
    if(tags->IF > highest) highest = IF;
    if(tags->II > highest) highest = II;
    if(tags->IO > highest) highest = IO;
    if(tags->IW > highest) highest = IW;
    if(tags->JJ > highest) highest = JJ;
    if(tags->JJR > highest) highest = JJR;
    if(tags->JJT > highest) highest = JJT;
    if(tags->JK > highest) highest = JK;
    if(tags->MC > highest) highest = MC;
    if(tags->MC1 > highest) highest = MC1;
    if(tags->MC2 > highest) highest = MC2;
    if(tags->MCGE > highest) highest = MCGE;
    if(tags->MCMC > highest) highest = MCMC;
    if(tags->MD > highest) highest = MD;
    if(tags->MF > highest) highest = MF;
    if(tags->ND1 > highest) highest = ND1;
    if(tags->NN > highest) highest = NN;
    if(tags->NN1 > highest) highest = NN1;
    if(tags->NN2 > highest) highest = NN2;
    if(tags->NNA > highest) highest = NNA;
    if(tags->NNB > highest) highest = NNB;
    if(tags->NNL1 > highest) highest = NNL1;
    if(tags->NNL2 > highest) highest = NNL2;
    if(tags->NNO > highest) highest = NNO;
    if(tags->NNO2 > highest) highest = NNO2;
    if(tags->NNT1 > highest) highest = NNT1;
    if(tags->NNT2 > highest) highest = NNT2;
    if(tags->NNU > highest) highest = NNU;
    if(tags->NNU1 > highest) highest = NNU1;
    if(tags->NNU2 > highest) highest = NNU2;
    if(tags->NP > highest) highest = NP;
    if(tags->NP1 > highest) highest = NP1;
    if(tags->NP2 > highest) highest = NP2;
    if(tags->NPD1 > highest) highest = NPD1;
    if(tags->NPD2 > highest) highest = NPD2;
    if(tags->NPM1 > highest) highest = NPM1;
    if(tags->NPM2 > highest) highest = NPM2;
    if(tags->PN > highest) highest = PN;
    if(tags->PN1 > highest) highest = PN1;
    if(tags->PNQO > highest) highest = PNQO;
    if(tags->PNQS > highest) highest = PNQS;
    if(tags->PNQV > highest) highest = PNQV;
    if(tags->PNX1 > highest) highest = PNX1;
    if(tags->PPGE > highest) highest = PPGE;
    if(tags->PPH1 > highest) highest = PPH1;
    if(tags->PPHO1 > highest) highest = PPHO1;
    if(tags->PPHO2 > highest) highest = PPHO2;
    if(tags->PPHS1 > highest) highest = PPHS1;
    if(tags->PPHS2 > highest) highest = PPHS2;
    if(tags->PPIO1 > highest) highest = PPIO1;
    if(tags->PPIO2 > highest) highest = PPIO2;
    if(tags->PPIS1 > highest) highest = PPIS1;
    if(tags->PPIS2 > highest) highest = PPIS2;
    if(tags->PPX1 > highest) highest = PPX1;
    if(tags->PPX2 > highest) highest = PPX2;
    if(tags->PPY > highest) highest = PPY;
    if(tags->RA > highest) highest = RA;
    if(tags->REX > highest) highest = REX;
    if(tags->RG > highest) highest = RG;
    if(tags->RGQ > highest) highest = RGQ;
    if(tags->RGQV > highest) highest = RGQV;
    if(tags->RGR > highest) highest = RGR;
    if(tags->RGT > highest) highest = RGT;
    if(tags->RL > highest) highest = RL;
    if(tags->RP > highest) highest = RP;
    if(tags->RPK > highest) highest = RPK;
    if(tags->RR > highest) highest = RR;
    if(tags->RRQ > highest) highest = RRQ;
    if(tags->RRQV > highest) highest = RRQV;
    if(tags->RRR > highest) highest = RRR;
    if(tags->RRT > highest) highest = RRT;
    if(tags->RT > highest) highest = RT;
    if(tags->TO > highest) highest = TO;
    if(tags->UH > highest) highest = UH;
    if(tags->VB0 > highest) highest = VB0;
    if(tags->VBDR > highest) highest = VBDR;
    if(tags->VBDZ > highest) highest = VBDZ;
    if(tags->VBG > highest) highest = VBG;
    if(tags->VBI > highest) highest = VBI;
    if(tags->VBM > highest) highest = VBM;
    if(tags->VBN > highest) highest = VBN;
    if(tags->VBR > highest) highest = VBR;
    if(tags->VBZ > highest) highest = VBZ;
    if(tags->VD0 > highest) highest = VD0;
    if(tags->VDD > highest) highest = VDD;
    if(tags->VDG > highest) highest = VDG;
    if(tags->VDI > highest) highest = VDI;
    if(tags->VDN > highest) highest = VDN;
    if(tags->VDZ > highest) highest = VDZ;
    if(tags->VH0 > highest) highest = VH0;
    if(tags->VHD > highest) highest = VHD;
    if(tags->VHG > highest) highest = VHG;
    if(tags->VHI > highest) highest = VHI;
    if(tags->VHN > highest) highest = VHN;
    if(tags->VHZ > highest) highest = VHZ;
    if(tags->VM > highest) highest = VM;
    if(tags->VMK > highest) highest = VMK;
    if(tags->VV0 > highest) highest = VV0;
    if(tags->VVD > highest) highest = VVD;
    if(tags->VVG > highest) highest = VVG;
    if(tags->VVGK > highest) highest = VVGK;
    if(tags->VVI > highest) highest = VVI;
    if(tags->VVN > highest) highest = VVN;
    if(tags->VVNK > highest) highest = VVNK;
    if(tags->VVZ > highest) highest = VVZ;
    if(tags->XX > highest) highest = XX;
    if(tags->ZZ1 > highest) highest = ZZ1;
    if(tags->ZZ2 > highest) highest = ZZ2;
    
    *hash = highest;
}



