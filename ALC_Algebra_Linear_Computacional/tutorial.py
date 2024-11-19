import numpy as np

from random import betavariate


print('Hello Woeld!')  # printa as coisas
print("doesn 't")
print('doesn \'t')

divFloat = 7/5
divInteiro = 7//5  # / divisão de float // divisao de int
multiplicacao = 5*5
potencia = 5**5
mod = 7 % 5

round(divFloat, 2)  # arredonda para 2 casas decimais
a, b, c = 3, 2, 1  # a=3, b=2, c=1

a < b < c  # comparison operators <, <=, >, >=, ==, !=, and, or, not

min(a, b, c)
max(a, b, c)

word = "Bolacha"
print(r'C:\some\name')
print("""aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa""")

print(3 * 'un' + 'ium')
print(word[0])
print(word[-1])
print(word[0:2])
print(word[:2])
print(word[4:])

len(word)

squares = [1, 4, 9, 16, 25]  # lista
squares[:] = []  # torna a lista vazia ou exclue elementos

squares2 = [1, 4, 9]
cubes = [1, 3, 9]
k = [squares2, cubes]

beatles = ['John', 'Paul']  # lista mutavel []
beatles.append('George')  # beatles = ['John','Paul','George']
# beatles = ['John','Paul','George','Stuart','Pete']
beatles.extende(['Stuart', 'Pete'])
beatles.index('George')  # retorna 2
beatles.count('John')  # retorna 1
beatles.remove('Stuart')  # beatles = ['John','Paul','George','Pete']
beatles.pop()  # beatles = ['John','Paul','George','Stuart']
beatles.insert(1, 'Ringo')  # adiciona
beatles.reverse()  # reverte
beatles.sort()  # organiza

t = ('a', 'b', 'c')  # tupla imutavel ()
# da pra mudar entre lista e tupla fazendo tupla(t) ou list(t)
'b' in t  # funciona com lista
'a' not in t  # funciona com lista

captitals = {'France': ('Paris', 2140526), 'Portugal': 'Lisbon'}  # dicionario
# adiciona uma palavra nova ao dicionario
captitals['Nigeria'] = ('Lagos', 6048430)
captitals.popitem()  # remove uma chave aleatoria do discionario
del captitals['Portugal']  # deleta portugal

y = 6


if y % 2 == 0:
    print('Even')
elif y == 1:
    print('One')
else:
    print('Odd')

colors = ['red', 'yellow', 'blue']
for color in colors:
    print(color)

comp_colors = ['green', 'purple', 'orange']
for i in range(len(comp_colors)):
    print(colors[i], comp_colors[i])

for j in range(3, 10, 2):  # 3 = inicio, 10 = final, 2 = passo
    print(j, end=' ')


def fib(n):  # funcao
    a, b = 0, 1
    while a < n:  # fibbonati
        print(a, end=', ')
        a, b = b, a+b


nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
#list(filter(lambda(n: n % 2 != 0, nums)))  # funcao temporaria

numeros = [x for x in range(1, 11)]  # cria lista altomatica
