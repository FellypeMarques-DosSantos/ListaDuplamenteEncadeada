#include "lista_dupla.h"
#include <stdio.h>
#include <stdlib.h>

// --- FUNÇÕES AUXILIARES ---

// Cria um novo nó
No* criar_no(TipoDado dado) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro de alocação de memória para o nó");
        exit(EXIT_FAILURE);
    }
    novo_no->dado = dado;
    novo_no->anterior = NULL;
    novo_no->proximo = NULL;
    return novo_no;
}

// --- FUNÇÕES DE CRIAÇÃO E STATUS ---

ListaDupla* criar_lista() {
    ListaDupla* nova_lista = (ListaDupla*)malloc(sizeof(ListaDupla));
    if (nova_lista == NULL) {
        perror("Erro de alocação de memória para a lista");
        exit(EXIT_FAILURE);
    }
    nova_lista->cabeca = NULL;
    nova_lista->cauda = NULL;
    nova_lista->tamanho = 0;
    return nova_lista;
}

bool lista_vazia(ListaDupla* lista) {
    return lista->tamanho == 0;
}

int tamanho_lista(ListaDupla* lista) {
    return lista->tamanho;
}

// --- FUNÇÕES DE INSERÇÃO ---

void inserir_inicio(ListaDupla* lista, TipoDado dado) {
    No* novo_no = criar_no(dado);
    if (lista_vazia(lista)) {
        lista->cabeca = novo_no;
        lista->cauda = novo_no;
    } else {
        novo_no->proximo = lista->cabeca;
        lista->cabeca->anterior = novo_no;
        lista->cabeca = novo_no;
    }
    lista->tamanho++;
}

void inserir_fim(ListaDupla* lista, TipoDado dado) {
    No* novo_no = criar_no(dado);
    if (lista_vazia(lista)) {
        lista->cabeca = novo_no;
        lista->cauda = novo_no;
    } else {
        novo_no->anterior = lista->cauda;
        lista->cauda->proximo = novo_no;
        lista->cauda = novo_no;
    }
    lista->tamanho++;
}

bool inserir_posicao(ListaDupla* lista, TipoDado dado, int posicao) {
    // Posições válidas: de 0 (início) até tamanho (fim)
    if (posicao < 0 || posicao > lista->tamanho) {
        fprintf(stderr, "Erro: Posicao %d invalida para insercao.\n", posicao);
        return false;
    }
    if (posicao == 0) {
        inserir_inicio(lista, dado);
        return true;
    }
    if (posicao == lista->tamanho) {
        inserir_fim(lista, dado);
        return true;
    }

    // 1. Encontra o nó na posição (agora será o próximo do novo nó)
    No* no_proximo = buscar_posicao(lista, posicao);
    if (no_proximo == NULL) return false; // Deve ser impossível se a verificação de limite estiver correta

    No* novo_no = criar_no(dado);
    No* no_anterior = no_proximo->anterior;

    // 2. Ajusta os ponteiros do novo nó
    novo_no->anterior = no_anterior;
    novo_no->proximo = no_proximo;

    // 3. Ajusta os ponteiros dos nós vizinhos
    no_anterior->proximo = novo_no;
    no_proximo->anterior = novo_no;

    lista->tamanho++;
    return true;
}

// --- FUNÇÕES DE REMOÇÃO ---

TipoDado remover_inicio(ListaDupla* lista) {
    if (lista_vazia(lista)) {
        fprintf(stderr, "Erro: Lista vazia. Nao e possivel remover do inicio.\n");
        exit(EXIT_FAILURE);
    }
    No* no_removido = lista->cabeca;
    TipoDado dado_removido = no_removido->dado;

    lista->cabeca = no_removido->proximo;

    if (lista->cabeca != NULL) {
        // Se ainda houver elementos, o novo primeiro nó deve ter anterior NULL
        lista->cabeca->anterior = NULL;
    } else {
        // Se a lista ficou vazia, a cauda também é NULL
        lista->cauda = NULL;
    }

    free(no_removido);
    lista->tamanho--;
    return dado_removido;
}

