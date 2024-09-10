# Solução

Para resolver este problema, basta notar que, de cada segmento maximal (não há elementos vizinhos que tenham o mesmo valor) de valores $x$, podemos tomar no máximo 1 elemento. Assim, a resposta será igual a $q + 1$, onde $q$ é a quantidade de posições $i$ tais que $a_{i - 1} \not = a_{i}$ com $i > 0$, considerando que as posições vão de $0$ até $N - 1$.