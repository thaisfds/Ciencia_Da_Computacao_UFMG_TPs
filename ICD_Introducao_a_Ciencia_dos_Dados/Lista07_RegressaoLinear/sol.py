# %% [markdown]
# # Imports
"""
Nome: Thaís Ferreira da Silva
Matricula: 2021092571
"""

# %%
# -*- coding: utf8

from scipy import stats as ss
from numpy.testing import assert_equal

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

plt.ion()

# %%
import seaborn as sns

PARAMETROS_RC = {  # Parâmetros RC para o matplotlib
  'figure.figsize': (12, 8),
  'axes.labelsize': 20,
  'axes.titlesize': 20,
  'legend.fontsize': 20,
  'xtick.labelsize': 20,
  'ytick.labelsize': 20,
  'lines.linewidth': 4,
}

sns.set(
    style="white",
    palette="colorblind",
    rc=PARAMETROS_RC,
)

# %%
def despine(ax=None):
    if ax is None:
        ax = plt.gca()
    # Hide the right and top spines
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)

    # Only show ticks on the left and bottom spines
    ax.yaxis.set_ticks_position('left')
    ax.xaxis.set_ticks_position('bottom')

# %% [markdown]
# # Lista 07 - Regressão Linear Simples

# %% [markdown]
# ## Introdução

# %% [markdown]
# Antes de iniciar o nosso estudo da regressão, vamos pensar em um modelo que tenta capturar o valor médio no eixo y. Para uma base de dados unidimensional (apenas Y), a média ($\bar{y}$) é um bom estimador. Por exemplo, imagine que você está em uma sala de aula e entra um novo aluno na sala. É possível prever alguma característica deste aluno (como o rendimento escolar) usando a média dos outros alunos.
# 
# Agora, como podemos proceder quando temos duas variáveis X e Y? Podemos usar a função de correlação para medir a força da relação linear entre duas variáveis. Para a maioria das aplicações, saber que esse relacionamento linear existe não é suficiente. Queremos ser capazes de entender a natureza do relacionamento. É aqui que vamos usar a regressão linear simples.
# 
# Vamos olhar para uma das bases dados que ajudaram a criar a regressão linear.

# %% [markdown]
# ## Poor Person's KNN  (Vizinhos Próximos Implementado de Forma Simples)

# %% [markdown]
# Vamos iniciar com a base de dados original analisada por [Galton](https://en.wikipedia.org/wiki/Francis_Galton). Tal base captura a altura de um filho, após alguns anos, com base na altura média dos pais. O problema era prever qual vai ser a altura futura de uma criança usando apenas a altura dos pais como entrada. Como temos um pai e uma mãe, usamos a média das alturas entre os dois.
# 
# Especificamente, temos que:
# 
# 1. X é a altura média dos pais
# 1. Y é a altura da criança após alguns anos (o mesmo número de anos para toda criança)

# %%
df = pd.read_csv('https://raw.githubusercontent.com/pedroharaujo/ICD_Docencia/master/galton.csv', index_col=0)
df.head()

# %% [markdown]
# Abaixo temos a dispersão dos dados

# %%
x = df['midparentHeight'].values
y = df['childHeight'].values

plt.scatter(x, y, alpha=0.8, edgecolors='k', s=80)
plt.xlabel('Altura média dos pais')
plt.ylabel('Altura dos filhos')
plt.title('Regressão linear simples')
despine()

# %% [markdown]
# Uma forma de capturar a correlação é fazer uma regressão de vizinhos próximos (nearest neighbors). Para tal, precisamos agrupar, no eixo-x, pontos próximos um dos outros. É possível fazer o mesmo nos eixos x e y usando uma distância euclideana. Por simplicidade vamos agrupar apenas em x. No caso particular destes dados onde os valores são bem espalhados no eixo x, podemos simplesmente arredondar os números

# %%
copy = df[['midparentHeight', 'childHeight']].copy()
copy['midparentHeight'] = copy['midparentHeight'].round()

# %% [markdown]
# Agrupar por x e tirar a média de y.

# %%
model = copy.groupby('midparentHeight').mean()
model.head()

# %% [markdown]
# Observando o modelo:

