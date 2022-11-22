#ifndef __PILHA_H__
#define __PILHA_H__

#include "../include/tipoItem.h"

class TipoCelula {
   public:
    TipoCelula();

   private:
    TipoItem item;
    TipoCelula* prox;
    friend class Pilha;
};

class Pilha {
   public:
    Pilha();
    ~Pilha();
    int getTamanho() { return tamanho; };
    bool vazia() { return tamanho == 0; };
    void empilha(TipoItem item);
    TipoItem desempilha();
    void limpa();

   private:
    int tamanho;
    TipoCelula* topo;
};

#endif  // PILHA_H__