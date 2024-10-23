# Solução

Para resolver este problema usando listas simplesmente encadeadas, vamos definir as estruturas da seguinte forma:

ListNode:

- `val`: Valor associado ao nó.
- `next`: Ponteiro para o próximo nó ou `NULL` se não existir.

List:
- `size`: Quantidade de elementos na lista.
- `head`: Primeiro elemento da lista ou `NULL` se a lista estiver vazia.

Agora, vejamos como implementar cada uma das operações requeridas:

-   `i p x`: Inserir  x  na posição  p  da lista encadeada. O double  x  passará a ocupar a posição  p  na lista encadeada. O double que ocupa a posição  p  antes da inserção ficará na posição  p+1. Se  p  for maior ou igual ao tamanho da lista encadeada, então a inserção deve ser feita no fim da lista encadeada. Por exemplo, se uma lista encadeada tiver  5  nós, a inserção de  3.14  na posição  9  deverá fazer com que  3.14  seja inserido na posição  5.
	- Consideraremos que o nó adicionado é `cur`. Como o novo nó deve ocupar a posição $p$, devemos encontrar o nó na posição $p - 1$ para atribuir o `next` de `cur` como o seguinte a esse ponteiro (chamemos de `ptr`) e depois definir `cur` como o novo `next` de `ptr`. Só precisamos considerar o caso especial $p = 0$, em que `cur` se torna o novo `head` da lista. Assumiremos que a função `get_kth(head, k)` obtém o $k$-ésimo nó da lista com elemento inicial `head`.
		```C
		if(p  ==  0) {
			cur  -> next  =  L  -> head;
			L  -> head  =  cur;
			return;
		}
		node  *ptr  =  get_kth(L  -> head, p  -  1);
		cur  -> next  =  ptr  -> next;
		ptr  -> next  =  cur;
		```
-   `r p`: Remover um nó da posição  p  da lista encadeada. Se não houver um nó naquela posição da lista encadeada, o programa não deverá fazer nada.
	- Como o nó $p$ deve ser eliminado, devemos encontrar o nó na posição $p - 1$ (chamemos de `ptr`) e, em seguida, definir o novo `next` de `ptr` como `ptr -> next -> next`. Só precisamos considerar o caso especial $p = 0$, em que `head -> next` se torna o novo `head` da lista. Assumiremos que a função `get_kth(head, k)` obtém o $k$-ésimo nó da lista com elemento inicial `head`.
		```C
		if(p  ==  0) {
			node  *new_head  =  L  -> head  ->  next;
			free(L  -> head);
			L  -> head  =  new_head;
			L  -> size  -=  1;
			return;
		}
		node  *ptr  =  get_kth(L  -> head, p  -  1);
		node  *cur_node  =  ptr  -> next;
		ptr  -> next  =  ptr  -> next  ->  next;
		```
    
-   `p`: Imprimir a lista encadeada em uma única linha. Cada elemento da lista encadeada deverá ser seguido de um espaço. A lista encadeada vazia deverá ser impressa como uma linha vazia.
	- Para esta função, basta iterar e imprimir os elementos seguindo o formato.
-   `v i t`: Reverter a ordem dos elementos no trecho  [i..t]  da lista encadeada. Seja  n  o tamanho da lista antes da operação. Se  $0 \leq i \leq t<n$  então a operação deve reverter a ordem dos elementos nas posições entre  i  e  t  inclusive. Caso contrário, a operação não deve fazer nada.
	- Em primeiro lugar, devemos notar que há 4 posições cruciais que nos interessam: $i$, $t$, a posição anterior a $i$ (chamemos de $p$) e a posição seguinte a $t$ (chamemos de $q$).
	![](https://i.imgur.com/6UEfRvV.png)
	Então, o que queremos é que o nó na posição $p$ aponte para $t$, o nó na posição $i$ aponte para $q$ e que todos os nós entre $i + 1$ e $t$ apontem para o nó anterior. Podemos reverter os elementos no intervalo $[i + 1, t]$ com uma função recursiva `recursive_reverse(l, r)` que cuidará de reverter as conexões dos nós posteriores a $l$ até chegar ao nó $r$. Depois disso, só precisaremos reatribuir os `next` de $p$, $i$ e (possivelmente) alterar o `head` da lista se $i = 0$.
	![](https://i.imgur.com/XcmqP3B.png)
-   `x i t p`: Mover o trecho  [i..t]  da lista encadeada para a posição  p. Seja  n  o tamanho da lista antes da operação. Se  $0 \leq i \leq t<n$  então a operação deve mover todos os elementos nas posições entre  i  e  t  inclusive de tal forma que os nós movidos fiquem imediatamente antes do nó na posição  p  (p  deve estar fora do intervalo  [i…t]). Se  p  for maior ou igual ao tamanho da lista encadeada, então o trecho deve ser movido para o fim da lista encadeada. Caso contrário, a operação não deve fazer nada.
	- Para mover o trecho $[i, t]$ para a esquerda da posição $p$, podem ser definidos 4 blocos dependendo do caso:
		- Quando $t < p$:
		![](https://i.imgur.com/PUUa9uH.png)
		Neste caso, queremos terminar com a lista formada pelos blocos em ordem $A, C, B, D$, então basta mover os ponteiros `next` das posições finais dos blocos $A, B, C$. O único caso especial a considerar é quando $C$ está vazio.
		- Quando $p < i$:
		![](https://i.imgur.com/qpNjicZ.png)
		Neste caso, queremos terminar com a lista formada pelos blocos em ordem $A, C, B, D$, então basta mover os ponteiros `next` das posições finais dos blocos $A, B, C$. O único caso especial a considerar é quando $A$ está vazio.