void inserirRegistro(FILE* arquivoDados, FILE* arquivoIndice, REGISTRO novoRegistro) {

    int posRegistro;
    printf("Qual o índice do registro que deseja inserir?");
    scanf("%d", &posRegistro);

    // Calcular tamanho do registro
    size_t tamanhoRegistro = strlen(novoRegistro[posRegistro].codCliente) + 1 +
                             strlen(novoRegistro[posRegistro].codVeiculo) + 1 +
                             strlen(novoRegistro[posRegistro].nomeCliente) + 1 +
                             strlen(novoRegistro[posRegistro].nomeVeiculo) + 1 +
                             sizeof(int) + 1;

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
    // Escrevendo o delimitador "|" no fim do registro
    char delimitador = '|';
    fwrite(&delimitador, sizeof(char), 1, arquivoDados);
    


    printf("Novo registro inserido no byte offset: %lu\n", byteOffset);
}