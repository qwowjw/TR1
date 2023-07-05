#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "CamadaFisica.h"

using namespace std;

int TipoDeCodificacao;

void AplicacaoTransmissora()
{  
    // Recebe a mensagem
    string mensagem;
    cout << "Digite uma mensagem: ";
    getline(cin, mensagem);

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem)
{
    int tamanhoMensagem = mensagem.length();

    // Conversão da mensagem para um vetor de inteiros representando os bits
    vector<int> quadro;
    for (int i = 0; i < tamanhoMensagem; i++)
    {   
        // Conversão da mensagem para ASCII
        int valorASCII = mensagem[i];

        // Conversão do valor ASCII para representaçáo binária
        for (int j = 7; j >= 0; j--){   // Percorre do bit mais significativo para o menos

            int bit = (valorASCII >> j) & 1;  // Desloca o valor ASCII para a direita por j bits e realiza uma operação AND bit a bit com 1
            quadro.push_back(bit);
        }
    }    
    cout << "Mensagem da camada de aplicacao transmissora: " << mensagem << endl;
    CamadaFisicaTransmissora(quadro);
}

// Camada onde é escolhida a decodificação, recebe a mensagem codificada e transmite ao meio de comunicação
void CamadaFisicaTransmissora(const vector<int> &quadro)
{
    cout << "ESCOLHA O TIPO DE CODIFICACAO:" << endl;
    cout << "(0) - BINARIA" << endl;
    cout << "(1) - MANCHESTER" <<  endl;
    cout << "(2) - BIPOLAR" << endl;

    
    cin >> TipoDeCodificacao;

    vector<int> fluxoBrutoDeBits;
    switch (TipoDeCodificacao)
    {
    case 0:
        fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
        break;
    case 1:
        fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
        break;
    case 2:
        fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
        break;
    default:
        throw runtime_error("Tipo de codificação inválido");
    }
    MeioDeComunicacao(fluxoBrutoDeBits);
}

// Função da decodificação binária. Obs: É feita e reaproveitada da CamadaDeAplicacaoTransmissora
vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(const vector<int> &quadro)
{
    return quadro;
}

// Função da decodificação Manchester
vector<int> CamadaFisicaTransmissoraCodificacaoManchester(const vector<int> &quadro)
{
    vector<int> fluxoBrutoDeBits;
    int bits;

    for (int i = 0; i < quadro.size(); i++)
    {
        switch (quadro[i])
        {
        case 0:
            fluxoBrutoDeBits.push_back(0);
            fluxoBrutoDeBits.push_back(1);
            break;
        case 1:
            fluxoBrutoDeBits.push_back(1);
            fluxoBrutoDeBits.push_back(0);
            break;
        }
    }
     cout << "Mensagem codificada em Manchester: ";
    for (int i = 0; i < fluxoBrutoDeBits.size(); i++){
        cout << fluxoBrutoDeBits[i];
    }
    cout << endl;
    return fluxoBrutoDeBits;
}

// Função da decodificação Manchester
vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(const vector<int> &quadro)
{
    vector<int> fluxoBrutoDeBits;

    int alternado = 0; // Variável que indicará o sentido do pulso quando o bit for 1 (flag)
    for (int i = 0; i < quadro.size(); i++)
    {   
        // Verifica se o bit é 0 ou 1
        if (quadro[i] == 1)
        {   
            // Verifica se o bit 1 anterior foi 1 ou -1
            switch (alternado)
            {
            case 0:
                alternado = 1;
                fluxoBrutoDeBits.push_back(1);
                break;
            case 1:
                alternado -= 1;
                fluxoBrutoDeBits.push_back(-1);
                break;
            }
        }
        else
        {
            fluxoBrutoDeBits.push_back(0);
        }
    }
    cout << "Mensagem codificada em bipolar: " ;
    for (int i = 0; i < fluxoBrutoDeBits.size(); i++){
        cout << fluxoBrutoDeBits[i];
    }
    cout << endl;
    return fluxoBrutoDeBits;
}

