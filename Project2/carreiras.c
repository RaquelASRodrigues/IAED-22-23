/* 
 * Ficheiro: carreiras.c
 * Autor: Raquel Rodrigues
 * Descricao: Ficheiro de fonte com funções que tratam de carreiras.
 */

#include "carreiras.h"

/* Inicializa uma lista de carreiras. */

lstCarreiras* mk_lstCarreiras() {
    lstCarreiras *l = (lstCarreiras*)malloc(sizeof(lstCarreiras));
    
    if (l == NULL) {
        printf("No memory.\n");
        exit(EXIT_FAILURE);
    }
    l->head = NULL;
    l->tail = NULL;
    return l;
}

/* Cria uma nova carreira e adiciona-a à lista de carreiras. */

void cria_carreira(lstCarreiras *l, char *nome_c) {
    nodeCarreira *new_node;
    new_node = (nodeCarreira*)malloc(sizeof(nodeCarreira));

    if (new_node == NULL) {
        printf("No memory.\n");
        exit(EXIT_FAILURE);
    }
    new_node->Carreira.nome = nome_c;
    new_node->Carreira.custoTotal = 0;
    new_node->Carreira.duracaoTotal = 0;
    new_node->Carreira.Ligacoes = mk_lstLigacoes();
    new_node->Carreira.numLigacoes = 0;
    new_node->next = NULL;

    if (l->tail != NULL) {
        l->tail->next = new_node;
    }
    l->tail = new_node;
    if (l->head == NULL) {
        l->head = new_node;
    }
}

/* Atualiza os valores da carreira. Se soma for VERDADE, adiciona os valores
 * à carreira. Caso contrário, subtrai-os. */

void atualiza_carreira(Carreira *carreira, double custo, double duracao,
    int soma) {
    
    if (soma == VERDADE) {
        carreira->custoTotal += custo;
        carreira->duracaoTotal += duracao;
        carreira->numLigacoes++;
    } else {
        carreira->custoTotal -= custo;
        carreira->duracaoTotal -= duracao;
        carreira->numLigacoes--;
    }
}

/* Remove uma carreira do vetor de carreiras da paragem. */

void remove_carreira_paragem(Paragem *paragem, Carreira *carreira) {
    int i, j;

    if (paragem->numCarreiras == 1 && paragem->ptrCarreiras[0] == carreira) {
        paragem->ptrCarreiras = NULL;
        paragem->numCarreiras--;
        return;
    }

    for (i = 0; i < paragem->numCarreiras; i++) {
        if (paragem->ptrCarreiras[i] == carreira) {
            /* deslocar os elementos restantes para a esquerda. */
            for (j = i; j < paragem->numCarreiras-1; j++)
                paragem->ptrCarreiras[j] = paragem->ptrCarreiras[j+1];
            /* reajustar o tamanho do vetor. */
            paragem->ptrCarreiras = realloc(paragem->ptrCarreiras,
                (paragem->numCarreiras-1)*sizeof(Carreira*));
            paragem->numCarreiras--;
            break;
        }
    }
}

/* Garante que todas as paragens por onde a carreira passa deixam
 * de estar associadas a ela. */

void remove_carreira_ligacoes(lstLigacoes *lLigacoes, Carreira *carreira) {
    nodeLigacao *t;
    Paragem *paragem;

    for (t = lLigacoes->head; t != NULL; t = t->next) {
        paragem = &(t->Ligacao.pOrigem->Paragem);
        remove_carreira_paragem(paragem, carreira);
    }
    if (lLigacoes->tail != NULL) {
        t = lLigacoes->tail;
        paragem = &(t->Ligacao.pDestino->Paragem);
        remove_carreira_paragem(paragem, carreira);
    }
}

/* Remove a carreira da lista de carreiras e todas as suas ligações. */

void remove_carreira(lstCarreiras *l, char *nome_c) {
    nodeCarreira *t, *ant;

    for (t = l->head, ant = NULL; t != NULL; ant = t, t = t->next) {
        if (!strcmp(t->Carreira.nome, nome_c)) {
            if (t == l->head)
                l->head = t->next;
            else
                ant->next = t->next;
            if (t == l->tail)
                l->tail = ant;

            remove_carreira_ligacoes(t->Carreira.Ligacoes, &(t->Carreira));
            free_lstLigacoes(t->Carreira.Ligacoes);
            free(t->Carreira.nome);
            free(t);
            break;
        }
    }
}

