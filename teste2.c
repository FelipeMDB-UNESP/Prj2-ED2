#include "header.h"
#include <stdio.h>
#include <stdlib.h>

STRING criar_string() {
    STRING str = (STRING) malloc(sizeof(char));
    str[0]='\0';
    return str;
}
void limpar_string(STRING* str) {
    free(*str);
}

void copiar_string(STRING* new,STRING* str) {
    strcpy(*new,*str);
}

void add_caractere_string(STRING* str, char caractere){
    STRING novaString;
    novaString = (STRING) malloc(sizeof(char) * strlen(*str) + 2);
    novaString[strlen(*str) + 1] = '\0';
    strcpy(novaString,(*str));
    novaString[strlen(*str)] = caractere;
    limpar_string(str);
    *str = novaString;
}

int main(){ 
    //STRING nome = (STRING)malloc(sizeof(char) * 4);
    STRING nome = criar_string();
    char caractere = 'R';
    add_caractere_string(&nome, caractere); 
    caractere = 'y';
    add_caractere_string(&nome, caractere); 
    caractere = 'a';
    add_caractere_string(&nome, caractere); 
    caractere = 'n';
    add_caractere_string(&nome, caractere);
    printf("\n%s", nome);
}