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


void updateTags(char* word, struct tagcounts_t *val, char* tag){
    
    unsigned long hash_value = hash(tag);
    switch(hash_value){
        case 210706734482: val->appge+=1; break;
        case 5863226: val->at+=1; break;
        case 193486507: val->at1+=1; break;
        case 193487094: val->bcl+=1; break;
        case 5863275: val->cc+=1; break;
        case 193488173: val->ccb+=1; break;
        case 5863291: val->cs+=1; break;
        case 193488700: val->csa+=1; break;
        case 193488713: val->csn+=1; break;
        case 193488719: val->cst+=1; break;
        case 193488722: val->csw+=1; break;
        case 5863306: val->da+=1; break;
        case 193489147: val->da1+=1; break;
        case 193489148: val->da2+=1; break;
        case 193489212: val->dar+=1; break;
        case 193489214: val->dat+=1; break;
        case 5863307: val->db+=1; break;
        case 193489181: val->db2+=1; break;
        case 5863309: val->dd+=1; break;
        case 193489246: val->dd1+=1; break;
        case 193489247: val->dd2+=1; break;
        case 193489310: val->ddq+=1; break;
        case 210709862090: val->ddqge+=1; break;
        case 6385147348: val->ddqv+=1; break;
        case 5863362: val->ex+=1; break;
        case 5863386: val->fo+=1; break;
        case 5863392: val->fu+=1; break;
        case 5863394: val->fw+=1; break;
        case 5863409: val->ge+=1; break;
        case 5863476: val->if+=1; break;
        case 5863479: val->ii+=1; break;
        case 5863485: val->io+=1; break;
        case 5863493: val->iw+=1; break;
        case 5863513: val->jj+=1; break;
        case 193496043: val->jjr+=1; break;
        case 193496045: val->jjt+=1; break;
        case 5863514: val->jk+=1; break;
        case 5863605: val->mc+=1; break;
        case 193499014: val->mc1+=1; break;
        case 193499015: val->mc2+=1; break;
        case 6385469345: val->mcge+=1; break;
        case 6385469541: val->mcmc+=1; break;
        case 5863606: val->md+=1; break;
        case 5863608: val->mf+=1; break;
        case 193500136: val->nd1+=1; break;
        case 5863649: val->nn+=1; break;
        case 193500466: val->nn1+=1; break;
        case 193500467: val->nn2+=1; break;
        case 193500514: val->nna+=1; break;
        case 193500515: val->nnb+=1; break;
        case 6385517374: val->nnl1+=1; break;
        case 6385517375: val->nnl2+=1; break;
        case 193500528: val->nno+=1; break;
        case 6385517474: val->nno2+=1; break;
        case 6385517638: val->nnt1+=1; break;
        case 6385517639: val->nnt2+=1; break;
        case 193500534: val->nnu+=1; break;
        case 6385517671: val->nnu1+=1; break;
        case 6385517672: val->nnu2+=1; break;
        case 5863651: val->np+=1; break;
        case 193500532: val->np1+=1; break;
        case 193500533: val->np2+=1; break;
        case 6385519288: val->npd1+=1; break;
        case 6385519289: val->npd2+=1; break;
        case 6385519585: val->npm1+=1; break;
        case 6385519586: val->npm2+=1; break;
        case 5863715: val->pn+=1; break;
        case 193502644: val->pn1+=1; break;
        case 6385589475: val->pnqo+=1; break;
        case 6385589479: val->pnqs+=1; break;
        case 6385589482: val->pnqv+=1; break;
        case 6385589644: val->pnx1+=1; break;
        case 6385591313: val->ppge+=1; break;
        case 6385591294: val->pph1+=1; break;
        case 210724514797: val->ppho1+=1; break;
        case 210724514798: val->ppho2+=1; break;
        case 210724514929: val->pphs1+=1; break;
        case 210724514930: val->pphs2+=1; break;
        case 210724515886: val->ppio1+=1; break;
        case 210724515887: val->ppio2+=1; break;
        case 210724516018: val->ppis1+=1; break;
        case 210724516019: val->ppis2+=1; break;
        case 6385591822: val->ppx1+=1; break;
        case 6385591823: val->ppx2+=1; break;
        case 193502782: val->ppy+=1; break;
        case 5863768: val->ra+=1; break;
        case 193504596: val->rex+=1; break;
        case 5863774: val->rg+=1; break;
        case 193504655: val->rgq+=1; break;
        case 6385653733: val->rgqv+=1; break;
        case 193504656: val->rgr+=1; break;
        case 193504658: val->rgt+=1; break;
        case 5863779: val->rl+=1; break;
        case 5863783: val->rp+=1; break;
        case 193504946: val->rpk+=1; break;
        case 5863785: val->rr+=1; break;
        case 193505018: val->rrq+=1; break;
        case 6385665712: val->rrqv+=1; break;
        case 193505019: val->rrr+=1; break;
        case 193505021: val->rrt+=1; break;
        case 5863787: val->rt+=1; break;
        case 5863848: val->to+=1; break;
        case 5863874: val->uh+=1; break;
        case 193508781: val->vb0+=1; break;
        case 6385791603: val->vbdr+=1; break;
        case 6385791611: val->vbdz+=1; break;
        case 193508836: val->vbg+=1; break;
        case 193508838: val->vbi+=1; break;
        case 193508842: val->vbm+=1; break;
        case 193508843: val->vbn+=1; break;
        case 193508847: val->vbr+=1; break;
        case 193508855: val->vbz+=1; break;
        case 193508847: val->vd0+=1; break;
        case 193508899: val->vdd+=1; break;
        case 193508902: val->vdg+=1; break;
        case 193508904: val->vdi+=1; break;
        case 193508909: val->vdn+=1; break;
        case 193508921: val->vdz+=1; break;
        case 193508979: val->vh0+=1; break;
        case 193509031: val->vhd+=1; break;
        case 193509034: val->vhg+=1; break;
        case 193509036: val->vhi+=1; break;
        case 193509041: val->vhn+=1; break;
        case 193509053: val->vhz+=1; break;
        case 5863912: val->vm+=1; break;
        case 193509203: val->vmk+=1; break;
        case 193509441: val->vv0+=1; break;
        case 193509493: val->vvd+=1; break;
        case 193509496: val->vvg+=1; break;
        case 6385813475: val->vvgk+=1; break;
        case 193509498: val->vvi+=1; break;
        case 193509503: val->vvn+=1; break;
        case 6385813706: val->vvnk+=1; break;
        case 193509515: val->vvz+=1; break;
        case 5863989: val->xx+=1; break;
        case 193513930: val->zz1+=1; break;
        case 193513931: val->zz2+=1; break;
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
          

