#include <stdio.h>
#include "no.h"

typedef struct {
    no *primeiro;
    no *ultimo;
    int tamanho;
} fila;

void inicia_fila(fila *);
int esta_vazia(fila *);
void enfileira(int, fila *);
int desenfileira(fila *);
int verifica_tamanho(fila *);
int consulta_primeiro(fila *);