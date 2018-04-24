#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tags.h"
int tag_to_hash(char *tag){
    //trim the tag
    char *saveptr;
    char *trimmed;
    char *tagcpy = (char*)malloc(sizeof(char)*TAG_BUFFER_LENGTH);
    tagcpy[TAG_BUFFER_LENGTH-1]='\0';
    strncpy(tagcpy, tag, TAG_BUFFER_LENGTH-1);
    trimmed = strtok_r(tagcpy, "\n ", &saveptr);
    //printf("tag: %.5s\n", trimmed);
    //trim at _ and @ characters -- that is how multiple tags
    //are delimited. We only care about the first tag.
    //run the hashing
    int hash = 5381;
    int c;
    while ((c = *trimmed++))
        hash = ((hash << 6) + hash) + c;
    free(tagcpy);
    return hash;
}
// default output of nullbyte indicates bad input hash
void hash_to_tag(int hash, char * tag){
    switch(hash){
        case APPGE: strcpy(tag, "appge"); break;
        case AT: strcpy(tag, "at"); break;
        case AT1: strcpy(tag, "at1"); break;
        case BCL: strcpy(tag, "bcl"); break;
        case CC: strcpy(tag, "cc"); break;
        case CCB: strcpy(tag, "ccb"); break;
        case CS: strcpy(tag, "cs"); break;
        case CSA: strcpy(tag, "csa"); break;
        case CSN: strcpy(tag, "csn"); break;
        case CST: strcpy(tag, "cst"); break;
        case CSW: strcpy(tag, "csw"); break;
        case DA: strcpy(tag, "da"); break;
        case DA1: strcpy(tag, "da1"); break;
        case DA2: strcpy(tag, "da2"); break;
        case DAR: strcpy(tag, "dar"); break;
        case DAT: strcpy(tag, "dat"); break;
        case DB: strcpy(tag, "db"); break;
        case DB2: strcpy(tag, "db2"); break;
        case DD: strcpy(tag, "dd"); break;
        case DD1: strcpy(tag, "dd1"); break;
        case DD2: strcpy(tag, "dd2"); break;
        case DDQ: strcpy(tag, "ddq"); break;
        case DDQGE: strcpy(tag, "ddqge"); break;
        case DDQV: strcpy(tag, "ddqv"); break;
        case EX: strcpy(tag, "ex"); break;
        case FO: strcpy(tag, "fo"); break;
        case FU: strcpy(tag, "fu"); break;
        case FW: strcpy(tag, "fw"); break;
        case GE: strcpy(tag, "ge"); break;
        case IF: strcpy(tag, "if"); break;
        case II: strcpy(tag, "ii"); break;
        case IO: strcpy(tag, "io"); break;
        case IW: strcpy(tag, "iw"); break;
        case JJ: strcpy(tag, "jj"); break;
        case JJR: strcpy(tag, "jjr"); break;
        case JJT: strcpy(tag, "jjt"); break;
        case JK: strcpy(tag, "jk"); break;
        case MC: strcpy(tag, "mc"); break;
        case MC1: strcpy(tag, "mc1"); break;
        case MC2: strcpy(tag, "mc2"); break;
        case MCGE: strcpy(tag, "mcge"); break;
        case MCMC: strcpy(tag, "mcmc"); break;
        case MD: strcpy(tag, "md"); break;
        case MF: strcpy(tag, "mf"); break;
        case ND1: strcpy(tag, "nd1"); break;
        case NN: strcpy(tag, "nn"); break;
        case NN1: strcpy(tag, "nn1"); break;
        case NN2: strcpy(tag, "nn2"); break;
        case NNA: strcpy(tag, "nna"); break;
        case NNB: strcpy(tag, "nnb"); break;
        case NNL1: strcpy(tag, "nnl1"); break;
        case NNL2: strcpy(tag, "nnl2"); break;
        case NNO: strcpy(tag, "nno"); break;
        case NNO2: strcpy(tag, "nno2"); break;
        case NNT1: strcpy(tag, "nnt1"); break;
        case NNT2: strcpy(tag, "nnt2"); break;
        case NNU: strcpy(tag, "nnu"); break;
        case NNU1: strcpy(tag, "nnu1"); break;
        case NNU2: strcpy(tag, "nnu2"); break;
        case NP: strcpy(tag, "np"); break;
        case NP1: strcpy(tag, "np1"); break;
        case NP2: strcpy(tag, "np2"); break;
        case NPD1: strcpy(tag, "npd1"); break;
        case NPD2: strcpy(tag, "npd2"); break;
        case NPM1: strcpy(tag, "npm1"); break;
        case NPM2: strcpy(tag, "npm2"); break;
        case PN: strcpy(tag, "pn"); break;
        case PN1: strcpy(tag, "pn1"); break;
        case PNQO: strcpy(tag, "pnqo"); break;
        case PNQS: strcpy(tag, "pnqs"); break;
        case PNQV: strcpy(tag, "pnqv"); break;
        case PNX1: strcpy(tag, "pnx1"); break;
        case PPGE: strcpy(tag, "ppge"); break;
        case PPH1: strcpy(tag, "pph1"); break;
        case PPHO1: strcpy(tag, "ppho1"); break;
        case PPHO2: strcpy(tag, "ppho2"); break;
        case PPHS1: strcpy(tag, "pphs1"); break;
        case PPHS2: strcpy(tag, "pphs2"); break;
        case PPIO1: strcpy(tag, "ppio1"); break;
        case PPIO2: strcpy(tag, "ppio2"); break;
        case PPIS1: strcpy(tag, "ppis1"); break;
        case PPIS2: strcpy(tag, "ppis2"); break;
        case PPX1: strcpy(tag, "ppx1"); break;
        case PPX2: strcpy(tag, "ppx2"); break;
        case PPY: strcpy(tag, "ppy"); break;
        case RA: strcpy(tag, "ra"); break;
        case REX: strcpy(tag, "rex"); break;
        case RG: strcpy(tag, "rg"); break;
        case RGQ: strcpy(tag, "rgq"); break;
        case RGQV: strcpy(tag, "rgqv"); break;
        case RGR: strcpy(tag, "rgr"); break;
        case RGT: strcpy(tag, "rgt"); break;
        case RL: strcpy(tag, "rl"); break;
        case RP: strcpy(tag, "rp"); break;
        case RPK: strcpy(tag, "rpk"); break;
        case RR: strcpy(tag, "rr"); break;
        case RRQ: strcpy(tag, "rrq"); break;
        case RRQV: strcpy(tag, "rrqv"); break;
        case RRR: strcpy(tag, "rrr"); break;
        case RRT: strcpy(tag, "rrt"); break;
        case RT: strcpy(tag, "rt"); break;
        case TO: strcpy(tag, "to"); break;
        case UH: strcpy(tag, "uh"); break;
        case VB0: strcpy(tag, "vb0"); break;
        case VBDR: strcpy(tag, "vbdr"); break;
        case VBDZ: strcpy(tag, "vbdz"); break;
        case VBG: strcpy(tag, "vbg"); break;
        case VBI: strcpy(tag, "vbi"); break;
        case VBM: strcpy(tag, "vbm"); break;
        case VBN: strcpy(tag, "vbn"); break;
        case VBR: strcpy(tag, "vbr"); break;
        case VBZ: strcpy(tag, "vbz"); break;
        case VD0: strcpy(tag, "vd0"); break;
        case VDD: strcpy(tag, "vdd"); break;
        case VDG: strcpy(tag, "vdg"); break;
        case VDI: strcpy(tag, "vdi"); break;
        case VDN: strcpy(tag, "vdn"); break;
        case VDZ: strcpy(tag, "vdz"); break;
        case VH0: strcpy(tag, "vh0"); break;
        case VHD: strcpy(tag, "vhd"); break;
        case VHG: strcpy(tag, "vhg"); break;
        case VHI: strcpy(tag, "vhi"); break;
        case VHN: strcpy(tag, "vhn"); break;
        case VHZ: strcpy(tag, "vhz"); break;
        case VM: strcpy(tag, "vm"); break;
        case VMK: strcpy(tag, "vmk"); break;
        case VV0: strcpy(tag, "vv0"); break;
        case VVD: strcpy(tag, "vvd"); break;
        case VVG: strcpy(tag, "vvg"); break;
        case VVGK: strcpy(tag, "vvgk"); break;
        case VVI: strcpy(tag, "vvi"); break;
        case VVN: strcpy(tag, "vvn"); break;
        case VVNK: strcpy(tag, "vvnk"); break;
        case VVZ: strcpy(tag, "vvz"); break;
        case XX: strcpy(tag, "xx"); break;
        case ZZ1: strcpy(tag, "zz1"); break;
        case ZZ2: strcpy(tag, "zz2"); break;
        case COL: strcpy(tag, ":"); break;
        case DQ: strcpy(tag, "\""); break;
        case SCOL: strcpy(tag, ";"); break;
        case LPAR: strcpy(tag, "("); break;
        case RPAR: strcpy(tag, ")"); break;
        case PER: strcpy(tag, "."); break;
        case COM: strcpy(tag, ","); break;
        case QUE: strcpy(tag, "?"); break;
        case ZZ: strcpy(tag, "zz"); break;
        case NUL: strcpy(tag, "null"); break;
        default: strcpy(tag, "none"); break; // change to \0 for error checks
    }
}
