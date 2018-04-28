#include <stdbool.h>
#include <stdio.h>
void getfileinfo(FILE *file, size_t *numlines, size_t *numchars){
    char cur;
    *numlines = 0;
    *numchars = 0;
    while((cur = getc(file))!=EOF){
        *numchars+=1;
        if(cur == '\n')
            *numlines+=1;
    }
    fseek(file, 0, SEEK_SET);
}
bool file_exists(char *fp){
    bool exists = false;
    FILE* file;
    file = fopen(fp, "r");
    if(file){
        exists = true;
    fclose(file);
    }
    return exists; 
}
