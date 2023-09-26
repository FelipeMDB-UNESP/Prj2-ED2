#include "header.h"

//Fazer os codigos abaixo para implementacao da main
#pragma region fazer_os_codigos




















STRING copiar_string(STRING* str) {
    STRING new = (STRING) malloc(strlen(*str)+1);
    strcpy(new,*str);
    return new;
}

PARAGRAFO copiar_paragrafo(PARAGRAFO* par) {
    PARAGRAFO new = (PARAGRAFO) malloc(sizeof(*par));
    int i;
    for (i=0; ((*par)[i])!=NULL; i++) {
        new[i] = copiar_string(&((*par)[i]));
    }
    new[i]=NULL;
    return new;
}

REGISTRO copiar_registro(REGISTRO* reg) {
    REGISTRO new = criar_registro();

    new->codCliente = copiar_string(&(*reg)->codCliente);
    new->codVeiculo = copiar_string(&(*reg)->codVeiculo);
    new->nomeCliente = copiar_string(&(*reg)->nomeCliente);
    new->nomeVeiculo = copiar_string(&(*reg)->nomeVeiculo);
    new->quantDias = criar_numero();
    *(new->quantDias) = *((*reg)->quantDias);

    return new;
}

PASTA copiar_pasta(PASTA* pst) {
    PASTA new = (PASTA) malloc(sizeof(*pst));
    int i;
    for (i=0; (*pst)[i]!=NULL ;i++) {
        new[i] = copiar_registro(&(*pst)[i]);
    }
    //TODO: tá certo esse i fora do FOR?????
    new[i]=NULL;
    return new;
}



/*Tamanho nas Alocações Dinâmicas*/

size_t tam_paragrafo(PARAGRAFO* par) {
    return (sizeof(*par));
}

size_t tam_registro(REGISTRO* reg) {
    return(sizeof(*reg));
}

size_t tam_pasta(PASTA* pst) {
    return (sizeof(*pst));
}

#pragma endregion fazer_os_codigos

#pragma region Codigo_Feito
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

#pragma endregion Codigo_Feito

int main() {

    //size_t tam_paragrafo(PARAGRAFO* par);
    //size_t tam_registro(PARAGRAFO* par);
    //size_t tam_pasta(PARAGRAFO* par);

    //REGISTRO copiar_registro(REGISTRO* reg);
    //PASTA copiar_pasta(PASTA* pst);

    //NUMERO criar_numero();
    //STRING criar_string();
    //PASTA criar_pasta();

    //void limpar_numero(NUMERO* num);
    //void limpar_string(STRING* str);
    //void limpar_parafrago(PARAGRAFO* par);
    //void limpar_registro(REGISTRO* reg);
    //void limpar_pasta(PASTA* pst);

    //Testando criar_string
    STRING string1 = criar_string();
    string1 = "string1 teste";
    //Testando copiar_string
    STRING string2 = copiar_string(&string1);
    printf("\n%s\n", string2);

    string2 = "string2 teste";

    //Testando criar_paragrafo
    //PARAGRAFO paragrafo1 = criar_paragrafo();
    PARAGRAFO paragrafo1 = (PARAGRAFO) malloc(sizeof(STRING)*3);
    paragrafo1[0] = string1;
    paragrafo1[1] = string2;
    paragrafo1[2] = NULL;
    printf("\n%s and %s\n", paragrafo1[0], paragrafo1[1]);
    PARAGRAFO paragrafo2 = copiar_paragrafo(&paragrafo1);
    printf("\n%s and %s\n", paragrafo1[0], paragrafo1[1]);

    int n = 2;
    REGISTRO registro1 = criar_registro();
    registro1->codCliente = "12121212121";
    registro1->codVeiculo = "ABC1234";
    registro1->nomeCliente = "Joao da Silva";
    registro1->nomeVeiculo = "Chevrolet Agile 2010";
    registro1->quantDias = &n;

    printf("\n%s\n%s\n%s\n%s\n%s\n", registro1->codCliente, registro1->codVeiculo, registro1->nomeCliente, registro1->nomeVeiculo, registro1->quantDias);

    REGISTRO registro2 = copiar_registro(&registro1);
    printf("\n%s\n%s\n%s\n%s\n%s\n", registro2->codCliente, registro2->codVeiculo, registro2->nomeCliente, registro2->nomeVeiculo, registro2->quantDias);

}

