# Solução

Para resolver este problema, podemos usar dois arrays $L$ e $R$ de tamanho $2 \cdot 10^{5} + 1$, de forma que:

- $L[x]$ armazena a peça que tem em sua parte esquerda o valor $x$.
- $R[x]$ armazena a peça que tem em sua parte direita o valor $x$.

Para saber se um valor aparece ou não como parte de uma peça, podemos inicializar os arrays com $-1$ em todas as posições.

Depois, para saber qual é a peça inicial, basta iterar sobre todas as peças $(l_{i}, r_{i})$ e verificar se existe alguma outra peça com $l_{i}$ em seu lado direito, o que é equivalente a verificar que $R[l_{i}] = -1$. Após identificar a peça inicial, $start$, podemos iterar sobre a cadeia que se formaria, atualizando $start$ com a próxima peça a ser colocada. Esta iteração terminará quando não houver mais nenhuma peça com $r_{start}$ em seu lado esquerdo, ou seja, depois da atualização, $start$ será igual a $-1$.