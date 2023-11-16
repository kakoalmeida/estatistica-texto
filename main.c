#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

#define TAM_MAX_PALAVRA 50
#define TAM_ALFABETO 26
#define COMPRIMENTO_PALAVRA 20
#define TAM_MIN_PALAVRA 3

int len(char *palavra){
    char *s = palavra;
    while(*s != '\0'){
        s++;
    }

    return s - palavra;
}

int verificaTamanhoLetraRpt(char *palavra){
    int tam = len(palavra);
    int i, j;

    for(i = 0; i < tam - 1; i++){
        if(!isalpha(palavra[i])){
            return 0;
        }
        for (j = i + 1; j < tam; j++){
            if(!isalpha(palavra[j])){
            return 0;
        }
            if(isalpha(palavra[j]) && tolower(palavra[i]) == tolower(palavra[j]))
                return 0;
        }
    }

    return tam >= 9;
}

int verificaTamLetraRptQuatro(char *palavra){
    int tam = len(palavra);
    int i, j;

    for(i = 0; i < tam - 1; i++){
        if(!isalpha(palavra[i])){
            return 0;
        }
        for (j = i + 1; j < tam; j++){
            if(!isalpha(palavra[j])){
            return 0;
        }
            if(isalpha(palavra[j]) && tolower(palavra[i]) == tolower(palavra[j]))
                return 0;
        }
    }

    return tam >= 4;
}

void geraArqSemLetraRpt(FILE *arq1, FILE *arq2){

    char palavra[TAM_MAX_PALAVRA];

    FILE *novoArq = fopen("sem_letras_repetidas-9.txt", "w");

    if(novoArq == NULL){
        printf("Erro ao criar arquivo sem letras repetidas >= 9");
        return;
    }

    long posicaoArq1 = ftell(arq1);
    long posicaoArq2 = ftell(arq2);

    while(fscanf(arq1, "%s", palavra) == 1){
        if(verificaTamanhoLetraRpt(palavra)){
            fprintf(novoArq, "%s\n", palavra);
        }
    }
    fseek(arq1, posicaoArq1, SEEK_SET);

    while(fscanf(arq2, "%s", palavra) == 1){
        if(verificaTamanhoLetraRpt(palavra)){
            fprintf(novoArq, "%s\n", palavra);
        }
    }
    fseek(arq2, posicaoArq2, SEEK_SET);
    fclose(novoArq);
    printf("Arquivos de palavras sem letras repetidas e comprimento >= 9 salvo no diretorio atual: sem_letras_repetidas-9.txt\n");
}

void geraArqSemLetraRptQuatro(FILE *arq1, FILE *arq2){

    char palavra[TAM_MAX_PALAVRA];

    FILE *semLetrasRptQuatro = fopen("sem_letras_repetidas-4.txt", "w");

    if(semLetrasRptQuatro == NULL){
      printf("Erro ao criar arquivo de letras repetidas com >= 4 letras\n");
      return;
    }

    long posicaoArq1 = ftell(arq1);
    long posicaoArq2 = ftell(arq2);

    while(fscanf(arq1, "%s", palavra) == 1){
        if(verificaTamLetraRptQuatro(palavra)){
            fprintf(semLetrasRptQuatro, "%s\n", palavra);
        }
    }
    fseek(arq1, posicaoArq1, SEEK_SET);

    while(fscanf(arq2, "%s", palavra) == 1){
        if(verificaTamLetraRptQuatro(palavra)){
            fprintf(semLetrasRptQuatro, "%s\n", palavra);
        }
    }
    fseek(arq2, posicaoArq2, SEEK_SET);

    fclose(semLetrasRptQuatro);

    printf("Arquivo que contem palavras sem letras e repetidas e tamanho >= 4 letras salvo no diretorio atual: sem_letras_repetidas-4.txt\n");
}

