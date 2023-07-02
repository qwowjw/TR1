#ifndef CAMADA_FISICA_H
#define CAMADA_FISICA_H
#include <string>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>
#include <bitset>
#include <vector>
using namespace std;

void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(string mensagem);
void CamadaFisicaTransmissora(const vector<int>& quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(const vector<int>& quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoManchester(const vector<int>& quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(const vector<int>& quadro);
void MeioDeComunicacao(const vector<int>& fluxoBrutoDeBits);
void CamadaFisicaReceptora(const vector<int>& quadro);
vector<int> CamadaFisicaReceptoraDecodificacaoBipolar(const vector<int>& quadro);
vector<int> CamadaFisicaReceptoraDecodificacaoManchester(const vector<int>& quadro);
vector<int> CamadaFisicaReceptoraDecodificacaoBinaria(const vector<int>& quadro);
void CamadaDeAplicacaoReceptora(const vector<int>& quadro);
void AplicacaoReceptora(const string& mensagem);
#endif  // CAMADA_FISICA_H
