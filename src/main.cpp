#include <getopt.h>
#include <time.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "../include/elemento.h"
#include "../include/quicksort.h"

using namespace std;

bool validaOpcoes(const string& versao, const string& semente,
                  const string& nomeArquivoDeEntrada,
                  const string& nomeArquivoDeSaida,
                  const string& numeroDeElementosMediana,
                  const string& tamanhoParticao) {
    if (versao.empty() || (versao != "1" && versao != "2" && versao != "3" &&
                           versao != "4" && versao != "5" && versao != "6" && versao != "7")) {
        cerr << "É necessário fornecer um argumento entre 1 e 7 para opção v. Ex: "
                "-v 1."
             << endl;
        return false;
    }
    if (nomeArquivoDeSaida.empty() || nomeArquivoDeEntrada.empty()) {
        cerr << "É necessário fornecer uma arquivo de entrada na opção 'i' e um de "
                "saída na opção 'o'"
             << endl;
        cerr << "Ex: -i input.txt -o output.txt." << endl;
        return false;
    }
    if (semente.empty()) {
        cerr << "É necessário fornecer um número inteiro para a opção s. Ex: -s 10."
             << endl;
        return false;
    }
    if (versao == "2" && numeroDeElementosMediana.empty()) {
        cerr << "A versão 2(Quicksort Mediana) exige um valor para a opção k. Ex: "
                "-k 5."
             << endl;
    }
    if (versao == "3" && tamanhoParticao.empty()) {
        cerr << "A versão 3(Quicksort Seleção) exige um valor para a opção m. Ex: "
                "-m 10."
             << endl;
        ;
        return false;
    }

    return true;
}

void escreveOResultadoNoArquivoDeSaida(const string& nomeArquivoDeSaida, const AnaliseQuicksort& parametrosDaOrdenacao) {
    ofstream arquivoDeSaida;
    arquivoDeSaida.open(nomeArquivoDeSaida, ios::app);
    arquivoDeSaida << parametrosDaOrdenacao.nomeDaVersao << " -> Total de elementos ordenados: " << parametrosDaOrdenacao.numeroDeElementosOrdenados <<
     " -> Total de comparações: " << parametrosDaOrdenacao.numeroDeComparacoes <<
      " -> Total de cópias: " << parametrosDaOrdenacao.numeroDeCopias << 
      " -> Tempo total gasto: " << parametrosDaOrdenacao.tempoTotalGastoPraOrdenar << endl;
}

void defineASementeParaGerarNumeros(const int& sementeEmInteiro) {
    srand(sementeEmInteiro);
}

bool lidaComArquivoDeEntrada(const string& versao,
                             const string& semente,
                             const string& nomeArquivoDeEntrada,
                             const string& nomeArquivoDeSaida,
                             const string& numeroDeElementosMediana,
                             const string& tamanhoParticao) {
    ifstream arquivoDeEntrada;
    arquivoDeEntrada.open(nomeArquivoDeEntrada);

    if (arquivoDeEntrada.fail()) {
        cerr << "Não foi possível abrir o arquivo:" << nomeArquivoDeEntrada << endl;
        return false;
    }

    string linha;
    int posicaoDaLinha = 0;
    int quantidadeDeElementosQueSeraoCriados;

    while (!arquivoDeEntrada.eof()) {
        if (posicaoDaLinha == 0) {
            getline(arquivoDeEntrada, linha);
        
        } else {
            getline(arquivoDeEntrada, linha);
            quantidadeDeElementosQueSeraoCriados = stoi(linha);
            Elemento* elementos = new Elemento[quantidadeDeElementosQueSeraoCriados];
            cout << "Elementos sem ordenação:" << endl;
            for (int i = 0; i < quantidadeDeElementosQueSeraoCriados; i++)
            {
                cout << elementos[i].getChave() << endl;
            }

            AnaliseQuicksort* metricas = new AnaliseQuicksort();
            
            ordenaAPartirDaVersao(elementos, quantidadeDeElementosQueSeraoCriados, versao, numeroDeElementosMediana, tamanhoParticao, metricas);

            cout << "Elementos com ordenação:" << endl;
            for (int i = 0; i < quantidadeDeElementosQueSeraoCriados; i++)
            {
                cout << elementos[i].getChave() << endl;
            }
            
            escreveOResultadoNoArquivoDeSaida(nomeArquivoDeSaida, *(metricas));
            delete[] elementos;
            delete metricas;

        }
        posicaoDaLinha++;
    }
    arquivoDeEntrada.close();
    return true;
}

int main(int argc, char* argv[]) {
    int opt;
    string versao;
    string semente;
    string nomeArquivoDeEntrada;
    string nomeArquivoDeSaida;
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
                nomeArquivoDeEntrada = optarg;
                break;
            case 'o':
                nomeArquivoDeSaida = optarg;
                break;
            case 'k':
                numeroDeElementosMediana = optarg;
                break;
            case 'm':
                tamanhoParticao = optarg;
                break;
            case '?':
                cerr << "Você digitou uma opção inváida." << endl;
                return 1;
                break;
        }
    }

    bool opcaoEValida =
        validaOpcoes(versao, semente, nomeArquivoDeEntrada, nomeArquivoDeSaida,
                     numeroDeElementosMediana, tamanhoParticao);

    if (!opcaoEValida) {
        cerr << "O programa foi encerrado. Verifique os argumentos fornecidos."
             << endl;
        return 1;
    }

    int sementeEmInteiro = stoi(semente);
    defineASementeParaGerarNumeros(sementeEmInteiro);

    bool conseguiuAbrirOArquivoDeEntrada = lidaComArquivoDeEntrada(versao, semente, nomeArquivoDeEntrada, nomeArquivoDeSaida, numeroDeElementosMediana, tamanhoParticao);
    if (!conseguiuAbrirOArquivoDeEntrada) {
        cerr << "O programa foi encerrado. Verifique o arquivo de entrada " << nomeArquivoDeEntrada << endl;
        return 0;
    }
}