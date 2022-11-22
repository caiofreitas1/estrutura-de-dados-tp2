#include "../include/elemento.h"
#include <time.h>
#include <cstdlib>

Elemento::Elemento() {
    this->chave = rand();
}

int Elemento::getChave() {
    return this->chave;
}

void Elemento::setChave(int chave) {
    this->chave = chave;
}
