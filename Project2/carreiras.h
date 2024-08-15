/* 
 * Ficheiro: carreiras.h
 * Autor: Raquel Rodrigues
 * Descricao: Ficheiro de cabeçalho com funções que tratam de carreiras.
 */

#ifndef _CARREIRAS_H_
#define _CARREIRAS_H_

#include "definicoes.h"
#include "ligacoes.h"

/* Protótipos. */

lstCarreiras* mk_lstCarreiras();
void cria_carreira(lstCarreiras *l, char *nome_c);
void atualiza_carreira(Carreira *carreira, double custo, double duracao,
    int soma);
void remove_carreira_paragem(Paragem *paragem, Carreira *carreira);
void remove_carreira_ligacoes(lstLigacoes *lLigacoes, Carreira *carreira);
void remove_carreira(lstCarreiras *l, char *nome_c);
void  free_lstCarreiras(lstCarreiras *l);
nodeCarreira *pesquisa_carreira(lstCarreiras *l, char *nome_c);
nodeLigacao *pesquisa_paragem_carreira(Carreira *carreira,
    nodeParagem *pParagem);
int carreira_vazia(nodeCarreira *pCarreira);
void lista_carreiras(lstCarreiras *l);
void escreve_carreira(nodeCarreira *pCarreira);
void lista_paragens_carreira(nodeCarreira *pCarreira, int inverso);

#endif