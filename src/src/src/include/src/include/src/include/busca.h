#ifndef BUSCA_H
#define BUSCA_H

#include "inventario.h"

/* Busca binária em vetor — iterativa e recursiva
   - pressupõe vetor ordenado por nome (case-insensitive)
   - retorna índice ou -1 se não encontrar
*/
int busca_binaria_iterativa(InventarioVetor *iv, const char *nome);
int busca_binaria_recursiva(InventarioVetor *iv, const char *nome, int lo, int hi);

#endif
