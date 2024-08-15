/* 
 * Ficheiro: paragens.c
 * Autor: Raquel Rodrigues
 * Descricao: Ficheiro de fonte com funções que tratam de paragens.
 */

#include "paragens.h"

/* Verifica se a string arg é um prefixo de pelo menos 3 caracteres da palavra
 * inverso. */

int verifica_inverso(char *arg) {
    char inv[] = "inverso";
    int tamanho = strlen(arg);

    if (!(tamanho >= 3 && tamanho < 8) || strncmp(arg, inv, tamanho)) {
        free(arg);
        return FALSO;
    } else {
        free(arg);
        return VERDADE;
    }
}

/* Inicializa uma lista de paragens. */

lstParagens* mk_lstParagens() {
    lstParagens *l = (lstParagens*)malloc(sizeof(lstParagens));
    
    if (l == NULL) {
        printf("No memory.\n");
        exit(EXIT_FAILURE);
    }
    l->head = NULL;
    l->tail = NULL;
    return l;
}

/* Cria uma nova paragem e adiciona-a à lista de paragens. */

void cria_paragem(lstParagens *l, char *nome_p, double latitude, double longitude) {
    nodeParagem *new_node;
    new_node = (nodeParagem*)malloc(sizeof(nodeParagem));

    if (new_node == NULL) {
        printf("No memory.\n");
        exit(EXIT_FAILURE);
    }
    new_node->Paragem.nome = nome_p;
    new_node->Paragem.latitude = latitude;
    new_node->Paragem.longitude = longitude;
    new_node->Paragem.ptrCarreiras = NULL;
    new_node->Paragem.numCarreiras = 0;
    new_node->next = NULL;

    if (l->tail != NULL) {
        l->tail->next = new_node;
    }
    l->tail = new_node;
    if (l->head == NULL) {
        l->head = new_node;
    }
}

/* Elimina uma paragem da única ligação da carreira e garante que a carreira da
 * outra paragem deixa de estar associada à mesma. */

void elimina_paragem_unica_ligacao(nodeLigacao *pLigacao, Carreira *carreira,
    nodeParagem *pParagem) {
    
    if (!(pLigacao->Ligacao.pDestino == pLigacao->Ligacao.pOrigem)) {
        if (extremo_esq(pParagem, carreira))
            remove_carreira_paragem(&(pLigacao->Ligacao.pDestino->Paragem),
                carreira);
        else
            remove_carreira_paragem(&(pLigacao->Ligacao.pOrigem->Paragem),
                carreira);
    }
    carreira->Ligacoes->head = NULL;
    carreira->Ligacoes->tail = NULL;

    atualiza_carreira(carreira, pLigacao->Ligacao.custo,
    pLigacao->Ligacao.duracao, FALSO);
    
}

/* Elimina a primeira paragem da carreira. */

void elimina_primeira_paragem(nodeLigacao *pLigacao, Carreira *carreira) {
    carreira->Ligacoes->head = pLigacao->next;
    carreira->Ligacoes->head->prev = NULL;
    atualiza_carreira(carreira, pLigacao->Ligacao.custo,
        pLigacao->Ligacao.duracao, FALSO);
}

/* Elimina a última paragem da carreira. */

void elimina_ultima_paragem(nodeLigacao *pLigacao, Carreira *carreira) {
    carreira->Ligacoes->tail = carreira->Ligacoes->tail->prev;
    carreira->Ligacoes->tail->next = NULL;
    atualiza_carreira(carreira, pLigacao->Ligacao.custo,
        pLigacao->Ligacao.duracao, FALSO);
}

/* Elimina uma paragem no meio da carreira. */

void elimina_paragem_meio(nodeLigacao *pLigacao, Carreira *carreira) {
    
    pLigacao->next->Ligacao.pOrigem = pLigacao->Ligacao.pOrigem;
    pLigacao->next->Ligacao.custo += pLigacao->Ligacao.custo;
    pLigacao->next->Ligacao.duracao += pLigacao->Ligacao.duracao;

    if (pLigacao == carreira->Ligacoes->head) {
        carreira->Ligacoes->head = pLigacao->next;
        carreira->Ligacoes->head->prev = NULL;
    }
    else {
        pLigacao->prev->next = pLigacao->next;
        pLigacao->next->prev = pLigacao->prev;
    }
}

/* Elimina todas as ocorrências de uma paragem na lista de ligações. */

void elimina_paragem_ligacoes(Carreira *carreira, nodeParagem *pParagem) {
    
    nodeLigacao *pLigacao = pesquisa_paragem_carreira(carreira, pParagem);
    
    while (pLigacao != NAO_ENCONTRADO) {  
        if (carreira->numLigacoes == 1) {
            elimina_paragem_unica_ligacao(pLigacao, carreira, pParagem);
            free(pLigacao);
            break;
        }
        else if (extremo_esq(pParagem, carreira) && 
            (pLigacao == carreira->Ligacoes->head)) {
            
            elimina_primeira_paragem(pLigacao, carreira);
        }
        else if (extremo_drt(pParagem, carreira) &&
            (pLigacao == carreira->Ligacoes->tail)) {
            
            elimina_ultima_paragem(pLigacao, carreira);
        }
        else {
            /* como pesquisa_paragem_carreira vai devolver a segunda ligação
             * que usa a paragem, apontamos pLigacao para o nó anterior. */
            pLigacao = pLigacao->prev;
            elimina_paragem_meio(pLigacao, carreira);
            carreira->numLigacoes--;
        }
        free(pLigacao);
        pLigacao = pesquisa_paragem_carreira(carreira, pParagem);
    }
}

