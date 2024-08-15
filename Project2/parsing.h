/* 
 * Ficheiro: parsing.h
 * Autor: Raquel Rodrigues
 * Descricao: Ficheiro de cabeçalho com funções que tratam do parsing do input.
 */

#ifndef _PARSING_H_
#define _PARSING_H_

#define MAX_TAMANHO_LINHA 65535

int leEspacos();
char *leNome();
void leAteFinalLinha(char buffer[]);

#endif