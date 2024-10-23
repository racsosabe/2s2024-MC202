#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "dequef.h"


/**
   Cria um deque vazio de floats.

   A capacidade é tanto a capacidade inicial quanto a mínima.
   O fator é o fator de redimensionamento, maior que 1.0.

   Em caso de sucesso, retorna o endereço de um novo dequef.
   Em caso de falha, retorna NULL.
**/
dequef* df_alloc(long capacity, double factor) {
   dequef * novo_deque = (dequef*)malloc(sizeof(dequef)); // Aloca memória para um novo deque
   novo_deque->data = (float*)malloc(capacity * sizeof(float)); // Aloca memória para os dados do deque
   novo_deque->factor = factor; // Define o fator de redimensionamento
   novo_deque->cap = capacity; // Define a capacidade inicial
   novo_deque->mincap = capacity;
   novo_deque->size=0;
   novo_deque->first = 0;
   return novo_deque; // Retorna o novo deque
}



/**
   Libera um dequef e seus dados.
**/
void df_free(dequef* D) {
   free(D->data); // Libera a memória dos dados
   free(D); // Libera a memória do deque
   return; // Retorna
}



/**
   Retorna o tamanho do deque.
**/
long df_size(dequef* D) {
   if(D!=NULL)
   return D->size; // Retorna a capacidade do deque
   return 0;
}

/** 
   Redimensiona o deque.

   Tenta aumentar o tamanho do array para
   capacity * factor.
   Em caso de sucesso, retorna 1.
**/

int df_Resize(dequef* D) {
    if (D->size <= (int)(D->cap / (D->factor * D->factor)) && D->cap > D->mincap) {
        // Lógica para reduzir o tamanho
        int new_cap = D->cap / D->factor; // Calcula nova capacidade
        if (new_cap < D->mincap) {
            new_cap = D->mincap; // Assegura que não seja menor que a mínima
        }

        float* temp = (float*)malloc(new_cap * sizeof(float)); // Aloca nova memória
        if (temp == NULL) {
            return 0; // Retorna falha
        }

        for (int i = 0; i < D->size; i++) {
            temp[i] = D->data[(D->first + i) % D->cap];
        }

        free(D->data);
        D->data = temp;
        D->first = 0;
        D->cap = new_cap;
    } else if (D->size >= D->cap) {
        // Lógica para aumentar o tamanho
        int new_cap = (int)(D->cap * D->factor);
        float* temp = (float*)malloc(new_cap * sizeof(float)); // Aloca nova memória
        if (temp == NULL) {
            return 0; // Retorna falha
        }

        for (int i = 0; i < D->size; i++) {
            temp[i] = D->data[(D->first + i) % D->cap];
        }

        free(D->data);
        D->data = temp;
        D->first = 0;
        D->cap = new_cap;
    }
    return 0; // Retorna sucesso
}

/**
   Reorganiza os dados do deque.

   Tenta organizar o array.
   Em caso de sucesso, retorna 1.
void df_Reorganize(dequef* D) {
    if (D->size == 0) { // Verifica se o deque está vazio
        return; // Não faz nada se estiver vazio
    }

    float *temp = malloc(D->cap * sizeof(float)); // Aloca memória para reorganização
    if (temp == NULL) { // Verifica se a alocação falhou
        return; // Não faz nada se a alocação falhar
    }

    // Copia os dados existentes para a nova memória
    for (int i = 0; i < D->size; i++) {
        temp[i] = D->data[(D->first + i) % D->cap];
    }

    free(D->data); // Libera a memória antiga
    D->data = temp; // Atualiza o ponteiro para os dados
    D->first = 0; // Reinicia o índice do primeiro elemento
    return; // Retorna
}
**/


/**
   Adiciona x ao final de D.

   Se o array estiver cheio, tenta aumentar o tamanho do array para
   capacity * factor.

   Em caso de sucesso, retorna 1.
   Se a tentativa de redimensionar o array falhar, retorna 0 e D permanece inalterado.
**/
int df_push(dequef* D, float x) {
    if (D->size >= D->cap) { // Alterado para '>=', garante que não exceda a capacidade
        if (!df_Resize(D)) {
            return 0; // Falha ao redimensionar
        }
    }
    D->data[(D->first + D->size) % D->cap] = x; // Adiciona o elemento corretamente
    D->size++;
    return 1; // Sucesso
}


/**
   Remove um float do final de D e o retorna.

   Se o deque tem capacidade/(factor^2), tenta reduzir o tamanho do array para
   capacity/factor. Se capacity/factor é menor que a capacidade mínima,
   a capacidade mínima é usada em vez disso. Se não for possível redimensionar, 
   o tamanho do array permanece inalterado.

   Retorna o float removido de D.
   O que acontece se D estiver vazio antes da chamada?
**/
float df_pop(dequef* D) {
    if (D->size == 0) { // Verifica se o deque está vazio
        return 0.0; // Retorna
    }
    float x = D->data[(D->first + D->size - 1) % D->cap]; // Acesso ao último elemento
    D->size--;
    df_Resize(D); // Redimensiona se necessário
    return x; // Retorna o valor removido
}


