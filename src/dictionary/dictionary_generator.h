//created by Colton Simmons
#include "../io/corpus_io.h"
#ifndef dictionary_generator_h
#define dictionary_generator_h
/* struct containing counts for each tag, 
   one struct for each unique string */
#define KEY_PREFIX ("somekey")
#define KEY_COUNT (1024*1024)
#define KEY_MAX_LENGTH (256)
typedef struct tagcounts_t
{
    int APPGE;   // possessive pronoun, pre-nominal (e.g. my, your, our)
    int AT;    // article (e.g. the, no)
    int AT1;     //singular article (e.g. a, an, every)
    int BCL;     //before-clause marker (e.g. in order (that),in order (to))
    int CC;    //coordinating conjunction (e.g. and, or)
    int CCB;     //adversative coordinating conjunction ( but)
    int CS;     //subordinating conjunction (e.g. if, because, unless, so, for)
    int CSA;     //as (as conjunction)
    int CSN;    //than (as conjunction)
    int CST;     //that (as conjunction)
    int CSW;     //whether (as conjunction)
    int DA;     //after-determiner or post-determiner capable of pronominal function (e.g. such, former, same)
    int DA1;     //singular after-determiner (e.g. little, much)
    int DA2;    //plural after-determiner (e.g. few, several, many)
    int DAR;     //comparative after-determiner (e.g. more, less, fewer)
    int DAT;     //superlative after-determiner (e.g. most, least, fewest)
    int DB;     //before determiner or pre-determiner capable of pronominal function (all, half)
    int DB2;    // plural before-determiner ( both)
    int DD;     //determiner (capable of pronominal function) (e.g any, some)
    int DD1;    // singular determiner (e.g. this, that, another)
    int DD2;   // plural determiner ( these,those)
    int DDQ;    // wh-determiner (which, what)
    int DDQGE;  //   wh-determiner, genitive (whose)
    int DDQV;   // wh-ever determiner, (whichever, whatever)
    int EX;     //existential there
    int FO;     //formula
    int FU;     //unclassified word
    int FW;     //foreign word
    int GE;     //germanic genitive marker - (' or's)
    int IF;     //for (as preposition)
    int II; //   general preposition
    int IO; //    of (as preposition)
    int IW; //    with, without (as prepositions)
    int JJ; //    general adjective
    int JJR;//     general comparative adjective (e.g. older, better, stronger)
    int JJT;//     general superlative adjective (e.g. oldest, best, strongest)
    int JK;//     catenative adjective (able in be able to, willing in be willing to)
    int MC;//     cardinal number,neutral for number (two, three..)
    int MC1;//     singular cardinal number (one)
    int MC2;//     plural cardinal number (e.g. sixes, sevens)
    int MCGE;//     genitive cardinal number, neutral for number (two's, 100's)
    int MCMC;//     hyphenated number (40-50, 1770-1827)
    int MD;//     ordinal number (e.g. first, second, next, last)
    int MF;//     fraction,neutral for number (e.g. quarters, two-thirds)
    int ND1;//     singular noun of direction (e.g. north, southeast)
    int NN;//     common noun, neutral for number (e.g. sheep, cod, headquarters)
    int NN1;//     singular common noun (e.g. book, girl)
    int NN2;//     plural common noun (e.g. books, girls)
    int NNA;//     following noun of title (e.g. M.A.)
    int NNB;//     preceding noun of title (e.g. Mr., Prof.)
    int NNL1;//     singular locative noun (e.g. Island, Street)
    int NNL2;//     plural locative noun (e.g. Islands, Streets)
    int NNO;//    numeral noun, neutral for number (e.g. dozen, hundred)
    int NNO2;//     numeral noun, plural (e.g. hundreds, thousands)
    int NNT1;//     temporal noun, singular (e.g. day, week, year)
    int NNT2;//     temporal noun, plural (e.g. days, weeks, years)
    int NNU;//     unit of measurement, neutral for number (e.g. in, cc)
    int NNU1;//     singular unit of measurement (e.g. inch, centimetre)
    int NNU2;//     plural unit of measurement (e.g. ins., feet)
    int NP;//     proper noun, neutral for number (e.g. IBM, Andes)
    int NP1;//     singular proper noun (e.g. London, Jane, Frederick)
    int NP2;//     plural proper noun (e.g. Browns, Reagans, Koreas)
    int NPD1;//     singular weekday noun (e.g. Sunday)
    int NPD2;//     plural weekday noun (e.g. Sundays)
    int NPM1;//     singular month noun (e.g. October)
    int NPM2;//     plural month noun (e.g. Octobers)
    int PN;//     indefinite pronoun, neutral for number (none)
    int PN1;//     indefinite pronoun, singular (e.g. anyone, everything, nobody, one)
    int PNQO;//     objective wh-pronoun (whom)
    int PNQS;//     subjective wh-pronoun (who)
    int PNQV;//     wh-ever pronoun (whoever)
    int PNX1;//     reflexive indefinite pronoun (oneself)
    int PPGE;//     nominal possessive personal pronoun (e.g. mine, yours)
    int PPH1;//     3rd person sing. neuter personal pronoun (it)
    int PPHO1;//     3rd person sing. objective personal pronoun (him, her)
    int PPHO2;//     3rd person plural objective personal pronoun (them)
    int PPHS1;//     3rd person sing. subjective personal pronoun (he, she)
    int PPHS2;//     3rd person plural subjective personal pronoun (they)
    int PPIO1;//     1st person sing. objective personal pronoun (me)
    int PPIO2;//     1st person plural objective personal pronoun (us)
    int PPIS1;//     1st person sing. subjective personal pronoun (I)
    int PPIS2;//     1st person plural subjective personal pronoun (we)
    int PPX1;//     singular reflexive personal pronoun (e.g. yourself, itself)
    int PPX2;//     plural reflexive personal pronoun (e.g. yourselves, themselves)
    int PPY;//     2nd person personal pronoun (you)
    int RA;//     adverb, after nominal head (e.g. else, galore)
    int REX;//     adverb introducing appositional constructions (namely, e.g.)
    int RG;//     degree adverb (very, so, too)
    int RGQ;//     wh- degree adverb (how)
    int RGQV;//     wh-ever degree adverb (however)
    int RGR;//     comparative degree adverb (more, less)
    int RGT;//     superlative degree adverb (most, least)
    int RL;//     locative adverb (e.g. alongside, forward)
    int RP;//     prep. adverb, particle (e.g about, in)
    int RPK;//     prep. adv., catenative (about in be about to)
    int RR;//     general adverb
    int RRQ;//     wh- general adverb (where, when, why, how)
    int RRQV;//     wh-ever general adverb (wherever, whenever)
    int RRR;//     comparative general adverb (e.g. better, longer)
    int RRT;//     superlative general adverb (e.g. best, longest)
    int RT;//     quasi-nominal adverb of time (e.g. now, tomorrow)
    int TO;//     infinitive marker (to)
    int UH;//     interjection (e.g. oh, yes, um)
    int VB0;//     be, base form (finite i.e. imperative, subjunctive)
    int VBDR;//     were
    int VBDZ;//     was
    int VBG;//     being
    int VBI;//     be, infinitive (To be or not... It will be ..)
    int VBM;//     am
    int VBN;//     been
    int VBR;//     are
    int VBZ;//    is
    int VD0;//     do, base form (finite)
    int VDD;//     did
    int VDG;//     doing
    int VDI;//     do, infinitive (I may do... To do...)
    int VDN;//    done
    int VDZ;//     does
    int VH0;//     have, base form (finite)
    int VHD;//     had (past tense)
    int VHG;//     having
    int VHI;//     have, infinitive
    int VHN;//     had (past participle)
    int VHZ;//     has
    int VM;//    modal auxiliary (can, will, would, etc.)
    int VMK;//     modal catenative (ought, used)
    int VV0;//     base form of lexical verb (e.g. give, work)
    int VVD;//     past tense of lexical verb (e.g. gave, worked)
    int VVG;//     -ing participle of lexical verb (e.g. giving, working)
    int VVGK;//     -ing participle catenative (going in be going to)
    int VVI;//     infinitive (e.g. to give... It will work...)
    int VVN;//     past participle of lexical verb (e.g. given, worked)
    int VVNK;//     past participle catenative (e.g. bound in be bound to)
    int VVZ;//     -s form of lexical verb (e.g. gives, works)
    int XX;     // not, n't
    int ZZ1; //    singular letter of the alphabet (e.g. A,b)
    int ZZ2;     //plural letter of the alphabet (e.g. A's, b's)
}tagcounts_t;
typedef struct data_struct_t
{
    char key_string[KEY_MAX_LENGTH];
    int number;
} data_struct_t;
void update_tags(char* , struct tagcounts_t *, int );
struct hashmap generate_dictionary(corpus_t corpus);
int get_highest_frequency(struct tagcounts_t*);

#endif
