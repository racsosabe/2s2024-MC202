# Solução

Para resolver o problema, devemos implementar o truque de $\sqrt{n}$, como é explicado no enunciado.

Em primeiro lugar, devemos considerar as seguintes ideias:

- Se $r$ é o tamanho do bloco, então a posição $i$ pertence ao bloco $\left \lfloor \frac{i}{r} \right\rfloor$.
- O $i$-ésimo bloco contém as posições no intervalo $[i \cdot r, \min\{n - 1, (i + 1)\cdot r - 1\}]$.

Agora vamos considerar o que deve ser feito para atualizar o valor em uma posição:

## Atualização

Já que realizar a atribuição direta $V_{i} \gets x$ não pode ser refletida facilmente no valor do bloco $R_{x}$, com $x = \left \lfloor \frac{i}{r} \right\rfloor$, teremos que recalcular o valor de $R_{x}$, o que levará $r$ operações.

## Consulta

Se nos pedirem para encontrar o máximo no intervalo de posições $[i, j]$, podemos dividir o processo em 3 fases:

1. O intervalo de $i$ até o início de um bloco.
2. O intervalo de blocos completamente contidos no intervalo.
3. O intervalo do último início de bloco (não completamente contido) até $j$.

Consideremos que a primeira fase pode ser realizada com um `while` que mantém as condições

- $i \not \equiv 0 (\mod r)$
- $i \leq j$

Isso porque precisamos que $i$ avance até ser o início de um bloco ou até já ter coberto todo o intervalo original.

A segunda fase considera blocos completamente incluídos no intervalo, então basta usar a condição:

- $i + r - 1 \leq j$

Já que isso implicará que o bloco de $i$ estará completamente contido no intervalo. Note que, se o intervalo já tiver sido coberto na primeira fase, a condição nunca será satisfeita, então a condição dada é suficiente.

Para a terceira fase, faremos algo semelhante à primeira, mas ignoraremos a primeira de suas condições, então iteraremos apenas enquanto:

- $i \leq j$

Note que nas fases 1 e 3 tomaremos como referência os valores $V_{i}$, enquanto que na fase 2 tomaremos como referência os valores $R_{\left \lfloor \frac{i}{r} \right\rfloor}$.