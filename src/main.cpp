#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include "../include/elemento.h"

using namespace std;

bool validaOpcoes(
    string& versao,
    string& semente,
    string& arquivoDeEntrada,
    string& arquivoDeSaida,
    string& numeroDeElementosMediana,
    string& tamanhoParticao
    ) {
        if(versao.empty() || (versao!= "1" && versao!= "2" && versao!= "3" && versao!= "4" && versao!= "5")) {
            cerr << "É necessário fornecer um argumento entre 1 e 5 para opção v. Ex: -v 1." << endl;
            return false;
        }
        if (arquivoDeSaida.empty() || arquivoDeEntrada.empty()) {
        cerr << "É necessário fornecer uma arquivo de entrada na opção 'i' e um de saída na opção 'o'" << endl;
        cerr << "Ex: -i input.txt -o output.txt." << endl;
        return false;
        }
        if (semente.empty()) {
            cerr << "É necessário fornecer um número inteiro para a opção s. Ex: -s 10." << endl;
            return false;
        }
        if (versao == "2" && numeroDeElementosMediana.empty()) {
            cerr << "A versão 2(Quicksort Mediana) exige um valor para a opção k. Ex: -k 5.";
        }
        if (versao == "3" && tamanhoParticao.empty()) {
            cerr << "A versão 3(Quicksort Seleção) exige um valor para a opção m. Ex: -m 10.";
            return false;
        }
        
        return true;
        
        
    }

int main(int argc, char* argv[]) {

     int opt;
     string versao;
     string semente;
     string arquivoDeEntrada;
     string arquivoDeSaida;
     string numeroDeElementosMediana;
     string tamanhoParticao;


  while ((opt = getopt(argc, argv, "v:s:i:o:k:m:")) != -1) {
     switch (opt) {
      case 'v':
        versao = optarg;
        break;
      case 's':
        semente = optarg;
        break;
      case 'i':
        arquivoDeEntrada = optarg;
        break;
      case 'o':
        arquivoDeSaida = optarg;
        break;
      case 'k':
        numeroDeElementosMediana = optarg;
        break;
      case 'm':
        tamanhoParticao = optarg;
        break;
      case '?':
        cerr << "Você digitou uma opção inváida."<< endl;
        return 1;
        break;
     }
  }

  bool opcaoEValida = validaOpcoes(versao, semente, arquivoDeEntrada, arquivoDeSaida, numeroDeElementosMediana, tamanhoParticao);

  if (!opcaoEValida){
      return 1;
  }
  

}