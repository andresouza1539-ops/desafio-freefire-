#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "inventario.h"
#include "lista_encadeada.h"
#include "busca.h"
#include "ordenacao.h"

void pausar() {
    printf("\nPressione ENTER para continuar...");
    while (getchar() != '\n');
}

/* helper para criar item com id automático */
Item novo_item(int id, const char *nome, const char *tipo, int qtd, int prio) {
    Item it;
    it.id = id;
    strncpy(it.nome, nome, MAX_NOME - 1);
    it.nome[MAX_NOME - 1] = '\0';
    strncpy(it.tipo, tipo, MAX_TIPO - 1);
    it.tipo[MAX_TIPO - 1] = '\0';
    it.quantidade = qtd;
    it.prioridade = prio;
    return it;
}

/* funções de menu e interação */
void menu_principal();
void etapa_1_organizacao(InventarioVetor *iv);
void etapa_2_eficiencia(InventarioVetor *iv, ListaEncadeada *le);
void etapa_3_estrategia(InventarioVetor *iv, ListaEncadeada *le);

/* leitura simples de linha */
void read_line(char *buf, int size) {
    if (fgets(buf, size, stdin)) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
    }
}

int main() {
    InventarioVetor iv;
    ListaEncadeada le;
    iv_inicializar(&iv);
    le_inicializar(&le);

    // itens iniciais (exemplos)
    iv_inserir(&iv, novo_item(1, "Cantil de Água", "Alimento", 3, 5));
    iv_inserir(&iv, novo_item(2, "Pistola 9mm", "Arma", 1, 8));
    iv_inserir(&iv, novo_item(3, "Corda", "Ferramenta", 2, 6));
    iv_inserir(&iv, novo_item(4, "Madeira", "Recurso", 10, 4));
    iv_inserir(&iv, novo_item(5, "Kit Medico", "Alimento", 1, 9));

    int opc;
    do {
        printf("\n=== Mini Game: Sobrevivência (TechNova) ===\n");
        printf("1. Etapa 1 — Organização (inventário vetor)\n");
        printf("2. Etapa 2 — Eficiência (lista encadeada vs vetor)\n");
        printf("3. Etapa 3 — Estratégia (construir torre de fuga)\n");
        printf("4. Exibir inventário (vetor)\n");
        printf("5. Exibir inventário (lista encadeada)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) {
            while (getchar() != '\n');
            opc = -1;
        }
        while (getchar() != '\n'); // limpar buffer

        switch (opc) {
            case 1:
                etapa_1_organizacao(&iv);
                break;
            case 2:
                etapa_2_eficiencia(&iv, &le);
                break;
            case 3:
                etapa_3_estrategia(&iv, &le);
                break;
            case 4:
                iv_exibir(&iv);
                pausar();
                break;
            case 5:
                le_exibir(&le);
                pausar();
                break;
            case 0:
                printf("Saindo... boa sorte na ilha!\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opc != 0);

    le_liberar(&le);
    return 0;
}

/* Etapa 1 — trabalhar com vetor */
void etapa_1_organizacao(InventarioVetor *iv) {
    int escolha;
    char buffer[128];
    static int proximo_id = 6; // já inserimos 5 iniciais

    do {
        printf("\n--- Etapa 1: Organização ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item por ID\n");
        printf("3. Buscar por nome (sequencial)\n");
        printf("4. Ordenar por nome (Selection Sort)\n");
        printf("5. Ordenar por prioridade (Selection Sort)\n");
        printf("6. Ordenar por tipo (Selection Sort)\n");
        printf("7. Buscar binária (iterativa)\n");
        printf("8. Buscar binária (recursiva)\n");
        printf("9. Mostrar inventário\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &escolha) != 1) {
            while (getchar() != '\n');
            escolha = -1;
        }
        while (getchar() != '\n');

        int idx;
        long comps;
        switch (escolha) {
            case 1:
                printf("Nome: ");
                read_line(buffer, sizeof(buffer));
                char tipo[32];
                printf("Tipo (Alimento/Arma/Ferramenta/Recurso): ");
                read_line(tipo, sizeof(tipo));
                int qtd, prio;
                printf("Quantidade: ");
                scanf("%d", &qtd); while (getchar() != '\n');
                printf("Prioridade (1-10): ");
                scanf("%d", &prio); while (getchar() != '\n');
                if (iv_inserir(iv, novo_item(proximo_id++, buffer, tipo, qtd, prio)))
                    printf("Item inserido com sucesso.\n");
                else printf("Falha ao inserir (capacidade máxima).\n");
                pausar();
                break;
            case 2:
                printf("ID para remover: ");
                int id; scanf("%d", &id); while (getchar() != '\n');
                if (iv_remover_por_id(iv, id)) printf("Removido.\n");
                else printf("ID não encontrado.\n");
                pausar();
                break;
            case 3:
                printf("Nome para buscar: ");
                read_line(buffer, sizeof(buffer));
                idx = iv_busca_sequencial(iv, buffer);
                if (idx >= 0) {
                    Item *it = &iv->itens[idx];
                    printf("Encontrado: ID %d — %s (%s)\n", it->id, it->nome, it->tipo);
                } else printf("Não encontrado.\n");
                pausar();
                break;
            case 4:
                iv_sort_by_name(iv, &comps);
                printf("Ordenado por nome. Comparações: %ld\n", comps);
                pausar();
                break;
            case 5:
                iv_sort_by_prioridade(iv, &comps);
                printf("Ordenado por prioridade (desc). Comparações: %ld\n", comps);
                pausar();
                break;
            case 6:
                iv_sort_by_tipo(iv, &comps);
                printf("Ordenado por tipo. Comparações: %ld\n", comps);
                pausar();
                break;
            case 7:
                printf("OBS: O inventário deve estar ordenado por nome antes da busca binária.\n");
                printf("Nome para buscar: ");
                read_line(buffer, sizeof(buffer));
                idx = busca_binaria_iterativa(iv, buffer);
                if (idx >= 0) {
                    Item *it = &iv->itens[idx];
                    printf("Encontrado (iterativo): ID %d — %s\n", it->id, it->nome);
                } else printf("Não encontrado.\n");
                pausar();
                break;
            case 8:
                printf("Nome para buscar: ");
                read_line(buffer, sizeof(buffer));
                idx = busca_binaria_recursiva(iv, buffer, 0, iv->tamanho - 1);
                if (idx >= 0) {
                    Item *it = &iv->itens[idx];
                    printf("Encontrado (recursivo): ID %d — %s\n", it->id, it->nome);
                } else printf("Não encontrado.\n");
                pausar();
                break;
            case 9:
                iv_exibir(iv);
                pausar();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 0);
}

/* Etapa 2 — comparar com lista encadeada */
void etapa_2_eficiencia(InventarioVetor *iv, ListaEncadeada *le) {
    int escolha;
    char buffer[128];
    static int proximo_id_le = 100; // ids diferentes para exemplaridade

    do {
        printf("\n--- Etapa 2: Eficiência (lista encadeada vs vetor) ---\n");
        printf("1. Inserir item na lista encadeada (fim)\n");
        printf("2. Inserir item na lista encadeada (início)\n");
        printf("3. Remover por ID (lista encadeada)\n");
        printf("4. Buscar por nome (lista encadeada)\n");
        printf("5. Comparar tempo lógico (simulação) de inserção/remocao\n");
        printf("6. Copiar vetor para lista encadeada\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &escolha) != 1) {
            while (getchar() != '\n');
            escolha = -1;
        }
        while (getchar() != '\n');

        Nodo *n;
        int id;
        switch (escolha) {
            case 1:
                printf("Nome: "); read_line(buffer, sizeof(buffer));
                char tipo[32];
                printf("Tipo: "); read_line(tipo, sizeof(tipo));
                int qtd, prio;
                printf("Quantidade: "); scanf("%d", &qtd); while (getchar() != '\n');
                printf("Prioridade: "); scanf("%d", &prio); while (getchar() != '\n');
                if (le_inserir_fim(le, novo_item(proximo_id_le++, buffer, tipo, qtd, prio)))
                    printf("Inserido no fim da lista.\n");
                else printf("Falha na inserção.\n");
                pausar();
                break;
            case 2:
                printf("Nome: "); read_line(buffer, sizeof(buffer));
                printf("Tipo: "); read_line(tipo, sizeof(tipo));
                printf("Quantidade: "); scanf("%d", &qtd); while (getchar() != '\n');
                printf("Prioridade: "); scanf("%d", &prio); while (getchar() != '\n');
                if (le_inserir_inicio(le, novo_item(proximo_id_le++, buffer, tipo, qtd, prio)))
                    printf("Inserido no início da lista.\n");
                else printf("Falha na inserção.\n");
                pausar();
                break;
            case 3:
                printf("ID para remover: "); scanf("%d", &id); while (getchar() != '\n');
                if (le_remover_por_id(le, id)) printf("Removido.\n");
                else printf("ID não encontrado.\n");
                pausar();
                break;
            case 4:
                printf("Nome para buscar: "); read_line(buffer, sizeof(buffer));
                n = le_busca_sequencial(le, buffer);
                if (n) printf("Encontrado: ID %d — %s\n", n->data.id, n->data.nome);
                else printf("Não encontrado.\n");
                pausar();
                break;
            case 5:
                printf("Simulação: inserir no fim (vetor vs lista)\n");
                printf("- Vetor: inserir no fim é O(1) amortizado (se houver espaço).\n");
                printf("- Lista encadeada: inserir no fim é O(n) se não tivermos ponteiro tail; O(1) se tivermos tail.\n");
                printf("Simulação: remover do meio:\n");
                printf("- Vetor: O(n) (shift de elementos)\n");
                printf("- Lista: O(n) (procura) mas remoção é O(1) após localizar\n");
                pausar();
                break;
            case 6:
                le_liberar(le);
                for (int i = 0; i < iv->tamanho; ++i) {
                    le_inserir_fim(le, iv->itens[i]);
                }
                printf("Copiado vetor para lista encadeada.\n");
                pausar();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 0);
}

/* Etapa 3 — estratégia e construção da torre de fuga */
void etapa_3_estrategia(InventarioVetor *iv, ListaEncadeada *le) {
    printf("\n--- Etapa 3: Estratégia ---\n");
    printf("Objetivo: construir a torre de fuga. Requer recursos: Madeiras >= 5, Cordas >= 2, Kit Medico >=1\n");
    int madeiras = 0, cordas = 0, kits = 0;
    // contar no inventário vetor
    for (int i = 0; i < iv->tamanho; ++i) {
        if (strcasecmp(iv->itens[i].nome, "Madeira") == 0) madeiras += iv->itens[i].quantidade;
        if (strcasecmp(iv->itens[i].nome, "Corda") == 0) cordas += iv->itens[i].quantidade;
        if (strcasecmp(iv->itens[i].nome, "Kit Medico") == 0) kits += iv->itens[i].quantidade;
    }
    printf("Recursos detectados — Madeiras: %d, Cordas: %d, Kits: %d\n", madeiras, cordas, kits);

    if (madeiras >= 5 && cordas >= 2 && kits >= 1) {
        printf("Você tem recursos suficientes para construir a torre!\n");
        printf("Deseja consumir os recursos e ativar a torre? (s/n): ");
        char op = getchar(); while (getchar() != '\n');
        if (tolower(op) == 's') {
            // remover parcialmente do inventário (simples: vamos reduzir quantidades)
            int need_m = 5, need_c = 2, need_k = 1;
            for (int i = 0; i < iv->tamanho && (need_m>0 || need_c>0 || need_k>0); ++i) {
                if (need_m > 0 && strcasecmp(iv->itens[i].nome, "Madeira") == 0) {
                    int use = iv->itens[i].quantidade < need_m ? iv->itens[i].quantidade : need_m;
                    iv->itens[i].quantidade -= use;
                    need_m -= use;
                }
                if (need_c > 0 && strcasecmp(iv->itens[i].nome, "Corda") == 0) {
                    int use = iv->itens[i].quantidade < need_c ? iv->itens[i].quantidade : need_c;
                    iv->itens[i].quantidade -= use;
                    need_c -= use;
                }
                if (need_k > 0 && strcasecmp(iv->itens[i].nome, "Kit Medico") == 0) {
                    int use = iv->itens[i].quantidade < need_k ? iv->itens[i].quantidade : need_k;
                    iv->itens[i].quantidade -= use;
                    need_k -= use;
                }
            }
            // limpar itens com quantidade 0
            for (int i = 0; i < iv->tamanho; ) {
                if (iv->itens[i].quantidade <= 0) {
                    iv_remover_por_id(iv, iv->itens[i].id);
                } else i++;
            }
            printf("Recursos consumidos. Torre ativada! Você escapou!\n");
        } else {
            printf("Você escolheu não ativar a torre agora.\n");
        }
    } else {
        printf("Recursos insuficientes. Dicas:\n");
        if (madeiras < 5) printf("- Colete %d madeiras a mais.\n", 5 - madeiras);
        if (cordas < 2) printf("- Colete %d cordas a mais.\n", 2 - cordas);
        if (kits < 1) printf("- Procure 1 kit médico.\n");
    }
    pausar();
}