# %%
x_nn = model.index
y_nn = model.values
plt.scatter(x, y, alpha=0.8, edgecolors='k', s=80)
plt.plot(x_nn, y_nn, color='magenta')
plt.xlabel('Altura média dos pais')
plt.ylabel('Altura dos filhos')
plt.title('Regressão linear simples')

# %% [markdown]
# Previsão: Para um novo ponto, arredondar seu peso. Ver valor de y_nn

# %%
altura_media_pais = 71
model.loc[71.0]

# %% [markdown]
# Observe que o modelo acima é muito perto de uma reta. Ele ilustra as principais ideias necessárias para entender a correlação linear:
# 
# 1. Capturar a média de valores próximos um dos outros em x
# 1. Capturar a média de valores próximos um dos outros em y
# 
# Resolvemos o (1) problema nos dados acima com um round. No caso (2) com um groupby e mean.
# 
# Observe como o modelo é quase o mesmo quando z-normalizamos os dados.

# %%
znormed = df[['midparentHeight', 'childHeight']].copy()
znormed = (znormed - znormed.mean()) / znormed.std(ddof=1)
znormed.head()

# %%
x = znormed['midparentHeight'].copy()
y = znormed['childHeight'].copy()

# %%
znormed['midparentHeight'] = znormed['midparentHeight'].round()
model = znormed.groupby('midparentHeight').mean()

# %%
x_nn = model.index
y_nn = model.values
plt.scatter(x, y, alpha=0.8, edgecolors='k', s=80)
plt.plot(x_nn, y_nn, color='magenta')
plt.xlabel('Altura média dos pais')
plt.ylabel('Altura dos filhos')
plt.title('Regressão linear simples')
despine()

# %% [markdown]
# ## Regressão Linear Simples

# %% [markdown]
# Nos slides da aula, leia a discussão sobre como uma regressão linear tenta capturar a mesma ideia do nosso KNN simples acima. De forma simples, queremos uma reta capaz de explicar tando a dispersão em x quanto em y. Tal reta deve se aproximar da média dos dois valores quando vistos em janelas (estilo o NN acima). Em particular, você supõe que existem constantes $\alpha$ (alfa) e $\beta$ (beta) tais que:
# 
# $$\hat{y}_i = \alpha + \beta x_i + \epsilon_i$$
# 
# onde $\epsilon_i$ é um termo de erro (esperançosamente pequeno) que representa o fato de que existem outros fatores não explicados por este modelo simples. Idealmente, essa estimativa consegue capturar o valor médio de $y_i$ para grupos de valores próximos em $x_i$.

# %% [markdown]
# ## Exercício 1: Reta

# %% [markdown]
# * Supondo que tenhamos determinado $\alpha$, $\beta$ e $x_i$, implemente uma função que recebe como parâmetro os valores de $\alpha$, $\beta$ e $x_i$ e retorna o valor predito, $\hat{y}_i$.
# 
# 

# %%
alpha = 1.5
beta = 0.8
x = 10

def predict(alpha, beta, x_i):
  # deve retornar o valor predito de y
  y_i = alpha + (beta*x_i)
  return y_i

# %%
foo = predict(alpha, beta, x)
assert_equal(foo, 9.5)

# %% [markdown]
# ## Exercício 2: Erro

# %% [markdown]
# **Como escolhemos alfa e beta?**
# 
# Bem, qualquer escolha de alfa e beta nos dá uma saída prevista para cada entrada $x_i$. Como sabemos a saída real $y_i$, podemos calcular o erro de cada par.
# 
# * Implemente uma função que recebe como parâmetro os valores de $\alpha$, $\beta$, $x$ e $y$ e retorna o erro da saída prevista pelo modelo.

# %%
y = 10.2

def error(alpha, beta, x, y):
  # SEU CODIGO AQUI
  # Deve retornar o erro da saída prevista pelo modelo
  erro  = y - predict(alpha, beta, x)
  return erro

# %%
erro = error(alpha, beta, x, y)
assert_equal(round(erro, 2), 0.7)

# %% [markdown]
# ## Exercício 3: Erro médio

