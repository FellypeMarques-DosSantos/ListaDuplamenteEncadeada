#ifndef lista_dupla.h
#define lista_dupla.h

#include <stdbool.h>

typedef int TipoDado;

typedef struct No {
    TipoDado dado;
    struct No* proximo;
    struct No* anterior;
} No;

typedef struct ListaDupla {
    No* cabeca;
    No* cauda;
    int tamanho;
} ListaDupla;

ListaDupla* criar_lista();
bool lista_vazia(ListaDupla* lista);
int tamanho_lista(ListaDupla* lista);

void inserir_inicio(ListaDupla* lista, TipoDado dado);
void inserir_fim(ListaDupla* lista, TipoDado dado);
bool inserir_posicao(ListaDupla* lista, TipoDado dado, int posicao);

TipoDado remover_inicio(ListaDupla* lista);
TipoDado remover_fim(ListaDupla* lista);
TipoDado remover_posicao(ListaDupla* lista, int posicao);
bool remover_valor(ListaDupla* lista, TipoDado valor);

No* buscar_posicao(ListaDupla* lista, int posicao);
No* buscar_valor(ListaDupla* lista, TipoDado valor);

void exibir_lista(ListaDupla* lista);
void exibir_lista_reversa(ListaDupla* lista);
void destruir_lista(ListaDupla* lista);

#endif // LISTA_DUPLA_H
