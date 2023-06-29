#include <iostream>
#include <string>

#include "CamadaFisica.hpp"

using namespace std;

void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(string mensagem);
void CamadaDeAplicacaoReceptora(int quadro[]);
void AplicacaoReceptora(string mensagem);
void MeioDeComunicacao(int fluxoBrutoDeBits[]);

int main() {
    AplicacaoTransmissora();
    return 0;
}

void AplicacaoTransmissora() {
    string mensagem;
    cout << "Digite uma mensagem: " << endl;
    cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem) {
    CamadaFisicaTransmissora((int*)mensagem.c_str());
}

void CamadaDeAplicacaoReceptora(int quadro[]) {
    AplicacaoReceptora((char*)quadro);
}

void AplicacaoReceptora(string mensagem) {
    cout << "A mensagem recebida foi: " << mensagem << endl;
}

void MeioDeComunicacao(int fluxoBrutoDeBits[]) {
    int* fluxoBrutoDeBitsPontoA;
    int* fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    while (fluxoBrutoDeBitsPontoB.length != fluxoBrutoDeBitsPontoA.length) {
        // Implementação do meio de comunicação
    }

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}
