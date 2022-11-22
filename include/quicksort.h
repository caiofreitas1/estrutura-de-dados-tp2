#include <sys/resource.h>
#include <time.h>

#include <iostream>
#include <string>

#include "../include/elemento.h"
#include "../include/pilha.h"
#include "../include/tipoItem.h"

using namespace std;

// Estrutura que irá armazenar as métricas do algoritmo de ordenação
struct AnaliseQuicksort {
    AnaliseQuicksort() {
        this->nomeDaVersao = "";
        this->numeroDeElementosOrdenados = 0;
        this->numeroDeComparacoes = 0;
        this->numeroDeCopias = 0;
        this->tempoTotalGastoPraOrdenar = 0.0;
    }
    string nomeDaVersao;
    int numeroDeElementosOrdenados;
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
            metricas.numeroDeCopias = metricas.numeroDeCopias + 3;
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

void selecao(int esquerda, int direita, Elemento* vetorDeElementos, AnaliseQuicksort& metricas) {
    int tamanhoDoVetor = direita - esquerda + 1;
    int i, j, min;
    for (i = esquerda; i < tamanhoDoVetor - 1; i++) {
        min = i;
        for (j = i + 1; j < tamanhoDoVetor; j++) {
            metricas.numeroDeComparacoes++;
            if (vetorDeElementos[j].getChave() < vetorDeElementos[min].getChave()) {
                min = j;
            }
        }
        metricas.numeroDeCopias++;
        trocaElementos(&(vetorDeElementos[i]), &(vetorDeElementos[min]));
    }
}

void ordenaRecursaoComSelecao(int esquerda, int direita, Elemento* vetorDeElementos, AnaliseQuicksort& metricas, const int& tamanhoDaParticao) {
    if ((direita - esquerda + 1) <= tamanhoDaParticao) {
        selecao(esquerda, direita, vetorDeElementos, metricas);
    }
    int i, j;
    particao(esquerda, direita, &i, &j, vetorDeElementos, metricas);
    if (esquerda < j) {
        ordenaRecursao(esquerda, j, vetorDeElementos, metricas);
    }
    if (i < direita) {
        ordenaRecursao(i, direita, vetorDeElementos, metricas);
    }
}

void ordenaQuickSortRecursivoComSelecao(Elemento* vetorDeElementos, const int& tamanhoDoVetor, AnaliseQuicksort& metricas, const int& tamanhoDaParticao) {
    ordenaRecursaoComSelecao(0, tamanhoDoVetor - 1, vetorDeElementos, metricas, tamanhoDaParticao);
}

void ordenaQuickSortNaoRecursivoInteligente(Elemento* vetorDeElementos, const int& tamanhoDoVetor, AnaliseQuicksort& metricas) {
    Pilha pilha;
    TipoItem item;
    int esquerda, direita, i, j;
    esquerda = 0;
    direita = tamanhoDoVetor - 1;
    item.direita = direita;
    item.esquerda = esquerda;
    pilha.empilha(item);
    do {
        if (direita > esquerda) {
            particao(esquerda, direita, &i, &j, vetorDeElementos, metricas);
            if ((j - esquerda) > (direita - i)) {
                item.direita = j;
                item.esquerda = esquerda;
                pilha.empilha(item);
                esquerda = i;
            } else {
                item.esquerda = i;
                item.direita = direita;
                pilha.empilha(item);
                direita = j;
            }
        } else {
            item = pilha.desempilha();
            direita = item.direita;
            esquerda = item.esquerda;
        }

    } while (!pilha.vazia());
}

void ordenaQuickSortNaoRecursivo(Elemento* vetorDeElementos, const int& tamanhoDoVetor, AnaliseQuicksort& metricas) {
    Pilha pilha;
    TipoItem item;
    int esquerda, direita, i, j;
    esquerda = 0;
    direita = tamanhoDoVetor - 1;
    item.direita = direita;
    item.esquerda = esquerda;
    pilha.empilha(item);
    do {
        if (direita > esquerda) {
            particao(esquerda, direita, &i, &j, vetorDeElementos, metricas);
            item.direita = j;
            item.esquerda = esquerda;
            pilha.empilha(item);
            esquerda = i;
            item.esquerda = i;
            item.direita = direita;
            pilha.empilha(item);
            direita = j;

        } else {
            item = pilha.desempilha();
            direita = item.direita;
            esquerda = item.esquerda;
        }

    } while (!pilha.vazia());
}

void particaoMediana(int esquerda, int direita, int* i, int* j, Elemento* vetorDeElementos, AnaliseQuicksort& metricas, const int& numeroDeElementosMediana) {
    Elemento pivo;
    *i = esquerda;
    *j = direita;
    int tamanhoDoVetor = (*j - *i) + 1;
    if (tamanhoDoVetor < numeroDeElementosMediana) {
        pivo = vetorDeElementos[(*i + *j) / 2];  // Caso o tamanho do vetor seja menor que o número de elementos da Mediana, o pivo será o termo do meio.
    } else {
        unsigned int vetorMediana[numeroDeElementosMediana];
        unsigned int aleatorio = 0;
        unsigned int mediana = 0;
        unsigned int inteiro_auxiliar;

        for (unsigned int i = 0; i < numeroDeElementosMediana; i++) {
            aleatorio = 0 + (rand() % tamanhoDoVetor);  // gera um número aleatório entre os limites 0 e o tamanho do vetor
            vetorMediana[i] = aleatorio;
        }

        for (unsigned int i = 0; i < numeroDeElementosMediana; i++) {  // este bloco faz a ordenação do vetor de números aleatórios k
            for (unsigned int j = 0; j < numeroDeElementosMediana; j++) {
                if (vetorMediana[i] < vetorMediana[j]) {
                    inteiro_auxiliar = vetorMediana[i];
                    vetorMediana[i] = vetorMediana[j];
                    vetorMediana[j] = inteiro_auxiliar;
                }
            }
        }

        if (numeroDeElementosMediana % 2 == 0) {  // se o valor de k for par, faz a mediana como a média dos valores centrais
            mediana = (vetorMediana[numeroDeElementosMediana] + vetorMediana[numeroDeElementosMediana + 1]) / 2;
        } else {
            mediana = (vetorMediana[((numeroDeElementosMediana - 1) / 2) + 1]);
        }
        pivo = vetorDeElementos[mediana]; /* obtem o pivo x através da mediana de k valores aleatórios */
    }

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
            metricas.numeroDeCopias = metricas.numeroDeCopias + 3;
            trocaElementos(&(vetorDeElementos[*i]), &(vetorDeElementos[*j]));
            (*i)++;
            (*j)--;
        }

    } while (*i <= *j);
}

