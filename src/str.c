#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "str.h"
#include "constants.h"

int str_starts_with(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

char *str_trim(char *str)
{
    char *end;

    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';

    return str;
}

char **str_explode(char* str, char c)
{
    static char* tmp[MAX_LINE_SIZE];
    int current = 0;
    tmp[current++] = str;
    while( *str ) {
        if ( *str == c ) {
            str = '\0';
            tmp[current++] = str+1;
        }
        ++str;
    }
    tmp[ current ] = 0;
    return tmp;
}

char** split(char* chaine, const char* delim, int vide, int *finalSize)
{
    
    char** tab=NULL;                    //tableau de chaine, tableau resultat
    char *ptr;                     //pointeur sur une partie de
    int sizeStr;                   //taille de la chaine à recupérer
    int sizeTab=0;                 //taille du tableau de chaine
    char* largestring;             //chaine à traiter
    
    int sizeDelim=strlen(delim);   //taille du delimiteur

    largestring = chaine;          //comme ca on ne modifie pas le pointeur d'origine
                                   //(faut ke je verifie si c bien nécessaire)
    

    while( (ptr=strstr(largestring, delim))!=NULL ){
        sizeStr=ptr-largestring;

        //si la chaine trouvé n'est pas vide ou si on accepte les chaine vide                   
        if(vide==1 || sizeStr!=0){
            //on alloue une case en plus au tableau de chaines
            sizeTab++;
            tab= (char**) realloc(tab,sizeof(char*)*sizeTab);

            //on alloue la chaine du tableau
            tab[sizeTab-1]=(char*) malloc( sizeof(char)*(sizeStr+1) );
            strncpy(tab[sizeTab-1],largestring,sizeStr);
            tab[sizeTab-1][sizeStr]='\0';
        }
        
        //on decale le pointeur largestring  pour continuer la boucle apres le premier elément traiter
        ptr=ptr+sizeDelim;
        largestring=ptr;
    }
    
    //si la chaine n'est pas vide, on recupere le dernier "morceau"
    if(strlen(largestring)!=0){
        sizeStr=strlen(largestring);
        sizeTab++;
        tab= (char**) realloc(tab,sizeof(char*)*sizeTab);
        tab[sizeTab-1]=(char*) malloc( sizeof(char)*(sizeStr+1) );
        strncpy(tab[sizeTab-1],largestring,sizeStr);
        tab[sizeTab-1][sizeStr]='\0';
    }
    else if(vide==1){ //si on fini sur un delimiteur et si on accepte les mots vides,on ajoute un mot vide
        sizeTab++;
        tab= (char**) realloc(tab,sizeof(char*)*sizeTab);
        tab[sizeTab-1]=(char*) malloc( sizeof(char)*1 );
        tab[sizeTab-1][0]='\0';
    }
    
    //on ajoute une case à null pour finir le tableau
    sizeTab++;
    tab = (char**) realloc(tab,sizeof(char*)*sizeTab);
    tab[sizeTab-1]=NULL;

    *finalSize = sizeTab-1;
    return tab;
}

int str_array_len(char **array)
{
    int i = 0;
    while ((array[i][0]) != '\0')
    {
        i++;
        // printf("len: %d\n", i);
    }

    return i;
}

int str_count_occurrences(char *str, char search)
{
    int count = 0;
    for (int i=0; str[i]; i++)  
    {
        if(str[i] == search)
        {
            count++;
        }
    }
    return count;
}

char *str_get_quotes_content(char *str)
{
    char tmp[MAX_LINE_SIZE];
    char *subString; // the "result"
    strcpy(tmp, str);

    subString = strtok(tmp, "\""); // find the first double quote
    subString = strtok(NULL, "\"");   // find the second double quote

    return subString;
}

void str_tolower(char *str)
{
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}