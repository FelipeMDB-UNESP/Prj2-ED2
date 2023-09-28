#include "header.h"


#pragma region codigo_feito

/*Adição nas Alocações Dinâmicas*/

void add_caractere_string(STRING* str, char caractere) {
    STRING novaString;
    novaString = (STRING) malloc(sizeof(char) * strlen(*str) + 2);
    novaString[strlen(*str) + 1] = '\0';
    strcpy(novaString, *str);
    novaString[strlen(*str)] = caractere;
    limpar_string(str);
    *str = novaString;
}

void add_string_string(STRING* str1, STRING* str2) {
    STRING novaString;
    novaString = (STRING) malloc(strlen(*str1) + strlen(*str2) + 1);
    copiar_string(&novaString, str1);
    strcat(novaString, *str2);
    limpar_string(str1);
    *str1 = novaString;
}

void add_string_paragrafo(PARAGRAFO* par, STRING* str) {
    
    int i;
    int tam = tam_paragrafo(par);
    PARAGRAFO novoParagrafo;
    novoParagrafo = (PARAGRAFO) malloc(sizeof(STRING) * (tam + 2));
    
    //Loop copiando strings de par para novoParagrafo
    for (int i = 0; i < tam; i++) {
        novoParagrafo[i] = (*par)[i];
    }

    //Insere a string e o NULL do final do paragrafo
    novoParagrafo[tam] = *str;
    novoParagrafo[tam+1] = NULL;

    //Limpa a alocação anterior, sem limpar os ponteiros internos
    free(*par);

    //Coloca a string recebida apontando para NULL a fim de evitar problemas de segmentation fault
    *str = NULL;

    //Passa o novo paragrafo criado ao endereço recebido como parâmetro
    *par = novoParagrafo;
}

/*
void add_paragrafo_paragrafo(PARAGRAFO* par1, PARAGRAFO* par2) {
    int i;
    int tam1 = tam_paragrafo(par1);
    int tam2 = tam_paragrafo(par2);
    PARAGRAFO novoParagrafo = (PARAGRAFO) malloc(sizeof(STRING) * (tam1 + tam2 + 1));

    for (i = 0; i < tam1; i++) {
        novoParagrafo[i] = (STRING) malloc(strlen(*par1[i]) + 1);
        copiar_string(&novoParagrafo[i], par1[i]);
    }

    for (int i = 0; i < tam2; i++) {
        novoParagrafo[tam1 + i] = (STRING) malloc(strlen(*par2[i]) + 1);
        copiar_string(&novoParagrafo[tam1 + i], par2[i]);
    }

    limpar_paragrafo(par1);
    *par1 = novoParagrafo;
}
*/

void add_registro_pasta(PASTA* pst, REGISTRO* reg) {
    int i;
    int tam = tam_pasta(pst);
    PASTA novaPasta;
    novaPasta = (PASTA) malloc(sizeof(REGISTRO) * (tam + 2));
    
    for (int i = 0; i < tam; i++) {
        novaPasta[i] = (*pst)[i];
    }

    novaPasta[tam] = *reg;
    novaPasta[tam+1] = NULL;

    free(pst);

    *reg = NULL;
    
    *pst = novaPasta;
}
/*
void add_pasta_pasta(PASTA* pst1, PASTA* pst2) {
    int i;
    int tam1 = tam_pasta(pst1);
    int tam2 = tam_pasta(pst2);
    PASTA novaPasta = (PASTA) malloc(sizeof(REGISTRO) * (tam1 + tam2 + 1));

    for (i = 0; i < tam1; i++) {
        novaPasta[i] = (REGISTRO) malloc(sizeof(*pst1[i]) + 1);
        copiar_registro(&novaPasta[i], pst1[i]);
    }

    for (int i = 0; i < tam2; i++) {
        novaPasta[tam1 + i] = (REGISTRO) malloc(sizeof(*pst2[i]) + 1);
        copiar_registro(&novaPasta[tam1 + i], pst2[i]);
    }

    limpar_pasta(pst1);
    *pst1 = novaPasta;
}
*/
/*Criação das Alocações Dinâmicas*/

//Aloca espaço para um int
NUMERO criar_numero() {
    NUMERO num = (NUMERO) malloc(sizeof(int));
    *num = -1;
    return num;
}

//Aloca espaço para um vetor de caracteres unitario
STRING criar_string() {
    STRING str = (STRING) malloc(sizeof(char));
    str[0]='\0';
    return str;
}

//Aloca espaço para um vetor de strings unitario
PARAGRAFO criar_paragrafo() {
    PARAGRAFO par = (PARAGRAFO) malloc(sizeof(STRING));
    par[0] = NULL;
    return par;
}

