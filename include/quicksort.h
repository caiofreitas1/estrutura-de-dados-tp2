#include <sys/resource.h>

#include <iostream>
#include <string>

#include "../include/elemento.h"

using namespace std;

// Estrutura que irá armazenar as métricas do algoritmo de ordenação
struct AnaliseQuicksort {
    AnaliseQuicksort() {
        this->numeroDeComparacoes = 0;
        this->numeroDeCopias = 0;
        this->tempoTotalGastoPraOrdenar = 0.0;
    }
    int numeroDeComparacoes;
    int numeroDeCopias;
    double tempoTotalGastoPraOrdenar;
};

void trocaElementos(Elemento* elementoA, Elemento* elementoB) {
    Elemento temporario = *elementoA;
    *elementoA = *elementoB;
    *elementoB = temporario;
}

void particao(int esquerda, int direita, int* i, int* j, Elemento* vetorDeElementos, AnaliseQuicksort& metricas) {
    Elemento pivo;
    *i = esquerda;
    *j = direita;
    pivo = vetorDeElementos[(*i + *j) / 2];  // define o elemento central do vetor de elementos como o pivô.
    do {
        metricas.numeroDeComparacoes++;
        while (pivo.getChave() > vetorDeElementos[*i].getChave()) {
            (*i)++;
            metricas.numeroDeComparacoes++;
        }
        metricas.numeroDeComparacoes++;
        while (pivo.getChave() < vetorDeElementos[*j].getChave()) {
            (*j)--;
            metricas.numeroDeComparacoes++;
        }
        if (*i <= *j) {
            metricas.numeroDeCopias++;
            trocaElementos(&(vetorDeElementos[*i]), &(vetorDeElementos[*j]));
            (*i)++;
            (*j)--;
        }

    } while (*i <= *j);
}

void ordenaRecursao(int esquerda, int direita, Elemento* vetorDeElementos, AnaliseQuicksort& metricas) {
    int i, j;
    particao(esquerda, direita, &i, &j, vetorDeElementos, metricas);
    if (esquerda < j) {
        ordenaRecursao(esquerda, j, vetorDeElementos, metricas);
    }
    if (i < direita) {
        ordenaRecursao(i, direita, vetorDeElementos, metricas);
    }
}

void ordenaQuickSortRecursivo(Elemento* vetorDeElementos, const int& tamanhoDoVetor, AnaliseQuicksort& metricas) {
    ordenaRecursao(0, tamanhoDoVetor - 1, vetorDeElementos, metricas);
}

void ordenaComQuicksortAPartirDaVersao(Elemento* vetorDeElementos,
                                       const int& tamanhoDoVetor,
                                       const string& versao,
                                       const string& numeroDeElementosMediana,
                                       const string& tamanhoParticao) {
    int versaoEmInteiro = stoi(versao);
    AnaliseQuicksort metricas;
    switch (versaoEmInteiro) {
        case 1:
            struct rusage resources;
            int rc;
            double utime, stime, total_time;
            ordenaQuickSortRecursivo(vetorDeElementos, tamanhoDoVetor, metricas);
            utime = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_utime.tv_usec;
            stime = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
            total_time = utime + stime;
            metricas.tempoTotalGastoPraOrdenar = total_time;
            cout << "O número de comparações para ordenar foi:" << metricas.numeroDeComparacoes << endl;
            cout << "O número de cópias para ordenar foi:" << metricas.numeroDeCopias << endl;
            cout << "O tempo total gasto para ordenar foi:" << metricas.tempoTotalGastoPraOrdenar << endl;
            break;

        default:
            break;
    }
}