void ordenaRecursaoMediana(int esquerda, int direita, Elemento* vetorDeElementos, AnaliseQuicksort& metricas, const int& numeroDeElementosMediana) {
    int i, j;
    particaoMediana(esquerda, direita, &i, &j, vetorDeElementos, metricas, numeroDeElementosMediana);
    if (esquerda < j) {
        ordenaRecursaoMediana(esquerda, j, vetorDeElementos, metricas, numeroDeElementosMediana);
    }
    if (i < direita) {
        ordenaRecursaoMediana(i, direita, vetorDeElementos, metricas, numeroDeElementosMediana);
    }
}

void ordenaQuickSortMediana(Elemento* vetorDeElementos, const int& tamanhoDoVetor, AnaliseQuicksort& metricas, const int& numeroDeElementosMediana) {
    ordenaRecursaoMediana(0, tamanhoDoVetor - 1, vetorDeElementos, metricas, numeroDeElementosMediana);
}

void merge(Elemento* vetorDeElementos, int esquerda, int meio,
           int const direita, AnaliseQuicksort& metricas) {
    auto const tamanhoPrimeiroSubArray = meio - esquerda + 1;
    auto const tamanhoSegundoSubArray = direita - meio;

    // Create temp arrays
    auto *arrayEsquerda = new Elemento[tamanhoPrimeiroSubArray],
         *arrayDireita = new Elemento[tamanhoSegundoSubArray];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < tamanhoPrimeiroSubArray; i++) {
        arrayEsquerda[i] = vetorDeElementos[esquerda + i];
    }
    for (auto j = 0; j < tamanhoSegundoSubArray; j++) {
        arrayDireita[j] = vetorDeElementos[meio + 1 + j];
    }

    auto indicePrimeiroSubArray = 0,   // Initial index of first sub-array
        indiceSegundoSubArray = 0;     // Initial index of second sub-array
    int indiceMergedArray = esquerda;  // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
    while (indicePrimeiroSubArray < tamanhoPrimeiroSubArray && indiceSegundoSubArray < tamanhoSegundoSubArray) {
        metricas.numeroDeComparacoes++;
        if (arrayEsquerda[indicePrimeiroSubArray].getChave() <= arrayDireita[indiceSegundoSubArray].getChave()) {
            metricas.numeroDeCopias++;
            vetorDeElementos[indiceMergedArray] = arrayEsquerda[indicePrimeiroSubArray];
            indicePrimeiroSubArray++;
        } else {
            metricas.numeroDeCopias++;
            vetorDeElementos[indiceMergedArray] = arrayDireita[indiceSegundoSubArray];
            indiceSegundoSubArray++;
        }
        indiceMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indicePrimeiroSubArray < tamanhoPrimeiroSubArray) {
        vetorDeElementos[indiceMergedArray] = arrayEsquerda[indicePrimeiroSubArray];
        indicePrimeiroSubArray++;
        indiceMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indiceSegundoSubArray < tamanhoSegundoSubArray) {
        vetorDeElementos[indiceMergedArray] = arrayDireita[indiceSegundoSubArray];
        indiceSegundoSubArray++;
        indiceMergedArray++;
    }
    delete[] arrayEsquerda;
    delete[] arrayDireita;
}

