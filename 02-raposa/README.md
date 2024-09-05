# Solução

Para resolver o problema, basta determinar o primeiro buraco com coordenadas $(x, y)$ tal que

$$tempo(raposa) \leq tempo(coelho)$$

$$\frac{distância(raposa)}{velocidade(raposa)} \leq \frac{distância(coelho)}{velocidade(coelho)}$$

Como a raposa tem o dobro da velocidade do coelho, teremos que

$$\frac{distância(raposa)}{2 \cdot velocidade(coelho)} \leq \frac{distância(coelho)}{velocidade(coelho)}$$

Podemos eliminar o fator $\frac{1}{velocidade(coelho)}$ e obtemos:

$$\frac{distância(raposa)}{2} \leq distância(coelho) \rightarrow distância(raposa) \leq 2 \cdot distância(coelho)$$

Assim, podemos validar que

$$ \sqrt{(x_{raposa} - x)^{2} + (y_{raposa} - y)^{2}} \leq 2 \cdot \sqrt{(x_{coelho} - x)^{2} + (y_{coelho} - y)^{2}} $$ 

Poderíamos elevar ambas as partes ao quadrado, se desejarmos, e validar

$$ (x_{raposa} - x)^{2} + (y_{raposa} - y)^{2} \leq 4 \cdot (x_{coelho} - x)^{2} + (y_{coelho} - y)^{2} $$ 

O que seria equivalente.

Para calcular os valores de distância, podem ser usadas as funções `sqrt` e `pow`. Outra alternativa seria usar a função `hypot`.

Para a parte de leitura, usaremos a função `scanf` e aproveitaremos que ela retorna a quantidade de valores lidos. Assim, tentaremos ler até que essa função nos retorne 0.
