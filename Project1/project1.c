/* iaed-23 - ist1106322 - project1 */

/* 
 * Ficheiro: projeto1.c
 * Autor: Raquel Rodrigues
 * Descricao: Programa que consiste num sistema de gestao de carreiras de transporte publico.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tamanho maximo do nome de uma carreira. */
#define DIM_NOME_C 21
/* Tamanho maximo do nome de uma paragem. */
#define DIM_NOME_P 51
/* Numero maximo de carreiras. */
#define MAX_CARREIRAS 200
/* Numero maximo de paragens. */
#define MAX_PARAGENS 10000
/* Numero maximo de ligacoes. */
#define MAX_LIGACOES 30000
/* Dimensao maxima do segundo argumento opcional do comando c*/
#define MAX_INPUT 81

/* Estrutura paragem caracterizada por um nome, um valor de latitude
 * e um valor de longitude. */
typedef struct paragem {
    char nome[DIM_NOME_P];
    double latitude;
    double longitude;
} paragem;

/* Estrutura carreira caracterizada por um nome e
 * indices de paragem de origem e de paragem de destino. */
typedef struct carreira {
    char nome[DIM_NOME_C];
    int i_origem;
    int i_destino;
} carreira;

/* Estrutura ligacao caracterizada por um indice de carreira, indices de
 *paragens de origem e de destino, custo e duracao. */
typedef struct ligacao {
    int i_carreira;
    int i_origem;
    int i_destino;
    double custo;
    double duracao;
} ligacao;

/* declaracao de variaveis globais */

/* vetores que contêm as carreiras, paragens e ligacoes criadas,
 * respetivamente. */
carreira registo_carreiras[MAX_CARREIRAS];
paragem registo_paragens[MAX_PARAGENS];
ligacao registo_ligacoes[MAX_LIGACOES];

/* numero de carreiras registadas. */
int n_carreiras;
/* numero de paragens registadas. */
int n_paragens;
/* numero de ligacoes registadas. */
int n_ligacoes;

/* Funcoes do comando c */

/* devolve o indice da carreira se existir uma carreira designada nome_c,
 * caso contrário devolve -1 */
int isCarreira(char nome_c[DIM_NOME_C]) {
    int i;
    for (i = 0; i < n_carreiras; i++) {
        if (!strcmp(registo_carreiras[i].nome, nome_c))
            return i;
    }
    return -1;
}

/* devolve a ligacao que pertenca à carreira de indice i_c e cujo indice
 * de origem, ou de destino (se inv for diferente de 0), seja igual a i_p */
ligacao pesquisa_l(int i_c, int i_p, int inv) {
    ligacao l;
    int i, cond;

    for (i = 0; i < n_ligacoes; i++) {
        l = registo_ligacoes[i];
        if (inv)
            cond = (l.i_destino == i_p);
        else
            cond = (l.i_origem == i_p);
        if (l.i_carreira == i_c && cond)
            return l;
    }
    return l;
}

/* recebe uma carreira c e o seu indice i_c e escreve as suas informações,
 * incluindo nome, paragem de origem e de destino, numero de paragens e custo
 * e duracao totais. As paragens são omitidas para carreiras sem ligacoes. */
void escreve_carreira(carreira c, int i_c) {
    paragem p_origem, p_destino;
    ligacao l;
    int current_p, nparagens_c = 0;
    double custo = 0.0;
    double duracao = 0.0;
    if (c.i_origem == -1) {
        printf("%s %d %.2f %.2f\n", c.nome, nparagens_c, custo, duracao);
    } else {
        p_origem = registo_paragens[c.i_origem];
        p_destino = registo_paragens[c.i_destino];
        current_p = c.i_origem;
        nparagens_c++; /* contar a paragem de origem da carreira */

        /* do while porque as carreiras circulares têm a mesma origem e destino */
        do {
            l = pesquisa_l(i_c, current_p, 0);
            current_p = l.i_destino;
            nparagens_c++;
            custo += l.custo;
            duracao += l.duracao;           
        } while (current_p != c.i_destino);

        printf("%s %s %s %d %.2f %.2f\n", c.nome, p_origem.nome, p_destino.nome,
            nparagens_c, custo, duracao);
    }
}

/* Lista as carreiras existentes no sistema pela ordem de criacao */
void lista_carreiras() {
    int i;
    for (i = 0; i < n_carreiras; i++) {
        escreve_carreira(registo_carreiras[i], i);
    }
}

/* cria uma carreira e adiciona-a ao sistema */
void cria_carreira(char nome_c[DIM_NOME_C]) {
    carreira c;
    strcpy(c.nome, nome_c);
    c.i_origem = -1;
    c.i_destino = -1;
    registo_carreiras[n_carreiras -1] = c;
}

