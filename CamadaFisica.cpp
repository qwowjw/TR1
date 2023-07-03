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
    vector<int> quadro(tamanhoMensagem);
    for (int i = 0; i < tamanhoMensagem; i++)
    {
        quadro[i] = mensagem[i];
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
    int tamanhoQuadro = quadro.size();
    
    vector<int> fluxoBrutoDeBits(tamanhoQuadro * 8);
    for (int i = 0; i < tamanhoQuadro; i++)
    {
        int valor = quadro[i];

        for (int j = 7; j >= 0; j--)
        {
            fluxoBrutoDeBits[i * 8 + j] = valor % 2;
            valor /= 2;
        }
    }
    cout << "Mensagem codificada em binario: ";
    for (int i = 0; i < fluxoBrutoDeBits.size(); i++){
        cout << fluxoBrutoDeBits[i];
    }
    cout << endl;
    cout << endl;
    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(const vector<int> &quadro)
{
    int tamanhoQuadro = quadro.size();
    vector<int> fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);

    vector<int> fluxonovodebits;
    int bits;

    for (int i = 0; i < fluxoBrutoDeBits.size(); i++)
    {
        switch (fluxoBrutoDeBits[i])
        {
        case 0:
            fluxonovodebits.push_back(0);
            fluxonovodebits.push_back(1);
            break;
        case 1:
            fluxonovodebits.push_back(1);
            fluxonovodebits.push_back(0);
            break;
        }
    }
     cout << "Mensagem codificada em Manchester: ";
    for (int i = 0; i < fluxonovodebits.size(); i++){
        cout << fluxonovodebits[i];
    }
    cout << endl;
    return fluxonovodebits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(const vector<int> &quadro)
{
    int tamanhoQuadro = quadro.size();
    vector<int> fluxoBrutoDeBits;
    fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
    vector<int> fluxonovodebits;

    // Estado inicial para detecção de erro

    int alternado = 0;
    for (int i = 0; i < fluxoBrutoDeBits.size(); i++)
    {
        if (fluxoBrutoDeBits[i] == 1)
        {
            switch (alternado)
            {
            case 0:
                alternado = 1;
                fluxonovodebits.push_back(1);
                break;
            case 1:
                alternado -= 1;
                fluxonovodebits.push_back(-1);
                break;
            }
        }
        else
        {
            fluxonovodebits.push_back(0);
        }
    }
    cout << "Mensagem codificada em bipolar: " ;
    for (int i = 0; i < fluxonovodebits.size(); i++){
        cout << fluxonovodebits[i];
    }
    cout << endl;
    return fluxonovodebits;
}

void MeioDeComunicacao(const vector<int> &fluxoBrutoDeBits)
{
    // Simulação do meio de comunicação (neste caso, apenas exibindo os bits transmitidos)
    cout << "Fluxo bruto de bits transmitidos depois do meio de comunicacao: ";
    int tamanhoFluxo = fluxoBrutoDeBits.size();
    for (int i = 0; i < tamanhoFluxo; i++)
    {
        cout << fluxoBrutoDeBits[i];
    }
    cout << endl;

    CamadaFisicaReceptora(fluxoBrutoDeBits);
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
    int tamanhoQuadro = quadro.size();
    vector<int> fluxoBrutoDeBits;

    // Estado inicial para detecção de erro
    int estado = 0;

    vector<int> fluxonovodebits;

    for (int i = 0; i < quadro.size(); i++)
    {
        switch (quadro[i])
        {
        case 0:
            fluxonovodebits.push_back(0);
            break;
        case 1:
            fluxonovodebits.push_back(1);
            break;
        case -1:
            fluxonovodebits.push_back(1);
            break;
        }
    }

    vector<int> mensagem;
    mensagem = CamadaFisicaReceptoraDecodificacaoBinaria(fluxonovodebits);
    return mensagem;
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

    vector<int> novofluxodebits;
    novofluxodebits = CamadaFisicaReceptoraDecodificacaoBinaria(fluxoBrutoDeBits);
    return novofluxodebits;
}

vector<int> CamadaFisicaReceptoraDecodificacaoBinaria(const vector<int> &quadro)
{
    int tamanhoQuadro = quadro.size();

    vector<int> fluxoBrutoDeBits(tamanhoQuadro / 8);

    for (int i = 0; i < tamanhoQuadro; i += 8)
    {
        int valor = 0;

        for (int j = 7; j >= 0; j--)
        {
            if (quadro[i + j] != 0 && quadro[i + j] != 1)
            {
                throw runtime_error("Erro na decodificação binária");
            }

            valor += quadro[i + j] * (1 << (7 - j));
        }

        fluxoBrutoDeBits[i / 8] = valor;
    }

    return fluxoBrutoDeBits;
}

void CamadaDeAplicacaoReceptora(const vector<int> &quadro)
{
    int tamanhoQuadro = quadro.size();
    //cout << "tamanho do quadro:" << tamanhoQuadro << endl;
    // Conversão do quadro para uma string
    string mensagem(tamanhoQuadro, ' ');

    for (int i = 0; i < tamanhoQuadro; i++)
    {
        mensagem[i] = quadro[i];
    }

    AplicacaoReceptora(mensagem);
}
void AplicacaoReceptora(const string &mensagem)
{
    cout << "Mensagem Decodificada: " << mensagem << endl;
}