void calculaFreq(FILE *arq1, FILE *arq2){

    int freqTotal[TAM_ALFABETO] = {0};
    int letras = 0, i;
    char caractere;

    FILE *arqFreq = fopen("frequencia.txt", "w");

    if (arqFreq == NULL){
        printf("Erro ao criar arquivo de frequencia\n");
        return;
    }

    long posicaoArq1 = ftell(arq1);
    long posicaoArq2 = ftell(arq2);

    while((caractere = fgetc(arq1)) != EOF){
        if(isalpha(caractere)) {
            freqTotal[tolower(caractere) - 'a']++;
            letras++;
        }
    }
    fseek(arq1, posicaoArq1, SEEK_SET);

    while((caractere = fgetc(arq2)) != EOF){
        if(isalpha(caractere)) {
            freqTotal[tolower(caractere) - 'a']++;
            letras++;
        }
    }
    fseek(arq2, posicaoArq2, SEEK_SET);

    for(i = 0; i < TAM_ALFABETO; i++){
        char letra = 'A' + i;
        float frequencia = letras > 0 ? (float)freqTotal[i] / letras * 100 : 0;
        fprintf(arqFreq, "A letra \'%c\' corresponde a %.2f%% das letras nos textos!\n", letra, frequencia);
    }

    fclose(arqFreq);
    printf("\nArquivo de frequencia de letras salvo no diretorio atual: frequencia.txt\n");
}

void percentualPalavras(FILE *arq1, FILE *arq2) {
    int palavrasTotal = 0;
    int freqTotal[TAM_ALFABETO] = {0};
    int i, j, p;

    long posicaoArq1 = ftell(arq1);
    long posicaoArq2 = ftell(arq2);

    char palavra[TAM_MAX_PALAVRA];
    FILE *freqPalavras = fopen("percentual_palavras.txt", "w");

    if (freqPalavras == NULL) {
        printf("Erro ao criar arquivo de percentual letras em palavras\n");
        return;
    }

    // Processar o conte�do do primeiro arquivo
    while (fscanf(arq1, "%s", palavra) == 1) {
        palavrasTotal++;
        for (i = 0; i < len(palavra); i++) {
            if(isalpha(palavra[i])){
                freqTotal[tolower(palavra[i]) - 'a']++;
            }
        }
    }

    fseek(arq1, posicaoArq1, SEEK_SET);

    while (fscanf(arq2, "%s", palavra) == 1) {
        palavrasTotal++;
        for (j = 0; j < len(palavra); j++) {
            if(isalpha(palavra[j])){
                freqTotal[tolower(palavra[j]) - 'a']++;
            }
        }
    }

    fseek(arq2, posicaoArq2, SEEK_SET);

    for (p = 0; p < TAM_ALFABETO; p++) {
        char letra = 'A' + p;
        float percentual = palavrasTotal > 0 ? (float)freqTotal[p] / palavrasTotal * 100 : 0;
        fprintf(freqPalavras, "A letra %c aparece em %.2f%% das palavras.\n", letra, percentual);
    }

    // Fechar o arquivo de percentual de letras
    fclose(freqPalavras);

    printf("Percentual de palavras foi salvo no diretorio atual: percentual_palavras.txt\n");
}

