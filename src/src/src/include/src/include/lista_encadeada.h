#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include "inventario.h"

/* Nodo para lista encadeada simples */
typedef struct Nodo {
    Item data;
    struct Nodo *next;
} Nodo;

/* Lista encadeada */
typedef struct {
    Nodo *head;
    int tamanho;
} ListaEncadeada;

/* Funções */
void le_inicializar(ListaEncadeada *l);
Nodo* le_criar_nodo(Item it);
int le_inserir_inicio(ListaEncadeada *l, Item it);
int le_inserir_fim(ListaEncadeada *l, Item it);
int le_remover_por_id(ListaEncadeada *l, int id);
Nodo* le_busca_sequencial(ListaEncadeada *l, const char *nome);
void le_exibir(ListaEncadeada *l);
void le_liberar(ListaEncadeada *l);

#endif
