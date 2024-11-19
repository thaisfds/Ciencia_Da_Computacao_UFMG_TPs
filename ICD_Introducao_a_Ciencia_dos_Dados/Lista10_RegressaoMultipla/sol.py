# %% [markdown]
# # Lista 10 - Regressão Múltipla
"""
Nome: Thaís Ferreira da Silva
Matricula: 2021092571
"""

# %% [markdown]
# ## Introdução

# %%
# -*- coding: utf8

from scipy import stats as ss

import matplotlib.pyplot as plt
from numpy.testing import assert_equal, assert_array_almost_equal
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
# Continuando da aula passada, vamos agora focar em casos mais específicos de regressão. Nesta aula, vamos estender a ideia de mínimos quadrados e de regressão linear para modelos mais complexos. Para tal, vamos continuar nosso foco nos dados de preços de apartamentos em BH.

# %% [markdown]
# ## Dados

# %% [markdown]
# Observe como temos 4 possíveis preditores de preço:
# 1. Área
# 1. Quartos
# 1. Suítes
# 1. Vagas

# %%
df = pd.read_csv('https://raw.githubusercontent.com/pedroharaujo/ICD_Docencia/master/aptosBH.txt', index_col=0)
df.head()

# %% [markdown]
# Cada preditor é correlacionado com o preço de alguma forma. No pairplot abaixo, observe a última coluna, onde cada linha corresponde a um preditor.

# %%
sns.pairplot(df, diag_kws={'edgecolor':'k'}, plot_kws={'alpha':0.5, 'edgecolor':'k'})

# %% [markdown]
# ## Regressão Múltipla

# %% [markdown]
# Para realizar uma regressão múltipla, vamos representar nossos dados na forma matricial. Se $n$ é o número de linhas dos nossos dados (observações) e $f$ é o número de colunas (features/atributos), então os dados podem ser representados por:
# 
# $$
# \mathbf{X} = \begin{pmatrix}\mathbf {x} _{1}^{\mathsf {T}}\\\mathbf {x} _{2}^{\mathsf {T}}\\\vdots \\\mathbf {x} _{n}^{\mathsf {T}}\end{pmatrix} =\begin{pmatrix}1&x_{11}&\cdots &x_{1f}\\1&x_{21}&\cdots &x_{2f}\\\vdots &\vdots &\ddots &\vdots \\1&x_{n1}&\cdots &x_{nf}\end{pmatrix}
# $$
# 
# Observe como a primeira coluna é toda $1$. A mesma vai capturar o fator constante, intercepto, da regressão linear. O nosso modelo é capturado pela equação:
# 
# $$y_i = \theta_0 x_{i0} + \theta_1 x_{i1}^{1} + \theta_2 x_{i2}^{2} + \cdots + \theta_f x_{if}^{f} + \epsilon_i$$
# 
# Aqui, $x_{i0} = 1$ sempre (por isso usamos uma coluna de 1s). Dessa forma, a equação acima pode ser simplificada para:
# 
# $$y_i = \theta_0 + \theta_1 x_{i1}^{1} + \theta_2 x_{i2}^{2} + \cdots + \theta_f x_{if}^{f} + \epsilon_i$$

# %% [markdown]
# Vamos organizar uma matriz de fatores explanatórios X usando pandas.

# %%
y = df['preco']
X = df[['area', 'quartos', 'suites', 'vagas']]
X['intercepto'] = 1
X = X[['intercepto', 'area', 'quartos', 'suites', 'vagas']]
X.head()

# %% [markdown]
# Temos 216 observações.

# %%
y.shape

# %% [markdown]
# 5 atributos, onde um deles é o intercepto.

# %%
X.shape

# %% [markdown]
# X.values retorna a matriz.

# %%
X = X.values
y = y.values # pegar a matrix
X

# %% [markdown]
# ## Modelo

# %% [markdown]
# Se $\mathbf{y}$ é a nossa resposta, então o nosso modelo tem a seguinte forma matricial:
# 
# 
# $$\mathbf {y} =\mathbf{X}{\boldsymbol {\theta }}+{\boldsymbol {\varepsilon }} $$
# 
# Cada observação $y_i$ vai ser capturada pelo modelo linear $y_i = \theta_0 + \theta_1 x_{i1}^{1} + \theta_2 x_{i2}^{2} + \cdots + \theta_f x_{if}^{f} + \epsilon_i$. Basta pensar em operações de matrizes e vetores como somatórios! Cada linha de $\mathbf{X}$ multiplica o vetor de parâmetros $\theta$.

