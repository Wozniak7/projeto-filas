#include "fila.h"

void inicia_fila (fila *f){
    f->primeiro = NULL;
    f->ultimo = NULL;
    f->tamanho = 0;
}

void inicia_fila(fila *);
int esta_vazia(fila *f){
    return f->tamanho == 0;
}
void enfileira(int i, fila *f){
    struct no * novo = aloca_no(i);
    if (esta_vazia(f)){
        f->primeiro = novo;
    }
    else{
        f->ultimo->proximo = novo;
    }
    f->ultimo = novo;
    f->tamanho++;
}
int desenfileira(fila *f){
    int aux_int = f->primeiro->info;
    struct no *aux_no = f->primeiro;
    f->primeiro = f->primeiro->proximo;
    f->tamanho--;
    if(esta_vazia(f))
        f->ultimo = NULL;
    free(aux_no);
    return aux_int;

}
int verifica_tamanho(fila *f){
    return f->tamanho;
}
int consulta_primeiro(fila *f){
    return f->primeiro->info;
}