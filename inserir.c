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
    novoRegistro1.codCliente = "7738192637182";
    novoRegistro1.codVeiculo = "6666";
    novoRegistro1.nomeCliente = "Darth Vader";
    novoRegistro1.nomeVeiculo = "Ferrari";
    novoRegistro1.quantDias = 39;
    DADOS novoRegistro2;
    novoRegistro2.codCliente = "26738491647";
    novoRegistro2.codVeiculo = "5555";
    novoRegistro2.nomeCliente = "João Pedro Caralho Santos";
    novoRegistro2.nomeVeiculo = "Tanque de guerrra";
    novoRegistro2.quantDias = 5;
    DADOS novoRegistro3;
    novoRegistro3.codCliente = "99999999999";
    novoRegistro3.codVeiculo = "1111";
    novoRegistro3.nomeCliente = "Felipe Birito";
    novoRegistro3.nomeVeiculo = "Land Roaver";
    novoRegistro3.quantDias = 888;
    DADOS novoRegistro4;
    novoRegistro4.codCliente = "88883333444";
    novoRegistro4.codVeiculo = "8931";
    novoRegistro4.nomeCliente = "Vladimir da Silva Putin";
    novoRegistro4.nomeVeiculo = "Voksvagem";
    novoRegistro4.quantDias = 45;

    DADOS dados[4] = {novoRegistro1, novoRegistro2, novoRegistro3, novoRegistro4};
    REGISTRO registro = dados;

    // Inserir o registro no final do arquivo de dados
    inserirRegistro(arquivoDados, arquivoIndice, registro);
    // // Inserir o registro no final do arquivo de dados
    // inserirRegistro(arquivoDados, registro);
    // // Atualizar o arquivo de índices com o novo byte offset
    // atualizarIndice(arquivoIndice, calcularTamanhoArquivo(arquivoDados) - sizeof(size_t));
    // // Inserir o registro no final do arquivo de dados
    // inserirRegistro(arquivoDados, registro);
    // // Atualizar o arquivo de índices com o novo byte offset
    // atualizarIndice(arquivoIndice, calcularTamanhoArquivo(arquivoDados) - sizeof(size_t));
    // // Inserir o registro no final do arquivo de dados
    // inserirRegistro(arquivoDados, registro);
    // // Atualizar o arquivo de índices com o novo byte offset
    // atualizarIndice(arquivoIndice, calcularTamanhoArquivo(arquivoDados) - sizeof(size_t));

    // Fechar os arquivos
    fclose(arquivoDados);
    fclose(arquivoIndice);

    return 0;
}
