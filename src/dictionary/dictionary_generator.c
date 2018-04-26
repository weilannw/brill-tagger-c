#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "../tagger/tags.h"
#include "dictionary_generator.h"
#include "../io/corpus_io.h"
#include "../lib/hashmap.h"
#include "dictionary_reduce.h"

void shorten_tag_struct(struct hashmap map);
HASHMAP_FUNCS_CREATE(tag, const char, struct tagcounts_t);
HASHMAP_FUNCS_CREATE(new, const char, int);
tagcounts_t frequency_count;
//call in generate dict = malloc (sizeof (struct tagcounts_t));
int most_common_tag;
 // call in generate dict= malloc (sizeof(int));


struct hashmap generate_dictionary(corpus_t corpus){

    FILE* fp = fopen("frequencies.txt", "r");
    if(fp == NULL){
    
        //Instantiate a new hashmap
        struct tagcounts_t *data;
        struct hashmap map;

        hashmap_init(&map, hashmap_hash_string, hashmap_compare_string, 0);
    
        for(int i = 0; i < corpus.num_lines; i++){

            if(!corpus.info[i].ignore_flag){
            data = tag_hashmap_get(&map, corpus.words[i]);
            
           
                if(data == NULL){
                    struct tagcounts_t *newtags = malloc (sizeof (struct tagcounts_t));
                    memset(newtags, 0, sizeof(struct tagcounts_t));
                    update_tags(corpus.words[i], newtags, corpus.human_tags[i]);
                    tag_hashmap_put(&map, corpus.words[i], newtags);
                }
            
                else{
                    update_tags(corpus.words[i], data, corpus.human_tags[i]);
                }
            }
        }
        return reduce_map(map);

    }
    
    else{
        struct hashmap newmap;
        hashmap_init(&newmap, hashmap_hash_string, hashmap_compare_string, 0);
        
        char* saveptr;
        char* line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, fp)) != -1) {
            char *saveptr;
            char* word = strtok_r(line, "\t", &saveptr);
            char* tag = strtok_r(NULL, " ", &saveptr);
            if(word[strlen(word)-1] == '\n') word[strlen(word)-1] = '\0';
            if(tag[strlen(tag)-1] == '\n') tag[strlen(tag)-1] = '\0';
            
            int* highest = (int *)malloc(sizeof(int));
            *highest = tag_to_hash(tag);
            
            char* key = (char*)malloc(strlen(word+1) * sizeof(char));
            strncpy(key, word, strlen(word));
            printf("Value of key: %s\n", key);
            new_hashmap_put(&newmap, key, highest);
        }
        
        return newmap;
        
    }
   


}
void update_tags(char* word, struct tagcounts_t *val, int tag){
    
    //Hash the tag value to save time in the future
    int hash_value = tag;
    
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
        //default: printf("Illegal input tag\n");
            /* punctuation not included because
             these tags are known up front */
    }
}



