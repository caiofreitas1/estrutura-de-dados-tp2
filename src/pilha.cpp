#include "../include/pilha.h"

TipoCelula::TipoCelula() {
    item.direita = -1;
    item.esquerda = -1;
    this->prox = nullptr;
}

Pilha::Pilha() {
    tamanho = 0;
    topo = nullptr;
}

Pilha::~Pilha() {
    limpa();
}
void Pilha::empilha(TipoItem item) {
    TipoCelula *nova;
    nova = new TipoCelula();
    nova->item = item;
    nova->prox = topo;
    topo = nova;
    tamanho++;
};

TipoItem Pilha::desempilha() {
    TipoItem aux;
    TipoCelula *p;
    if (this->getTamanho() != 0) {
        aux = topo->item;
        p = topo;
        topo = topo->prox;
        delete p;
        tamanho--;
        return aux;
    } else {
        throw "Pilha vazia";
    }
}

void Pilha::limpa() {
    while (!vazia())
        desempilha();
}
