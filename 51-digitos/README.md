# Solução

Para resolver este problema, basta iterar sobre todos os números no intervalo $[N, M]$ e verificar quais deles têm dígitos diferentes. Para saber se um número inteiro tem dígitos diferentes, podemos remover o seu dígito mais à direita e marcar em um array de tamanho $10$ se o dígito já apareceu anteriormente ou não.