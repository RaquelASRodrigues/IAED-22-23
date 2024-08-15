/* iaed-23 - ist1106322 - project2 */

/* 
 * Ficheiro: project2.c
 * Autor: Raquel Rodrigues
 * Descricao: Programa que consiste num sistema de gestao de carreiras de transporte publico.
 */

#include "definicoes.h"
#include "parsing.h"
#include "paragens.h"
#include "carreiras.h"
#include "ligacoes.h"

/* Liberta toda a memória do sistema. */

void free_memoria(lstCarreiras *lC, lstParagens *lP) {
    free_lstCarreiras(lC);
    free_lstParagens(lP);
}

/* Lê os argumentos do comando 'c' e executa as ações respetivas. */

void carreiras(lstCarreiras *lCarreiras, char buffer[]) {
    int fimLinha = leEspacos();
    char *nome_c, *arg_inv;
    nodeCarreira *pCarreira;

    if (!fimLinha) {
        lista_carreiras(lCarreiras);
        return;
    }
    nome_c = leNome();
    pCarreira = pesquisa_carreira(lCarreiras, nome_c);
    fimLinha = leEspacos();
    if (!fimLinha) {
        if (pCarreira == NAO_ENCONTRADO)
            cria_carreira(lCarreiras, nome_c);
        else {
            lista_paragens_carreira(pCarreira, FALSO);
            free(nome_c);
        }
    } else {
        arg_inv = leNome();
        if (verifica_inverso(arg_inv))
            lista_paragens_carreira(pCarreira, VERDADE);
        else
            printf("incorrect sort option.\n");
        free(nome_c);
        leAteFinalLinha(buffer);
    }
}

/* Lê os argumentos do comando 'p' e executa as ações respetivas. */

void paragens(lstParagens *lParagens, char buffer[]) {
    int fimLinha = leEspacos();
    char *nome_p;
    nodeParagem *pParagem;

    if (!fimLinha) {
        lista_paragens(lParagens);
        return;
    }
    nome_p = leNome();
    fimLinha = leEspacos();
    if (!fimLinha) {
        if ((pParagem = pesquisa_paragem(lParagens, nome_p)) == NAO_ENCONTRADO)
            printf("%s: no such stop.\n", nome_p);
        else
            escreve_paragem(pParagem);
        free(nome_p);
    } else {
        double latitude, longitude;
        scanf("%lf%lf", &latitude, &longitude);
        if ((pParagem = pesquisa_paragem(lParagens, nome_p)) == NAO_ENCONTRADO)
            cria_paragem(lParagens, nome_p, latitude, longitude);
        else {
            printf("%s: stop already exists.\n", nome_p);
            free(nome_p);
        }
        leAteFinalLinha(buffer);
    }
}

/* Lê os argumentos do comando 'l' e executa as ações respetivas. */

void ligacoes(lstCarreiras *lCarreiras, lstParagens *lParagens, char buffer[]) {

    char *nome_c, *nome_origem, *nome_destino;
    double custo, duracao;
    nodeCarreira *pCarreira;
    nodeParagem *pOrigem, *pDestino;

    leNomesComando(&nome_c, &nome_origem, &nome_destino);
    scanf("%lf%lf", &custo, &duracao);
    leAteFinalLinha(buffer);

    pCarreira = pesquisa_carreira(lCarreiras, nome_c);
    if (pCarreira == NAO_ENCONTRADO)
        printf("%s: no such line.\n", nome_c);
    else {
        pOrigem = pesquisa_paragem(lParagens, nome_origem);
        if (pOrigem == NAO_ENCONTRADO)
            printf("%s: no such stop.\n", nome_origem);
        else {
            pDestino = pesquisa_paragem(lParagens, nome_destino);
            if (pDestino == NAO_ENCONTRADO)
                printf("%s: no such stop.\n", nome_destino);
            else if (!carreira_vazia(pCarreira) && 
                !extremo_esq(pDestino, &(pCarreira->Carreira)) && 
                !extremo_drt(pOrigem, &(pCarreira->Carreira)))

                printf("link cannot be associated with bus line.\n");
            else if (custo < 0 || duracao < 0)
                printf("negative cost or duration.\n");
            else {
                adiciona_ligacao(pCarreira, pOrigem, pDestino,
                    custo, duracao);
            }
        }
    }
    free(nome_c);
    free(nome_origem);
    free(nome_destino);
}

/* Função que trata do comando 'i'. */

void intersecoes(lstParagens *lParagens, char buffer[]) {
    leAteFinalLinha(buffer);
    mostraIntersecoes(lParagens);
}

/* Lê o argumento do comando 'r' e executa as ações respetivas. */

void comando_r(lstCarreiras *lCarreiras, char buffer[]) {
    char *nome_c;
    leEspacos();
    nome_c = leNome();
    leAteFinalLinha(buffer);
    if (pesquisa_carreira(lCarreiras, nome_c) == NAO_ENCONTRADO)
        printf("%s: no such line.\n", nome_c);
    else {
        remove_carreira(lCarreiras, nome_c);
    }
    free(nome_c);
}

/* Lê o argumento do comando 'e' e executa as ações respetivas. */

void comando_e(lstParagens *lParagens, char buffer[]) {
    char *nome_p;
    leEspacos();
    nome_p = leNome();
    leAteFinalLinha(buffer);
    if (pesquisa_paragem(lParagens, nome_p) == NAO_ENCONTRADO)
        printf("%s: no such stop.\n", nome_p);
    else {
        elimina_paragem(lParagens, nome_p);
    }
    free(nome_p);
}

/* recebe um ou mais comandos com um numero de argumentos e 
 * executa as instrucoes respetivas. */
int main() {
    char cmd, buffer[MAX_TAMANHO_LINHA]; /* Buffer auxiliar. */
    lstParagens *lParagens = mk_lstParagens();
    lstCarreiras *lCarreiras = mk_lstCarreiras();

    do {
        cmd = getchar();
        switch(cmd) {
            case 'a':
                free_memoria(lCarreiras, lParagens);
                lParagens = mk_lstParagens();
                lCarreiras = mk_lstCarreiras();
                break;
            case 'q':
                free_memoria(lCarreiras, lParagens);
                break;
            case 'c':
                carreiras(lCarreiras, buffer);
                break;
            case 'p':
                paragens(lParagens, buffer);
                break;
            case 'l':
                ligacoes(lCarreiras, lParagens, buffer);
                break;
            case 'i':
                intersecoes(lParagens, buffer);
                break;
            case 'r':
                comando_r(lCarreiras, buffer);
                break;
            case 'e':
                comando_e(lParagens, buffer);
                break;
            default:
            /* Ignorar linhas em branco */
	        if (cmd == ' ' || cmd == '\t' || cmd == '\n') break;
        }
    } while (cmd != 'q');
    return 0;
}