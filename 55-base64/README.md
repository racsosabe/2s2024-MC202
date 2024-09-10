# Solução

Para resolver este problema, podemos iterar em blocos de $3$ caracteres, considerando que o último bloco pode ter menos de $3$ caracteres.

Para processar um bloco, temos que considerar alguns casos:

- O bloco tem $3$ caracteres: São usados $24$ bits para os $4$ caracteres em base64.
- O bloco tem $2$ caracteres: São usados $16$ bits para os $3$ primeiros caracteres em base64.
- O bloco tem $1$ caractere: São usados $8$ bits para os $2$ primeiros caracteres em base64.

Para evitar o uso de condicionais, podemos aproveitar que, se temos $x$ caracteres, eles cobrem $8x$ bits, então serão preenchidos $\left \lceil \frac{8x}{6} \right\rceil$ caracteres com essa informação e o resto das posições serão preenchidas com caracteres '='.

Para processar os bits, basta usar o algoritmo clássico para obter os dígitos de um número em base $10$, mas substituindo o $10$ por $2$:

```C++
while(x > 0) {
    int digit = x % 2;
    x /= 2;
}
```

O restante do problema se reduz a implementar adequadamente onde os bits calculados devem ser posicionados e como obter os caracteres em base64 após obter sua posição. Para obter os caracteres em base64, podemos definir uma função que nos devolva o caractere correspondente dado o valor no intervalo $[0, 63]$ (é simples usando o código ASCII).