//Aloca espaço para um registro de dados
REGISTRO criar_registro() {
    REGISTRO reg = (REGISTRO) malloc(sizeof(DADOS));
    reg->codCliente = criar_string();
    reg->codVeiculo = criar_string();
    reg->nomeCliente = criar_string();
    reg->nomeVeiculo = criar_string();
    reg->quantDias = criar_numero();
    return reg;
}

//Aloca espaço para um vetor de registros unitario
PASTA criar_pasta() {
    PASTA pst = (PASTA) malloc(sizeof(REGISTRO));
    pst[0]=NULL;
    return pst;
}


/*Limpeza das Alocações Dinâmicas*/

//Limpar a alocação de um int
void limpar_numero(NUMERO* num) {
    free(*num);
}

//Limpar a alocação de um vetor de caracteres
void limpar_string(STRING* str) {
    free(*str);
}

//Limpar a alocação de um vetor de strings
void limpar_paragrafo(PARAGRAFO* par) {
    int i;
    for (i=0; (*par)[i] != NULL; i++) {
        limpar_string(&(*par)[i]);
    }
    free(*par);
}

//Limpar a alocação de um registro de dados
void limpar_registro(REGISTRO* reg) {
    limpar_string(&(*reg)->codCliente);
    limpar_string(&(*reg)->codVeiculo);
    limpar_string(&(*reg)->nomeCliente);
    limpar_string(&(*reg)->nomeVeiculo);
    limpar_numero(&(*reg)->quantDias);
    free(*reg);
}

//Limpar a alocação de um vetor de registros
void limpar_pasta(PASTA* pst) {
    int i;
    //
    for (i=0; (*pst)[i] != NULL; i++) {
        limpar_registro(&((*pst)[i]));
    }
    free(*pst);
}


/*Copia nas Alocações Dinâmicas*/

void copiar_string(STRING* new, STRING* str) {
    strcpy(*new,*str);
}
/*
void copiar_paragrafo(PARAGRAFO* new, PARAGRAFO* par) {
    int i;
    for (int i=0; (*par)[i]!= NULL; i++) {
        copiar_string(&(*new)[i], &(*par)[i]);
    }
    new[i]=NULL;
}

void copiar_registro(REGISTRO* new, REGISTRO* reg) {

    copiar_string(&((*new)->codCliente), &((*reg)->codCliente));
    copiar_string(&((*new)->codVeiculo), &((*reg)->codVeiculo));
    copiar_string(&((*new)->nomeCliente), &((*reg)->nomeCliente));
    copiar_string(&((*new)->nomeVeiculo), &((*reg)->nomeVeiculo));
    *((*new)->quantDias) = *((*reg)->quantDias);
}

void copiar_pasta(PASTA* new, PASTA* pst) {
    int i;
    for (i=0; (*pst)[i] != NULL; i++) {
        copiar_registro(&(*new)[i], &(*pst)[i]);
    }
    new[i] = NULL;
}
*/

/*Tamanho nas Alocações Dinâmicas*/

int tam_paragrafo(PARAGRAFO* par) {
    int i;
    for (i=0; (*par)[i] != NULL; i++) {
    }
    return i;
}

int tam_pasta(PASTA* pst) {
    int i;
    for (i=0; (*pst)[i] != NULL; i++) {
    }
    return i;
}

#pragma endregion codigo_feito

#pragma region trabalho_anterior

FILE* abrir_arquivo_binario(STRING nome_do_arquivo) {

    FILE* arq;
    bool inexistencia;
    char recado[64];

    arq = fopen(nome_do_arquivo, "rb");
    inexistencia = (arq == NULL);


    if (inexistencia) {
        strcpy(recado, "Arquivo Binário \"");
        strcat(recado, nome_do_arquivo);
        strcat(recado, "\" Inexistente.");
        atualiza_log(recado);
        return NULL;
    } else {
        fclose(arq);
    }


    strcpy(recado, "Arquivo Binário \"");
    strcat(recado, nome_do_arquivo);
    strcat(recado, "\" Aberto.");
    atualiza_log(recado);

    arq = fopen(nome_do_arquivo, "r+b");
    return arq;
}


#pragma region cemiterio_de_funcoes

