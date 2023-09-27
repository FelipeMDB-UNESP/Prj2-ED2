#include "header.h"

//Fazer os codigos abaixo para implementacao da main
#pragma region fazer_os_codigos

/*Adição nas Alocações Dinâmicas*/

// WORKING ON IT - MESTRE
void add_caractere_string(STRING* str, char caractere){
    STRING novaString;
    novaString = (STRING) malloc(sizeof(char) * strlen(*str) + 2);
    novaString[strlen(*str) + 1] = '\0';
    strcpy(novaString, *str);
    novaString[strlen(*str)] = caractere;
    limpar_string(str);
    *str = novaString;
}

void add_string_string(STRING* str1, STRING* str2){
    STRING novaString;

}

void add_string_paragrafo(PARAGRAFO* par, STRING* str);
void add_paragrafo_paragrafo(PARAGRAFO* par1, PARAGRAFO* par2);
void add_registro_pasta(PASTA* pst, REGISTRO* reg);
void add_pasta_pasta(PASTA* pst1, PASTA* pst2);

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
void limpar_parafrago(PARAGRAFO* par) {
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


STRING copiar_string(STRING* str) {
    STRING new = (STRING) malloc(strlen(*str)+1);
    strcpy(new,*str);
    return new;
}

PARAGRAFO copiar_paragrafo(PARAGRAFO* par) {
    PARAGRAFO new = (PARAGRAFO) malloc(sizeof(*par));
    int i;
    for (int i=0; (*par)[i]!=NULL; i++) {
        new[i] = copiar_string(&((*par)[i]));
    }
    new[i]=NULL;
    return new;
}

REGISTRO copiar_registro(REGISTRO* reg) {
    REGISTRO new = criar_registro();

    new->codCliente = copiar_string(&((*reg)->codCliente));
    new->codVeiculo = copiar_string(&((*reg)->codVeiculo));
    new->nomeCliente = copiar_string(&((*reg)->nomeCliente));
    new->nomeVeiculo = copiar_string(&((*reg)->nomeVeiculo));
    new->quantDias = criar_numero();
    *(new->quantDias) = *((*reg)->quantDias);

    return new;
}

PASTA copiar_pasta(PASTA* pst) {
    PASTA new = (PASTA) malloc(sizeof(*pst));
    int i;
    for (i=0; (*pst)[i]!=NULL ;i++) {
        new[i] = copiar_registro(&((*pst)[i]));
    }
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

    //FILE* arq = abrir_criar_arq_bin("Data.bin");
    REGISTRO registro;
    bool load_de_arquivos = false;
    int opcao;
    PASTA pasta;
    PARAGRAFO chaveiro;

    do {
        atualiza_log("Execucao do Menu");

        // Exibe o menu
        printf("Menu:\n");
        printf("1. Insercao\n");
        printf("2. Pesquisar\n");
        printf("3. Carregar Arquivo\n");
        printf("4. Limpar Log\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao (0-4): ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                atualiza_log("Realizando a Insercao:\n");
                break;
            case 2:
            atualiza_log("Realizando a compactação\n");
                printf("Compactacao:\n");
                break;
            case 3:
                pasta = carregar_dados("insere.bin");
                //chaveiro = carregar_chaves_delecao("remove.bin");
                atualiza_log("Arquivos carregados");
                load_de_arquivos = true;
                break;
            case 4:
                limpar_log();
                break;
            case 0:
                atualiza_log("Execucao Finalizada.");
                exit(0);
            default:
                atualiza_log("Opcao invalida. Por favor, escolha uma opcao valida (0-4).");
                break;
        }
    } while (opcao != 0);   



    return 0;

}