TipoDado remover_fim(ListaDupla* lista) {
    if (lista_vazia(lista)) {
        fprintf(stderr, "Erro: Lista vazia. Nao e possivel remover do fim.\n");
        exit(EXIT_FAILURE);
    }
    No* no_removido = lista->cauda;
    TipoDado dado_removido = no_removido->dado;

    lista->cauda = no_removido->anterior;

    if (lista->cauda != NULL) {
        // Se ainda houver elementos, o novo último nó deve ter proximo NULL
        lista->cauda->proximo = NULL;
    } else {
        // Se a lista ficou vazia, a cabeça também é NULL
        lista->cabeca = NULL;
    }

    free(no_removido);
    lista->tamanho--;
    return dado_removido;
}

TipoDado remover_posicao(ListaDupla* lista, int posicao) {
    if (posicao < 0 || posicao >= lista->tamanho) {
        fprintf(stderr, "Erro: Posicao %d invalida para remocao.\n", posicao);
        exit(EXIT_FAILURE);
    }
    if (posicao == 0) {
        return remover_inicio(lista);
    }
    if (posicao == lista->tamanho - 1) {
        return remover_fim(lista);
    }

    // 1. Encontra o nó a ser removido
    No* no_removido = buscar_posicao(lista, posicao);
    if (no_removido == NULL) {
        fprintf(stderr, "Erro interno: Nó na posicao %d nao encontrado.\n", posicao);
        exit(EXIT_FAILURE);
    }

    No* no_anterior = no_removido->anterior;
    No* no_proximo = no_removido->proximo;

    // 2. Ajusta os ponteiros dos vizinhos (re-encadeamento)
    no_anterior->proximo = no_proximo;
    no_proximo->anterior = no_anterior;

    // 3. Obtém o dado, libera a memória e atualiza o tamanho
    TipoDado dado_removido = no_removido->dado;
    free(no_removido);
    lista->tamanho--;
    return dado_removido;
}

bool remover_valor(ListaDupla* lista, TipoDado valor) {
    No* no_removido = buscar_valor(lista, valor);
    if (no_removido == NULL) {
        return false; // Valor não encontrado
    }

    // Caso o nó seja a cabeça
    if (no_removido == lista->cabeca) {
        remover_inicio(lista);
        return true;
    }

    // Caso o nó seja a cauda
    if (no_removido == lista->cauda) {
        remover_fim(lista);
        return true;
    }

    // Caso o nó esteja no meio
    No* no_anterior = no_removido->anterior;
    No* no_proximo = no_removido->proximo;

    // Re-encadeia os vizinhos
    no_anterior->proximo = no_proximo;
    no_proximo->anterior = no_anterior;

    free(no_removido);
    lista->tamanho--;
    return true;
}

// --- FUNÇÕES DE BUSCA ---

No* buscar_posicao(ListaDupla* lista, int posicao) {
    if (posicao < 0 || posicao >= lista->tamanho) {
        return NULL;
    }

    No* atual;
    
    // Otimização de busca: Se a posição for na primeira metade, busca da cabeça.
    // Se for na segunda metade, busca da cauda (vantagem da lista dupla).
    if (posicao < lista->tamanho / 2) {
        atual = lista->cabeca;
        for (int i = 0; i < posicao; i++) {
            atual = atual->proximo;
        }
    } else {
        atual = lista->cauda;
        for (int i = lista->tamanho - 1; i > posicao; i--) {
            atual = atual->anterior;
        }
    }
    
    return atual;
}

No* buscar_valor(ListaDupla* lista, TipoDado valor) {
    No* atual = lista->cabeca;
    while (atual != NULL) {
        if (atual->dado == valor) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// --- FUNÇÕES DE EXIBIÇÃO E DESTRUIÇÃO ---

void exibir_lista(ListaDupla* lista) {
    if (lista_vazia(lista)) {
        printf("Lista Duplamente Encadeada: VAZIA.\n");
        return;
    }
    
    printf("Lista (%d elementos - Inicio -> Fim): ", lista->tamanho);
    No* atual = lista->cabeca;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

void exibir_lista_reversa(ListaDupla* lista) {
    if (lista_vazia(lista)) {
        printf("Lista Duplamente Encadeada: VAZIA.\n");
        return;
    }
    
    printf("Lista (Fim -> Inicio): ");
    No* atual = lista->cauda;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->anterior;
    }
    printf("\n");
}

void destruir_lista(ListaDupla* lista) {
    No* atual = lista->cabeca;
    No* proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(lista);
    printf("\nLista destruida e memoria liberada.\n");
}