# %% [markdown]
# ## Soma dos erros quadrados

# %% [markdown]
# A função de perda na forma matricial é:
# 
# $$L({\boldsymbol {\theta }}) = ||\mathbf{y} - \mathbf{X} {\boldsymbol {\theta }}||^2_2$$
# 
# Essa função é obtida através do quadrado da norma de Frobenius (com p=2), cuja fórmula é dada por:
# 
# $$||A||_p = \left(\sum_i \sum_j |a_{i,j}|^p\right)^{\frac{1}{p}}$$

# %% [markdown]
# ## Jacobiana

# %% [markdown]
# Quando temos várias derivadas de equações na forma matricial, estamos computando a Jacobiana J (vetor de derivadas). Cada elemento do vetor J é uma derivada:
# 
# $$J(\theta) =
#   \left(
#     \begin{matrix}
#     \frac{dL}{d\theta_0} & \frac{dL}{d\theta_1} & ... & \frac{dL}{d\theta_f}
#     \end{matrix}
#   \right)
# $$
# 
# 
# Um fator bastante interessante deste modelo é que todas as derivadas (para cada $\theta_i$) têm a mesma forma. Como temos uma soma de fatores lineares, cada $\theta_i$ vai ter o mesmo formato. Assim:
# 
# $$\frac{dL}{d\theta_j} = -2n^{-1} \sum_{i=1}^{n} \left(y_i - \sum_{j=0} \theta_j x_{ij}\right) x_{ij}$$
# 
# $$\frac{dL}{d\theta_j} = -2n^{-1} \sum_{i=1}^{n} \epsilon_i x_{ij}$$
# 
# A função abaixo computa tal derivada explorando o conceito de vetorização.

# %%
def derivadas_regressao_media_old(theta, X, y):
    return -2 * ((y - X @ theta) * X.T).mean(axis=1)

# %%
def derivadas_regressao(theta, X, y):
    return -2 * ((y - X @ theta) @ X)

# %% [markdown]
# ## Versão nova da função da média

# %%
def derivadas_regressao_media(theta, X, y):
    return -2 * ((y - X @ theta) @ X) / len(y)

# %% [markdown]
# ## Gradiente Descendente

# %% [markdown]
# Após definir o modelo, a função de erro e a Jacobiana para a Regressão Múltipla, podemos calcular o gradiente descendente!

# %%
def gd(theta, d_fun, X, y, lambda_=0.0001, tol=0.00001, max_iter=10000):
  theta = theta.copy()
  #print('Iter {}; theta = '.format(0), theta)
  old_err_sq = np.inf
  i = 0
  while True:
    # Computar as derivadas
    grad = d_fun(theta, X, y)
    # Atualizar
    theta_novo = theta - lambda_ * grad

    # Parar quando o erro convergir
    err_sq = ((X.dot(theta) - y) ** 2).mean()
    if np.abs(old_err_sq - err_sq) <= tol:
      break
    theta = theta_novo
    old_err_sq = err_sq
    #print('Iter {}; theta = '.format(i+1), theta)
    i += 1
    if i == max_iter:
      break
  return theta

# %% [markdown]
# ## Gradiente Descendente Estocástico

# %% [markdown]
# O gradiente descendente estocástico também funciona! Entretanto, temos que acertar a taxa de aprendizado.
# Um dos problemas do uso recorrente do gradiente descendente estocástico é que não sabemos ainda como acertar nossa taxa. Para tal, geralmente fazemos uso de treino/validação/teste (assunto das próximas aulas).

# %%
def sgd(theta, d_fun, X, y, lambda_=0.001, tol=0.01, max_iter=10000):
  theta = theta.copy()
  #print('Iter {}; alpha, beta = '.format(0), theta)
  old_err_sq = np.inf
  for i in range(max_iter):
    # Escolhe ponto aleatório
    r = np.random.randint(len(y))
    X_r, y_r = X[r], y[r]
    X_r = X_r.reshape(1, len(X_r)) # transforma o vetor linha em matriz

    # Deriva e atualiza
    grad = d_fun(theta, X_r, y_r)
    theta_novo = theta - lambda_ * grad

    #Calcula o erro
    err_sq = ((X.dot(theta) - y) ** 2).mean()

    theta = theta_novo
    if err_sq < tol:
      break

      #print('Iter {}; alpha, beta = '.format(i+1), theta)

  return theta

