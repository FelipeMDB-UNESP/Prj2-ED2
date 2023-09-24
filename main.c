#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef size_t ENDERECO;
typedef int* NUMERO;
typedef int** CONJUNTO;
typedef char* STRING;
typedef char** PARAGRAFO;
typedef char*** TEXTO;

typedef struct dados{
    STRING codCliente;
    STRING codVeiculo;
    STRING nomeCliente;
    STRING nomeVeiculo;
    NUMERO quantDias;
} DADOS;

typedef DADOS* REGISTRO;
typedef DADOS** PASTA;
typedef DADOS*** GAVETA;


/*Criação das Alocações Dinâmicas*/

NUMERO criar_numero() {
    NUMERO num = (NUMERO) malloc(sizeof(int));
    *num = -1;
    return num;
}

STRING criar_string() {
    STRING str = (STRING) malloc(sizeof(char));
    str[0]='\0';
    return str;
}

PARAGRAFO criar_paragrafo() {
    PARAGRAFO par = (PARAGRAFO) malloc(sizeof(STRING));
    par[0] = NULL;
    return par;
}

REGISTRO criar_registro() {
    REGISTRO reg = (REGISTRO) malloc(sizeof(DADOS));
    reg->codCliente = criar_string();
    reg->codVeiculo = criar_string();
    reg->nomeCliente = criar_string();
    reg->nomeVeiculo = criar_string();
    reg->quantDias = criar_numero();
    return reg;
}

PASTA criar_pasta() {
    PASTA pst = (PASTA) malloc(sizeof(REGISTRO));
    pst[0]=NULL;
    return pst;
}


/*Limpeza das Alocações Dinâmicas*/

void limpar_numero(NUMERO* num) {
    free(*num);
}

void limpar_string(STRING* str) {
    free(*str);
}

void limpar_parafrago(PARAGRAFO* par) {
    int i;
    for (i=0; (*par)[i] != NULL; i++) {
        limpar_string(&(*par)[i]);
    }
    free(*par);
}

void limpar_registro(REGISTRO* reg) {
    limpar_string(&(*reg)->codCliente);
    limpar_string(&(*reg)->codVeiculo);
    limpar_string(&(*reg)->nomeCliente);
    limpar_string(&(*reg)->nomeVeiculo);
    limpar_numero(&(*reg)->quantDias);
    free(*reg);
}

void limpar_pasta(PASTA* pst) {
    int i;
    for (i=0; (*pst)[i] != NULL; i++) {
        limpar_registro(&((*pst)[i]));
    }
    free(*pst);
}


/*Adição nas Alocações Dinâmicas*/

void add_caractere_string(STRING* str, char caractere);
void add_string_string(STRING* str1, STRING* str2);
void add_string_paragrafo(PARAGRAFO* par, STRING* str);
void add_paragrafo_paragrafo(PARAGRAFO* par1, PARAGRAFO* par2);
void add_registro_pasta(PASTA* pst, REGISTRO* reg);
void add_pasta_pasta(PASTA* pst1, PASTA* pst2);


/*Remoção nas Alocações Dinâmicas*/

void rmv_first_caractere_string(STRING* str);
void rmv_first_string_paragrafo(PARAGRAFO* par);
void rmv_first_registro_pasta(PASTA* pst);

void rmv_last_caractere_string(STRING* str);
void rmv_last_string_paragrafo(PARAGRAFO* par);
void rmv_last_registro_pasta(PASTA* pst);


/*Copia nas Alocações Dinâmicas*/

STRING copiar_string(STRING* str);
PARAGRAFO copiar_paragrafo(PARAGRAFO* par);
REGISTRO copiar_registro(REGISTRO* reg);
PASTA copiar_pasta(PASTA* pst);


/*Tamanho nas Alocações Dinâmicas*/

size_t tam_paragrafo(PARAGRAFO* par);
size_t tam_registro(REGISTRO* reg);
size_t tam_pasta(PASTA* pst);

/*Comparação nas Alocações Dinâmicas*/

int comparar_paragrafos(PARAGRAFO* par1, PARAGRAFO* par2);
int comparar_registros(REGISTRO* reg1, REGISTRO* reg2);
int comparar_pastas(PASTA* pst1, PASTA* pst2);

int main() {

}