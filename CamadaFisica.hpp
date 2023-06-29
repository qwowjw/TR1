#ifndef CAMADAFISICA_HPP
#define CAMADAFISICA_HPP

void CamadaFisicaTransmissora(int quadro[]);
int* CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[]);
int* CamadaFisicaTransmissoraCodificacaoManchester(int quadro[]);
void CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[]);
void CamadaFisicaReceptora(int quadro[]);
int* CamadaFisicaReceptoraDecodificacaoBinaria(int quadro[]);
int* CamadaFisicaReceptoraDecodificacaoManchester(int quadro[]);
void CamadaFisicaReceptoraDecodificacaoBipolar(int quadro[]);

#endif