# %% [markdown]
# ## Normalização dos Dados

# %% [markdown]
# A normalização dos dados pode ser útil para ajudar o gradiente. O algoritmo funciona sem tal passo, porém é mais chato definir uma taxa de aprendizado sem normalização e a convergência é mais lenta.
# 
# Quando as features aparecem com ordens de grandeza muito diferentes (ex: idade entre 0 a 100 e renda mensal entre  800 e 100.000 reais) a função de custo é distorcida, tornando o ponto mínimo difícil de alcançar. Sendo assim, um truque importante é garantir que todos as features estejam em uma escala similar.
# 
# Abaixo normalizamos as features dos dados de preços de apartamentos em BH e, em seguida, calculamos o gradiente descendente e o gradiente descendente estocástico.

# %%
df = pd.read_csv('https://raw.githubusercontent.com/pedroharaujo/ICD_Docencia/master/aptosBH.txt', index_col=0)
z_df = (df-df.mean())/df.std()

y = z_df['preco']
X = z_df[['area', 'quartos', 'suites', 'vagas']]
X['intercepto'] = 1

X = X.values
y = y.values

theta = np.ones(5)
theta = gd(theta, derivadas_regressao, X, y)

# %%
print("theta = ", theta)
print()
print(X[0:4])

# %%
df = pd.read_csv('https://raw.githubusercontent.com/pedroharaujo/ICD_Docencia/master/aptosBH.txt', index_col=0)
z_df = (df-df.mean())/df.std()

y = z_df['preco']
X = z_df[['area', 'quartos', 'suites', 'vagas']]
X['intercepto'] = 1

X = X.values
y = y.values

theta = np.ones(5)
theta = sgd(theta, derivadas_regressao, X, y, lambda_=0.002)

# %%
print("theta = ", theta)

# %% [markdown]
# Observe como os resultados batem com o scikit learn.

# %%
from sklearn.linear_model import LinearRegression
model = LinearRegression(fit_intercept=True)
model.fit(X, y)

# %%
model.coef_

# %%
model.intercept_

# %% [markdown]
# ## Erros e Validação

# %% [markdown]
# Ainda podemos usar o R-quadrado para avaliar a qualidade de uma regressão linear múltipla. A interpretação permanece a mesma: quanto da variância dos dados é capturada pelo modelo.

# %%
def erro(y, X, theta):
  return y - X@theta

def multiple_r_squared(X, y, theta):
  sse = sum(erro(y, X, theta)**2)
  sst = sum((y - np.mean(y))**2)
  return 1.0 - sse / sst


df = pd.read_csv('https://raw.githubusercontent.com/pedroharaujo/ICD_Docencia/master/aptosBH.txt', index_col=0)

y = df['preco']
X = df[['area', 'quartos', 'suites', 'vagas']]
X['intercepto'] = 1

X = X.values
y = y.values

model = LinearRegression(fit_intercept=False)
model.fit(X, y)
print(model.coef_)
print("R2 sem normalizacao = ", model.score(X, y))


df = pd.read_csv('https://raw.githubusercontent.com/pedroharaujo/ICD_Docencia/master/aptosBH.txt', index_col=0)
z_df=(df-df.mean())/df.std()

y = z_df['preco']
X = z_df[['area', 'quartos', 'suites', 'vagas']]
X['intercepto'] = 1

X = X.values
y = y.values

model = LinearRegression(fit_intercept=False)
model.fit(X, y)
print(model.coef_)
print("R2 com normalizacao = ", model.score(X, y))

# %% [markdown]
# ## Bootstrap para entender a importância de fatores