# %% [markdown]
# * Voltando ao exemplo que utiliza a base de dados original analisada por Galton, utilize a função de erro implementada e calcule o erro médio do modelo. Considere $x$ a altura média dos pais e $y$ a altura da criança.

# %%
x = df['midparentHeight']
y = df['childHeight']

# %% [markdown]
# * Inicialmente, considere $\alpha$ = 1 e $\beta$ = 0.5.

# %%
alpha = 1
beta = 0.5

def mean_error(alpha, beta, x, y):
  # SEU CODIGO AQUI
  return error(alpha, beta, x, y).mean()

# %%
erro_medio1 = mean_error(alpha, beta, x, y)
assert_equal(round(erro_medio1, 2), 31.14)

# %% [markdown]
# * A seguir, mostre o gráfico de dispersão dos dados e a reta gerada pelo modelo. (SEM CORREÇÃO AUTOMÁTICA)

# %%
# código para o gráfico aqui
x = df['midparentHeight'].values
y = df['childHeight'].values

y_predict = predict(alpha, beta, x)

plt.scatter(x, y, alpha=0.8, edgecolors='k', s=80)
plt.plot(x, y_predict, color='magenta')
plt.xlabel('Altura média dos pais')
plt.ylabel('Altura dos filhos')
plt.title('Regressão linear simples')

# %% [markdown]
# * Repita o cálculo considerando $\alpha$ = 22 e $\beta$ = 0.5.

# %%
alpha = 22
beta = 0.5

erro_medio2 = mean_error(alpha, beta, x, y)
assert_equal(round(erro_medio2, 2), 10.14)

# %% [markdown]
# * A seguir, mostre o gráfico de dispersão dos dados e a reta gerada pelo modelo. (SEM CORREÇÃO AUTOMÁTICA)

# %%
# código para o gráfico aqui
x = df['midparentHeight'].values
y = df['childHeight'].values

y_predict = predict(alpha, beta, x)

plt.scatter(x, y, alpha=0.8, edgecolors='k', s=80)
plt.plot(x, y_predict, color='magenta')
plt.xlabel('Altura média dos pais')
plt.ylabel('Altura dos filhos')
plt.title('Regressão linear simples')

# %% [markdown]
# Você deve notar que o segundo modelo é bem melhor. Porém os dois são péssimos.

# %% [markdown]
# ## Exercício 4: Soma dos erros quadrados

# %% [markdown]
# O que realmente gostaríamos de saber é o erro total em todo o conjunto de dados. Inicialmente, pode-se pensar que a soma dos erros nos daria esse valor, porém esse não é o caso. Se a previsão para um dado $x_1$ for muito alta (erro positivo) e a previsão para $x_2$ for muito baixa (erro negativo), esses erros se cancelariam na soma.
# 
# A correção mais simples para esse problema seria considerar a soma dos erros absolutos. Contudo, esse tipo de erro ($\vert x \vert$) não é interessante de um ponto de vista matemático, uma vez que não é bem comportado (não possui derivada) em $x=0$. No geral, aprendizado de máquina depende da minimização (ou maximização) de funções. Como deve ter aprendido nos cursos de cálculo, esses pontos extremos estão diretamente relacionados à noção de derivada (ou gradiente) e, assim, a não existência da derivada em $x=0$ é um grave problema.
# 
# De qualquer forma, ainda existem várias formas de calcular erros sem as dificuldades discutidas acima: qualquer erro não-negativo e bem-comportado para todos os números reais seria uma solução válida. Dentre eles, o mais comum é o erro quadrado. Essa não é uma escolha puramente arbitrária, já que no caso da regressão linear existe uma conexão entre minimização da soma dos erros quadrados e o processo (ainda a ser estudado) de máxima verossimilhança.
# 
# - Implemente uma função que recebe como parâmetro os valores de $\alpha$, $\beta$, $x$ e $y$ e retorna a soma dos erros quadrados da saída prevista pelo modelo.

# %%
def sum_of_squared_errors(alpha, beta, x, y):
  # SEU CODIGO AQUI
  return pow(error(alpha, beta, x, y),2).sum() 

