#include "CamadaFisica.hpp"

#include <iostream>

using namespace std;

int* CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[]) {
    // Implementação da codificação binária
}

int* CamadaFisicaTransmissoraCodificacaoManchester(int quadro[]) {
    // Implementação da codificação Manchester
}

void CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[]) {
    // Implementação da codificação bipolar
}

void CamadaFisicaTransmissora(int quadro[]) {
    int tipoDeCodificacao = 0;
    int* fluxoBrutoDeBits;

    switch (tipoDeCodificacao) {
        case 0:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2:
            CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
            break;
    }
    // Implementação do meio de comunicação
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

void CamadaFisicaReceptora(int quadro[]) {
    int tipoDeDecodificacao = 0;
    int* fluxoBrutoDeBits;

    switch (tipoDeDecodificacao) {
        case 0:
            fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(quadro);
            break;
        case 2:
            CamadaFisicaReceptoraDecodificacaoBipolar(quadro);
            break;
    }
    // Implementação da camada de aplicação receptora
}