void letrasInicio(FILE *arq1, FILE *arq2) {

    int palavras = 0;
    int freqTotal[TAM_ALFABETO] = {0};
    int i;

    char palavra[TAM_MAX_PALAVRA];

    FILE *letrasInicio = fopen("letras_inicio.txt", "w");

    if(letrasInicio == NULL){
        printf("Erro ao criar arquivo de letras iniciais\n");
        return;
    }

    long posicaoArq1 = ftell(arq1);
    long posicaoArq2 = ftell(arq2);

    while(fscanf(arq1, "%s", palavra) == 1){
        palavras++;
        if(isalpha(palavra[0])){
            freqTotal[tolower(palavra[0]) - 'a']++;
        }
    }

    fseek(arq1, posicaoArq1, SEEK_SET);

    while(fscanf(arq2, "%s", palavra) == 1){
        palavras++;
        if(isalpha(palavra[0])){
            freqTotal[tolower(palavra[0]) - 'a']++;
        }
    }

    fseek(arq2, posicaoArq2, SEEK_SET);

    for(i = 0; i < TAM_ALFABETO; i++){
        char letra = 'A' + i;
        float freqLetra = palavras > 0 ? (float)freqTotal[i] / palavras * 100 : 0;
        fprintf(letrasInicio, "%.2f%% das palavras iniciam com a letra %c\n", freqLetra, letra);
    }

    fclose(letrasInicio);

    printf("Arquivo de letras no inicio da string salvo no diretorio atual: letras_inicio.txt\n");
}

void letrasFinal(FILE *arq1, FILE *arq2) {

    int palavras = 0;
    int freqTotal[TAM_ALFABETO] = {0};
    int i;

    char palavra[TAM_MAX_PALAVRA];

    FILE *letrasFinal = fopen("letras_final.txt", "w");

    if(letrasFinal == NULL){
        printf("Erro ao criar arquivo de letras finais\n");
        return;
    }

    long posicaoArq1 = ftell(arq1);
    long posicaoArq2 = ftell(arq2);

    while(fscanf(arq1, "%s", palavra) == 1){
        palavras++;
        int tam = len(palavra);
        if(isalpha(palavra[tam - 1])){
            freqTotal[tolower(palavra[tam - 1]) - 'a']++;
        }
    }

    fseek(arq1, posicaoArq1, SEEK_SET);

    while(fscanf(arq2, "%s", palavra) == 1){
        palavras++;
        int tam = len(palavra);
        if(isalpha(palavra[tam - 1])){
            freqTotal[tolower(palavra[tam - 1]) - 'a']++;
        }
    }

    fseek(arq2, posicaoArq2, SEEK_SET);

    for(i = 0; i < TAM_ALFABETO; i++){
        char letra = 'A' + i;
        float freqLetra = palavras > 0 ? (float)freqTotal[i] / palavras * 100 : 0;
        fprintf(letrasFinal, "%.2f%% das palavras terminam com a letra %c\n", freqLetra, letra);
    }

    fclose(letrasFinal);

    printf("Arquivo de letras no final da string salvo no diretorio atual: letras_final.txt\n");
}

int verificaNletras(char *palavra, int n){
    int i;
    int tam = len(palavra);

    while (tam > 0 && (palavra[tam - 1] == ',' || palavra[tam - 1] == '.')) {
        tam--;
    }

    for(i = 0; i < tam; i++){
        if(!isalpha(palavra[i])){
            return 0;
        }
    }

    return tam >= n;
}

void palavraNletras(FILE *arq1, FILE *arq2, int N) {
    char palavra[TAM_MAX_PALAVRA];

    long posicaoArq1 = ftell(arq1);
    long posicaoArq2 = ftell(arq2);

    FILE *nLetras = fopen("N-letras.txt", "w");

    if (nLetras == NULL) {
        printf("Erro ao criar o arquivo de palavras com N letras.\n");
        return;
    }

    while (fscanf(arq1, "%s", palavra) == 1) {
        if (len(palavra) == N) {
            if(verificaNletras(palavra, N)){
                fprintf(nLetras, "%s\n", palavra);
            }
        }
    }

    fseek(arq1, posicaoArq1, SEEK_SET);

    while (fscanf(arq2, "%s", palavra) == 1) {
        if (len(palavra) == N) {
            if(verificaNletras(palavra, N)){
                fprintf(nLetras, "%s\n", palavra);
            }
        }
    }

    fseek(arq2, posicaoArq2, SEEK_SET);

    fclose(nLetras);

    printf("Arquivo de palavras com exatamente %d letras foram salvas no diretorio atual: N-letras.txt\n", N);
}

