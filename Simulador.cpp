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
    // Recebe a mensagem
    string mensagem;
    cout << "Digite uma mensagem: " << endl;
    cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem) {
    int tamanhoMensagem = mensagem.length();

    // Conversão da mensagem para um array de inteiros
    // Os caracteres das palavras são representados por inteiros que correspodem ao seus códigos ASCII
    int* quadro = new int[tamanhoMensagem];
    for (int i = 0; i < tamanhoMensagem; i++) {
        quadro[i] = mensagem[i];
    }
    CamadaFisicaTransmissora(quadro);
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
