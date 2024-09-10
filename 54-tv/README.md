# Solução

Para resolver este problema, podemos usar um array 2D e calcular o deslocamento total no eixo horizontal e no eixo vertical, já que, se realizarmos os deslocamentos $dx_{1}, dx_{2}, \ldots, dx_{k}$ de forma sucessiva, isso é equivalente a realizar um único deslocamento com valor $(dx_{1} + dx_{2} + \cdots + dx_{k}) \mod L$, onde $L$ é o tamanho dessa dimensão.

Para evitar criar duas matrizes, podemos simplesmente notar que, se o deslocamento total em ambas as dimensões for $(X, Y)$, então na posição $(i, j)$ estará o elemento na posição $((i + n - X) \mod n, (j + m - Y) \mod m)$.