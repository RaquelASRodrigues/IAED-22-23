/* 
 * Ficheiro: ligacoes.c
 * Autor: Raquel Rodrigues
 * Descricao: Ficheiro de fonte com funções que tratam de ligações.
 */

#include "ligacoes.h"

/* Lê o nome de uma carreira e de duas paragens de uma ligação. */

void leNomesComando(char **nome_c, char **nome_origem, char **nome_destino) {
    leEspacos();
    *nome_c = leNome();
    leEspacos();
    *nome_origem = leNome();
    leEspacos();
    *nome_destino = leNome();
}

/* Inicializa uma lista de ligações. */

lstLigacoes* mk_lstLigacoes() {
    lstLigacoes *l = (lstLigacoes*)malloc(sizeof(lstLigacoes));
    
    if (l == NULL) {
        printf("No memory.\n");
        exit(EXIT_FAILURE);
    }
    l->head = NULL;
    l->tail = NULL;
    return l;
}

/* Cria uma nova ligação, devolvendo um ponteiro para o seu nó. */

nodeLigacao *cria_ligacao(nodeCarreira *pCarreira, nodeParagem *pOrigem,
    nodeParagem *pDestino, double custo, double duracao) {
    
    nodeLigacao *new_node;
    new_node = (nodeLigacao*)malloc(sizeof(nodeLigacao));

    if (new_node == NULL) {
        printf("No memory.\n");
        exit(EXIT_FAILURE);
    }
    new_node->Ligacao.pCarreira = pCarreira;
    new_node->Ligacao.pOrigem = pOrigem;
    new_node->Ligacao.pDestino = pDestino;
    new_node->Ligacao.custo = custo;
    new_node->Ligacao.duracao = duracao;
    
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

/* verifica se a paragem é a primeira da carreira. */

int extremo_esq(nodeParagem *pParagem, Carreira *carreira) {
    return (carreira->Ligacoes->head->Ligacao.pOrigem == pParagem);
}

/* verifica se a paragem é a última da carreira. */

int extremo_drt(nodeParagem *pParagem, Carreira *carreira) {
    return (carreira->Ligacoes->tail->Ligacao.pDestino == pParagem);
}

/* Acrescenta uma ligação ao final da lista de ligações da carreira. */

void acrescenta_ligacao_fim(nodeCarreira *pCarreira, nodeLigacao *lNode) {
    lNode->prev = pCarreira->Carreira.Ligacoes->tail;
    pCarreira->Carreira.Ligacoes->tail->next = lNode;
    pCarreira->Carreira.Ligacoes->tail = lNode;

    atualiza_carreira(&(pCarreira->Carreira),
        lNode->Ligacao.custo, lNode->Ligacao.duracao, VERDADE);
}

/* Acrescenta uma ligação ao início da lista de ligações da carreira. */

void acrescenta_ligacao_inicio(nodeCarreira *pCarreira, nodeLigacao *lNode) {
    lNode->next = pCarreira->Carreira.Ligacoes->head;
    pCarreira->Carreira.Ligacoes->head->prev = lNode;
    pCarreira->Carreira.Ligacoes->head = lNode;

    atualiza_carreira(&(pCarreira->Carreira),
        lNode->Ligacao.custo, lNode->Ligacao.duracao, VERDADE);
}

/* Adiciona uma nova carreira ao vetor de carreiras da paragem. */

void adiciona_carreira_paragem(nodeParagem *pParagem, nodeCarreira *pCarreira) {
    int size = pParagem->Paragem.numCarreiras + 1;
    pParagem->Paragem.ptrCarreiras = realloc(pParagem->Paragem.ptrCarreiras,
        size*sizeof(Carreira*));
    if (pParagem->Paragem.ptrCarreiras == NULL) {
        printf("No memory.\n");
        exit(EXIT_FAILURE);
    }
    pParagem->Paragem.ptrCarreiras[size-1] = &(pCarreira->Carreira);
    pParagem->Paragem.numCarreiras++;
}

/* Adiciona a primeira ligação da carreira. */

void adiciona_primeira_ligacao(nodeCarreira *pCarreira, nodeParagem *pOrigem,
    nodeParagem *pDestino, double custo, double duracao) {
    
    nodeLigacao *lNode;
    adiciona_carreira_paragem(pOrigem, pCarreira);
    if (pOrigem != pDestino)
        adiciona_carreira_paragem(pDestino, pCarreira);
    lNode = cria_ligacao(pCarreira, pOrigem, pDestino, custo, duracao);
    
    /* adicionar o primeiro nó. */
    pCarreira->Carreira.Ligacoes->head = lNode;
    pCarreira->Carreira.Ligacoes->tail = lNode;
    
    atualiza_carreira(&(pCarreira->Carreira), custo, duracao, VERDADE);
}

/* Adiciona uma nova ligação a uma carreira. */

void adiciona_ligacao(nodeCarreira *pCarreira, nodeParagem *pOrigem,
    nodeParagem *pDestino, double custo, double duracao) {
    
    nodeLigacao *lNode;

    if (carreira_vazia(pCarreira))
        adiciona_primeira_ligacao(pCarreira, pOrigem, pDestino, custo, duracao);
    else {
        lNode = cria_ligacao(pCarreira, pOrigem, pDestino, custo, duracao);
        if (extremo_drt(pOrigem, &(pCarreira->Carreira))) {
            if (pesquisa_paragem_carreira(&(pCarreira->Carreira), pDestino)
                == NAO_ENCONTRADO)
                adiciona_carreira_paragem(pDestino, pCarreira);
            acrescenta_ligacao_fim(pCarreira, lNode);
        } else if (extremo_esq(pDestino, &(pCarreira->Carreira))) {
            if (pesquisa_paragem_carreira(&(pCarreira->Carreira), pOrigem)
                == NAO_ENCONTRADO)
                adiciona_carreira_paragem(pOrigem, pCarreira);
            acrescenta_ligacao_inicio(pCarreira, lNode);
        }
    }
}

/* Liberta a memória associada à lista de ligações. */

void free_lstLigacoes(lstLigacoes *l) {
    nodeLigacao *t, *next; 
       
    for (t = l->head; t != NULL; t = next) {
        next = t->next;
        free(t);
    }
    free(l);
}