# %% [markdown]
# Podemos aplicar um bootstrap para entender a importância dos fatores. Nós repetidamente tomamos um `bootstrap_regression` dos nossos dados e estimamos o vetor $\Theta$ com base nessa amostra. Se o coeficiente correspondente a uma das variáveis independentes não variar muito entre as amostras, podemos ter certeza de que nossa estimativa é relativamente segura. Se o coeficiente variar muito entre as amostras, não podemos ficar confiantes em nossa estimativa. Caso o intervalo capture o zero, o fator não importa do ponto de vista estatístico. Vamos fazer uso de scikit learn.
# 
# Vamos ver exemplos nos dados dos apartamentos.

# %%
def bootstrap_regression(X, y, n=10000, size=None):
  if size is None:
    size = len(df)

  T = np.zeros(shape=(n, X.shape[1]))
  for i in range(n):
    # Gera amostras com reposição
    idx = np.random.choice(len(y), len(y))
    Xb = X[idx]
    yb = y[idx]

    # Fit usando sklearn
    model = LinearRegression(fit_intercept=True)
    model.fit(Xb, yb)

    T[i] = model.coef_
  return T

# %% [markdown]
# A seguir, não usamos o scikit learn e eliminamos duplicatas da amostra:

# %%
def bootstrap_regression_gd(X, y, n=10000, size=None):
  if size is None:
    size = len(df)

  T = np.zeros(shape=(n, X.shape[1]))
  for i in range(n):
    if i%400 == 0:
      print("bootstrap iter ", i)
    # Gera amostras com reposição e remove duplicatas
    idx = list(np.random.choice(len(y), len(y)))
    Xb = X[idx]
    yb = y[idx]

    # Fit usando gd
    theta = np.ones(X.shape[1])
    theta = gd(theta, derivadas_regressao, Xb, yb)

    T[i] = theta
  return T

# %%
y = z_df['preco'].values
names = ['area', 'quartos', 'suites', 'vagas']
X = z_df[names]
X['intercepto'] = 1
X = X.values

T = bootstrap_regression_gd(X, y)
names = ['area', 'quartos', 'suites', 'vagas', 'intercepto']

# %%
def plota_bootstrap_para_iesimo_parametro(T, i):
  fig = plt.figure()
  plt.hist(T[:, i], edgecolor='k')
  plt.title('{} - 95% CI Bootstrap: ({:.2f}, {:.2f})'.format(names[i],
                                                              np.percentile(T[:, i], 2.5),
                                                              np.percentile(T[:, i], 97.5)))
  plt.xlabel(r'$\theta_i$')
  plt.ylabel('# Boot Amostras')
  despine()
  plt.show()

plota_bootstrap_para_iesimo_parametro(T, 0)

# %% [markdown]
# ##  Exercícios - Outros datasets:

# %% [markdown]
# ### Carros

# %% [markdown]
# Utilizando a base de dados carros, ``hybrid.csv``, vamos fazer um gradiente descendente para uma regressão linear com múltiplas variáveis. As colunas são definidas da seguinte forma:
# 
# - veículo (vehicle): modelo do carro
# 
# - ano (year): ano de fabricação
# 
# - msrp: preço de varejo em dólar sugerido pelo fabricante em 2013.
# 
# - aceleração (acceleration): taxa de aceleração em km por hora por segundo
# 
# - mpg: economia de combustível em milhas por galão
# 
# - classe (class): a classe do modelo.
# 
# Nosso objetivo será estimar o valor de preço sugerido dos carros a partir dos demais atributos (exluindo o nome do veículo e a classe).
# Portanto, teremos a regressão definida pela fórmula:
# 
# $$ Y = X\Theta + \epsilon $$
# 
# onde, Y corresponde à coluna ``msrp`` dos dados, e X corresponde às colunas ``year,acceleration,mpg``.

# %% [markdown]
# Observe a forma dos dados e a correlação entre as variáveis:

# %%
df = pd.read_csv('https://raw.githubusercontent.com/pedroharaujo/ICD_Docencia/master/hybrid.csv')
df.head()

# %%
import seaborn as sns
sns.pairplot(df, diag_kws={'edgecolor':'k'}, plot_kws={'alpha':0.5, 'edgecolor':'k'})

# %% [markdown]
# **Exercício 1:** Selecione apenas as colunas que serão utilizadas e normalize os dados para que o gradiente descendente rode sem problemas.

# %%
# SELECIONE AS COLUNAS
X = df[["year", "acceleration", "mpg"]]
y = df["msrp"]