void MeioDeComunicacao(const vector<int> &fluxoBrutoDeBits)
{    
    cout << "Fluxo bruto de bits transmitidos depois do meio de comunicacao: ";
    int tamanhoFluxo = fluxoBrutoDeBits.size();
    for (int i = 0; i < tamanhoFluxo; i++)
    {
        cout << fluxoBrutoDeBits[i];
    }
    cout << endl;

  vector<int> fluxoBrutoDeBitsA, fluxoBrutoDeBitsB;
  fluxoBrutoDeBitsA = fluxoBrutoDeBits;

  for (int i = 0; i < fluxoBrutoDeBitsA.size(); i++){
    fluxoBrutoDeBitsB.push_back(fluxoBrutoDeBitsA[i]);
  }

    CamadaFisicaReceptora(fluxoBrutoDeBitsB);
}

void CamadaFisicaReceptora(const vector<int> &quadro){
    
    vector<int> fluxoBrutoDeBits;
    switch (TipoDeCodificacao)
    {
    case 0:
        fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBinaria(quadro);
        break;
    case 1:
        fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(quadro);
        break;
    case 2:
        fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBipolar(quadro);
        break;
    default:
        throw runtime_error("Tipo de codificação inválido");
    }

    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
};

vector<int> CamadaFisicaReceptoraDecodificacaoBipolar(const vector<int> &quadro)
{
    vector<int> fluxoBrutoDeBits;

    for (int i = 0; i < quadro.size(); i++)
    {
        switch (quadro[i])
        {
        case 0:
            fluxoBrutoDeBits.push_back(0);
            break;
        case 1:
            fluxoBrutoDeBits.push_back(1);
            break;
        case -1:
            fluxoBrutoDeBits.push_back(1);
            break;
        }
    }

    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraDecodificacaoManchester(const vector<int> &quadro)
{
    int tamanhoQuadro = quadro.size();

    vector<int> fluxoBrutoDeBits(tamanhoQuadro / 2);

    for (int i = 0; i < tamanhoQuadro; i += 2)
    {
        int bit1 = quadro[i];
        int bit2 = quadro[i + 1];

        // Decodificação Manchester
        if (bit1 == 0 && bit2 == 1)
        {
            fluxoBrutoDeBits[i / 2] = 0;
        }
        else if (bit1 == 1 && bit2 == 0)
        {
            fluxoBrutoDeBits[i / 2] = 1;
        }
        else
        {
            throw runtime_error("Erro na decodificação Manchester");
        }
    }

    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraDecodificacaoBinaria(const vector<int> &quadro)
{     
    return quadro;
}

void CamadaDeAplicacaoReceptora(const vector<int> &quadro)
{
    int tamanhoQuadro = quadro.size();

    // Decodificação binária
    vector<int> fluxoBrutoDeBits(tamanhoQuadro / 8);

    for (int i = 0; i < tamanhoQuadro; i += 8)
    {
        int valor = 0;

        // quadro[i + j] representa o bit atual que está sendo considerado no loop. Pode ser 0 ou 1, pois é o resultado da decodificação binária de cada bit do quadro.
        for (int j = 7; j >= 0; j--)
        {   
        // (1 << (7 - j)) é uma operação de deslocamento à esquerda (bitwise left shift). O número 1 é deslocado para a esquerda pela quantidade (7 - j) de vezes
            valor += quadro[i + j] * (1 << (7 - j));
        //A expressão quadro[i + j] * (1 << (7 - j)) multiplica o valor do bit (0 ou 1) pelo peso correspondente.
        //Se o bit for 0, o peso não será adicionado ao valor. Se o bit for 1, o peso será adicionado ao valor.
        }

        fluxoBrutoDeBits[i / 8] = valor;
    }

    string mensagem;
    mensagem.reserve(fluxoBrutoDeBits.size());  // usada para reservar espaço antecipadamente na memória a fim de evitar realocações frequentes

    for (int i = 0; i < fluxoBrutoDeBits.size(); i++)
    {
        mensagem += static_cast<char>(fluxoBrutoDeBits[i]); // operador de conversão para o tipo char
    }

    AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(const string &mensagem)
{
    cout << "Mensagem Decodificada: " << mensagem << endl;
}
