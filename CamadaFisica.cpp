#include <string>
#include <vector>
#include <stdexcept>
#include "CamadaFisica.h"

void AplicacaoTransmissora() {
    // Recebe a mensagem
    string mensagem;
    cout << "Digite uma mensagem: ";
    getline(cin, mensagem);

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem) {
    int tamanhoMensagem = mensagem.length();

    // Conversão da mensagem para um vetor de inteiros
    vector<int> quadro(tamanhoMensagem);
    for (int i = 0; i < tamanhoMensagem; i++) {
        quadro[i] = mensagem[i];
        cout << "letra: " << mensagem[i] << ", quadro: " << quadro[i] << endl;
    }
    cout << endl;
    CamadaFisicaTransmissora(quadro);
}

void CamadaFisicaTransmissora(const vector<int>& quadro) {
    vector<int> fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
    fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(fluxoBrutoDeBits);
    fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(fluxoBrutoDeBits);
    MeioDeComunicacao(fluxoBrutoDeBits);
}

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

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(const vector<int>& quadro) {
    int tamanhoQuadro = quadro.size();

    vector<int> fluxoBrutoDeBits(tamanhoQuadro * 2);

    for (int i = 0; i < tamanhoQuadro; i++) {
        int bit = quadro[i];

        // Codificação Manchester
        fluxoBrutoDeBits[i * 2] = bit;
        fluxoBrutoDeBits[i * 2 + 1] = (bit == 0) ? 1 : 0;
    }

    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(const vector<int>& quadro) {
    int tamanhoQuadro = quadro.size();

    vector<int> fluxoBrutoDeBits(tamanhoQuadro * 2);

    // Estado inicial para detecção de erro
    int estado = 0;

    for (int i = 0; i < tamanhoQuadro; i++) {
        int bit = quadro[i];

        // Codificação bipolar
        if (bit == 0) {
            fluxoBrutoDeBits[i * 2] = estado;
            fluxoBrutoDeBits[i * 2 + 1] = estado;
        } else {
            fluxoBrutoDeBits[i * 2] = estado;
            fluxoBrutoDeBits[i * 2 + 1] = (estado == 0) ? 1 : 0;
            estado = (estado == 0) ? 1 : 0;
        }
    }

    return fluxoBrutoDeBits;
}

void MeioDeComunicacao(const vector<int>& fluxoBrutoDeBits) {
    // Simulação do meio de comunicação (neste caso, apenas exibindo os bits transmitidos)
    cout << "Fluxo bruto de bits transmitidos depois do meio de comunicacao: ";
    int tamanhoFluxo = fluxoBrutoDeBits.size();
    for (int i = 0; i < tamanhoFluxo; i++) {
        cout << fluxoBrutoDeBits[i];
    }
    cout << endl;

    CamadaFisicaReceptora(fluxoBrutoDeBits);
}

void CamadaFisicaReceptora(const vector<int>& quadro) {
    vector<int> fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBipolar(quadro);
    fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(fluxoBrutoDeBits);
    fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBinaria(fluxoBrutoDeBits);
    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}

vector<int> CamadaFisicaReceptoraDecodificacaoBipolar(const vector<int>& quadro) {
    int tamanhoQuadro = quadro.size();

    vector<int> fluxoBrutoDeBits(tamanhoQuadro / 2);

    // Estado inicial para detecção de erro
    int estado = 0;

    for (int i = 0; i < tamanhoQuadro; i += 2) {
        int bit1 = quadro[i];
        int bit2 = quadro[i + 1];

        // Decodificação bipolar
        if (bit1 == estado && bit2 == estado) {
            fluxoBrutoDeBits[i / 2] = 0;
        } else if (bit1 == estado && bit2 != estado) {
            fluxoBrutoDeBits[i / 2] = 1;
            estado = (estado == 0) ? 1 : 0;
        } else {
            throw runtime_error("Erro na decodificação bipolar");
        }
    }

    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraDecodificacaoManchester(const vector<int>& quadro) {
    int tamanhoQuadro = quadro.size();

    vector<int> fluxoBrutoDeBits(tamanhoQuadro / 2);

    for (int i = 0; i < tamanhoQuadro; i += 2) {
        int bit1 = quadro[i];
        int bit2 = quadro[i + 1];

        // Decodificação Manchester
        if (bit1 == 0 && bit2 == 1) {
            fluxoBrutoDeBits[i / 2] = 0;
        } else if (bit1 == 1 && bit2 == 0) {
            fluxoBrutoDeBits[i / 2] = 1;
        } else {
            throw runtime_error("Erro na decodificação Manchester");
        }
    }

    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraDecodificacaoBinaria(const vector<int>& quadro) {
    int tamanhoQuadro = quadro.size();

    vector<int> fluxoBrutoDeBits(tamanhoQuadro / 8);

    for (int i = 0; i < tamanhoQuadro; i += 8) {
        int valor = 0;

        for (int j = 7; j >= 0; j--) {
            if (quadro[i + j] != 0 && quadro[i + j] != 1) {
                throw runtime_error("Erro na decodificação binária");
            }

            valor += quadro[i + j] * (1 << (7 - j));
        }

        fluxoBrutoDeBits[i / 8] = valor;
    }

    return fluxoBrutoDeBits;
}

void CamadaDeAplicacaoReceptora(const vector<int>& quadro) {
    int tamanhoQuadro = quadro.size();
    cout << "tamanhoQuadro:" << tamanhoQuadro << endl;
    // Conversão do quadro para uma string
    string mensagem(tamanhoQuadro, ' ');

    /*for (int i = 0; i < quadro.size(); i++) {
        std::cout << quadro[i] << " ";
    }*/
    for (int i = 0; i < tamanhoQuadro; i++) {
        mensagem[i] = quadro[i];
    }

    AplicacaoReceptora(mensagem);

}
void AplicacaoReceptora(const string& mensagem) {
    cout << "Mensagem recebida: " << mensagem << endl;
}
