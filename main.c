#include "header.h"

#pragma region codigo_feito

#pragma region criacao_alocacoes_dinamicas

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
#pragma endregion criacao_alocacoes_dinamicas

#pragma region limpeza_alocacoes_dinamicas

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

#pragma endregion limpeza_alocacoes_dinamicas

#pragma region copia_alocacoes_dinamicas

void copiar_string(STRING* new, STRING* str) {
    strcpy(*new,*str);
}

#pragma endregion copia_alocacoes_dinamicas

#pragma region tamanho_alocacoes_dinamicas

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

#pragma endregion tamanho_alocacoes_dinamicas

#pragma region insercao_alocacoes_dinamicas

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

#pragma endregion insercao_alocacoes_dinamicas

#pragma endregion codigo_feito

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

#pragma region funcoes_inserir
// Função para calcular o tamanho de um arquivo
size_t calcularTamanhoArquivo(FILE* arquivo) {
    fseek(arquivo, 0, SEEK_END);
    size_t tamanho = ftell(arquivo);
    rewind(arquivo);
    return tamanho;
}

// Função para atualizar o arquivo de índices
void atualizarIndice(FILE* arquivoIndice, size_t byteOffset, STRING chavePrimaria) {
    // Mover ponteiro de para o final do arquivo de índices
    fseek(arquivoIndice, 0, SEEK_END);

    // Escrever o novo índice (byteOffset) no arquivo de índices
    fwrite(&byteOffset, sizeof(size_t), 1, arquivoIndice);
    fwrite(chavePrimaria, sizeof(char), strlen(chavePrimaria) + 1, arquivoIndice);
}

void inserirRegistro(FILE* arquivoDados, FILE* arquivoIndice, REGISTRO novoRegistro) {

    int posRegistro;
    printf("Qual o índice do registro que deseja inserir?");
    scanf("%d", &posRegistro);

    // Calcular tamanho do registro
    size_t tamanhoRegistro = strlen(novoRegistro[posRegistro].codCliente) + 1 +
                             strlen(novoRegistro[posRegistro].codVeiculo) + 1 +
                             strlen(novoRegistro[posRegistro].nomeCliente) + 1 +
                             strlen(novoRegistro[posRegistro].nomeVeiculo) + 1 +
                             sizeof(int);

    // Obter o byte offset atual
    size_t byteOffset = calcularTamanhoArquivo(arquivoDados);

    // Escrever o tamanho do registro no início do registro
    fwrite(&tamanhoRegistro, 1, 1, arquivoDados);

    // Escrever os campos no arquivo de dados
    fwrite(novoRegistro[posRegistro].codCliente, sizeof(char), strlen(novoRegistro[posRegistro].codCliente) + 1, arquivoDados);
    fwrite(novoRegistro[posRegistro].codVeiculo, sizeof(char), strlen(novoRegistro[posRegistro].codVeiculo) + 1, arquivoDados);
    fwrite(novoRegistro[posRegistro].nomeCliente, sizeof(char), strlen(novoRegistro[posRegistro].nomeCliente) + 1, arquivoDados);
    fwrite(novoRegistro[posRegistro].nomeVeiculo, sizeof(char), strlen(novoRegistro[posRegistro].nomeVeiculo) + 1, arquivoDados);
    fwrite(&(novoRegistro[posRegistro].quantDias), sizeof(int), 1, arquivoDados);

    STRING chavePrimaria;
    strcat(chavePrimaria, novoRegistro[posRegistro].codCliente);
    strcat(chavePrimaria, novoRegistro[posRegistro].codVeiculo);

    // Atualizar o arquivo de índices com o novo byte offset
    atualizarIndice(arquivoIndice, calcularTamanhoArquivo(arquivoDados) - sizeof(size_t), chavePrimaria);

    //printf("Novo registro inserido no byte offset: %lu\n", byteOffset);
}
#pragma endregion funcoes_inserir

int main() {

    FILE* arq_data = abrir_arquivo_binario("data.bin");
    if (arq_data == NULL) {
        fclose(arq_data);
        arq_data = fopen("data.bin","wb");
        fclose(arq_data);
        arq_data = fopen("data.bin","r+b");
    }

    FILE* arq_index = abrir_arquivo_binario("index.bin");
    if (arq_index == NULL) {
        fclose(arq_index);
        arq_index = fopen("index.bin","wb");
        fclose(arq_index);
        arq_index = fopen("index.bin","r+b");
    }

    REGISTRO registro;
    bool load_de_arquivos = false;
    int opcao;
    PASTA pasta;
    PARAGRAFO chaves;

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
                if (load_de_arquivos) {
                inserirRegistro();   
                } break;
            case 2:
                if (load_de_arquivos) {
                    
                } break;
            case 3:
                pasta = carregar_dados("insere.bin");
                chaves = carregar_chaves("busca_p.bin");
                atualiza_log("Arquivos carregados.");
                load_de_arquivos = true;
                break;
            case 4:
                limpar_log();
                break;
            case 0:
                atualiza_log("Execucao Finalizada.");
                fcloseall();
                exit(0);
            default:
                atualiza_log("Opcao invalida. Por favor, escolha uma opcao valida (0-4).");
                break;
        }
    } while (opcao != 0);   



    return 0;

}