#ifndef __ELEMENTO_H__
#define __ELEMENTO_H__

class Elemento {
   public:
    Elemento();
    int getChave();

   private:
    int chave;
    char cadeiasDeCaracteres[15][200];
    double numerosReais[10];
};

#endif  // ELEMENTO_H__