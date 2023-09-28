#include "header.h"

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
    
    STRING chavePrimaria = (STRING)malloc(strlen(novoRegistro[posRegistro].codCliente) + strlen(novoRegistro[posRegistro].codVeiculo) + 1);
    //strcat(chavePrimaria, novoRegistro[posRegistro].codCliente);
    //strcat(chavePrimaria, novoRegistro[posRegistro].codVeiculo);

    if (chavePrimaria != NULL) {
    strcpy(chavePrimaria, ""); // Inicialize a chavePrimaria com uma string vazia
    strcat(chavePrimaria, novoRegistro[posRegistro].codCliente);
    strcat(chavePrimaria, novoRegistro[posRegistro].codVeiculo);
    } else {
        printf("Falha na alocação de memória.\n");
    }


    // Atualizar o arquivo de índices com o novo byte offset
    atualizarIndice(arquivoIndice, calcularTamanhoArquivo(arquivoDados) - sizeof(size_t), chavePrimaria);

    // libereção de memória não mais necessária
    free(chavePrimaria);

    // Escrever o tamanho do registro no início do registro
    fwrite(&tamanhoRegistro, 1, 1, arquivoDados);

    // Crie cópias das strings com '|' como separador
    char codClienteCopy[strlen(novoRegistro[posRegistro].codCliente) + 2]; // +2 para acomodar o '|' e o '\0'
    char codVeiculoCopy[strlen(novoRegistro[posRegistro].codVeiculo) + 2];
    char nomeClienteCopy[strlen(novoRegistro[posRegistro].nomeCliente) + 2];
    char nomeVeiculoCopy[strlen(novoRegistro[posRegistro].nomeVeiculo) + 2];

    strcpy(codClienteCopy, novoRegistro[posRegistro].codCliente);
    strcat(codClienteCopy, "|");

    strcpy(codVeiculoCopy, novoRegistro[posRegistro].codVeiculo);
    strcat(codVeiculoCopy, "|");

    strcpy(nomeClienteCopy, novoRegistro[posRegistro].nomeCliente);
    strcat(nomeClienteCopy, "|");

    strcpy(nomeVeiculoCopy, novoRegistro[posRegistro].nomeVeiculo);
    strcat(nomeVeiculoCopy, "|");

    // Escrevendo os campos no arquivo 
    fwrite(codClienteCopy, sizeof(char), strlen(codClienteCopy), arquivoDados);
    fwrite(codVeiculoCopy, sizeof(char), strlen(codVeiculoCopy), arquivoDados);
    fwrite(nomeClienteCopy, sizeof(char), strlen(nomeClienteCopy), arquivoDados);
    fwrite(nomeVeiculoCopy, sizeof(char), strlen(nomeVeiculoCopy), arquivoDados);
    fwrite(&(novoRegistro[posRegistro].quantDias), sizeof(int), 1, arquivoDados);

    


    printf("Novo registro inserido no byte offset: %lu\n", byteOffset);
}

