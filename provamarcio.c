#include <stdio.h>
#include <string.h>

#define QTD_COLUNAS 3

int removerRepetidos(int v[], int tam) {
    int i, novoTam;

    if (tam <= 0) {
        return 0;
    }

    novoTam = 1;

    for (i = 1; i < tam; i++) {
        if (v[i] != v[novoTam - 1]) {
            v[novoTam] = v[i];
            novoTam++;
        }
    }

    return novoTam;
}

void ordenar(int v[], int tam) {
    int i, j, aux;

    for (i = 0; i < tam - 1; i++) {
        for (j = 0; j < tam - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

int primoUsandoVetor(int numero, int v[], int qtdPrimos) {
    int i;

    if (numero < 2) {
        return 0;
    }

    for (i = 0; i < qtdPrimos; i++) {
        if (numero % v[i] == 0) {
            return 0;
        }
    }

    return 1;
}

void preencherPrimos(int v[], int tam) {
    int qtd = 0;
    int candidato = 2;

    while (qtd < tam) {
        if (primoUsandoVetor(candidato, v, qtd)) {
            v[qtd] = candidato;
            qtd++;
        }

        candidato++;
    }
}

void maiorPorLinha(int m[][QTD_COLUNAS], int lin, int col, int v[]) {
    int i, j, maior;

    for (i = 0; i < lin; i++) {
        maior = m[i][0];

        for (j = 1; j < col; j++) {
            if (m[i][j] > maior) {
                maior = m[i][j];
            }
        }

        v[i] = maior;
    }
}

void inverterTrecho(char str[], int inicio, int fim) {
    char aux;

    while (inicio < fim) {
        aux = str[inicio];
        str[inicio] = str[fim];
        str[fim] = aux;

        inicio++;
        fim--;
    }
}

void inverterPalavras(char str[]) {
    int i = 0;
    int inicio;

    while (str[i] != '\0') {
        if (str[i] == ' ') {
            i++;
        } else {
            inicio = i;

            while (str[i] != ' ' && str[i] != '\0') {
                i++;
            }

            inverterTrecho(str, inicio, i - 1);
        }
    }
}

void imprimirVetor(int v[], int tam) {
    int i;

    printf("{");

    for (i = 0; i < tam; i++) {
        printf("%d", v[i]);

        if (i < tam - 1) {
            printf(", ");
        }
    }

    printf("}\n");
}

int main(void) {

    /* QUESTAO A */
    int v1[] = {3, 3, 4, 5, 6, 6, 6, 7};
    int novoTam;

    novoTam = removerRepetidos(v1, 8);

    printf("A) Vetor sem repetidos: ");
    imprimirVetor(v1, novoTam);
    printf("Novo tamanho: %d\n\n", novoTam);


    /* QUESTAO B */
    int v2[] = {9, 2, 7, 1, 5};

    ordenar(v2, 5);

    printf("B) Vetor ordenado: ");
    imprimirVetor(v2, 5);
    printf("\n");


    /* QUESTAO C */
    int primos[10];

    preencherPrimos(primos, 10);

    printf("C) Primeiros 10 primos: ");
    imprimirVetor(primos, 10);
    printf("\n");


    /* QUESTAO D */
    int matriz[3][QTD_COLUNAS] = {
        {10, 5, 20},
        {-4, -2, -8},
        {7, 7, 3}
    };

    int maiores[3];

    maiorPorLinha(matriz, 3, QTD_COLUNAS, maiores);

    printf("D) Maior de cada linha: ");
    imprimirVetor(maiores, 3);
    printf("\n");


    /* QUESTAO E */
    char str[] = "o rato roeu";

    inverterPalavras(str);

    printf("E) String invertida por palavra: \"%s\"\n", str);

    return 0;
}