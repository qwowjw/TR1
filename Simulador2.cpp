#include <iostream>
#include <string>
#include "CamadaFisica.h"

using namespace std;

void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(const string& mensagem);
void CamadaDeAplicacaoReceptora(const vector<int>& quadro);
void AplicacaoReceptora(const string& mensagem);
vector<int> MeioDeComunicacao(vector<int>& fluxoBrutoDeBits);

int main() {
    AplicacaoTransmissora();
    return 0;
}

void AplicacaoTransmissora() {
    // Recebe a mensagem
    string mensagem;
    cout << "Digite uma mensagem: " << endl;
    getline(cin, mensagem);

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(const string& mensagem) {
    int tamanhoMensagem = mensagem.length();

    // Conversão da mensagem para um vetor de inteiros
    // Os caracteres das palavras são representados por inteiros que correspondem aos seus códigos ASCII
    vector<int> quadro(tamanhoMensagem);
    for (int i = 0; i < tamanhoMensagem; i++) {
        quadro[i] = mensagem[i];
    }
    CamadaFisicaTransmissora(quadro);
}

void CamadaDeAplicacaoReceptora(const vector<int>& quadro) {
    // Processar o quadro recebido (não implementado neste código)
    string mensagem;
    for (int i = 0; i < quadro.size(); i++) {
        mensagem += static_cast<char>(quadro[i]);
    }
    AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(const string& mensagem) {
    cout << "A mensagem recebida foi: " << mensagem << endl;
}

void MeioDeComunicacao(vector<int>& fluxoBrutoDeBits) {
    vector<int> fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
    vector<int> fluxoBrutoDeBitsPontoB;

    while (fluxoBrutoDeBitsPontoB.size() != fluxoBrutoDeBitsPontoA.size()) {
        // Implementação do meio de comunicação
    }

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}
