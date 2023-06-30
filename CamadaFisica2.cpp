#include "CamadaFisica.h"

#include <iostream>

using namespace std;

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(const vector<int>& quadro) {
    int tamanhoQuadro = quadro.size();

    vector<int> fluxoBrutoDeBits(tamanhoQuadro * 8);

    for (int i = 0; i < tamanhoQuadro; i++) {
        int valor = quadro[i];

        for (int j = 7; j >= 0; j--) {
            fluxoBrutoDeBits[i * 8 + j] = valor % 2;
            valor /= 2;
        }
    }

    return fluxoBrutoDeBits;
}

int* CamadaFisicaTransmissoraCodificacaoManchester(int quadro[]) {
    // Implementação da codificação Manchester
}

void CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[]) {
    // Implementação da codificação bipolar
}

void CamadaFisicaTransmissora(const vector<int>& quadro) {
    int tipoDeCodificacao = 0;
    vector<int> fluxoBrutoDeBits;

    // Armazena o valor de retorno conforme a Codificação
    switch (tipoDeCodificacao) {
        case 0:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1:
            //fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2:
            //CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
            break;
    }
    MeioDeComunicacao(fluxoBrutoDeBits);
}

int* CamadaFisicaReceptoraDecodificacaoBinaria(int quadro[]) {
    // Implementação da decodificação binária
}

int* CamadaFisicaReceptoraDecodificacaoManchester(int quadro[]) {
    // Implementação da decodificação Manchester
}

void CamadaFisicaReceptoraDecodificacaoBipolar(int quadro[]) {
    // Implementação da decodificação bipolar
}

void CamadaFisicaReceptora(const vector<int>& quadro) {
    int tipoDeDecodificacao = 0;
    int* fluxoBrutoDeBits;

    switch (tipoDeDecodificacao) {
        case 0:
            fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBinaria(quadro.data());
            break;
        case 1:
            //fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(quadro.data());
            break;
        case 2:
            //CamadaFisicaReceptoraDecodificacaoBipolar(quadro.data());
            break;
    }

    vector<int> fluxoBrutoDeBitsVector(fluxoBrutoDeBits, fluxoBrutoDeBits + quadro.size());
    CamadaDeAplicacaoReceptora(fluxoBrutoDeBitsVector);
}
