#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// Função para inicializar as cidades no TAD Estrada a partir de um arquivo
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) return NULL;

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) return NULL;

    // Lendo comprimento total da estrada
    if (fscanf(file, "%d", &(estrada->T)) != 1) {
        free(estrada);
        fclose(file);
        return NULL;
    }

    // Lendo número de cidades
    if (fscanf(file, "%d", &(estrada->N)) != 1) {
        free(estrada);
        fclose(file);
        return NULL;
    }

    if (estrada->T < 3 || estrada->T > 1000000 || estrada->N < 2 || estrada->N > 10000) {
        free(estrada);
        fclose(file);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        free(estrada);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        if (fscanf(file, "%d %s", &(estrada->C[i].Posicao), estrada->C[i].Nome) != 2) {
            free(estrada->C);
            free(estrada);
            fclose(file);
            return NULL;
        }
        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T) {
            free(estrada->C);
            free(estrada);
            fclose(file);
            return NULL;
        }
        for (int j = 0; j < i; j++) {
            if (estrada->C[i].Posicao == estrada->C[j].Posicao) {
                free(estrada->C);
                free(estrada);
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    return estrada;
}

// Função para calcular a menor vizinhança entre as cidades
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return -1;

    double menor_vizinhanca = estrada->T;

    for (int i = 1; i < estrada->N; i++) {
        double vizinhanca = (estrada->C[i].Posicao - estrada->C[i-1].Posicao) / 2.0;
        if (vizinhanca < menor_vizinhanca) {
            menor_vizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menor_vizinhanca;
}

// Função para retornar o nome da cidade com a menor vizinhança
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return NULL;

    double menor_vizinhanca = estrada->T;
    int cidade_index = -1;

    for (int i = 1; i < estrada->N; i++) {
        double vizinhanca = (estrada->C[i].Posicao - estrada->C[i-1].Posicao) / 2.0;
        if (vizinhanca < menor_vizinhanca) {
            menor_vizinhanca = vizinhanca;
            cidade_index = i;
        }
    }

    char *cidade = NULL;
    if (cidade_index != -1) {
        cidade = (char *)malloc((strlen(estrada->C[cidade_index].Nome) + 1) * sizeof(char));
        strcpy(cidade, estrada->C[cidade_index].Nome);
    }

    free(estrada->C);
    free(estrada);
    return cidade;
}