//This method takes in a tag structure along with an allocated integer.
//The method stores the most frequent value's hash into the address of the passed in int pointer
int get_highest_frequency(tagcounts_t* tags){
    int highest = -1;
    int temp = -1;
    
    
    if(tags->APPGE > temp){temp = tags->APPGE; highest = APPGE;}
    if(tags->AT > temp){temp = tags->AT; highest = AT;}
    if(tags->AT1 > temp){temp = tags->AT1; highest = AT1;}
    if(tags->BCL > temp){temp = tags->BCL; highest = BCL;}
    if(tags->CC > temp){temp = tags->CC; highest = CC;}
    if(tags->CCB > temp){temp = tags->CCB; highest = CCB;}
    if(tags->CS > temp){temp = tags->CS; highest = CS;}
    if(tags->CSA > temp){temp = tags->CSA; highest = CSA;}
    if(tags->CSN > temp){temp = tags->CSN; highest = CSN;}
    if(tags->CST > temp){temp = tags->CST; highest = CST;}
    if(tags->CSW > temp){temp = tags->CSW; highest = CSW;}
    if(tags->DA > temp){temp = tags->DA; highest = DA;}
    if(tags->DA1 > temp){temp = tags->DA1; highest = DA1;}
    if(tags->DA2 > temp){temp = tags->DA2; highest = DA2;}
    if(tags->DAR > temp){temp = tags->DAR; highest = DAR;}
    if(tags->DAT > temp){temp = tags->DAT; highest = DAT;}
    if(tags->DB > temp){temp = tags->DB; highest = DB;}
    if(tags->DB2 > temp){temp = tags->DB2; highest = DB2;}
    if(tags->DD > temp){temp = tags->DD; highest = DD;}
    if(tags->DD1 > temp){temp = tags->DD1; highest = DD1;}
    if(tags->DD2 > temp){temp = tags->DD2; highest = DD2;}
    if(tags->DDQ > temp){temp = tags->DDQ; highest = DDQ;}
    if(tags->DDQGE > temp){temp = tags->DDQGE; highest = DDQGE;}
    if(tags->DDQV > temp){temp = tags->DDQV; highest = DDQV;}
    if(tags->EX > temp){temp = tags->EX; highest = EX;}
    if(tags->FO > temp){temp = tags->FO; highest = FO;}
    if(tags->FU > temp){temp = tags->FU; highest = FU;}
    if(tags->FW > temp){temp = tags->FW; highest = FW;}
    if(tags->GE > temp){temp = tags->GE; highest = GE;}
    if(tags->IF > temp){temp = tags->IF; highest = IF;}
    if(tags->II > temp){temp = tags->II; highest = II;}
    if(tags->IO > temp){temp = tags->IO; highest = IO;}
    if(tags->IW > temp){temp = tags->IW; highest = IW;}
    if(tags->JJ > temp){temp = tags->JJ; highest = JJ;}
    if(tags->JJR > temp){temp = tags->JJR; highest = JJR;}
    if(tags->JJT > temp){temp = tags->JJT; highest = JJT;}
    if(tags->JK > temp){temp = tags->JK; highest = JK;}
    if(tags->MC > temp){temp = tags->MC; highest = MC;}
    if(tags->MC1 > temp){temp = tags->MC1; highest = MC1;}
    if(tags->MC2 > temp){temp = tags->MC2; highest = MC2;}
    if(tags->MCGE > temp){temp = tags->MCGE; highest = MCGE;}
    if(tags->MCMC > temp){temp = tags->MCMC; highest = MCMC;}
    if(tags->MD > temp){temp = tags->MD; highest = MD;}
    if(tags->MF > temp){temp = tags->MF; highest = MF;}
    if(tags->ND1 > temp){temp = tags->ND1; highest = ND1;}
    if(tags->NN > temp){temp = tags->NN; highest = NN;}
    if(tags->NN1 > temp){temp = tags->NN1; highest = NN1;}
    if(tags->NN2 > temp){temp = tags->NN2; highest = NN2;}
    if(tags->NNA > temp){temp = tags->NNA; highest = NNA;}
    if(tags->NNB > temp){temp = tags->NNB; highest = NNB;}
    if(tags->NNL1 > temp){temp = tags->NNL1; highest = NNL1;}
    if(tags->NNL2 > temp){temp = tags->NNL2; highest = NNL2;}
    if(tags->NNO > temp){temp = tags->NNO; highest = NNO;}
    if(tags->NNO2 > temp){temp = tags->NNO2; highest = NNO2;}
    if(tags->NNT1 > temp){temp = tags->NNT1; highest = NNT1;}
    if(tags->NNT2 > temp){temp = tags->NNT2; highest = NNT2;}
    if(tags->NNU > temp){temp = tags->NNU; highest = NNU;}
    if(tags->NNU1 > temp){temp = tags->NNU1; highest = NNU1;}
    if(tags->NNU2 > temp){temp = tags->NNU2; highest = NNU2;}
    if(tags->NP > temp){temp = tags->NP; highest = NP;}
    if(tags->NP1 > temp){temp = tags->NP1; highest = NP1;}
    if(tags->NP2 > temp){temp = tags->NP2; highest = NP2;}
    if(tags->NPD1 > temp){temp = tags->NPD1; highest = NPD1;}
    if(tags->NPD2 > temp){temp = tags->NPD2; highest = NPD2;}
    if(tags->NPM1 > temp){temp = tags->NPM1; highest = NPM1;}
    if(tags->NPM2 > temp){temp = tags->NPM2; highest = NPM2;}
    if(tags->PN > temp){temp = tags->PN; highest = PN;}
    if(tags->PN1 > temp){temp = tags->PN1; highest = PN1;}
    if(tags->PNQO > temp){temp = tags->PNQO; highest = PNQO;}
    if(tags->PNQS > temp){temp = tags->PNQS; highest = PNQS;}
    if(tags->PNQV > temp){temp = tags->PNQV; highest = PNQV;}
    if(tags->PNX1 > temp){temp = tags->PNX1; highest = PNX1;}
    if(tags->PPGE > temp){temp = tags->PPGE; highest = PPGE;}
    if(tags->PPH1 > temp){temp = tags->PPH1; highest = PPH1;}
    if(tags->PPHO1 > temp){temp = tags->PPHO1; highest = PPHO1;}
    if(tags->PPHO2 > temp){temp = tags->PPHO2; highest = PPHO2;}
    if(tags->PPHS1 > temp){temp = tags->PPHS1; highest = PPHS1;}
    if(tags->PPHS2 > temp){temp = tags->PPHS2; highest = PPHS2;}
    if(tags->PPIO1 > temp){temp = tags->PPIO1; highest = PPIO1;}
    if(tags->PPIO2 > temp){temp = tags->PPIO2; highest = PPIO2;}
    if(tags->PPIS1 > temp){temp = tags->PPIS1; highest = PPIS1;}
    if(tags->PPIS2 > temp){temp = tags->PPIS2; highest = PPIS2;}
    if(tags->PPX1 > temp){temp = tags->PPX1; highest = PPX1;}
    if(tags->PPX2 > temp){temp = tags->PPX2; highest = PPX2;}
    if(tags->PPY > temp){temp = tags->PPY; highest = PPY;}
    if(tags->RA > temp){temp = tags->RA; highest = RA;}
    if(tags->REX > temp){temp = tags->REX; highest = REX;}
    if(tags->RG > temp){temp = tags->RG; highest = RG;}
    if(tags->RGQ > temp){temp = tags->RGQ; highest = RGQ;}
    if(tags->RGQV > temp){temp = tags->RGQV; highest = RGQV;}
    if(tags->RGR > temp){temp = tags->RGR; highest = RGR;}
    if(tags->RGT > temp){temp = tags->RGT; highest = RGT;}
    if(tags->RL > temp){temp = tags->RL; highest = RL;}
    if(tags->RP > temp){temp = tags->RP; highest = RP;}
    if(tags->RPK > temp){temp = tags->RPK; highest = RPK;}
    if(tags->RR > temp){temp = tags->RR; highest = RR;}
    if(tags->RRQ > temp){temp = tags->RRQ; highest = RRQ;}
    if(tags->RRQV > temp){temp = tags->RRQV; highest = RRQV;}
    if(tags->RRR > temp){temp = tags->RRR; highest = RRR;}
    if(tags->RRT > temp){temp = tags->RRT; highest = RRT;}
    if(tags->RT > temp){temp = tags->RT; highest = RT;}
    if(tags->TO > temp){temp = tags->TO; highest = TO;}
    if(tags->UH > temp){temp = tags->UH; highest = UH;}
    if(tags->VB0 > temp){temp = tags->VB0; highest = VB0;}
    if(tags->VBDR > temp){temp = tags->VBDR; highest = VBDR;}
    if(tags->VBDZ > temp){temp = tags->VBDZ; highest = VBDZ;}
    if(tags->VBG > temp){temp = tags->VBG; highest = VBG;}
    if(tags->VBI > temp){temp = tags->VBI; highest = VBI;}
    if(tags->VBM > temp){temp = tags->VBM; highest = VBM;}
    if(tags->VBN > temp){temp = tags->VBN; highest = VBN;}
    if(tags->VBR > temp){temp = tags->VBR; highest = VBR;}
    if(tags->VBZ > temp){temp = tags->VBZ; highest = VBZ;}
    if(tags->VD0 > temp){temp = tags->VD0; highest = VD0;}
    if(tags->VDD > temp){temp = tags->VDD; highest = VDD;}
    if(tags->VDG > temp){temp = tags->VDG; highest = VDG;}
    if(tags->VDI > temp){temp = tags->VDI; highest = VDI;}
    if(tags->VDN > temp){temp = tags->VDN; highest = VDN;}
    if(tags->VDZ > temp){temp = tags->VDZ; highest = VDZ;}
    if(tags->VH0 > temp){temp = tags->VH0; highest = VH0;}
    if(tags->VHD > temp){temp = tags->VHD; highest = VHD;}
    if(tags->VHG > temp){temp = tags->VHG; highest = VHG;}
    if(tags->VHI > temp){temp = tags->VHI; highest = VHI;}
    if(tags->VHN > temp){temp = tags->VHN; highest = VHN;}
    if(tags->VHZ > temp){temp = tags->VHZ; highest = VHZ;}
    if(tags->VM > temp){temp = tags->VM; highest = VM;}
    if(tags->VMK > temp){temp = tags->VMK; highest = VMK;}
    if(tags->VV0 > temp){temp = tags->VV0; highest = VV0;}
    if(tags->VVD > temp){temp = tags->VVD; highest = VVD;}
    if(tags->VVG > temp){temp = tags->VVG; highest = VVG;}
    if(tags->VVGK > temp){temp = tags->VVGK; highest = VVGK;}
    if(tags->VVI > temp){temp = tags->VVI; highest = VVI;}
    if(tags->VVN > temp){temp = tags->VVN; highest = VVN;}
    if(tags->VVNK > temp){temp = tags->VVNK; highest = VVNK;}
    if(tags->VVZ > temp){temp = tags->VVZ; highest = VVZ;}
    if(tags->XX > temp){temp = tags->XX; highest = XX;}
    if(tags->ZZ1 > temp){temp = tags->ZZ1; highest = ZZ1;}
    if(tags->ZZ2 > temp){temp = tags->ZZ2; highest = ZZ2;}
    
    return highest;
}