/* Garante que todas as carreiras que passavam pela paragem deixem de
 * o fazer. */

void elimina_paragem_carreiras(nodeParagem *pParagem) {
    int i, numCarreiras;

    numCarreiras = pParagem->Paragem.numCarreiras;
    for (i = 0; i < numCarreiras; i++) {
        elimina_paragem_ligacoes(pParagem->Paragem.ptrCarreiras[i], pParagem);
    }
}

/* Elimina a paragem da lista de paragens e retira-a das carreiras. */

void elimina_paragem(lstParagens *l, char *nome_p) {
    nodeParagem *t, *ant;

    for (t = l->head, ant = NULL; t != NULL; ant = t, t = t->next) {
        if (!strcmp(t->Paragem.nome, nome_p)) {
            if (t == l->head)
                l->head = t->next;
            else
                ant->next = t->next;
            if (t == l->tail)
                l->tail = ant;
            
            elimina_paragem_carreiras(t);
            free(t->Paragem.ptrCarreiras);
            free(t->Paragem.nome);
            free(t);
            break;
        }
    }
}

/* Liberta a memória associada à lista de paragens. */

void free_lstParagens(lstParagens *l) {
    nodeParagem *t, *next;

    for (t = l->head; t != NULL; t = next) {
        free(t->Paragem.ptrCarreiras);
        free(t->Paragem.nome);
        next = t->next;
        free(t);
    }
    free(l);
}

/* Procura uma paragem nomeada nome_p. Caso exista, devolve um ponteiro
 * para o seu nó. Caso contrário devolve NAO_ENCONTRADO. */

nodeParagem *pesquisa_paragem(lstParagens *l, char *nome_p) {
    nodeParagem *t;

    for (t = l->head; t != NULL; t = t->next)
        if (!strcmp(t->Paragem.nome , nome_p))
            return t;
    return NAO_ENCONTRADO;
}

/* Lista as paragens existentes no sistema pela ordem de criacao */

void lista_paragens(lstParagens *l) {
    nodeParagem* t;

    for (t = l->head; t != NULL; t = t->next) {
        printf("%s: %16.12f %16.12f %d\n", t->Paragem.nome, t->Paragem.latitude,
                t->Paragem.longitude, t->Paragem.numCarreiras);
    }
}

/* Escreve as informações da paragem. */

void escreve_paragem(nodeParagem *pParagem) {
    printf("%16.12f %16.12f\n", pParagem->Paragem.latitude,
        pParagem->Paragem.longitude);
}

/* Troca dois ponteiros para carreiras. */

void troca(Carreira **p1, Carreira **p2) {
    Carreira *tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

/* Organiza os ponteiros do vetor ptrCarreiras de maneira a que todos os
 * elementos menores que o pivot se encontrem à sua esquerda e todos os
 * elementos maiores se encontrem à sua direita. */

int particao(Carreira **ptrCarreiras, int esq, int drt) {
    int i = esq-1;
    int j = drt;
    Carreira* pivot = ptrCarreiras[drt];

    while (i < j) {
        while (strcmp(ptrCarreiras[++i]->nome, pivot->nome) < 0);
        while (strcmp(ptrCarreiras[--j]->nome, pivot->nome) > 0)
            if (j == esq)
                break;
        if (i < j) {
            troca(&ptrCarreiras[i], &ptrCarreiras[j]);
        }
    }
    troca(&ptrCarreiras[i], &ptrCarreiras[drt]);
    return i;
}

/* Ordena um vetor de ponteiros para carreiras alfabeticamente. */

void ordena_carreiras(Carreira **ptrCarreiras, int esq, int drt) {
    int i;
    if (drt <= esq) 
        return;
    i = particao(ptrCarreiras, esq, drt);
    ordena_carreiras(ptrCarreiras, esq, i-1);
    ordena_carreiras(ptrCarreiras, i+1, drt);
}

/* Mostra todas as paragens onde há uma interseção e
 * as respetivas carreiras. */

void mostraIntersecoes(lstParagens *l) {
    nodeParagem *t;
    Carreira *Carreira;
    int i, numCarreiras;

    for (t = l->head; t != NULL; t = t->next) {
        numCarreiras = t->Paragem.numCarreiras;
        if (numCarreiras > 1) {
            printf("%s %d:", t->Paragem.nome, numCarreiras);
            ordena_carreiras(t->Paragem.ptrCarreiras, 0, numCarreiras-1);
            for (i = 0; i < numCarreiras; i++) {
                Carreira = t->Paragem.ptrCarreiras[i];
                printf(" %s", Carreira->nome);
            }
            putchar('\n');
        }
    }
}