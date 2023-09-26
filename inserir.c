#include "header.h"

// Função para calcular o tamanho de um arquivo
size_t calcularTamanhoDoArquivo(FILE* arquivo) {
    fseek(arquivo, 0, SEEK_END);
    size_t tamanho = ftell(arquivo);
    rewind(arquivo);
    return tamanho;
}

void inserirRegistro(FILE* arquivoDados, DADOS novoRegistro) {
    // Calcular tamanho do registro
    size_t tamanhoRegistro = strlen(novoRegistro.codCliente) + 1 +
                             strlen(novoRegistro.codVeiculo) + 1 +
                             strlen(novoRegistro.nomeCliente) + 1 +
                             strlen(novoRegistro.nomeVeiculo) + 1 +
                             sizeof(int);

    // Obter o byte offset atual
    size_t byteOffset = tamanhoDoArquivo(arquivoDados);

    // Escrever o tamanho do registro no início do registro
    fwrite(&tamanhoRegistro, sizeof(size_t), 1, arquivoDados);

    // Escrever os campos no arquivo de dados
    fwrite(novoRegistro.codCliente, sizeof(char), strlen(novoRegistro.codCliente) + 1, arquivoDados);
    fwrite(novoRegistro.codVeiculo, sizeof(char), strlen(novoRegistro.codVeiculo) + 1, arquivoDados);
    fwrite(novoRegistro.nomeCliente, sizeof(char), strlen(novoRegistro.nomeCliente) + 1, arquivoDados);
    fwrite(novoRegistro.nomeVeiculo, sizeof(char), strlen(novoRegistro.nomeVeiculo) + 1, arquivoDados);
    fwrite(&(novoRegistro.quantDias), sizeof(int), 1, arquivoDados);

    //printf("Novo registro inserido no byte offset: %lu\n", byteOffset);
}

// Função para atualizar o arquivo de índices
void atualizarIndice(FILE* arquivoIndice, size_t byteOffset) {
    // Mover ponteiro de para o final do arquivo de índices
    fseek(arquivoIndice, 0, SEEK_END);

    // Escrever o novo índice (byteOffset) no arquivo de índices
    fwrite(&byteOffset, sizeof(size_t), 1, arquivoIndice);
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

    // Inserir o registro no final do arquivo de dados
    inserirRegistro(arquivoDados, novoRegistro1);
    // Atualizar o arquivo de índices com o novo byte offset
    atualizarIndice(arquivoIndice, tamanhoDoArquivo(arquivoDados) - sizeof(size_t));
    // Inserir o registro no final do arquivo de dados
    inserirRegistro(arquivoDados, novoRegistro2);
    // Atualizar o arquivo de índices com o novo byte offset
    atualizarIndice(arquivoIndice, tamanhoDoArquivo(arquivoDados) - sizeof(size_t));
    // Inserir o registro no final do arquivo de dados
    inserirRegistro(arquivoDados, novoRegistro3);
    // Atualizar o arquivo de índices com o novo byte offset
    atualizarIndice(arquivoIndice, tamanhoDoArquivo(arquivoDados) - sizeof(size_t));
    // Inserir o registro no final do arquivo de dados
    inserirRegistro(arquivoDados, novoRegistro4);
    // Atualizar o arquivo de índices com o novo byte offset
    atualizarIndice(arquivoIndice, tamanhoDoArquivo(arquivoDados) - sizeof(size_t));

    // Fechar os arquivos
    fclose(arquivoDados);
    fclose(arquivoIndice);

    return 0;
}