void ordenaMergeSortRecursao(Elemento* vetorDeElementos, int esquerda, int direita, AnaliseQuicksort& metricas) {
    if (esquerda >= direita) {
        return;
    }
    auto meio = (esquerda + direita) / 2;
    ordenaMergeSortRecursao(vetorDeElementos, esquerda, meio, metricas);
    ordenaMergeSortRecursao(vetorDeElementos, meio + 1, direita, metricas);
    merge(vetorDeElementos, esquerda, meio, direita, metricas);
}

void mergeSort(Elemento* vetorDeElementos, const int& tamanhoDoVetor, AnaliseQuicksort& metricas) {
    ordenaMergeSortRecursao(vetorDeElementos, 0, tamanhoDoVetor - 1, metricas);
}

void refaz(Elemento* vetorDeElementos, int esquerda, int direita) {
    int i, j;
    Elemento x;
    i = esquerda;
    j = (i * 2);
    x = vetorDeElementos[i];
    while (j <= direita) {
        if(j < direita) {
            if(vetorDeElementos[j].getChave() < vetorDeElementos[j+1].getChave()) {
                j++;
            }
        }
        if(x.getChave() >= vetorDeElementos[j].getChave()) {
            break;
        }
        vetorDeElementos[i] = vetorDeElementos[j];
        i = j;
        j = i *2;
    }
    vetorDeElementos[i] = x;

}

void constroiHeap(Elemento* vetorDeElementos, int tamanho) {
    int esquerda;
    esquerda = tamanho/2 + 1;
    while (esquerda > 0) {
        esquerda--;
        refaz(vetorDeElementos, esquerda, tamanho);
    }
}

void heapSort(Elemento* vetorDeElementos, const int& tamanhoDoVetor, AnaliseQuicksort& metricas) {
    int esquerda, direita;
    Elemento auxiliar;
    constroiHeap(vetorDeElementos, tamanhoDoVetor);
    esquerda = 0;
    direita = tamanhoDoVetor -1;
    while (direita > 0) {
        auxiliar = vetorDeElementos[0];
        vetorDeElementos[0] = vetorDeElementos[direita];
        vetorDeElementos[direita] = auxiliar;
        direita --;
        refaz(vetorDeElementos, esquerda, direita);
    }
}

