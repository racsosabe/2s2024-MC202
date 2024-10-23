# Solução

Para resolver este problema, basta implementar um vetor dentro da estrutura de deque. Consideraremos que nossa estrutura está definida da seguinte forma:

- `data`: Vetor de dados.
- `first`: Posição do primeiro elemento na deque (se não houver elementos, pode ser qualquer posição entre $0$ e $cap - 1$).
- `size`: Tamanho da deque, ou seja, quantidade de elementos que contém.
- `cap`: Capacidade máxima de elementos que pode armazenar `data`.
- `mincap`: Capacidade mínima de elementos que pode armazenar `data`.
- `factor`: Fator de redimensionamento.

Vamos analisar o que devemos fazer para cada função solicitada:

-   `push(D, x)`: adicionar o elemento $x$ ao final da deque $D$.
	- Em primeiro lugar, teremos que verificar se a quantidade de elementos armazenados é igual à capacidade do vetor. Nesse caso, devemos realocar o vetor com uma nova capacidade, transferir os dados originais e, em seguida, adicionar o novo elemento ao final da deque. Vale notar que adicionar um elemento ao final da deque pode ser feito com o trecho de código:
	```C
	data[(deque -> first + deque -> size++) % deque -> cap] = x;
	```
-   `pop(D)`: extrair o último elemento da deque $D$ e retorná-lo.
	- Primeiramente, reduziremos o valor de `deque -> size` em 1, e, em seguida, redimensionaremos o vetor `data` se a quantidade de elementos for igual a $\left\lfloor\frac{deque\to cap}{deque\to factor^{2}}\right\rfloor$. Podemos armazenar o valor a ser retornado em uma variável antes de realizar o processo mencionado.
-   `inject(D, x)`: adicionar o elemento $x$ ao início da deque $D$.
	- Em primeiro lugar, teremos que verificar se a quantidade de elementos armazenados é igual à capacidade do vetor. Nesse caso, devemos realocar o vetor com uma nova capacidade, transferir os dados originais e, em seguida, adicionar o novo elemento ao início da deque. Vale notar que adicionar um elemento ao início da deque pode ser feito com o seguinte trecho de código:
	```C
	deque -> first = (deque -> first + deque -> cap - 1) % deque -> cap;
	deque -> size += 1;
	data[deque -> first] = x;
	```
-   `eject(D)`: extrair o primeiro elemento da deque $D$ e retorná-lo.
	- Primeiramente, reduziremos o valor de `deque -> size` em 1, aumentaremos `deque -> first` em 1, e, em seguida, redimensionaremos o vetor `data` se a quantidade de elementos for igual a $\left\lfloor\frac{deque\to cap}{deque\to factor^{2}}\right\rfloor$. Podemos armazenar o valor a ser retornado em uma variável antes de realizar o processo mencionado.
-   `set(D, k, x)`: atualizar o valor do $k$-ésimo elemento da deque $D$ para $x$.
	- Para determinar o $k$-ésimo elemento (0-indexado), basta calcular `(deque -> first + k) % deque -> cap`. Podemos então atribuir o valor com o seguinte trecho de código:
	```C
	data[(deque -> first + k) % deque -> cap] = x;
	```
-   `get(D, i)`: retornar o elemento na posição $i$ da deque $D$ (sem extraí-lo).
	- Para determinar o $i$-ésimo elemento (0-indexado), basta calcular `(deque -> first + k) % deque -> cap`. Podemos então retornar o valor `data[(deque -> first + k) % deque -> cap]`.