float vogalPorcentagem(FILE *arq1, FILE *arq2) {
    int consoantes = 0;
    int vogais = 0;

    char caractere;

    long posicaoArq1 = ftell(arq1);
    long posicaoArq2 = ftell(arq2);

    // Processar o conte�do do primeiro arquivo
    while ((caractere = fgetc(arq1)) != EOF) {
        if (isalpha(caractere)) {
            consoantes++;
            if (caractere == 'a' || caractere == 'e' || caractere == 'i' || caractere == 'o' || caractere == 'u' ||
                caractere == 'A' || caractere == 'E' || caractere == 'I' || caractere == 'O' || caractere == 'U') {
                vogais++;
            }
        }
    }

    fseek(arq1, posicaoArq1, SEEK_SET);

    while ((caractere = fgetc(arq2)) != EOF) {
        if (isalpha(caractere)) {
            consoantes++;
            if (caractere == 'a' || caractere == 'e' || caractere == 'i' || caractere == 'o' || caractere == 'u' ||
                caractere == 'A' || caractere == 'E' || caractere == 'I' || caractere == 'O' || caractere == 'U') {
                vogais++;
            }
        }
    }

    fseek(arq2, posicaoArq2, SEEK_SET);

    float porcentagemVogais = (float)vogais / consoantes * 100;

    return porcentagemVogais;
}

int verificaConsoante(char letra){
    letra = tolower(letra);
    return isalpha(letra) && letra != 'a' && letra != 'e' && letra != 'i' && letra != 'o' && letra != 'u';
}

char consoanteMaiorFreq(FILE *arq1, FILE *arq2){
    int frequencia[TAM_ALFABETO] = {0};
    char c;
    char consoanteMaiorRpt = ' ';
    int count = 0, i;

    long posicaoArq1 = ftell(arq1);
    long posicaoArq2 = ftell(arq2);

    while((c = fgetc(arq1)) != EOF) {
        if(verificaConsoante(c)){
            frequencia[tolower(c) - 'a']++;
        }
    }
    fseek(arq1, posicaoArq1, SEEK_SET);

     while((c = fgetc(arq2)) != EOF) {
        if(verificaConsoante(c)){
            frequencia[tolower(c) - 'a']++;
        }
    }
    fseek(arq2, posicaoArq2, SEEK_SET);

    for(i = 0; i < TAM_ALFABETO; i++){
        if(frequencia[i] > count){
            count = frequencia[i];
            consoanteMaiorRpt = 'a' + i;
        }
    }

    return consoanteMaiorRpt;
}

void comprimentoPalavras(FILE *arq1, FILE *arq2) {
    int contaLetras[COMPRIMENTO_PALAVRA] = {0};
    char palavra[TAM_MAX_PALAVRA];
    int i;

    FILE *comprimentoPalavras = fopen("comprimento_palavras.txt", "w");

    if (comprimentoPalavras == NULL) {
        printf("Erro ao criar o arquivo de comprimento de palavras.\n");
        return;
    }

    long posicaoArq1 = ftell(arq1);
    long posicaoArq2 = ftell(arq2);

    while (fscanf(arq1, "%s", palavra) == 1) {
        int tam = len(palavra);
        if (tam >= TAM_MIN_PALAVRA && tam <= COMPRIMENTO_PALAVRA) {
            contaLetras[tam - TAM_MIN_PALAVRA]++;
        }
    }

    fseek(arq1, posicaoArq1, SEEK_SET);
    fseek(arq2, posicaoArq2, SEEK_SET);

    while (fscanf(arq2, "%s", palavra) == 1) {
        int tam = len(palavra);
        if (tam >= TAM_MIN_PALAVRA && tam <= COMPRIMENTO_PALAVRA) {
            contaLetras[tam - TAM_MIN_PALAVRA]++;
        }
    }

    for (i = TAM_MIN_PALAVRA; i <= COMPRIMENTO_PALAVRA; i++) {
        fprintf(comprimentoPalavras, "%d palavras com %d letras.\n", contaLetras[i - TAM_MIN_PALAVRA], i);
    }

    fclose(comprimentoPalavras);

    printf("Arquivo de quantidade de palavras por comprimento salvo no diretorio atual: comprimento_palavras.txt\n");
}

