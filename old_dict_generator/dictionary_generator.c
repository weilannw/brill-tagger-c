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
    switch(hash_value){
        case 210667599090: val->APPGE+=1; break;
        case 5862138: val->AT+=1; break;
        case 193450603: val->AT1+=1; break;
        case 193451158: val->BCL+=1; break;
        case 5862187: val->CC+=1; break;
        case 193452237: val->CCB+=1; break;
        case 5862203: val->CS+=1; break;
        case 193452764: val->CSA+=1; break;
        case 193452777: val->CSN+=1; break;
        case 193452783: val->CST+=1; break;
        case 193452786: val->CSW+=1; break;
        case 5862218: val->DA+=1; break;
        case 193453243: val->DA1+=1; break;
        case 193453244: val->DA2+=1; break;
        case 193453276: val->DAR+=1; break;
        case 193453278: val->DAT+=1; break;
        case 5862219: val->DB+=1; break;
        case 193453277: val->DB2+=1; break;
        case 5862221: val->DD+=1; break;
        case 193453342: val->DD1+=1; break;
        case 193453343: val->DD2+=1; break;
        case 193453374: val->DDQ+=1; break;
        case 210670726698: val->DDQGE+=1; break;
        case 6383961428: val->DDQV+=1; break;
        case 5862274: val->EX+=1; break;
        case 5862298: val->FO+=1; break;
        case 5862304: val->FU+=1; break;
        case 5862306: val->FW+=1; break;
        case 5862321: val->GE+=1; break;
        case 5862388: val->IF+=1; break;
        case 5862391: val->II+=1; break;
        case 5862397: val->IO+=1; break;
        case 5862405: val->IW+=1; break;
        case 5862425: val->JJ+=1; break;
        case 193460107: val->JJR+=1; break;
        case 193460109: val->JJT+=1; break;
        case 5862426: val->JK+=1; break;
        case 5862517: val->MC+=1; break;
        case 193463110: val->MC1+=1; break;
        case 193463111: val->MC2+=1; break;
        case 6384283425: val->MCGE+=1; break;
        case 6384283621: val->MCMC+=1; break;
        case 5862518: val->MD+=1; break;
        case 5862520: val->MF+=1; break;
        case 193464232: val->ND1+=1; break;
        case 5862561: val->NN+=1; break;
        case 193464562: val->NN1+=1; break;
        case 193464563: val->NN2+=1; break;
        case 193464578: val->NNA+=1; break;
        case 193464579: val->NNB+=1; break;
        case 6384331486: val->NNL1+=1; break;
        case 6384331487: val->NNL2+=1; break;
        case 193464592: val->NNO+=1; break;
        case 6384331586: val->NNO2+=1; break;
        case 6384331750: val->NNT1+=1; break;
        case 6384331751: val->NNT2+=1; break;
        case 193464598: val->NNU+=1; break;
        case 6384331783: val->NNU1+=1; break;
        case 6384331784: val->NNU2+=1; break;
        case 5862563: val->NP+=1; break;
        case 193464628: val->NP1+=1; break;
        case 193464629: val->NP2+=1; break;
        case 6384333400: val->NPD1+=1; break;
        case 6384333401: val->NPD2+=1; break;
        case 6384333697: val->NPM1+=1; break;
        case 6384333698: val->NPM2+=1; break;
        case 5862627: val->PN+=1; break;
        case 193466740: val->PN1+=1; break;
        case 6384403555: val->PNQO+=1; break;
        case 6384403559: val->PNQS+=1; break;
        case 6384403562: val->PNQV+=1; break;
        case 6384403756: val->PNX1+=1; break;
        case 6384405393: val->PPGE+=1; break;
        case 6384405406: val->PPH1+=1; break;
        case 210685379437: val->PPHO1+=1; break;
        case 210685379438: val->PPHO2+=1; break;
        case 210685379569: val->PPHS1+=1; break;
        case 210685379570: val->PPHS2+=1; break;
        case 210685380526: val->PPIO1+=1; break;
        case 210685380527: val->PPIO2+=1; break;
        case 210685380658: val->PPIS1+=1; break;
        case 210685380659: val->PPIS2+=1; break;
        case 6384405934: val->PPX1+=1; break;
        case 6384405935: val->PPX2+=1; break;
        case 193466846: val->PPY+=1; break;
        case 5862680: val->RA+=1; break;
        case 193468660: val->REX+=1; break;
        case 5862686: val->RG+=1; break;
        case 193468719: val->RGQ+=1; break;
        case 6384467813: val->RGQV+=1; break;
        case 193468720: val->RGR+=1; break;
        case 193468722: val->RGT+=1; break;
        case 5862691: val->RL+=1; break;
        case 5862695: val->RP+=1; break;
        case 193469010: val->RPK+=1; break;
        case 5862697: val->RR+=1; break;
        case 193469082: val->RRQ+=1; break;
        case 6384479792: val->RRQV+=1; break;
        case 193469083: val->RRR+=1; break;
        case 193469085: val->RRT+=1; break;
        case 5862699: val->RT+=1; break;
        case 5862760: val->TO+=1; break;
        case 5862786: val->UH+=1; break;
        case 193472877: val->VB0+=1; break;
        case 6384605683: val->VBDR+=1; break;
        case 6384605691: val->VBDZ+=1; break;
        case 193472900: val->VBG+=1; break;
        case 193472902: val->VBI+=1; break;
        case 193472906: val->VBM+=1; break;
        case 193472907: val->VBN+=1; break;
        case 193472911: val->VBR+=1; break;
        case 193472919: val->VBZ+=1; break;
        case 193472943: val->VD0+=1; break;
        case 193472963: val->VDD+=1; break;
        case 193472966: val->VDG+=1; break;
        case 193472968: val->VDI+=1; break;
        case 193472973: val->VDN+=1; break;
        case 193472985: val->VDZ+=1; break;
        case 193473075: val->VH0+=1; break;
        case 193473095: val->VHD+=1; break;
        case 193473098: val->VHG+=1; break;
        case 193473100: val->VHI+=1; break;
        case 193473105: val->VHN+=1; break;
        case 193473117: val->VHZ+=1; break;
        case 5862824: val->VM+=1; break;
        case 193473267: val->VMK+=1; break;
        case 193473537: val->VV0+=1; break;
        case 193473557: val->VVD+=1; break;
        case 193473560: val->VVG+=1; break;
        case 6384627555: val->VVGK+=1; break;
        case 193473562: val->VVI+=1; break;
        case 193473567: val->VVN+=1; break;
        case 6384627786: val->VVNK+=1; break;
        case 193473579: val->VVZ+=1; break;
        case 5862901: val->XX+=1; break;
        case 193478026: val->ZZ1+=1; break;
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
  struct tagcounts_t *finalval = malloc (sizeof (struct tagcounts_t));
   if(hashmap_get(mymap, name, (void **)&finalval) == MAP_OK)
    printf("Key: %s\nValues: APPGE=%d\tZZ1=%d\tZZ2=%d\n", name, finalval->APPGE, finalval->ZZ1, finalval->ZZ2);

}
          

