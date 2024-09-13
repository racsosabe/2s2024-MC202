# Solução

Para resolver o problema, devemos pensar em como aplicar cada regra de forma eficiente:

- Os dígitos devem ser lidos como números e devemos somá-los em uma variável $sum$.
- Caracteres especiais (que não sejam letras, dígitos ou espaços) devem ser removidos da string.
- As palavras devem receber o tratamento adequado dependendo da sua letra inicial.

Primeiro, consideraremos um algoritmo que permita remover caracteres da string original **sem a necessidade de criar uma string extra**.

A ideia principal parte do fato de que, se processarmos $c$ caracteres, a quantidade de caracteres na string filtrada não excederá $c$, então podemos manter uma variável $at$ que será o tamanho da string filtrada dos caracteres processados até agora. Desta forma, podemos projetar o seguinte algoritmo:

```
int at = 0;
int len = strlen(s);
for(i = 0; i < len; i++) {
	if(must_remove(s[i])) continue;
	s[at++] = s[i];
}
```

Um exemplo de execução sobre a string `s = "Sim, MC202 e legal"` em que filtramos **sinais de pontuação e dígitos** seria o seguinte (para melhor visualização, colocamos hifens '-' no lugar de espaços ' '):

$$\begin{array}{c|c|c|c}
i &\text{Caso} &at\text{ depois da decisão} &\text{Estado de }s \\ \hline
0 &s_{i} \text{ permanece} &1 &"\text{Sim,-MC202-e-legal}" \\ \hline
1 &s_{i} \text{ permanece} &2 &"\text{Sim,-MC202-e-legal}" \\ \hline
2 &s_{i} \text{ permanece} &3 &"\text{Sim,-MC202-e-legal}" \\ \hline
3 &s_{i} \text{ é removido} &3 &"\text{Sim,-MC202-e-legal}" \\ \hline
4 &s_{i} \text{ permanece} &4 &"\text{Sim-}\text{-MC202-e-legal}" \\ \hline
5 &s_{i} \text{ permanece} &5 &"\text{Sim-MMC202-e-legal}" \\ \hline
6 &s_{i} \text{ permanece} &6 &"\text{Sim-MCC202-e-legal}" \\ \hline
7 &s_{i} \text{ é removido} &6 &"\text{Sim-MCC202-e-legal}" \\ \hline
8 &s_{i} \text{ é removido} &6 &"\text{Sim-MCC202-e-legal}" \\ \hline
9 &s_{i} \text{ é removido} &6 &"\text{Sim-MCC202-e-legal}" \\ \hline
10 &s_{i} \text{ permanece} &7 &"\text{Sim-MC-202-e-legal}" \\ \hline
11 &s_{i} \text{ permanece} &8 &"\text{Sim-MC-e02-e-legal}" \\ \hline
12 &s_{i} \text{ permanece} &9 &"\text{Sim-MC-e-2-e-legal}" \\ \hline
13 &s_{i} \text{ permanece} &10 &"\text{Sim-MC-e-l-e-legal}" \\ \hline
14 &s_{i} \text{ permanece} &11 &"\text{Sim-MC-e-lee-legal}" \\ \hline
15 &s_{i} \text{ permanece} &12 &"\text{Sim-MC-e-leg-legal}" \\ \hline
16 &s_{i} \text{ permanece} &13 &"\text{Sim-MC-e-legalegal}" \\ \hline
17 &s_{i} \text{ permanece} &14 &"\text{Sim-MC-e-legalegal}" \\ \hline
\end{array} $$

Podemos notar que o valor final de $j = 14$ é o comprimento da string após filtrar os caracteres desejados, então podemos ignorar os seguintes.

Aplicaremos isso à string original que temos para filtrar os dígitos e caracteres especiais sem problemas, e até poderemos lidar adequadamente com os espaços com algumas observações.

## Lidando com os dígitos

Para lidar com os dígitos e somá-los à nossa variável $sum$, usaremos uma variável extra chamada $cur$, que representará o valor numérico dos dígitos lidos até agora. Esta variável deve ser inicializada em $0$, e consideraremos o valor de $s_{i}$ para modificá-la e também $sum$:

- Se $s_{i}$ é um dígito, devemos adicionar o dígito $s_{i}$ à direita do valor numérico $cur$ até o momento, o que é equivalente a:
$$cur \gets  10\cdot cur + valor(s_{i})$$
Onde $valor(c)$ é o valor numérico do caractere $c$, que pode ser obtido usando o código ASCII como `c -'0'`.
- Caso contrário, faremos as seguintes atribuições na ordem:
$$sum \gets sum + cur$$

$$cur \gets  0$$

É importante notar que, se tivermos dois caracteres consecutivos que não sejam dígitos, isso não alterará a correção de $sum$, pois no segundo caractere o valor de $cur$ será $0$.

## Lidando com os espaços

Para evitar adicionar vários espaços consecutivos, consideraremos adicionar o espaço atual à nova string **somente se**

- $at > 0$
- O último caractere adicionado à nova string **não** for um espaço.

Isso pode ser verificado com uma condicional.

Depois de filtrar os caracteres especiais e dígitos, lidando corretamente com os espaços, teremos que a string $s[0,\ldots, at - 1]$ contém as palavras corretamente filtradas e com exatamente um espaço entre cada uma.

Como já temos o valor de $sum$ calculado, podemos imprimir a mensagem inicial "[sum] goats say:" ou "[sum] goat says:", e depois processaremos todas as palavras considerando que os espaços são caracteres de separação entre elas.

## Lidando com as palavras

Usaremos uma variável $last$, que representará a posição do último espaço encontrado durante a iteração da string. Esta variável será inicializada em $-1$, pois, se encontrarmos um espaço na posição $i$, a palavra a ser analisada estará no intervalo de posições $[last + 1, i - 1]$.

**Nota:** Para evitar ter que analisar separadamente a última palavra (já que não teremos um espaço na última posição), adicionaremos um espaço ao final da string **somente se não estiver vazia**.

Uma vez definido o intervalo de posições $[l, r]$ da palavra atual, podemos processá-la conforme apropriado:

- Se $s_{l}$ for uma vogal, podemos imprimir caractere por caractere as posições no intervalo $[l, r]$. Em seguida, imprimimos "ma" e, finalmente, $r - l + 1$ vezes o caractere 'a'.
- Se $s_{l}$ for uma consoante, podemos imprimir caractere por caractere as posições no intervalo $[l + 1, r]$ e depois imprimir o caractere $s_{l}$. Em seguida, imprimimos "ma" e, finalmente, $r - l + 1$ vezes o caractere 'a'.

Como já imprimimos a mensagem inicial sem espaços antes das palavras, devemos imprimir um espaço antes de cada palavra processada.

Com tudo isso, teremos resolvido o problema corretamente.