//Funcoes de trabalho com strings de tamanho variavel.
/*
void adicionar_caractere_string(STRING *string, char caractere) {
    STRING segunda_string;

    if ((*string)[0] == '\0') {
        segunda_string = (STRING) malloc(sizeof(char) * 2);
        segunda_string[0] = caractere;
        segunda_string[1] = '\0';
    } else {
        segunda_string = (STRING) malloc(sizeof(char) * (strlen(*string) + 2));
        segunda_string[strlen(*string) + 1] = '\0';
        strcpy(segunda_string, *string);
        segunda_string[strlen(*string)] = caractere;
    }
    limpar_string(string);
    *string = segunda_string;
}

void copiar_pastas(REGISTRO** pasta1, REGISTRO** pasta2) {
    int i;
    for (i=0; pasta1[i]!=NULL && pasta2[i]!=NULL; i++) {
        pasta1[i] = pasta2[i];
    }
    pasta1[i]=NULL;
}

void adicionar_registro_pasta(REGISTRO** pasta, REGISTRO* registro) {
    
    REGISTRO** segunda_pasta;

    if (pasta[0] == NULL) {
        segunda_pasta = (REGISTRO**) malloc(sizeof(REGISTRO*)*2);
        segunda_pasta[0] = registro;
        segunda_pasta[1] = NULL;
    } else {
        segunda_pasta = (REGISTRO**) malloc(sizeof(REGISTRO*)*(tam_pasta(pasta)+2));
        segunda_pasta[tam_pasta(pasta)+1] = NULL;
        copiar_pastas(segunda_pasta, pasta);
        segunda_pasta[tam_pasta(pasta)] = registro;
    }
    limpar_pasta(pasta);
    pasta = segunda_pasta;
}
*/

#pragma endregion cemiterio_de_funcoes

PASTA carregar_dados(STRING nomeArquivoInsercao) {
    FILE* arq;
    arq = abrir_arquivo_binario(nomeArquivoInsercao);
    if (arq == NULL) {
        // Tratamento de erro: não foi possível abrir o arquivo.
        atualiza_log("Erro ao abrir o arquivo binario de insercao.");
        exit(0);
    }

    int cont;
    char caractere;
    PASTA pasta = criar_pasta();
    REGISTRO registro;
    bool fim_de_arquivo = false;

    STRING inteiro;

    while (!fim_de_arquivo) {
        
        registro = criar_registro();
        inteiro = criar_string();

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0'){
            add_caractere_string(&(registro->codCliente),caractere);
        }

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0'){
            add_caractere_string(&(registro->codVeiculo),caractere);
        }

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0'){
            add_caractere_string(&(registro->nomeCliente),caractere);
        }

        while (((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere == '\0') {}

        add_caractere_string(&registro->nomeVeiculo,caractere);
        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0'){
            add_caractere_string(&registro->nomeVeiculo,caractere);
        }

        while (((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere == '\0') {}

        add_caractere_string(&inteiro,caractere);
        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0'){
            add_caractere_string(&inteiro,caractere);
        }

        while (((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere == '\0') {}
        fseek(arq,(-1)*sizeof(char),SEEK_CUR);

        *(registro->quantDias) = atoi(inteiro);
        limpar_string(&inteiro);

        if (cont==0) {
            fim_de_arquivo = true;
        }
        
        add_registro_pasta(&pasta,&registro);
    }
    atualiza_log("Arquivo de Insercao Carregado.");
    fclose(arq);
    return pasta;
}

PARAGRAFO carregar_chaves(STRING nomeArquivoChaves) {
    FILE* arq;
    arq = abrir_arquivo_binario(nomeArquivoChaves);
    if (arq == NULL) {
        // Tratamento de erro: não foi possível abrir o arquivo.
        atualiza_log("Erro ao abrir o arquivo binario de chaves.");
        exit(0);
    }
    
    int cont;
    char caractere;
    PARAGRAFO paragrafo = criar_paragrafo();
    bool fim_de_arquivo = false;

    STRING codCliente;
    STRING codVeiculo;

    while (!fim_de_arquivo) {
        
        codCliente = criar_string();
        codVeiculo = criar_string();

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0'){
            add_caractere_string(&codCliente,caractere);
        }

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0'){
            add_caractere_string(&codVeiculo,caractere);
        }

        if (cont==0) {
            fim_de_arquivo = true;
        }

        add_string_string(&codCliente, &codVeiculo);
        add_string_paragrafo(&paragrafo,&codCliente);
        limpar_string(&codCliente);
        limpar_string(&codVeiculo);
    }
    
    atualiza_log("Arquivo de Chaves de Busca Carregado.");
    fclose(arq);
    return paragrafo;
}

#pragma endregion trabalho_anterior

int main() {
    int i;

    PASTA pasta = carregar_dados("insere.bin");
    for (i=0;pasta[i]!=NULL;i++) {
        printf("Registro %d:\n", i+1);
        printf("%s\n", (pasta[i])->codCliente);
        printf("%s\n", (pasta[i])->codVeiculo);
        printf("%s\n", (pasta[i])->nomeCliente);
        printf("%s\n", (pasta[i])->nomeVeiculo);
        printf("%d\n\n", *((pasta[i])->quantDias));
    }

    PARAGRAFO paragrafo = carregar_chaves("busca_p.bin");
    for (i=0;paragrafo[i]!=NULL;i++)
        printf("%s\n", paragrafo[i]);
}