# %% [markdown]
# A *solução de mínimos quadrados (least squares solution)*  é escolher o alfa e o beta que tornam a soma dos erros quadrados a menor possível. Para chegar em tais valores, podemos ver o erro como uma função de $\alpha$, $\beta$. Vamos iniciar com o caso normalizado. Aqui $\alpha=0$.

# %% [markdown]
# ### Dados Normalizados

# %% [markdown]
# A z-normalização de dados $(x_i, y_i)$ é obtida atráves de $x'_i = \frac{x_i - \bar{x}}{s_x}$ e $y'_i = \frac{y_i - \bar{y}}{s_y}$.
# 
# Note como a média dos dados z-normalizados tanto em X quanto em Y é zero:
# 
# $$\bar{x'} = n^{-1} \sum_{i=1}^n \frac{x_i - \bar{x}}{s_x}$$
# 
# $$\bar{x'} = n^{-1} s^{-1}_x \left(\sum_{i=1}^n x_i - \bar{x} \sum_{i=1}^n 1\right)$$
# 
# $$\bar{x'} = n^{-1} s^{-1}_x \left(\sum_{i=1}^n x_i - n \bar{x}\right)$$
# 
# $$\bar{x'} = n^{-1} s^{-1}_x \left(\sum_{i=1}^n x_i - n\frac{1}{n}\sum_{i=1}^n x_i\right)$$
# 
# $$\bar{x'} = n^{-1} s^{-1}_x \sum_{i=1}^n \left(x_i - x_i\right)$$
# 
# $$\bar{x'} = n^{-1} s^{-1}_x \cdot 0 = 0$$
# 
# Além do mais, o desvio padrão é 1. Provando:
# 
# $$s_{x'} = n^{-1} \sum_i \left(\frac{x_i - \bar{x}}{s_x} - 0\right)^2$$
# $$s_{x'} = s^{-1}_x n^{-1} \sum_i (x_i - \bar{x})^2$$
# $$s_{x'} = s^{-1}_x s_x = 1$$
# 
# Como a média dos pontos é $(0, 0)$, a nossa melhor reta vai passar pela origem. Ou seja, $\alpha=0$. Além do mais,  cada ponto dos seus dados é uma reta entre $(0, 0)$ e o ponto $(x'_i, y'_i)$. Dessa forma, podemos resolver o problema abaixo para chegar na equação da reta:
# 
# $$L(\beta) = \sum_i (y'_i - \hat{y}'_i)^2$$
# 
# $$L(\beta) = \sum_i (y'_i - \beta x'_i)^2$$
# 
# $$L(\beta) = \sum_i (y'^2_i - 2 \beta x'_i y'_i + \beta^2 x'^2_i)$$
# 
# Derivando a função em $\beta$:
# 
# $$\frac{d}{d\beta} L(\beta) = -\sum_i (2 x'_i y'_i + 2 \beta x'^2_i)$$
# 
# Fazendo $\frac{dL}{d\beta}=0$:
# 
# $$\beta = \frac{\sum_i x'_i y'_i}{\sum_i x'^2_i}$$
# 
# Nos slides discutimos como tal solução é uma função da covariância dos dados.

# %% [markdown]
# ### Dados Originais