/* verifica se a carreira de indice i_c está vazia */
int carreira_vazia(int i_c) {
    carreira c = registo_carreiras[i_c];
    return c.i_origem == -1;
}

/* lista as paragens da carreira designada nome_c da origem ao destino */
void lista_paragens_carreira(char nome_c[DIM_NOME_C], int inv) {
    ligacao l;
    int current_p, i_c;
    /* i_p identifica a ultima paragem que queremos encontrar */
    int i_p;
    char nome_p[DIM_NOME_P];
    
    i_c = isCarreira(nome_c);

    /* no caso da listagem inversa, a ultima paragem a encontrar
     * é a da origem da carreira. Na listagem regular, será a de destino. */
    if (inv) {
        current_p = registo_carreiras[i_c].i_destino;
        i_p = registo_carreiras[i_c].i_origem;
    } else {
        current_p = registo_carreiras[i_c].i_origem;
        i_p = registo_carreiras[i_c].i_destino;
    }
    printf("%s", registo_paragens[current_p].nome);

    /* do while porque as carreiras circulares têm a mesma origem e destino */
    do {
        l = pesquisa_l(i_c, current_p, inv);
        if (inv)
            current_p = l.i_origem;
        else
            current_p = l.i_destino;
        strcpy(nome_p, registo_paragens[current_p].nome);
        printf(", %s", nome_p);        
    } while (current_p != i_p);
    putchar('\n');
}

/* lê o segundo argumento opcional do comando c e executa a listagem 
 * das paragens da carreira se o argumento for valido */
void le_arg_inverso(char nome_c[DIM_NOME_C]) {
    int tamanho, i_c;
    char arg[MAX_INPUT];
    
    scanf("%s", arg);
    tamanho = strlen(arg);

    /* verificar que o segundo argumento e valido */
    if (!(tamanho >= 3 && tamanho < 8) || 
        strncmp(arg, "inverso", tamanho)) {
        printf("incorrect sort option.\n");
    } else if (((i_c = isCarreira(nome_c)) != -1) && (!carreira_vazia(i_c))) {
        lista_paragens_carreira(nome_c, 1);
    }
}

/* lê os argumentos do comando c e executa as ações respetivas */
void case_c() {
    int i, i_c;
    char c, nome_c[DIM_NOME_C];

    c = getchar();
    if (c == ' ') {
        for (i = 0; (c = getchar()) != '\n' && c != ' '; i++) {
            nome_c[i] = c; /* nome da carreira*/
        }
        nome_c[i] = '\0';

        /* se forem introduzidos dois argumentos */
        if (c == ' ') {
           le_arg_inverso(nome_c);
        } else { /* se for introduzido um argumento apenas */
            if (((i_c = isCarreira(nome_c)) != -1) && (!carreira_vazia(i_c))) {
                lista_paragens_carreira(nome_c, 0);
            } else {
                n_carreiras++;
                cria_carreira(nome_c);
            }
        }
    } else { /* se nao forem introduzidos parametros opcionais */
        lista_carreiras(n_carreiras);
    }
}

/* Funcoes do comando p */

/* devolve 1 se i_c é um elemento do vetor v, 0 caso contrário */
int inVetor(char nome_c[DIM_NOME_C], char* v[],
    int nc) {
    int i;
    for (i = 0; i < nc; i++) {
        if (!strcmp(v[i], nome_c))
            return 1;
    }
    return 0;
}

/* recebe pointeiros para pointeiros de caracteres e troca as strings
 * para as quais os pointeiros apontam */
