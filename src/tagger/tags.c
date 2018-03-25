#include <stdlib.h>
#include "tags.h"
void apply_tag(int tag_hash, char * line){
    hash_to_tag(tag_hash, &line[find_start_of_tag(line)]);
}
char * get_tagged_text(int tag, int index){
    return NULL;
}
int word_length(char * line){
    int i = 0;
    while (line[i] != '\t'){
        if(i > LINE_MAX_LENGTH) 
            return -1; // error (avoids infinite looping for invalid file)
        i++;
    }
    return i;
}
int tag_to_hash(char *tag)
{
    int hash = 5381;
    int c;
    while ((c = *tag++))
        hash = ((hash << 6) + hash) + c; /* hash * 33 + c */
    return hash;
}
void hash_to_tag(int hash, char * tag){
    switch(hash){
        case APPGE: tag="appge"; break;
        case AT: tag="at"; break;
        case AT1: tag="at1"; break;
        case BCL: tag="bcl"; break;
        case CC: tag="cc"; break;
        case CCB: tag="ccb"; break;
        case CS: tag="cs"; break;
        case CSA: tag="csa"; break;
        case CSN: tag="csn"; break;
        case CST: tag="cst"; break;
        case CSW: tag="csw"; break;
        case DA: tag="da"; break;
        case DA1: tag="da1"; break;
        case DA2: tag="da2"; break;
        case DAR: tag="dar"; break;
        case DAT: tag="dat"; break;
        case DB: tag="db"; break;
        case DB2: tag="db2"; break;
        case DD: tag="dd"; break;
        case DD1: tag="dd1"; break;
        case DD2: tag="dd2"; break;
        case DDQ: tag="ddq"; break;
        case DDQGE: tag="ddqge"; break;
        case DDQV: tag="ddqv"; break;
        case EX: tag="ex"; break;
        case FO: tag="fo"; break;
        case FU: tag="fu"; break;
        case FW: tag="fw"; break;
        case GE: tag="ge"; break;
        case IF: tag="if"; break;
        case II: tag="ii"; break;
        case IO: tag="io"; break;
        case IW: tag="iw"; break;
        case JJ: tag="jj"; break;
        case JJR: tag="jjr"; break;
        case JJT: tag="jjt"; break;
        case JK: tag="jk"; break;
        case MC: tag="mc"; break;
        case MC1: tag="mc1"; break;
        case MC2: tag="mc2"; break;
        case MCGE: tag="mcge"; break;
        case MCMC: tag="mcmc"; break;
        case MD: tag="md"; break;
        case MF: tag="mf"; break;
        case ND1: tag="nd1"; break;
        case NN: tag="nn"; break;
        case NN1: tag="nn1"; break;
        case NN2: tag="nn2"; break;
        case NNA: tag="nna"; break;
        case NNB: tag="nnb"; break;
        case NNL1: tag="nnl1"; break;
        case NNL2: tag="nnl2"; break;
        case NNO: tag="nno"; break;
        case NNO2: tag="nno2"; break;
        case NNT1: tag="nnt1"; break;
        case NNT2: tag="nnt2"; break;
        case NNU: tag="nnu"; break;
        case NNU1: tag="nnu1"; break;
        case NNU2: tag="nnu2"; break;
        case NP: tag="np"; break;
        case NP1: tag="np1"; break;
        case NP2: tag="np2"; break;
        case NPD1: tag="npd1"; break;
        case NPD2: tag="npd2"; break;
        case NPM1: tag="npm1"; break;
        case NPM2: tag="npm2"; break;
        case PN: tag="pn"; break;
        case PN1: tag="pn1"; break;
        case PNQO: tag="pnqo"; break;
        case PNQS: tag="pnqs"; break;
        case PNQV: tag="pnqv"; break;
        case PNX1: tag="pnx1"; break;
        case PPGE: tag="ppge"; break;
        case PPH1: tag="pph1"; break;
        case PPHO1: tag="ppho1"; break;
        case PPHO2: tag="ppho2"; break;
        case PPHS1: tag="pphs1"; break;
        case PPHS2: tag="pphs2"; break;
        case PPIO1: tag="ppio1"; break;
        case PPIO2: tag="ppio2"; break;
        case PPIS1: tag="ppis1"; break;
        case PPIS2: tag="ppis2"; break;
        case PPX1: tag="ppx1"; break;
        case PPX2: tag="ppx2"; break;
        case PPY: tag="ppy"; break;
        case RA: tag="ra"; break;
        case REX: tag="rex"; break;
        case RG: tag="rg"; break;
        case RGQ: tag="rgq"; break;
        case RGQV: tag="rgqv"; break;
        case RGR: tag="rgr"; break;
        case RGT: tag="rgt"; break;
        case RL: tag="rl"; break;
        case RP: tag="rp"; break;
        case RPK: tag="rpk"; break;
        case RR: tag="rr"; break;
        case RRQ: tag="rrq"; break;
        case RRQV: tag="rrqv"; break;
        case RRR: tag="rrr"; break;
        case RRT: tag="rrt"; break;
        case RT: tag="rt"; break;
        case TO: tag="to"; break;
        case UH: tag="uh"; break;
        case VB0: tag="vb0"; break;
        case VBDR: tag="vbdr"; break;
        case VBDZ: tag="vbdz"; break;
        case VBG: tag="vbg"; break;
        case VBI: tag="vbi"; break;
        case VBM: tag="vbm"; break;
        case VBN: tag="vbn"; break;
        case VBR: tag="vbr"; break;
        case VBZ: tag="vbz"; break;
        case VD0: tag="vd0"; break;
        case VDD: tag="vdd"; break;
        case VDG: tag="vdg"; break;
        case VDI: tag="vdi"; break;
        case VDN: tag="vdn"; break;
        case VDZ: tag="vdz"; break;
        case VH0: tag="vh0"; break;
        case VHD: tag="vhd"; break;
        case VHG: tag="vhg"; break;
        case VHI: tag="vhi"; break;
        case VHN: tag="vhn"; break;
        case VHZ: tag="vhz"; break;
        case VM: tag="vm"; break;
        case VMK: tag="vmk"; break;
        case VV0: tag="vv0"; break;
        case VVD: tag="vvd"; break;
        case VVG: tag="vvg"; break;
        case VVGK: tag="vvgk"; break;
        case VVI: tag="vvi"; break;
        case VVN: tag="vvn"; break;
        case VVNK: tag="vvnk"; break;
        case VVZ: tag="vvz"; break;
        case XX: tag="xx"; break;
        case ZZ1: tag="zz1"; break;
        case ZZ2: tag="zz2"; break;
        case COL: tag=":"; break;
        case DQ: tag="\""; break;
        case SCOL: tag=";"; break;
        case LPAR: tag="("; break;
        case RPAR: tag=")"; break;
        case PER: tag="."; break;
        case COM: tag=","; break;
        case QUE: tag="?"; break;
        case ZZ: tag="zz"; break;
        default: tag = NULL; break;
    }
}