int verificaMetadeVogal(char *palavra) {
    int tam = len(palavra);
    int vogais = 0, i;

    for (i = 0; i < tam; i++) {
        if (palavra[i] == 'a' || palavra[i] == 'e' || palavra[i] == 'i' || palavra[i] == 'o' || palavra[i] == 'u' ||
                palavra[i] == 'A' || palavra[i] == 'E' || palavra[i] == 'I' || palavra[i] == 'O' || palavra[i] == 'U') {
                vogais++;
        }
    }

    return (vogais * 2 >= tam);
}

void palavrasMetadeVogais(FILE *arq1, FILE *arq2){

    char palavra[TAM_MAX_PALAVRA];

    FILE *arqVogais = fopen("metade_vogais.txt", "w");

    if(arqVogais == NULL){
        printf("Erro ao criar arquivo de metade vogais\n");
        return;
    }

    long posicaoArq1 = ftell(arq1);
    long posicaoArq2 = ftell(arq2);

    while(fscanf(arq1, "%s", palavra) == 1){
        if(verificaMetadeVogal(palavra)){
            fprintf(arqVogais, "%s\n", palavra);
        }
    }
    fseek(arq1, posicaoArq1, SEEK_SET);

    while(fscanf(arq2, "%s", palavra) == 1){
        if(verificaMetadeVogal(palavra)){
            fprintf(arqVogais, "%s\n", palavra);
        }
    }
    fseek(arq2, posicaoArq2, SEEK_SET);

    fclose(arqVogais);

    printf("Arquivo de metade vogais criado no diretorio atual: metade_vogais.txt\n");
}

int main() {

    setlocale(LC_ALL, "");

    FILE *arquivo1, *arquivo2;
    char nomeArquivo1[100], nomeArquivo2[100];
    int n;
    float porcentagemVogal;
    char consoanteMaisRpt = ' ';

    printf("Digite o nome do primeiro arquivo: ");
    scanf("%s", nomeArquivo1);

    printf("Digite o nome do segundo arquivo: ");
    scanf("%s", nomeArquivo2);

    arquivo1 = fopen(nomeArquivo1, "r");
    arquivo2 = fopen(nomeArquivo2, "r");

    if (arquivo1 == NULL) printf("Erro ao abrir o primeiro arquivo!\n");
    if (arquivo2 == NULL) printf("Erro ao abrir o segundo arquivo!\n");

    printf("\nArquivos ok");

    geraArqSemLetraRpt(arquivo1, arquivo2);

    calculaFreq(arquivo1, arquivo2);

    percentualPalavras(arquivo1, arquivo2);

    letrasInicio(arquivo1, arquivo2);

    letrasFinal(arquivo1, arquivo2);

    printf("Digite um numero entre 3 e 20 para criar um arquivo com N palavras:\n");
    scanf("%d", &n);

    palavraNletras(arquivo1, arquivo2, n);

    porcentagemVogal = vogalPorcentagem(arquivo1, arquivo2);
    printf("As vogais representam %.2f%% das letras presentes nos dois arquivos\n", porcentagemVogal);

    consoanteMaisRpt = consoanteMaiorFreq(arquivo1, arquivo2);
    printf("A consoante de maior repeticao nos arquivos eh: '%c'\n", consoanteMaisRpt - 32);

    comprimentoPalavras(arquivo1, arquivo2);

    geraArqSemLetraRptQuatro(arquivo1, arquivo2);

    palavrasMetadeVogais(arquivo1, arquivo2);

    fclose(arquivo1);
    fclose(arquivo2);

    return 0;
}