/* Liberta a memória associada à lista de carreiras. */

void free_lstCarreiras(lstCarreiras *l) {
    nodeCarreira *t, *next;

    for (t = l->head; t != NULL; t = next) {
        free_lstLigacoes(t->Carreira.Ligacoes);
        free(t->Carreira.nome);
        next = t->next;
        free(t);
    }
    free(l);
}

/* Procura uma carreira nomeada nome_c. Caso exista, devolve um ponteiro
 * para o seu nó. Caso contrário devolve NAO_ENCONTRADO. */

nodeCarreira *pesquisa_carreira(lstCarreiras *l, char *nome_c) {
    nodeCarreira *t;

    for (t = l->head; t != NULL; t = t->next)
        if (!strcmp(t->Carreira.nome , nome_c))
            return t;
    return NAO_ENCONTRADO;
}

/* Procura uma paragem na lista de ligações de uma carreira.
 * Caso a encontre, devolve um ponteiro para o nó da primeira ligação que a
 * tenha como origem (ou da última ligação se a paragem for o destino).
 * Caso contrário, devolve NAO_ENCONTRADO. */

nodeLigacao *pesquisa_paragem_carreira(Carreira *carreira,
    nodeParagem *pParagem) {
    
    nodeLigacao *t;
    
    for (t = carreira->Ligacoes->head; t != NULL; t = t->next)
        if (t->Ligacao.pOrigem == pParagem)
            return t;

    t = carreira->Ligacoes->tail;
    if (t != NULL && t->Ligacao.pDestino == pParagem)
        return t;
    return NAO_ENCONTRADO;
}

/* Verifica se a carreira está vazia. */

int carreira_vazia(nodeCarreira *pCarreira) {
    return (pCarreira->Carreira.numLigacoes == 0);
}

/* Lista as carreiras existentes no sistema pela ordem de criação. */

void lista_carreiras(lstCarreiras *l) {
    nodeCarreira* t;

    for (t = l->head; t != NULL; t = t->next) {
        escreve_carreira(t);
    }
}

/* Escreve as informações relativas a uma carreira. As paragens são omitidas
 * para carreiras sem ligações. */

void escreve_carreira(nodeCarreira *pCarreira) {
    printf("%s ", pCarreira->Carreira.nome);
    if (!carreira_vazia(pCarreira)) {
        nodeLigacao *lOrigem = pCarreira->Carreira.Ligacoes->head;
        nodeLigacao *lDestino = pCarreira->Carreira.Ligacoes->tail;
        
        printf("%s %s ", lOrigem->Ligacao.pOrigem->Paragem.nome,
            lDestino->Ligacao.pDestino->Paragem.nome);
        printf("%d %.2f %.2f\n", pCarreira->Carreira.numLigacoes+1,
            pCarreira->Carreira.custoTotal, pCarreira->Carreira.duracaoTotal);
    }
    else
        printf("%d %.2f %.2f\n", 0, 0.0, 0.0);
}

/* Lista as paragens de uma carreira. A ordem é invertida se inverso 
 * for VERDADE. */

void lista_paragens_carreira(nodeCarreira *pCarreira, int inverso) {
    nodeLigacao *t;
    
    if (pCarreira == NULL || pCarreira->Carreira.numLigacoes == 0)
        return;
    if (inverso == FALSO) {
        for (t = pCarreira->Carreira.Ligacoes->head; t != NULL; t = t->next)
            printf("%s, ", t->Ligacao.pOrigem->Paragem.nome);
        t = pCarreira->Carreira.Ligacoes->tail;
        printf("%s\n", t->Ligacao.pDestino->Paragem.nome);
    }
    else {
        for (t = pCarreira->Carreira.Ligacoes->tail; t != NULL; t = t->prev)
            printf("%s, ", t->Ligacao.pDestino->Paragem.nome);
        t = pCarreira->Carreira.Ligacoes->head;
        printf("%s\n", t->Ligacao.pOrigem->Paragem.nome);
    }
}