#ifndef CAMADAFISICA_H
#define CAMADAFISICA_H

#include <vector>
#include <string>

void CamadaFisicaTransmissora(const std::vector<int>& quadro);
std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(const std::vector<int>& quadro);
int* CamadaFisicaTransmissoraCodificacaoManchester(int quadro[]);
void CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[]);
void CamadaFisicaReceptora(const std::vector<int>& quadro);
int* CamadaFisicaReceptoraDecodificacaoBinaria(int quadro[]);
int* CamadaFisicaReceptoraDecodificacaoManchester(int quadro[]);
void CamadaFisicaReceptoraDecodificacaoBipolar(int quadro[]);

#endif