void troca(char **s1, char **s2) {
    char *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

/* organiza as strings do vetor v de maneira que todos os elementos menores
 * que o pivot se encontrem à sua esquerda e todos os elementos maiores se
 * encontrem à sua direita */
int particao(char *v[], int esq, int drt) {
    int i = esq-1;
    int j = drt;
    char* pivot = v[drt]; /* escolha do pivot */

    while (i < j) {
        while (strcmp(v[++i], pivot) < 0);
        while (strcmp(v[--j], pivot) > 0)
            if (j == esq)
                break;
        if (i < j) {
            troca(&v[i], &v[j]);
        }
    }
    troca(&v[i], &v[drt]);
    return i;
}

/* ordena um vetor de strings alfabeticamente */
void ordena_alfabeticamente(char *v[], int esq, int drt) {
    int i;
    if (drt <= esq) 
        return;
    i = particao(v, esq, drt);
    ordena_alfabeticamente(v, esq, i-1);
    ordena_alfabeticamente(v, i+1, drt);
}

/* devolve o numero de carreiras diferentes que passam pela paragem 
 * de indice i_p */
int n_carreiras_p(int i_p, char cmd) {
    char nome_p[DIM_NOME_P], nome_c[DIM_NOME_C];
    int i, j, nc = 0;
    /* vetor v que guarda os nomes das carreiras que passam pela paragem */
    char *v[DIM_NOME_C];
    ligacao l;
    for (i = 0; i < n_ligacoes; i++) {
        l = registo_ligacoes[i];
        if ((i_p == l.i_origem ||
            i_p == l.i_destino) && /* verificar se o nome já está no vetor */
            !inVetor(registo_carreiras[l.i_carreira].nome, v, nc)) {

            strcpy(nome_c, registo_carreiras[l.i_carreira].nome);
            v[nc] = malloc(strlen(nome_c) + 1);
            strcpy(v[nc], registo_carreiras[l.i_carreira].nome);
            nc++;
            }
    }
    if (cmd == 'i' && nc > 1) { /* caso do comando i */
        ordena_alfabeticamente(v, 0, nc-1);
        strcpy(nome_p, registo_paragens[i_p].nome);
        printf("%s %d:", nome_p, nc);
        for (j = 0; j < nc; j++) {
            /* nomes das carreiras que passam pela paragem nome_p */
            strcpy(nome_c, v[j]);
            printf(" %s", nome_c);
        }
        putchar('\n');
    }
    for (i = 0; i < nc; i++)
        free(v[i]);
    return nc;
}

/* Lista as paragens existentes no sistema pela ordem de criacao */
void lista_paragens() {
    paragem p;
    int i;
    for (i = 0; i < n_paragens; i++) {
        p = registo_paragens[i];
        printf("%s: %16.12f %16.12f %d\n", p.nome, p.latitude, p.longitude,
            n_carreiras_p(i, 'p'));
    }
}

/* devolve o indice i se existir uma paragem designada nome_p,
 * caso contrário devolve -1 */
int isParagem(char nome_p[DIM_NOME_P]) {
    int i;
    for (i = 0; i < n_paragens; i++) {
        if (!strcmp(registo_paragens[i].nome, nome_p))
            return i;
    }
    return -1;
}

/* cria uma paragem e adiciona-a ao sistema */
void cria_paragem(char nome_p[DIM_NOME_P], double latitude, double longitude) {
    paragem p;
    strcpy(p.nome, nome_p);
    p.latitude = latitude;
    p.longitude = longitude;
    registo_paragens[n_paragens-1] = p;
}

/* escreve a latitude e longitude da paragem cujo indice foi introduzido */
void escreve_paragem(int i_p) {
    paragem p;
    p = registo_paragens[i_p];
    printf("%16.12f %16.12f\n", p.latitude, p.longitude);
}

/* le o nome da paragem recebida do standard input e devolve o ultimo
 * caracter lido */
char input_paragem(char *nome_p) {
    int i;
    char c;

    if ((c = getchar()) == '\"') {
        /* ler o nome da paragem entre aspas*/
        for (i = 0; (c = getchar()) != '\"'; i++) {
            nome_p[i] = c;
        }
        /* lê o caracter branco que segue as aspas */
        c = getchar();
    } else {
        i = 0;
        nome_p[i] = c; /* guardar o primeiro caracter que foi lido */
        i++;
        /* ler o nome da paragem */
        for (i = 1; (c = getchar()) != '\n' && c != ' '; i++) {
            nome_p[i] = c;
        }
    }
    nome_p[i] = '\0';
    return c; /* caracter branco que segue o nome */
}

/* lê os argumentos do comando p e executa as ações respetivas */
void case_p() {
    char c, nome_p[DIM_NOME_P];
    double latitude, longitude;
    int indice_p;

    c = getchar();
    if (c == ' ') { /* comando com argumentos */   
        c = input_paragem(nome_p);
        /* se forem introduzidos mais argumentos */
        if (c == ' ') {
            scanf("%lf %lf", &latitude, &longitude);
            if (isParagem(nome_p) != -1) {
                printf("%s: stop already exists.\n", nome_p);
            } else {
                n_paragens++;
                cria_paragem(nome_p, latitude, longitude);
            }
        } else { /* se for introduzido um argumento apenas */
            if ((indice_p = isParagem(nome_p)) != -1) {
                escreve_paragem(indice_p);
            } else {
                printf("%s: no such stop.\n", nome_p);
            }
        }
    } else { /* se nao forem introduzidos parametros opcionais */
        lista_paragens(n_paragens);
    }
}

/* Funcoes do comando l */

/* verifica se i_p é o indice da paragem de destino da carreira de indice i_c*/
int extremo_drt(int i_p, int i_c) {
    return i_p == registo_carreiras[i_c].i_destino;
}

/* verifica se i_p é o indice da paragem de origem da carreira de indice i_c*/
int extremo_esq(int i_p, int i_c) {
    return i_p == registo_carreiras[i_c].i_origem;
}

/* substitui o indice da paragem de origem da carreira identificada 
 * por i_c por i_p_origem */
void atualiza_origem(int i_c, int i_p_origem) {
    registo_carreiras[i_c].i_origem = i_p_origem;
}

/* substitui o indice da paragem de destino da carreira identificada 
 * por i_c por i_p_destino */
void atualiza_destino(int i_c, int i_p_destino) {
    registo_carreiras[i_c].i_destino = i_p_destino;
}

/* cria uma ligacao com os parametros introduzidos e adiciona-a ao registo. */
void cria_ligacao(int i_c, int i_p_origem, int i_p_destino,
    double custo, double duracao) {
        ligacao l;
        l.i_carreira = i_c;
        l.i_origem = i_p_origem;
        l.i_destino = i_p_destino;
        l.custo = custo;
        l.duracao = duracao;
        registo_ligacoes[n_ligacoes-1] = l;
    }

/* atualiza a origem e ou destino da carreira identificada por i_c de acordo 
 * com os indices de paragens i_p_origem e i_p_destino */
void atualiza_c(int i_c, int i_p_origem, int i_p_destino) {
    if (carreira_vazia(i_c)) {
        /* a nova ligacao é a única da carreira */
        atualiza_origem(i_c, i_p_origem);
        atualiza_destino(i_c, i_p_destino);
    } else if (extremo_drt(i_p_origem, i_c)) {
        /* a nova ligacao é inserida no fim da carreira */
        atualiza_destino(i_c, i_p_destino);
    } else if (extremo_esq(i_p_destino, i_c)) {
        /* a nova ligacao é inserida no início da carreira */
        atualiza_origem(i_c, i_p_origem);        
    }
}

/* lê os argumentos do comando p que seguem o nome da carreira
 * e executa as ações respetivas */
void case_l(char nome_c[DIM_NOME_C]) {
    char nome_p_origem[DIM_NOME_P], nome_p_destino[DIM_NOME_P];
    int i_c, i_p_origem, i_p_destino;
    double custo, duracao;

    if ((i_c = isCarreira(nome_c)) == -1) {
        printf("%s: no such line.\n", nome_c);
        return;
    }
   
    /* ler os nomes das paragens de origem e de destino */
    input_paragem(nome_p_origem);
    input_paragem(nome_p_destino);
    /* verificar se as paragens sao validas e guardar os seus indices */
    if ((i_p_origem = isParagem(nome_p_origem)) == -1) {
        printf("%s: no such stop.\n", nome_p_origem);
        return;
    } else if ((i_p_destino = isParagem(nome_p_destino)) == -1) {
        printf("%s: no such stop.\n", nome_p_destino);
        return;
    }
    /* verificar que podemos adicionar a ligacao à carreira */
    if (!carreira_vazia(i_c) && !extremo_esq(i_p_destino, i_c) &&
        !extremo_drt(i_p_origem, i_c)) {
        printf("link cannot be associated with bus line.\n");
        return;
        }

    /* ler o custo e a duracao */
    scanf("%lf %lf", &custo, &duracao);
    if (custo < 0 || duracao < 0) {
        printf("negative cost or duration.\n");
        return;
    }

    atualiza_c(i_c, i_p_origem, i_p_destino);
    n_ligacoes++;
    cria_ligacao(i_c, i_p_origem, i_p_destino, custo, duracao);
}

/* recebe um ou mais comandos com um numero de argumentos e 
 * executa as instrucoes respetivas */
int main() {
    char cmd = 'a';
    char nome_c[DIM_NOME_C];
    int i;

    /* inicializar os contadores */
    n_carreiras = 0, n_paragens = 0, n_ligacoes = 0;

    while (cmd != 'q') {
        scanf("%c", &cmd);
        switch(cmd) {
            case 'q':
                exit(0);
                break;
            case 'c':
                case_c();
                break;
            case 'p':
                case_p();
                break;
            case 'l':
                scanf("%s ", nome_c);  /* ler o nome da carreira */
                case_l(nome_c);
                break;
            case 'i':
                for (i = 0; i < n_paragens; i++) {
                    n_carreiras_p(i, 'i');
                }
                break;
        }
    }
    return 0;
}
