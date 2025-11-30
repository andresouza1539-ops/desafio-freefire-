#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_encadeada.h"

void le_inicializar(ListaEncadeada *l) {
    l->head = NULL;
    l->tamanho = 0;
}

Nodo* le_criar_nodo(Item it) {
    Nodo *n = (Nodo*) malloc(sizeof(Nodo));
    if (!n) return NULL;
    n->data = it;
    n->next = NULL;
    return n;
}

int le_inserir_inicio(ListaEncadeada *l, Item it) {
    Nodo *n = le_criar_nodo(it);
    if (!n) return 0;
    n->next = l->head;
    l->head = n;
    l->tamanho++;
    return 1;
}

int le_inserir_fim(ListaEncadeada *l, Item it) {
    Nodo *n = le_criar_nodo(it);
    if (!n) return 0;
    if (l->head == NULL) {
        l->head = n;
    } else {
        Nodo *p = l->head;
        while (p->next) p = p->next;
        p->next = n;
    }
    l->tamanho++;
    return 1;
}

int le_remover_por_id(ListaEncadeada *l, int id) {
    Nodo *cur = l->head;
    Nodo *prev = NULL;
    while (cur) {
        if (cur->data.id == id) {
            if (prev) prev->next = cur->next;
            else l->head = cur->next;
            free(cur);
            l->tamanho--;
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

Nodo* le_busca_sequencial(ListaEncadeada *l, const char *nome) {
    Nodo *cur = l->head;
    while (cur) {
        if (strcasecmp(cur->data.nome, nome) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

void le_exibir(ListaEncadeada *l) {
    if (l->head == NULL) {
        printf("Lista encadeada vazia.\n");
        return;
    }
    printf("Inventário (lista encadeada) — %d itens:\n", l->tamanho);
    printf("ID | Nome                          | Tipo       | Qtd | Prio\n");
    printf("---------------------------------------------------------------\n");
    Nodo *p = l->head;
    while (p) {
        Item *it = &p->data;
        printf("%2d | %-28s | %-10s | %3d | %4d\n",
               it->id, it->nome, it->tipo, it->quantidade, it->prioridade);
        p = p->next;
    }
}

void le_liberar(ListaEncadeada *l) {
    Nodo *p = l->head;
    while (p) {
        Nodo *t = p;
        p = p->next;
        free(t);
    }
    l->head = NULL;
    l->tamanho = 0;
}
