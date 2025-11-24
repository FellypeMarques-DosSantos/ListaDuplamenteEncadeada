#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H

#include <stdbool.h>

// Definição do Tipo de Dado a ser armazenado na lista
typedef int TipoDado;

// 1. Estrutura do Nó (Node)
typedef struct No {
    TipoDado dado;
    struct No* proximo;
    struct No* anterior;
} No;

// 2. Estrutura da Lista Duplamente Encadeada (TAD)
typedef struct ListaDupla {
    No* cabeca;
    No* cauda;
    int tamanho;
} ListaDupla;

// --- ASSINATURAS DAS FUNÇÕES (INTERFACE) ---

// Funções de Criação e Status
ListaDupla* criar_lista();
bool lista_vazia(ListaDupla* lista);
int tamanho_lista(ListaDupla* lista);

// Funções de Inserção
void inserir_inicio(ListaDupla* lista, TipoDado dado);
void inserir_fim(ListaDupla* lista, TipoDado dado);
bool inserir_posicao(ListaDupla* lista, TipoDado dado, int posicao);

// Funções de Remoção
TipoDado remover_inicio(ListaDupla* lista);
TipoDado remover_fim(ListaDupla* lista);
TipoDado remover_posicao(ListaDupla* lista, int posicao);
bool remover_valor(ListaDupla* lista, TipoDado valor);

// Funções de Busca
No* buscar_posicao(ListaDupla* lista, int posicao);
No* buscar_valor(ListaDupla* lista, TipoDado valor);

// Funções de Exibição e Destruição
void exibir_lista(ListaDupla* lista);
void exibir_lista_reversa(ListaDupla* lista);
void destruir_lista(ListaDupla* lista);

#endif // LISTA_DUPLA_H
