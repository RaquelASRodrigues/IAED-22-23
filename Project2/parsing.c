/* 
 * Ficheiro: parsing.c
 * Autor: Raquel Rodrigues
 * Descricao: Ficheiro de fonte com funções que tratam do parsing do input.
 */

#include "definicoes.h"
#include "parsing.h"

/* Le espaços. Devolve 0 se chegou ao final de linha ou 1 caso contrário. */

int leEspacos() {
    int c;
    while ((c = getchar()) == ' ' || c == '\t');
    if (c == '\n')
        return 0;
    ungetc(c, stdin);
    return 1;
}

/* Le um nome para a string buffer que recebe como parametro e copia o seu 
 * conteúdo para a string s, devolvendo um ponteiro para a mesma. */

char *leNome() {
    int i = 0, c;
    char *s;
    char buffer[MAX_TAMANHO_LINHA]; /* Buffer auxiliar. */;

    buffer[0] = getchar();
    if (buffer[0] != '"') {
        i = 1;
        while ((c = getchar()) != ' ' && c != '\t' && c != '\n')
            buffer[i++] = c;
        ungetc(c, stdin);
    }
    else {
        while((c = getchar()) != '"')
            buffer[i++] = c;
    }
    buffer[i++] = '\0';
    s = (char*)malloc((strlen(buffer)+1)*sizeof(char));
    strcpy(s, buffer);
    return s;
}

/* Le todo o texto até ao final de linha. */

void leAteFinalLinha(char buffer[]) {
    char c;
    int i = 0;
    while ((c = getchar()) != '\n') {
        buffer[i++] = c;
    }
    buffer[i] = '\0';
}