#include "CamadaFisica.hpp"

#include <iostream>

using namespace std;

int* CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[]) {
    /* A função sizeof retorna o tamanho em bytes de uma expressao.
    Neste caso, ele divide o tamanho total pelo tamanho de um elemento,
    obtendo o número de elementos presentes no quadro.
    */
    int tamanhoQuadro = sizeof(quadro) / sizeof(quadro[0]);

    int* fluxoBrutoDeBits = new int[tamanhoQuadro * 8]; // *8 pois transforma de byte pra bit.

    for (int i = 0; i < tamanhoQuadro; i++) {
        int valor = quadro[i]; // Itera cada elemento do quadro.

        for (int j = 7; j >= 0; j--) { // De 7 a 0 representando 8 bits.
            fluxoBrutoDeBits[i * 8 + j] = valor % 2; // Extraindo o ultimo bit do valor atual
            valor /= 2; // Deslocando para a direita, descartando o bit mais a direita (já processado)
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

void CamadaFisicaTransmissora(int quadro[]) {
    int tipoDeCodificacao = 0;
    int* fluxoBrutoDeBits;

    // Armazena o valor de retorno conforme a Codificação
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
