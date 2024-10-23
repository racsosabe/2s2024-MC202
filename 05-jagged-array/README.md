# Solução

Para resolver este problema, basta declarar um ponteiro de ponteiros para a matriz de forma que a $i$-ésima linha tenha $i$ elementos. Dessa forma, precisaremos apenas de $\frac{n(n + 1)}{2}$ elementos em vez de $n^{2}$.

Em seguida, bastará calcular a média e o desvio padrão usando as seguintes fórmulas:

$$ \text{Média} = \frac{\sum\limits_{i = 1}^{n}\sum\limits_{j = 1}^{i}M_{i, j}}{\frac{n(n + 1)}{2}} $$

$$ \text{Desvio padrão} = \sqrt{\frac{1}{\frac{n(n + 1)}{2}}\sum\limits_{i = 1}^{n}\sum\limits_{j = 1}^{i}(M_{i, j} - \text{Média})^{2}} $$
