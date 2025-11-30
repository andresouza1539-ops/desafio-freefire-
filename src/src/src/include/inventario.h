#ifndef INVENTARIO_H
#define INVENTARIO_H

#define MAX_ITENS 100
#define MAX_NOME 50
#define MAX_TIPO 20

typedef struct {
    int id;
    char nome[MAX_NOME];
    char tipo[MAX_TIPO]; // "Alimento", "Arma", "Ferramenta", "Recurso"
    int quantidade;
    int prioridade; // maior = mais importante
} Item;

/* Vetor (lista sequencial) */
typedef struct {
    Item itens[MAX_ITENS];
    int tamanho;
} InventarioVetor;

/* Funções do inventário vetor */
void iv_inicializar(InventarioVetor *iv);
int iv_inserir(InventarioVetor *iv, Item it);
int iv_remover_por_id(InventarioVetor *iv, int id);
int iv_busca_sequencial(InventarioVetor *iv, const char *nome);
void iv_exibir(InventarioVetor *iv);
void iv_sort_by_name(InventarioVetor *iv, long *comparacoes);
void iv_sort_by_tipo(InventarioVetor *iv, long *comparacoes);
void iv_sort_by_prioridade(InventarioVetor *iv, long *comparacoes);

#endif
