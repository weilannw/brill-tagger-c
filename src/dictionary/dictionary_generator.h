//created by Colton Simmons
#include "../lib/hashmap.h"
#ifndef dictionary_generator_h
#define dictionary_generator_h
/* struct containing counts for each tag, 
   one struct for each unique string */
#define KEY_PREFIX ("somekey")
#define KEY_COUNT (1024*1024)
#define KEY_MAX_LENGTH (256)
typedef struct tagcounts_t
{
    int appge;   // possessive pronoun, pre-nominal (e.g. my, your, our)
    int at;    // article (e.g. the, no)
    int at1;     //singular article (e.g. a, an, every)
    int bcl;     //before-clause marker (e.g. in order (that),in order (to))
    int cc;    //coordinating conjunction (e.g. and, or)
    int ccb;     //adversative coordinating conjunction ( but)
    int cs;     //subordinating conjunction (e.g. if, because, unless, so, for)
    int csa;     //as (as conjunction)
    int csn;    //than (as conjunction)
    int cst;     //that (as conjunction)
    int csw;     //whether (as conjunction)
    int da;     //after-determiner or post-determiner capable of pronominal function (e.g. such, former, same)
    int da1;     //singular after-determiner (e.g. little, much)
    int da2;    //plural after-determiner (e.g. few, several, many)
    int dar;     //comparative after-determiner (e.g. more, less, fewer)
    int dat;     //superlative after-determiner (e.g. most, least, fewest)
    int db;     //before determiner or pre-determiner capable of pronominal function (all, half)
    int db2;    // plural before-determiner ( both)
    int dd;     //determiner (capable of pronominal function) (e.g any, some)
    int dd1;    // singular determiner (e.g. this, that, another)
    int dd2;   // plural determiner ( these,those)
    int ddq;    // wh-determiner (which, what)
    int ddqge;  //   wh-determiner, genitive (whose)
    int ddqv;   // wh-ever determiner, (whichever, whatever)
    int ex;     //existential there
    int fo;     //formula
    int fu;     //unclassified word
    int fw;     //foreign word
    int ge;     //germanic genitive marker - (' or's)
    int if;     //for (as preposition)
    int ii; //   general preposition
    int io; //    of (as preposition)
    int iw; //    with, without (as prepositions)
    int jj; //    general adjective
    int jjr;//     general comparative adjective (e.g. older, better, stronger)
    int jjt;//     general superlative adjective (e.g. oldest, best, strongest)
    int jk;//     catenative adjective (able in be able to, willing in be willing to)
    int mc;//     cardinal number,neutral for number (two, three..)
    int mc1;//     singular cardinal number (one)
    int mc2;//     plural cardinal number (e.g. sixes, sevens)
    int mcge;//     genitive cardinal number, neutral for number (two's, 100's)
    int mcmc;//     hyphenated number (40-50, 1770-1827)
    int md;//     ordinal number (e.g. first, second, next, last)
    int mf;//     fraction,neutral for number (e.g. quarters, two-thirds)
    int nd1;//     singular noun of direction (e.g. north, southeast)
    int nn;//     common noun, neutral for number (e.g. sheep, cod, headquarters)
    int nn1;//     singular common noun (e.g. book, girl)
    int nn2;//     plural common noun (e.g. books, girls)
    int nna;//     following noun of title (e.g. m.a.)
    int nnb;//     preceding noun of title (e.g. mr., prof.)
    int nnl1;//     singular locative noun (e.g. island, street)
    int nnl2;//     plural locative noun (e.g. islands, streets)
    int nno;//    numeral noun, neutral for number (e.g. dozen, hundred)
    int nno2;//     numeral noun, plural (e.g. hundreds, thousands)
    int nnt1;//     temporal noun, singular (e.g. day, week, year)
    int nnt2;//     temporal noun, plural (e.g. days, weeks, years)
    int nnu;//     unit of measurement, neutral for number (e.g. in, cc)
    int nnu1;//     singular unit of measurement (e.g. inch, centimetre)
    int nnu2;//     plural unit of measurement (e.g. ins., feet)
    int np;//     proper noun, neutral for number (e.g. ibm, andes)
    int np1;//     singular proper noun (e.g. london, jane, frederick)
    int np2;//     plural proper noun (e.g. browns, reagans, koreas)
    int npd1;//     singular weekday noun (e.g. sunday)
    int npd2;//     plural weekday noun (e.g. sundays)
    int npm1;//     singular month noun (e.g. october)
    int npm2;//     plural month noun (e.g. octobers)
    int pn;//     indefinite pronoun, neutral for number (none)
    int pn1;//     indefinite pronoun, singular (e.g. anyone, everything, nobody, one)
    int pnqo;//     objective wh-pronoun (whom)
    int pnqs;//     subjective wh-pronoun (who)
    int pnqv;//     wh-ever pronoun (whoever)
    int pnx1;//     reflexive indefinite pronoun (oneself)
    int ppge;//     nominal possessive personal pronoun (e.g. mine, yours)
    int pph1;//     3rd person sing. neuter personal pronoun (it)
    int ppho1;//     3rd person sing. objective personal pronoun (him, her)
    int ppho2;//     3rd person plural objective personal pronoun (them)
    int pphs1;//     3rd person sing. subjective personal pronoun (he, she)
    int pphs2;//     3rd person plural subjective personal pronoun (they)
    int ppio1;//     1st person sing. objective personal pronoun (me)
    int ppio2;//     1st person plural objective personal pronoun (us)
    int ppis1;//     1st person sing. subjective personal pronoun (i)
    int ppis2;//     1st person plural subjective personal pronoun (we)
    int ppx1;//     singular reflexive personal pronoun (e.g. yourself, itself)
    int ppx2;//     plural reflexive personal pronoun (e.g. yourselves, themselves)
    int ppy;//     2nd person personal pronoun (you)
    int ra;//     adverb, after nominal head (e.g. else, galore)
    int rex;//     adverb introducing appositional constructions (namely, e.g.)
    int rg;//     degree adverb (very, so, too)
    int rgq;//     wh- degree adverb (how)
    int rgqv;//     wh-ever degree adverb (however)
    int rgr;//     comparative degree adverb (more, less)
    int rgt;//     superlative degree adverb (most, least)
    int rl;//     locative adverb (e.g. alongside, forward)
    int rp;//     prep. adverb, particle (e.g about, in)
    int rpk;//     prep. adv., catenative (about in be about to)
    int rr;//     general adverb
    int rrq;//     wh- general adverb (where, when, why, how)
    int rrqv;//     wh-ever general adverb (wherever, whenever)
    int rrr;//     comparative general adverb (e.g. better, longer)
    int rrt;//     superlative general adverb (e.g. best, longest)
    int rt;//     quasi-nominal adverb of time (e.g. now, tomorrow)
    int to;//     infinitive marker (to)
    int uh;//     interjection (e.g. oh, yes, um)
    int vb0;//     be, base form (finite i.e. imperative, subjunctive)
    int vbdr;//     were
    int vbdz;//     was
    int vbg;//     being
    int vbi;//     be, infinitive (to be or not... it will be ..)
    int vbm;//     am
    int vbn;//     been
    int vbr;//     are
    int vbz;//    is
    int vd0;//     do, base form (finite)
    int vdd;//     did
    int vdg;//     doing
    int vdi;//     do, infinitive (i may do... to do...)
    int vdn;//    done
    int vdz;//     does
    int vh0;//     have, base form (finite)
    int vhd;//     had (past tense)
    int vhg;//     having
    int vhi;//     have, infinitive
    int vhn;//     had (past participle)
    int vhz;//     has
    int vm;//    modal auxiliary (can, will, would, etc.)
    int vmk;//     modal catenative (ought, used)
    int vv0;//     base form of lexical verb (e.g. give, work)
    int vvd;//     past tense of lexical verb (e.g. gave, worked)
    int vvg;//     -ing participle of lexical verb (e.g. giving, working)
    int vvgk;//     -ing participle catenative (going in be going to)
    int vvi;//     infinitive (e.g. to give... it will work...)
    int vvn;//     past participle of lexical verb (e.g. given, worked)
    int vvnk;//     past participle catenative (e.g. bound in be bound to)
    int vvz;//     -s form of lexical verb (e.g. gives, works)
    int xx;     // not, n't
    int zz1; //    singular letter of the alphabet (e.g. a,b)
    int zz2;     //plural letter of the alphabet (e.g. a's, b's)
}tagcounts_t;
typedef struct data_struct_t
{
    char key_string[KEY_MAX_LENGTH];
    int number;
} data_struct_t;
void updateTags(char* , struct tagcounts_t *, char* );
void printMap(map_t mymap, char* );
map_t generate_dictionary(char *);
#endif
