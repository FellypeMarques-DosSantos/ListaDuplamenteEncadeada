#include "lista_dupla.h"
#include <stdio.h>

int main() {
    ListaDupla* minha_lista = criar_lista();
    printf("--- TAD LISTA DUPLA: TESTE ---\n");

    inserir_inicio(minha_lista, 50); 
    inserir_fim(minha_lista, 10);    
    inserir_inicio(minha_lista, 100); 
    inserir_fim(minha_lista, 5);     
    inserir_posicao(minha_lista, 75, 2);
    
    printf("\n** APOS INSERCOES **\n");
    exibir_lista(minha_lista);
    exibir_lista_reversa(minha_lista);

    No* no_busca_pos = buscar_posicao(minha_lista, 3);
    if (no_busca_pos) {
        printf("\n** BUSCA POR POSICAO **\n");
        printf("Elemento na posicao 3: %d\n", no_busca_pos->dado);
    }

    No* no_busca_val = buscar_valor(minha_lista, 50);
    if (no_busca_val) {
        printf("\n** BUSCA POR VALOR **\n");
        printf("Valor 50 encontrado: %d\n", no_busca_val->dado);
    }

    printf("\n** REMOCAO POR VALOR **\n");
    if (remover_valor(minha_lista, 75)) { // Remove 75 (meio)
        printf("Valor 75 removido com sucesso.\n");
    }
    exibir_lista(minha_lista);

    printf("\n** REMOCAO POR POSICAO **\n");
    TipoDado removido_pos = remover_posicao(minha_lista, 0);
    printf("Removido da posicao 0: %d\n", removido_pos);
    exibir_lista(minha_lista);
    
    remover_fim(minha_lista);
    remover_inicio(minha_lista); 
    exibir_lista(minha_lista); 

    destruir_lista(minha_lista);

    return 0;
}