// Função para pesquisar por chave primária
void pesquisarPorChavePrimaria(FILE* arquivoIndice, FILE* arquivoDados, STRING chavePrimaria) {
    // Variáveis para armazenar o byteOffset e a chave primária lida do arquivo de índices
    size_t byteOffsetLido;
    STRING chavePrimariaLida = (STRING)malloc(strlen(chavePrimaria) + 1);
    bool achouRegistro = false;

    if (chavePrimariaLida == NULL) {
        printf("Falha na alocação de memória.\n");
        return;
    }

    // Reinicializar a chavePrimariaLida
    strcpy(chavePrimariaLida, "");

    // Reinicializar o arquivo de índices para o início
    rewind(arquivoIndice);

    while (!feof(arquivoIndice)) {
        // Ler o byteOffset e a chave primária do arquivo de índices
        fread(&byteOffsetLido, sizeof(size_t), 1, arquivoIndice);
        fread(chavePrimariaLida, sizeof(char), strlen(chavePrimaria) + 1, arquivoIndice);

        // Verificar se a chave primária lida corresponde à chavePrimaria passada como parâmetro
        if (strcmp(chavePrimariaLida, chavePrimaria) == 0) {

            // define flag informando que o registro foi encontrado
            achouRegistro = true;

            // Se for uma correspondência, use o byteOffset para ler os dados do registro no arquivo dados.bin
            fseek(arquivoDados, byteOffsetLido, SEEK_SET);

            // Primeiro, leia o tamanho do registro
            size_t tamanhoRegistro;
            fread(&tamanhoRegistro, sizeof(size_t), 1, arquivoDados);

            // Agora, aloque memória para ler o registro completo
            char* registroCompleto = (char*)malloc(tamanhoRegistro);
            if (registroCompleto == NULL) {
                printf("Falha na alocação de memória.\n");
                free(chavePrimariaLida);
                return;
            }

            // Leia o registro completo do arquivo de dados
            fread(registroCompleto, sizeof(char), tamanhoRegistro, arquivoDados);

            // Printa os dados do registro encontrado
            printf("Registro encontrado:\n%s\n", registroCompleto);

            // Libera a memória do registro encontrado
            free(registroCompleto);

            break;
        }
    }

    if(!achouRegistro){
        printf("O registro que você deseja encontrar não existe!\n");
    }

    // Libera a memória da chavePrimária temporária
    free(chavePrimariaLida);
}

int main() {
    // Abrir o arquivo de dados em modo de escrita binária
    FILE* arquivoDados = fopen("dados.bin", "ab+");

    if (arquivoDados == NULL) {
        perror("Erro ao abrir o arquivo de dados");
        return 1;
    }

    // Abrir o arquivo de índices em modo de leitura e escrita
    FILE* arquivoIndice = fopen("indices.bin", "ab+");

    if (arquivoIndice == NULL) {
        perror("Erro ao abrir o arquivo de índices");
        fclose(arquivoDados);
        return 1;
    }

    // Criar um novo registro de exemplo
    DADOS novoRegistro1;
    novoRegistro1.codCliente = "73825671819";
    novoRegistro1.codVeiculo = "6666666";
    novoRegistro1.nomeCliente = "Darth Vader";
    novoRegistro1.nomeVeiculo = "Ferrari";
    novoRegistro1.quantDias = 39;
    DADOS novoRegistro2;
    novoRegistro2.codCliente = "11839405647";
    novoRegistro2.codVeiculo = "5555555";
    novoRegistro2.nomeCliente = "Joao Pedro Caralho Santos";
    novoRegistro2.nomeVeiculo = "Tanque de guerra";
    novoRegistro2.quantDias = 5;
    DADOS novoRegistro3;
    novoRegistro3.codCliente = "99999999999";
    novoRegistro3.codVeiculo = "1111111";
    novoRegistro3.nomeCliente = "Felipe Birito";
    novoRegistro3.nomeVeiculo = "Land Roaver";
    novoRegistro3.quantDias = 888;
    DADOS novoRegistro4;
    novoRegistro4.codCliente = "88883333444";
    novoRegistro4.codVeiculo = "8931000";
    novoRegistro4.nomeCliente = "Vladimir da Silva Putin";
    novoRegistro4.nomeVeiculo = "Voksvagem";
    novoRegistro4.quantDias = 45;

    DADOS dados[4] = {novoRegistro1, novoRegistro2, novoRegistro3, novoRegistro4};
    REGISTRO registro = dados;

    // Inserir o registro no final do arquivo de dados
    //inserirRegistro(arquivoDados, arquivoIndice, registro);

    STRING chavePrimariaPesquisa = "999999999991111111";
    pesquisarPorChavePrimaria(arquivoIndice, arquivoDados, chavePrimariaPesquisa);

    // Fechar os arquivos
    fclose(arquivoDados);
    fclose(arquivoIndice);


    return 0;
}