void ordenaAPartirDaVersao(Elemento* vetorDeElementos,
                           const int& tamanhoDoVetor,
                           const string& versao,
                           const string& numeroDeElementosMediana,
                           const string& tamanhoParticao,
                           AnaliseQuicksort* metricas) {
    int versaoEmInteiro = stoi(versao);

    int tamanhoParticaoInteiro;
    int numerosDeElementoMedianaInteiro;
    struct timespec inicio, fim;
    long segundos, nanosegundos;
    switch (versaoEmInteiro) {
        case 1:
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &inicio);
            ordenaQuickSortRecursivo(vetorDeElementos, tamanhoDoVetor, *metricas);

            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fim);
            segundos = fim.tv_sec - inicio.tv_sec;
            nanosegundos = fim.tv_nsec - inicio.tv_nsec;

            (*metricas).tempoTotalGastoPraOrdenar = segundos + nanosegundos * 1e-9;
            (*metricas).nomeDaVersao = "Quicksort recursivo";
            (*metricas).numeroDeElementosOrdenados = tamanhoDoVetor;
            break;
        case 2:
            numerosDeElementoMedianaInteiro = stoi(numeroDeElementosMediana);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &inicio);

            ordenaQuickSortMediana(vetorDeElementos, tamanhoDoVetor, *metricas, numerosDeElementoMedianaInteiro);

            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fim);
            segundos = fim.tv_sec - inicio.tv_sec;
            nanosegundos = fim.tv_nsec - inicio.tv_nsec;

            (*metricas).tempoTotalGastoPraOrdenar = segundos + nanosegundos * 1e-9;
            (*metricas).nomeDaVersao = "Quicksort recursivo mediana";
            (*metricas).numeroDeElementosOrdenados = tamanhoDoVetor;
            break;
        case 3:
            tamanhoParticaoInteiro = stoi(tamanhoParticao);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &inicio);
            ordenaQuickSortRecursivoComSelecao(vetorDeElementos, tamanhoDoVetor, *metricas, tamanhoParticaoInteiro);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fim);
            segundos = fim.tv_sec - inicio.tv_sec;
            nanosegundos = fim.tv_nsec - inicio.tv_nsec;
            (*metricas).tempoTotalGastoPraOrdenar = segundos + nanosegundos * 1e-9;
            (*metricas).nomeDaVersao = "Quicksort recursivo com seleção:";
            (*metricas).numeroDeElementosOrdenados = tamanhoDoVetor;
            break;
        case 4:
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &inicio);

            ordenaQuickSortNaoRecursivo(vetorDeElementos, tamanhoDoVetor, *metricas);

            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fim);
            segundos = fim.tv_sec - inicio.tv_sec;
            nanosegundos = fim.tv_nsec - inicio.tv_nsec;

            (*metricas).tempoTotalGastoPraOrdenar = segundos + nanosegundos * 1e-9;
            (*metricas).nomeDaVersao = "Quicksort não recursivo:";
            (*metricas).numeroDeElementosOrdenados = tamanhoDoVetor;
            break;
        case 5:
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &inicio);
            ordenaQuickSortNaoRecursivoInteligente(vetorDeElementos, tamanhoDoVetor, *metricas);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fim);
            segundos = fim.tv_sec - inicio.tv_sec;
            nanosegundos = fim.tv_nsec - inicio.tv_nsec;
            (*metricas).tempoTotalGastoPraOrdenar = segundos + nanosegundos * 1e-9;
            (*metricas).nomeDaVersao = "Quicksort não recursivo inteligente:";
            (*metricas).numeroDeElementosOrdenados = tamanhoDoVetor;
            break;
        case 6:
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &inicio);
            mergeSort(vetorDeElementos, tamanhoDoVetor, *metricas);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fim);
            segundos = fim.tv_sec - inicio.tv_sec;
            nanosegundos = fim.tv_nsec - inicio.tv_nsec;
            (*metricas).tempoTotalGastoPraOrdenar = segundos + nanosegundos * 1e-9;
            (*metricas).nomeDaVersao = "Mergesort:";
            (*metricas).numeroDeElementosOrdenados = tamanhoDoVetor;
            break;
        case 7:
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &inicio);
            heapSort(vetorDeElementos, tamanhoDoVetor, *metricas);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fim);
            segundos = fim.tv_sec - inicio.tv_sec;
            nanosegundos = fim.tv_nsec - inicio.tv_nsec;
            (*metricas).tempoTotalGastoPraOrdenar = segundos + nanosegundos * 1e-9;
            (*metricas).nomeDaVersao = "HeapSort:";
            (*metricas).numeroDeElementosOrdenados = tamanhoDoVetor;
            break;

        default:
            break;
    }
}