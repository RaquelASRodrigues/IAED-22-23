/* 
 * Ficheiro: definicoes.h
 * Autor: Raquel Rodrigues
 * Descricao: Ficheiro de cabeçalho com definições de estruturas e constantes.
 */

#ifndef _DEFINICOES_H_
#define _DEFINICOES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAO_ENCONTRADO NULL
#define VERDADE 1
#define FALSO 0

typedef struct str_carreira Carreira;
typedef struct str_lstLigacoes lstLigacoes;

/* Paragens. */

typedef struct {
    char *nome;
    double latitude;
    double longitude;
    Carreira **ptrCarreiras;
    int numCarreiras;
} Paragem;

typedef struct str_nodeP {
    Paragem Paragem;
    struct str_nodeP *next;
} nodeParagem;

typedef struct {
    nodeParagem *head, *tail;
} lstParagens;

/* Carreiras. */

struct str_carreira {
    char *nome;
    double custoTotal;
    double duracaoTotal;
    lstLigacoes *Ligacoes;
    int numLigacoes;
};

typedef struct str_nodeC {
    Carreira Carreira;
    struct str_nodeC *next;
} nodeCarreira;

typedef struct {
    nodeCarreira *head, *tail;
} lstCarreiras;

/* Ligacoes. */

typedef struct {
    nodeCarreira *pCarreira;
    nodeParagem *pOrigem, *pDestino;
    double custo;
    double duracao;
} Ligacao;

typedef struct str_nodeL {
    Ligacao Ligacao;
    struct str_nodeL *prev, *next;
} nodeLigacao;

struct str_lstLigacoes {
    nodeLigacao *head, *tail;
};

#endif