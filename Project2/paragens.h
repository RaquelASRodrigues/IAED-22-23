/* 
 * Ficheiro: paragens.h
 * Autor: Raquel Rodrigues
 * Descricao: Ficheiro de cabeçalho com funções que tratam de paragens.
 */

#ifndef _PARAGENS_H_
#define _PARAGENS_H_

#include "definicoes.h"
#include "carreiras.h"

/* Protótipos. */

int verifica_inverso(char *arg);
lstParagens* mk_lstParagens();
void cria_paragem(lstParagens *l, char *nome_p, double latitude, double longitude);
void elimina_paragem_unica_ligacao(nodeLigacao *pLigacao, Carreira *carreira,
    nodeParagem *pParagem);
void elimina_primeira_paragem(nodeLigacao *pLigacao, Carreira *carreira);
void elimina_ultima_paragem(nodeLigacao *pLigacao, Carreira *carreira);
void elimina_paragem_meio(nodeLigacao *pLigacao, Carreira *carreira);
void elimina_paragem_ligacoes(Carreira *carreira, nodeParagem *pParagem);
void elimina_paragem_carreiras(nodeParagem *pParagem);
void elimina_paragem(lstParagens *l, char *nome_p);
void  free_lstParagens(lstParagens *l);
nodeParagem *pesquisa_paragem(lstParagens *l, char *nome_p);
void lista_paragens(lstParagens *l);
void escreve_paragem(nodeParagem *pParagem);
void mostraIntersecoes(lstParagens *l);

#endif