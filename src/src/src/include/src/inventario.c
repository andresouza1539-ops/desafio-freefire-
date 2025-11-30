#include <stdio.h>
#include <string.h>
#include "inventario.h"

void iv_inicializar(InventarioVetor *iv) {
    iv->tamanho = 0;
}

int iv_inserir(InventarioVetor *iv, Item it) {
    if (iv->tamanho >= MAX_ITENS) return 0;
    iv->itens[iv->tamanho++] = it;
    return 1;
}

int iv_remover_por_id(InventarioVetor *iv, int id) {
    for (int i = 0; i < iv->tamanho; ++i) {
        if (iv->itens[i].id == id) {
            // shift left
            for (int j = i; j < iv->tamanho - 1; ++j)
                iv->itens[j] = iv->itens[j+1];
            iv->tamanho--;
            return 1;
        }
    }
    return 0;
}

int iv_busca_sequencial(InventarioVetor *iv, const char *nome) {
    for (int i = 0; i < iv->tamanho; ++i) {
        if (strcasecmp(iv->itens[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

void iv_exibir(InventarioVetor *iv) {
    if (iv->tamanho == 0) {
        printf("Inventário (vetor) vazio.\n");
        return;
    }
    printf("Inventário (vetor) — %d itens:\n", iv->tamanho);
    printf("ID | Nome                          | Tipo       | Qtd | Prio\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < iv->tamanho; ++i) {
        Item *it = &iv->itens[i];
        printf("%2d | %-28s | %-10s | %3d | %4d\n",
               it->id, it->nome, it->tipo, it->quantidade, it->prioridade);
    }
}

/* Selection sort helper for string compare by campo */
static void swap_items(Item *a, Item *b) {
    Item t = *a;
    *a = *b;
    *b = t;
}

void iv_sort_by_name(InventarioVetor *iv, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < iv->tamanho - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < iv->tamanho; ++j) {
            (*comparacoes)++;
            if (strcasecmp(iv->itens[j].nome, iv->itens[min].nome) < 0) {
                min = j;
            }
        }
        if (min != i) swap_items(&iv->itens[i], &iv->itens[min]);
    }
}

void iv_sort_by_tipo(InventarioVetor *iv, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < iv->tamanho - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < iv->tamanho; ++j) {
            (*comparacoes)++;
            int cmp = strcasecmp(iv->itens[j].tipo, iv->itens[min].tipo);
            if (cmp < 0 || (cmp == 0 && iv->itens[j].prioridade > iv->itens[min].prioridade)) {
                min = j;
            }
        }
        if (min != i) swap_items(&iv->itens[i], &iv->itens[min]);
    }
}

void iv_sort_by_prioridade(InventarioVetor *iv, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < iv->tamanho - 1; ++i) {
        int max = i;
        for (int j = i + 1; j < iv->tamanho; ++j) {
            (*comparacoes)++;
            if (iv->itens[j].prioridade > iv->itens[max].prioridade) {
                max = j;
            }
        }
        if (max != i) swap_items(&iv->itens[i], &iv->itens[max]);
    }
}
