# Solução

Para resolver este problema, podemos estabelecer a *invariante* de que as listas que representam os conjuntos estarão sempre ordenadas após cada operação. Sob essa invariante, todas as operações se tornam simples.

Consideraremos que cada lista tem a seguinte estrutura:

ListNode:
- `val`: Valor do nó.
- `next`: Ponteiro para o próximo nó.
- `prev`: Ponteiro para o nó anterior.

List:
- `name`: Nome da lista.
- `size`: Tamanho da lista.
- `head`: Nó inicial ou `NULL` se a lista estiver vazia.

Agora podemos analisar cada função:

-   `i A t x1 ... xt`: Inserir os elementos $x_{1},\ldots,x_{t}$ no conjunto $A$. Obviamente, se algum elemento a ser inserido já estiver no conjunto $A$, ele deve ser ignorado.
	- Para esta função, basta inserir cada elemento um por um. No caso do elemento $x_{i}$, devemos procurar a posição mais à esquerda onde o valor seja maior ou igual a $x_{i}$ (se não houver nenhum elemento, consideraremos esta posição como a próxima ao último da lista). Se o valor for igual a $x_{i}$ ou `NULL`, não fazemos nada; caso contrário, inserimos na posição.
-   `r A t x1 ... xt`: Remover os elementos $x_{1}, \ldots, x_{t}$ do conjunto $A$. Se algum elemento a ser removido não estiver no conjunto $A$, ele deve ser ignorado.
	- Para esta função, basta remover cada elemento um por um. No caso do elemento $x_{i}$, devemos procurar a posição mais à esquerda onde o valor seja maior ou igual a $x_{i}$ (se não houver nenhum elemento, consideraremos esta posição como a próxima ao último da lista). Se o valor for igual a $x_{i}$ ou `NULL`, não fazemos nada; caso contrário, removemos da posição.
-   `u A B C`: Atribuir ao conjunto $A$ a união dos conjuntos $B$ e $C$. $A$, $B$ e $C$ são inteiros maiores que zero e $A \not \in \{B,C\}$.
	- Para esta função, bastaria simplesmente limpar a lista $A$ (se existir) e inserir os elementos de $B$ e de $C$ na lista de maneira sequencial. Outra opção mais otimizada é manter um ponteiro $p_{B}$ no primeiro elemento de $B$ e outro ponteiro $p_{C}$ em $C$, e adicionar à lista $A$ o menor dos dois valores (se não houver tal valor, podemos considerá-lo como infinito). Se os dois valores forem iguais, avançamos ambos os ponteiros ao mesmo tempo após adicionar o valor repetido uma vez.
-   `n A B C`: Atribuir ao conjunto $A$ a interseção dos conjuntos $B$ e $C$. $A$, $B$ e $C$ são inteiros maiores que zero e $A \not \in \{B,C\}$.
	- Para esta função, bastaria simplesmente limpar a lista $A$ (se existir) e inserir os elementos de $B$ apenas se também estiverem em $C$. Outra opção mais otimizada é manter um ponteiro $p_{B}$ no primeiro elemento de $B$ e outro ponteiro $p_{C}$ em $C$, e iterar sobre todos os elementos de $B$, avançando o ponteiro $p_{C}$ até encontrar o primeiro elemento maior ou igual ao de $p_{B}$. Se os elementos forem iguais, adicionamos o valor; caso contrário, não adicionamos a $A$.
-   `m A B C`: Atribuir ao conjunto $A$ a diferença dos conjuntos $B$ e $C$. $A$, $B$ e $C$ são inteiros maiores que zero e $A \not \in \{B,C\}$.
	- Para esta função, bastaria simplesmente limpar a lista $A$ (se existir) e inserir os elementos de $B$ em $A$ se eles não estiverem em $C$. Outra opção mais otimizada é manter um ponteiro $p_{B}$ no primeiro elemento de $B$ e outro ponteiro $p_{C}$ em $C$, e iterar sobre todos os elementos de $B$, avançando o ponteiro $p_{C}$ até encontrar o primeiro elemento maior ou igual ao de $p_{B}$. Se os elementos forem iguais, não adicionamos o valor; caso contrário, adicionamos a $A$.
-   `e A x`: Imprimir "x está em CA" ou "x não está em CA" em uma única linha, conforme ilustrado no exemplo.
	- Para esta função, basta iterar sobre os elementos de $A$ e compará-los com $x$.
-   `p A`: Imprimir os elementos do conjunto $A$ em ordem crescente e em uma única linha, conforme ilustrado abaixo.
	- Para esta função, basta iterar e imprimir os elementos seguindo o formato.
