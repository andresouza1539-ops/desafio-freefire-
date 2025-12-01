#include <string.h>
#include "ordenacao.h"

static void swap_item(Item *a, Item *b) {
    Item t = *a;
    *a = *b;
    *b = t;
}

void bubble_sort_by_name(InventarioVetor *iv, long *comparacoes) {
    *comparacoes = 0;
    int n = iv->tamanho;
    int swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = 0;
        for (int j = 0; j < n - 1 - i; ++j) {
            (*comparacoes)++;
            if (strcasecmp(iv->itens[j].nome, iv->itens[j+1].nome) > 0) {
                swap_item(&iv->itens[j], &iv->itens[j+1]);
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

void insertion_sort_by_name(InventarioVetor *iv, long *comparacoes) {
    *comparacoes = 0;
    int n = iv->tamanho;
    for (int i = 1; i < n; ++i) {
        Item key = iv->itens[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (strcasecmp(iv->itens[j].nome, key.nome) > 0) {
                iv->itens[j+1] = iv->itens[j];
                j--;
            } else break;
        }
        iv->itens[j+1] = key;
    }
}
