#include <string>
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

    // Conversão da mensagem para um vetor de inteiros
    vector<int> quadro;
    for (int i = 0; i < tamanhoMensagem; i++)
    {
        int valorASCII = mensagem[i];

        // Conversão do valor ASCII para representação binária
        for (int j = 7; j >= 0; j--)
        {
            int bit = (valorASCII >> j) & 1; // Operação AND bit a bit entre o resultado do deslocamento à direita e o valor 1. 
            quadro.push_back(bit);
        }
    }
    cout << "Mensagem da camada de aplicacao transmissora: " << mensagem << endl;
    CamadaFisicaTransmissora(quadro);
}


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

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(const vector<int> &quadro)
{
    return quadro;
}

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

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(const vector<int> &quadro)
{

    vector<int> fluxoBrutoDeBits;

    // Estado inicial para detecção de erro

    int flat = 0;
    for (int i = 0; i < quadro.size(); i++)
    {
        if (quadro[i] == 1)
        {
            switch (flat)
            {
            case 0:
                flat = 1;
                fluxoBrutoDeBits.push_back(1);
                break;
            case 1:
                flat -= 1;
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

void CamadaDeAplicacaoReceptora(vector<int> quadro)
{
  string mensagem;

  // Percorre o vetor quadro em incrementos de 8
  for (int i = 0; i < quadro.size(); i += 8)
  {
    // Inicializa o caractere atual como vazio
    char c = '\0';

    // Percorre os 8 bits do caractere
    for (int j = 7; j >= 0; j--)
    {
      // Realiza o deslocamento à esquerda do caractere e faz um OR bit a bit com o bit do quadro
      c <<= 1;
      c |= quadro[i + j];
    }

    // Adiciona o caractere reconstruído à mensagem
    mensagem.push_back(c);
  }

  // Chama a função AplicacaoReceptora com a mensagem reconstruída
  AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(const string &mensagem)
{
    cout << "Mensagem Decodificada: " << mensagem << endl;
}