# %% [markdown]
# Agora vamos resolver sem normalizar os dados. Vamos definir $\Theta = [\alpha, \beta]$, isto é, um vetor com alfa e beta.
# 
# $$L(\Theta) = \sum_i (y_i - \hat{y}_i)^2$$
# 
# $$L(\Theta) = \sum_i \Big(y_i - (\beta x_i + \alpha)\Big)^2$$
# 
# Resolvendo o quadrado dentro do somatório temos:
# 
# $$L(\Theta) = \sum_i (y_i^2 - 2 \beta x_i y_i - 2 \alpha y_i + x_i^2\beta^2 + 2 \beta \alpha x_i + \alpha^2)$$
# 
# Derivando em relação a $\alpha$:
# 
# $$\frac{d}{d\alpha} L(\Theta)= \sum_i (- 2 y_i + 2 \beta x_i + 2\alpha)$$
# 
# Derivando em relação a $\beta$:
# 
# $$\frac{d}{d\beta} L(\Theta) = \sum_i (- 2 x_i y_i + 2x_i^2\beta + 2 \alpha x_i)$$
# 
# Para otimizar esta função precisamos que as duas derivadas sejam zero.
# 
# $$\frac{d}{d\alpha} L(\Theta) = 0$$
# 
# $$\frac{d}{d\beta} L(\Theta) = 0$$
# 
# Após isto, podemos encontrar os valores ótimos de $\alpha$ e $\beta$. Note que esta é uma otimização um pouco chata de resolver.
# 
# \begin{align}
#  \alpha & = \bar{y} - \beta\,\bar{x}, \\[5pt]
#   \beta &= \frac{ \sum_{i=1}^n (x_i - \bar{x})(y_i - \bar{y}) }{ \sum_{i=1}^n (x_i - \bar{x})^2 } \\[6pt]
#             &= \frac{ \operatorname{Cov}(x, y) }{ \operatorname{Var}(x) } \\[5pt]
#             &= r_{xy} \frac{s_y}{s_x}. \\[6pt]
# \end{align}
# 
# Sem passar pela matemática exata, vamos pensar em por que isso pode ser uma solução razoável. A escolha do alfa simplesmente diz que quando vemos o valor médio da variável independente $x$, predizemos o valor médio da variável dependente $y$.
# 
# A escolha de beta significa que quando o valor de entrada aumenta pelo desvio padrão de $x$, a previsão de $y$ aumenta pela correlação entre $x$ e $y$ multiplicada pelo desvio padrão de $y$ ($r_{xy} s_y$). No caso em que $x$ e $y$ estão perfeitamente correlacionados, um aumento de um desvio padrão em $x$ resulta em um aumento de um desvio padrão de $y$ na predição. Quando eles são perfeitamente anti-correlacionados, o aumento em $x$ resulta em uma *diminuição* no valor da previsão. E quando a correlação é *zero*, o beta é *zero*, o que significa que as alterações em $x$ não afetam a previsão.
# 
# Para um pouco mais sobre a intuição dessa fórmula, veja este [vídeo](https://www.khanacademy.org/math/ap-statistics/bivariate-data-ap/least-squares-regression/v/calculating-the-equation-of-a-regression-line).
# - Utilizando a derivação mostrada acima, implemente uma função que recebe como parâmetro os valores de $x$ e $y$ e retorne os valores ótimos de $\alpha$ e $\beta$.

# %%
def least_squares_fit(x, y):
  # SEU CODIGO AQUI
  # deve retornar alpha, beta
  beta = ss.pearsonr(x, y)[0] * (y.std(ddof=1) / x.std(ddof=1))
  alpha = y.mean() - beta * x.mean()
  return alpha, beta

# %% [markdown]
# - A seguir, mostre o gráfico de dispersão dos dados e a reta gerada pelo modelo com os parâmetros ótimos (SEM CORREÇÃO AUTOMÁTICA). Quais são os valores ótimos para $\alpha$ e $\beta$ ? (COM CORREÇÃO AUTOMÁTICA)

# %%
x = df['midparentHeight'].values
y = df['childHeight'].values

alpha, beta = least_squares_fit(x, y)

assert_equal(round(alpha, 2), 22.64)
assert_equal(round(beta, 2), 0.64)

# %%
# código para o gráfico aqui
x = df['midparentHeight'].values
y = df['childHeight'].values

y_predict = predict(alpha, beta, x)

plt.scatter(x, y, alpha=0.8, edgecolors='k', s=80)
plt.plot(x, y_predict, color='magenta')
plt.xlabel('Altura média dos pais')
plt.ylabel('Altura dos filhos')
plt.title('Regressão linear simples')

# %% [markdown]
# Os valores de alfa e beta encontrados nos levam a concluir que as crianças vão ser aproximadamente $\alpha$ polegadas maiores do que $\beta$ vezes a média da altura dos seus pais.

# %% [markdown]
# ## Exercício 5: R-quadrado