# NORMALIZE OS DADOS
X = (X - X.mean()) / X.std(ddof=1)
y = (y - y.mean()) / y.std(ddof=1)

# ACRESCENTE INTERCEPTO
inter: np.ndarray = np.ones(y.size)
X.insert(0, "Intercepto", inter, True)

# EXTRAIA MATRIZES COM .VALUES
X = X.values
y = y.values

# %% [markdown]
# **Exercício 2:** Implemente a função de gradiente dos parâmetros da regressão, retornando um array com os valores dos gradientes para cada parâmetro.

# %%
def gradients(theta, X, y):
    # YOUR CODE HERE
    # x : matriz nxm
    # y : array nx1
    # theta : array mx1
    return -2 * ((y - X @ theta) @ X) / len(y)

# %% [markdown]
# * Implemente a função de gradiente descendente para os parâmetros da regressão, retornando um array com os valores de alpha e os valores de beta para cada coluna. Você deve usar a função `gradients` definida anteriormente.

# %%
def descent(theta0, X, y, learning_rate=0.005, tolerance=0.0000001):
    # YOUR CODE HERE
    old_err_sq = np.inf
    i = 0
    while True:
        grad = gradients(theta0, X, y)
        theta_novo = theta0 - learning_rate * grad
        err_sq = ((X.dot(theta_novo) - y) ** 2).mean()

        if np.abs(old_err_sq - err_sq) <= tolerance:
            break
        theta0 = theta_novo
        old_err_sq = err_sq

        i += 1
        if i == 9999999:
            break
    return theta_novo

# %%
_teste_param0 = np.array([ 1000, 1, 1, 1 ])
theta = descent(_teste_param0, X, y)
assert_array_almost_equal(np.round(theta,4), np.round([ 0.00201339, -0.04349112,  0.59055261, -0.23979036],4))

# %% [markdown]
# **Exercício 3:** Agora vamos tentar avaliar o modelo de regressão linear obtido com o gradiente descendente. Para isso, implemente a função que calcula o R-quadrado.
# 
# Lembre-se que, para calcular o R-quadrado, você precisa do valor da soma total dos quadrados e da soma dos erros quadrados. Os parâmetros de entrada de cada função são dados.

# %%
def sst(y):
  # YOUR CODE HERE
  return ((y - y.mean()) ** 2).sum()

def predict(X, theta):
  # YOUR CODE HERE
  return X @ theta.T

def sse(X, y, theta):
  # YOUR CODE HERE
  return y.T @ y - (y.T @ X @ np.linalg.inv(X.T @ X) @ X.T @ y)

def rsquared(X, y, theta):
  # YOUR CODE HERE
  return 1 - (sse(X, y, theta) / sst(y))

# %%
rs = rsquared(X, y, theta)
assert_equal(np.round(rs,4), np.round(0.5288887684860548,4))

# %% [markdown]
# Se observarmos os dados pelos gráficos que mostram as correlações entre as variáveis, podemos perceber que nem todos possuem uma relação linear. Vamos tentar transformar os dados de um dos atributos dos carros, para que uma regressão linear possa ser aplicada com melhores resultados.
# 
# **Exercício 4:** Para isso, tire o logaritmo da variável ```mpg``` e, em seguida, z-normalize os dados (todos as variáveis em X).

# %%
from scipy.stats import zscore
y = df['msrp'].copy()
X = df[['year','acceleration','mpg']].copy()

# TIRE O LOG DA VARIAVEL MPG
aux = X.copy()
for i in range(len(y)):
    aux.iloc[i, 2] = np.log(aux.iloc[i, 2])
X = aux

# Z-NORMALIZE OS DADOS
X = X.apply(zscore)

# ADICIONE O INTERCEPTO
inter: np.ndarray = np.ones(y.size)
X.insert(0, "Intercepto", inter, True)

# DEFINA X e Y UTILIZANDO .VALUES
X = X.values
y = y.values

# %% [markdown]
# * Rode novamente o código do gradiente descendente e verifique se o R-quadrado da regressão melhorou ou piorou após a transformação dos dados.

# %%
_teste_param0 = np.array([ 1000, 1, 1, 1 ])
theta = descent(_teste_param0, X, y)
rs1 = rsquared(X, y, theta)
assert_equal(np.round(rs1,4), np.round(0.5543728866213389,4))