/**
   Adiciona x ao início de D.

   Se o array estiver cheio, tenta aumentar o tamanho do array para
   capacity * factor.

   Em caso de sucesso, retorna 1.
   Se a tentativa de redimensionar o array falhar, retorna 0 e D permanece inalterado.
**/
int df_inject(dequef* D, float x) {
   if(df_Resize(D) || D->size < D->cap) { // Tenta redimensionar ou verifica se há espaço
      if (D->first == 0) { // Se o índice do primeiro elemento for 0
        D->first = D->cap - 1; // Faz o primeiro elemento apontar para o final
      } else {
        D->first--; // Decrementa o índice do primeiro elemento
      }
      puts("ASSIGNING");
      printf("%ld\n", D -> first);
      D->data[D->first] = x; // Adiciona x no início
      puts("ASSIGNED");
      D->size++; // Incrementa o tamanho

      return 1; // Retorna sucesso
   }
   return 0; // Retorna falha
}



/**
   Remove um float do início de D e o retorna.

   Se o deque tem capacity/(factor^2) elementos, essa função tenta reduzir
   o tamanho do array para capacity/factor. Se capacity/factor é menor que a
   capacidade mínima, a capacidade mínima é usada em vez disso.

   Se não for possível redimensionar, o tamanho do array permanece inalterado.

   Retorna o float removido de D.
   O que acontece se D estiver vazio antes da chamada?
**/
float df_eject(dequef* D) {
    if (D->size == 0) { // Verifica se o deque está vazio
        // Lida com o caso de deque vazio, retornando um valor sentinel ou tratando erro
        fprintf(stderr, "Erro: Tentativa de ejetar de um deque vazio.\n");
        return -1; // Retorna um float inválido como indicação de erro
    }

    float removed_value = D->data[D->first]; // Obtém o valor a ser removido

    // Atualiza o índice do primeiro elemento para remover o elemento
    D->first = (D->first + 1) % D->cap; 
    D->size--; // Decrementa o tamanho

    // Verifica se é necessário redimensionar o array
    if (D->size <= D->cap / (D->factor * D->factor)) {
        int new_cap = D->cap / D->factor; // Calcula nova capacidade
        if (new_cap < D->mincap) {
            new_cap = D->mincap; // Assegura que a nova capacidade não seja menor que a mínima
        }

        float* temp = (float*)malloc(new_cap * sizeof(float)); // Aloca nova memória para o redimensionamento
        if (temp != NULL) {
            // Copia os dados existentes para a nova memória
            for (int i = 0; i < D->size; i++) {
                temp[i] = D->data[(D->first + i) % D->cap];
            }

            free(D->data); // Libera a memória antiga
            D->data = temp; // Atualiza o ponteiro para os dados
            D->first = 0; // Reinicia o índice do primeiro elemento
            D->cap = new_cap; // Atualiza a capacidade
        }
    }

    return removed_value; // Retorna o valor removido
}

/**
   Retorna D[i].

   Se i não está em [0,|D|-1], o que acontece então?
**/
float df_get(dequef* D, long i) {
    if (i < 0 || i >= D->size) { // Verifica se o índice está fora dos limites
        fprintf(stderr, "Erro: Índice %ld está fora dos limites.\n", i);
        return -1; // Retorna um valor inválido
    }

    return D->data[(D->first + i) % D->cap]; // Retorna o valor no índice i
}

/**
   Define D[i] como x.

   Se i não está em [0,|D|-1], o que acontece então?
**/
void df_set(dequef* D, long i, float x) {
    if (i < 0 || i >= D->size) { // Verifica se o índice está fora dos limites
        fprintf(stderr, "Erro: Índice %ld está fora dos limites.\n", i);
        return; // Retorna sem fazer nada
    }
    D->data[(D->first + i) % D->cap] = x; // Define o valor no índice i
}

/**
   Imprime os elementos de D em uma única linha.
**/
void df_print(dequef* D) {
    if (D->size == 0) { // Verifica se o deque está vazio
        printf("deque (0):\n");
        return; // Retorna se estiver vazio
    }

    printf("deque (%li): ",D->size); // Mensagem de cabeçalho
    for (int i = 0; i < D->size; i++) { // Itera sobre os elementos
        printf("%.1f ", D->data[(D->first + i) % D->cap]); // Imprime cada elemento
    }
    printf("\n"); // Nova linha após a impressão
}