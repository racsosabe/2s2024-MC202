# Solução

Para resolver este problema usando o [*treap implícito*](https://cp-algorithms.com/data_structures/treap.html#implicit-treaps), vamos definir as estruturas da seguinte forma:

TreapNode:

- `val`: Valor armazenado no nó.
- `cnt`: Quantidade de elementos na subárvore do nó.
- `priority`: Prioridade do nó (número aleatório para formar a árvore com estrutura de *heap* em relação a esse valor).
- `rev`: Booleano que representa se o revertimento de todos os elementos na subárvore está pendente ou não.
- `left`: Ponteiro para o filho esquerdo do nó.
- `right`: Ponteiro para o filho direito do nó.

Treap:
- `root`: Nó raiz do treap.

Vamos considerar que temos tudo o necessário para construir um treap (um gerador aleatório de números) e que também implementamos adequadamente as seguintes funções:

- `split(root, key)`: Divide a árvore em duas subárvores $L$ e $R$, tais que $L$ consiste nos primeiros $key$ nós da *travessia in-order* da subárvore original e $R$ consiste nos restantes.
- `merge(l, r)`: Une duas subárvores com raízes $l$ e $r$ em uma única árvore.

Agora, vejamos como implementar cada uma das operações requeridas:

-   `i p x`: Inserir  x  na posição  p  da lista encadeada. O double  x  ocupará a posição  p  na lista encadeada. O double que ocupa a posição  p  antes da inserção ficará na posição  p+1. Se  p  for maior ou igual ao tamanho da lista encadeada, a inserção deve ser feita no fim da lista encadeada. Por exemplo, se uma lista encadeada tiver  5  nós, a inserção de  3.14  na posição  9  fará com que  3.14  seja inserido na posição  5.
	- Consideraremos que o nó adicionado é `cur`. Podemos chamar a função `split(root, p)`, e isso nos dará duas subárvores `L` e `R`, entre as quais devemos colocar `cur`. Finalmente, podemos chamar `merge(L, merge(cur, R))`, e a nova árvore coincidirá com o que desejamos.
-   `r p`: Remover um nó da posição  p  da lista encadeada. Podemos chamar a função `split(root, p)`, que nos dará duas subárvores `L` e `R`. Em seguida, podemos chamar `split(R, 1)`, que nos dará `R1` e `R2`, onde `R1` é o nó que queremos remover. Finalmente, chamamos `merge(L, R2)`, e a nova árvore coincidirá com o que desejamos.
-   `p`: Imprimir a lista encadeada em uma única linha. Cada elemento da lista encadeada deve ser seguido de um espaço. A lista encadeada vazia deve ser impressa como uma linha vazia.
	- Para essa função, basta chamar uma *travessia in-order* na árvore.
-   `v i t`: Reverter a ordem dos elementos no trecho  [i..t]  da lista encadeada. Seja  n  o tamanho da lista antes da operação. Se  $0 \leq i \leq t<n$, a operação deve reverter a ordem dos elementos nas posições entre  i  e  t  inclusive. Caso contrário, a operação não deve fazer nada.
	- Para esta função, basta fazer um `split(root, t + 1)`, que nos dará `L` e `R`, e então um `split(L, i)`, que nos dará `L1` e `L2`. Depois, marcamos o booleano `L2 -> rev = true` e chamamos `merge(L1, merge(L2, R))`.
-   `x i t p`: Mover o trecho  [i..t]  da lista encadeada para a posição  p. Seja  n  o tamanho da lista antes da operação. Se  $0 \leq i \leq t<n$, a operação deve mover todos os elementos nas posições entre  i  e  t  inclusive, de modo que os nós movidos fiquem imediatamente antes do nó na posição  p  (p  deve estar fora do intervalo  [i…t]). Se  p  for maior ou igual ao tamanho da lista encadeada, o trecho deve ser movido para o final da lista encadeada. Caso contrário, a operação não deve fazer nada.
	- Para mover o trecho $[i, t]$ à esquerda da posição $p$, podemos definir 4 blocos, dependendo do caso:
		- Quando $t < p$:
		![](https://i.imgur.com/PUUa9uH.png)
		Então, nesse caso, desejamos terminar com a lista formada pelos blocos na ordem $A, C, B, D$. Para isso, basta fazer os splits e mergear as subárvores na nova ordem desejada.
			1. `split(root, t  +  1)`, que nos dá `M` e `R`.	
			2. `split(M, i)`, que nos dá `A` e `B`.
			3. `split(R, p - t + 1)`, que nos dá `C` e `D`.
			4. `merge(merge(A, C), merge(B, D))`
		- Quando $p < i$:
		![](https://i.imgur.com/qpNjicZ.png)
		Então, nesse caso, desejamos terminar com a lista formada pelos blocos na ordem $A, C, B, D$. Para isso, basta fazer os splits e mergear as subárvores na nova ordem desejada.
			1. `split(root, t  +  1)`, que nos dá `M` e `D`.
			2. `split(M, i)`, que nos dá `L` e `C`.
			3. `split(L, p)`, que nos dá `A` e `B`.
			4. `merge(merge(A, C), merge(B, D))`