# %% [markdown]
# ### ATENÇÃO

# %% [markdown]
# Os próximos dois exercícios não possuem correção automática, porém são de vital importância. Ambos os datasets utilizados nos exercícios a seguir são datasets com grande número de variáveis, o que se aproxima de problemas reais. Como a realização de testes com os valores é dificultada devido ao alto número de variáveis, optou-se pela não correção automática.
# 
# Tente encontrar o modelo que melhor se ajusta aos dados, com maior valor de $R^2$. Tente também compreender a interpretação dos coeficientes para cada variável explicativa. Em caso de dúvidas, acione o monitor da disciplina.

# %% [markdown]
# ### Dataset Reações Químicas - SEM CORREÇÃO AUTOMÁTICA

# %% [markdown]
# Um cientista maluco misturou quantidades (em milímetros cúbicos) aleatórias de diversos reagentes e conseguiu gerar uma determinada quantidade (em milímetros cúbicos) de um produto químico, que embora não sirva para nada, não é tóxico e é muito bonito. O problema é que o cientista não sabe quais reagentes estão, de fato, reagindo e gerando o tal produto. Mais importante, ele não sabe a quantidade que ele tem que colocar de cada reagente para gerar uma dada quantidade do produto. Para descobrir, ele misturou quantidades aleatórias de cada reagente 1000 vezes e anotou a quantidade do produto que foi gerada em cada um desses experimentos. Para encontrar a fórmula mágica tão desejada, ele pediu a sua ajuda. Os experimentos estão descritos nas linhas do arquivo. A quantidade gerada do produto para cada experimento está descrita na linha "q_produto".
# 
# E aí? Será que regressão linear múltipla resolve? O professor sabe que resolve, e tem um modelo com $R^2$ superior a $0.99$.
# 
# * Encontre esse modelo e mostre os coeficientes, a qualidade do ajuste, e os fatores significativos. Você pode utilizar as funções definidas anteriormente, ou utilizar a biblioteca sklearn.

# %%
df = pd.read_csv('https://raw.githubusercontent.com/pedroharaujo/ICD_Docencia/master/chemical_reaction.csv')
df.head()

# %%
X = df.iloc[:, 1:].values
y = df.iloc[:, 0].values

lm = LinearRegression()
lm.fit(X, y)

print("Coeficientes: {}".format(lm.coef_))
print("Intercept: {}".format(lm.intercept_))
print("R^2: {}".format(lm.score(X, y)))

import statsmodels.api as sm

X = sm.add_constant(X)

model = sm.OLS(y, X).fit()
predictions = model.predict(X)

print_model = model.summary()
print(print_model)

# %% [markdown]
# ### Dataset FIFA - SEM CORREÇÃO AUTOMÁTICA

# %% [markdown]
# O [FIFA](https://pt.wikipedia.org/wiki/FIFA_(s%C3%A9rie)) é um jogo eletrônico de futebol muito popular em que, parte da diversão, é poder jogar partidas envolvendo jogadores reais. Para simular um jogador real, o jogo descreve-os usando diversos atributos (como poder do chute, velocidade, etc) os quais, de alguma forma, representam em sua habilidade como um todo (*overall*).
# 
# * Neste exercício você deve encontrar um modelo linear que explique a habilidade *overall* dos jogadores do FIFA a partir das suas outras habilidades. Para isso, utilize o arquivo contendo as habilidades de 20 mil jogadores. Mostre os coeficientes, a qualidade do ajuste e os fatores significativos.
# 
# **Dica:** pode haver mais de um modelo!

# %%
df = pd.read_csv('https://raw.githubusercontent.com/pedroharaujo/ICD_Docencia/master/skills_and_overall_sample_20k.csv', index_col=0)
df.head()

# %%
from sklearn.linear_model import LinearRegression

X = df.iloc[:, 1:33].values
y = df.iloc[:, 33].values

lm = LinearRegression()
lm.fit(X, y)

print("Coeficientes: {}".format(lm.coef_))
print("Intercept: {}".format(lm.intercept_))
print("R^2: {}".format(lm.score(X, y)))

import statsmodels.api as sm

X = sm.add_constant(X)

model = sm.OLS(y, X).fit()
predictions = model.predict(X)

print_model = model.summary()
print(print_model)