# %% [markdown]
# É claro que precisamos de uma maneira melhor de descobrir o quão bem nós ajustamos os dados do que simplesmente encarar o gráfico da regressão. Uma medida comum é o coeficiente de determinação (ou R-quadrado, ou $R^2$, ou R-dois), que mede a fração da variação total na variável dependente ($y$) que é capturada pelo modelo.
# 
# $$R^2 = 1 - \frac{\sum_i (y_i - \hat{y}_i)^2}{\sum_i (y_i - \bar{y})^2} = 1 - \frac{\text{Soma dos erros quadrados}}{\text{Soma total de quadrados}}$$

# %% [markdown]
# * Implemente uma função que recebe como parâmetro os valores de $\alpha$, $\beta$, $x$ e $y$ e retorne o valor do $R^2$.

# %%
def r_squared(alpha, beta, x, y):
  # SEU CODIGO AQUI
  return 1 - (sum_of_squared_errors(alpha, beta, x, y) / pow(y - y.mean(),2).sum())

# %% [markdown]
# Utilizando a função implementada, qual o valor do $R^2$ no modelo com os valores ótimos de $\alpha$ e $\beta$ ?

# %%
R2 = r_squared(alpha, beta, x, y)
assert_equal(round(R2, 4), 0.1030)

# %% [markdown]
# O modelo linear mais simples que poderíamos ter escolhido é "sempre prever a média de $y$" (correspondendo a `alpha = np.mean(y)` e `beta = 0`), cuja soma dos erros quadrados é exatamente igual a sua soma total de quadrados. Tal ajuste possui um $R^2$ de zero, isto é, um modelo que (obviamente, neste caso) não funciona melhor do que apenas prever a média.
# 
# Claramente, o modelo de mínimos quadrados deve ser pelo menos tão bom quanto esse, o que significa que a soma dos erros quadrados é no máximo a soma total de quadrados, o que significa que o $R^2$ deve ser pelo menos zero. Além disso, a soma dos erros quadrados deve ser pelo menos $0$, o que significa que o $R^2$ pode ser no máximo $1$.
# 
# Quanto maior for o $R^2$, melhor o nosso modelo se ajusta aos dados. Um $R^2$ próximo de 0 nos diz que o nosso modelo está fraco para ajustar aos dados, e que claramente existem outros fatores em jogo.

# %% [markdown]
# Plotar os dados em outra escala pode ser uma boa forma de visualizar a variabilidade nos dados que não é capturada pelo modelo.
# * Para visualizar isso, plote o gráfico de dispersão dos dados e a reta gerada pelo modelo com os parâmetros ótimos. Porém, desta vez, brinque com os limites dos eixos x e y e observe a variabilidade do eixo-y que não é capturada pelo modelo.

# %%
x = df['midparentHeight'].values
y = df['childHeight'].values
alpha, beta = least_squares_fit(x, y)
y_model = beta * x + alpha
plt.scatter(x, y, alpha=0.8, edgecolors='k', s=80)
plt.plot(x, y_model, color='magenta')
plt.xlabel('Altura média dos pais')
plt.ylabel('Altura dos filhos')
plt.title('Regressão linear simples')
plt.xlim((55, 80))
plt.ylim((55, 80))

# %% [markdown]
# * Por fim, verifique que a raiz de $R^2$ é a própria correlação.

# %%
print(r_squared(alpha, beta, x, y) ** 0.5, ss.pearsonr(x, y)[0])

# %% [markdown]
# Existem algumas formas de interpretar o $R^2$:
# 
# 1. Quão melhor é o meu modelo quando comparado a um que retorna apenas a média de y.
# 1. Quanto da variancia de y é explicada por x.
# 
# Para entender o segundo ponto, note que:
# 
# \begin{align*}
#   R^2
#     &=  1 - \frac{\sum_i(y_i - \hat{y}_i)^2}{\sum_i(y_i - \bar{y})^2} \\
#     &=  1 - \frac{\frac{1}{n-1}\sum_i(y_i - \hat{y}_i)^2}{\frac{1}{n-1}\sum_i(y_i - \bar{y})^2} \\
#     &= 1 - \frac{\text{Variância Inexplicada pelo Modelo}}{\text{Variância Total}} \\
#     &= \frac{\text{Variância Explicada pelo Modelo}}{\text{Variância Total}} \\
# \end{align*}
# 


