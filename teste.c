#include "header.h"
void limpar_string(STRING* str);

//Fazer os codigos abaixo para implementacao da main
#pragma region fazer_os_codigos

/*Adição nas Alocações Dinâmicas*/

// WORKING ON IT - MESTRE
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
    copiar_string(&novaString, str2);
    limpar_string(str1);
    *str1 = novaString;
}

void add_string_paragrafo(PARAGRAFO* par, STRING* str) {
    
    int i;
    size_t tam = tam_paragrafo(par);
    PARAGRAFO novoParagrafo;
    novoParagrafo = (PARAGRAFO) malloc(sizeof(STRING) * (tam + 1));
    
    //Loop copiando strings de par para novoParagrafo
    for (int i = 0; i < tam; i++) {
        novoParagrafo[i] = (*par)[i];
    }

    //Alocando um espaco dentro de novoParagrafo (tam = tamanho da string) para inserirmos str
    novoParagrafo[tam] = (STRING) malloc(strlen(*str) + 1);

    copiar_string(&novoParagrafo[tam], str);
    limpar_paragrafo(par);
    *par = novoParagrafo;
}

void add_paragrafo_paragrafo(PARAGRAFO* par1, PARAGRAFO* par2) {
    int i;
    size_t tam1 = tam_paragrafo(par1);
    size_t tam2 = tam_paragrafo(par2);
    PARAGRAFO novoParagrafo = (PARAGRAFO) malloc(sizeof(STRING) * (tam1 + tam2));

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

void add_registro_pasta(PASTA* pst, REGISTRO* reg) {
    int i;
    size_t tam = tam_pasta(pst);
    PASTA novaPasta;
    novaPasta = (PASTA) malloc(sizeof(REGISTRO) * (tam + 1));
    
    for (int i = 0; i < tam; i++) {
        novaPasta[i] = (*pst)[i];
    }

    novaPasta[tam] = (REGISTRO) malloc(sizeof(*reg));

    copiar_registro(&novaPasta[tam], reg);
    limpar_pasta(pst);
    *pst = novaPasta;
}

void add_pasta_pasta(PASTA* pst1, PASTA* pst2) {
    int i;
    size_t tam1 = tam_pasta(pst1);
    size_t tam2 = tam_pasta(pst2);
    PASTA novaPasta = (PASTA) malloc(sizeof(REGISTRO) * (tam1 + tam2));

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

#pragma endregion fazer_os_codigos

#pragma region Codigo_Feito
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

void copiar_paragrafo(PARAGRAFO* new, PARAGRAFO* par) {
    int i;
    for (int i=0; (*par)[i]!= NULL; i++) {
        copiar_string(new[i], par[i]);
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
        copiar_registro(new[i], pst[i]);
    }
    new[i] = NULL;
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

#pragma endregion Codigo_Feito

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

//Funcoes de trabalho com strings de tamanho variavel.

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

PASTA carregar_dados(STRING nomeArquivoInsercao) {
    FILE* arq;
    arq = abrir_arquivo_binario(nomeArquivoInsercao);
    if (arq == NULL) {
        // Tratamento de erro: não foi possível abrir o arquivo.
        perror("Erro ao abrir o arquivo binário");
        return NULL;
    }
    printf("Existe");
    int i;
    int cont;
    char caractere;
    PASTA pasta = criar_pasta();
    REGISTRO registro;
    bool fim_de_arquivo = false;

    STRING inteiro = "0"; 
    atoi(inteiro);

    for (i=0; !fim_de_arquivo; i++) {
    printf("\nLaco %d fim do arquivo = %d", i, fim_de_arquivo);
        
        registro = criar_registro();
        inteiro = criar_string();
        printf("\nPos %d\n", i);

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0'){

            adicionar_caractere_string(&registro->codCliente,caractere);
        }

            printf("\nPos1 %d\n", i);

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0'){

            adicionar_caractere_string(&registro->codVeiculo,caractere);
        }

            printf("\nPos2 %d\n", i);

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0'){

            adicionar_caractere_string(&registro->nomeCliente,caractere);
        }

            printf("\nPos3 %d\n", i);

        for (fread(&caractere,sizeof(char),1,arq);caractere == '\0';fread(&caractere,sizeof(char),1,arq)) {}
        fseek(arq,(-1)*sizeof(char),SEEK_CUR);

        printf("\nPos4 %d\n", i);

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0'){

            adicionar_caractere_string(&registro->nomeVeiculo,caractere);
        }

            printf("\nPos5 %d\n", i);

        for (fread(&caractere,sizeof(char),1,arq);caractere == '\0';fread(&caractere,sizeof(char),1,arq)) {}
        fseek(arq,(-1)*sizeof(char),SEEK_CUR);

        printf("\nPos6 %d\n", i);

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0'){

            adicionar_caractere_string(&inteiro,caractere);
        }

            printf("\nPos7 %d\n", i);

        for (fread(&caractere,sizeof(char),1,arq);caractere == '\0';fread(&caractere,sizeof(char),1,arq)) {}
        fseek(arq,(-1)*sizeof(char),SEEK_CUR);
        printf("\nPos8 %d\n", i);

        *(registro->quantDias) = atoi(inteiro);
        limpar_string(&inteiro);

        if (cont==0) {
            limpar_registro(&registro);
            limpar_string(&inteiro);
            fim_de_arquivo = true;
            break;
        }
        adicionar_registro_pasta(&pasta,&registro);
    }
    atualiza_log("Arquivo Dados Carregado.");
    return pasta;
}



int main() {

    STRING a = (STRING) malloc(sizeof(char)*7);
    a = "string";

    STRING b = (STRING) malloc(sizeof(a)+1);
    strcpy(b,a);

    printf("%s", b);

}