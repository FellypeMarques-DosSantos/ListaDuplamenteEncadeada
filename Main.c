#include "lista_dupla.h"
#include <stdio.h>

int main() {
    // 1. CRIAÇÃO
    ListaDupla* minha_lista = criar_lista();
    printf("--- TAD LISTA DUPLA: TESTE ---\n");

    // 2. INSERÇÃO
    inserir_inicio(minha_lista, 50); // [50]
    inserir_fim(minha_lista, 10);    // [50, 10]
    inserir_inicio(minha_lista, 100); // [100, 50, 10]
    inserir_fim(minha_lista, 5);     // [100, 50, 10, 5]
    inserir_posicao(minha_lista, 75, 2); // [100, 50, 75, 10, 5]
    
    printf("\n** APOS INSERCOES **\n");
    exibir_lista(minha_lista);
    exibir_lista_reversa(minha_lista); // Testa os ponteiros 'anterior'

    // 3. BUSCA POR POSIÇÃO
    No* no_busca_pos = buscar_posicao(minha_lista, 3);
    if (no_busca_pos) {
        printf("\n** BUSCA POR POSICAO **\n");
        printf("Elemento na posicao 3: %d\n", no_busca_pos->dado); // Deve ser 10
    }

    // 4. BUSCA POR VALOR
    No* no_busca_val = buscar_valor(minha_lista, 50);
    if (no_busca_val) {
        printf("\n** BUSCA POR VALOR **\n");
        printf("Valor 50 encontrado: %d\n", no_busca_val->dado);
    }

    // 5. REMOÇÃO POR VALOR
    printf("\n** REMOCAO POR VALOR **\n");
    if (remover_valor(minha_lista, 75)) { // Remove 75 (meio)
        printf("Valor 75 removido com sucesso.\n");
    }
    exibir_lista(minha_lista); // Lista: [100, 50, 10, 5]

    // 6. REMOÇÃO POR POSIÇÃO
    printf("\n** REMOCAO POR POSICAO **\n");
    TipoDado removido_pos = remover_posicao(minha_lista, 0); // Remove 100 (inicio)
    printf("Removido da posicao 0: %d\n", removido_pos);
    exibir_lista(minha_lista); // Lista: [50, 10, 5]
    
    // 7. REMOÇÃO INICIO/FIM
    remover_fim(minha_lista); // Remove 5
    remover_inicio(minha_lista); // Remove 50
    exibir_lista(minha_lista); // Lista: [10]

    // 8. DESTRUIÇÃO
    destruir_lista(minha_lista);

    return 0;
}
