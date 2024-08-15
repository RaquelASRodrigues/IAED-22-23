/* 
 * Ficheiro: ligacoes.h
 * Autor: Raquel Rodrigues
 * Descricao: Ficheiro de cabeçalho com funções que tratam de ligações.
 */

#ifndef _LIGACOES_H_
#define _LIGACOES_H_

#include "definicoes.h"
#include "parsing.h"
#include "paragens.h"
#include "carreiras.h"

/* Protótipos. */

void leNomesComando(char **nome_c, char **nome_origem, char **nome_destino);
lstLigacoes* mk_lstLigacoes();
nodeLigacao *cria_ligacao(nodeCarreira *pCarreira, nodeParagem *pOrigem,
    nodeParagem *pDestino, double custo, double duracao);
int extremo_esq(nodeParagem *pParagem, Carreira *carreira);
int extremo_drt(nodeParagem *pParagem, Carreira *carreira);
void acrescenta_ligacao_fim(nodeCarreira *pCarreira, nodeLigacao *lNode);
void acrescenta_ligacao_inicio(nodeCarreira *pCarreira, nodeLigacao *lNode);
void adiciona_carreira_paragem(nodeParagem *pParagem, nodeCarreira *pCarreira);
void adiciona_primeira_ligacao(nodeCarreira *pCarreira, nodeParagem *pOrigem,
    nodeParagem *pDestino, double custo, double duracao);
void adiciona_ligacao(nodeCarreira *pCarreira, nodeParagem *pOrigem,
    nodeParagem *pDestino, double custo, double duracao);

void free_lstLigacoes(lstLigacoes *l);

#endif