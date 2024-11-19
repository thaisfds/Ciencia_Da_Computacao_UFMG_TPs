#===========================================================
Este trabalho foi desenvolvido por:

- 2021031777 Bernardo do Nascimento Nunes
- 2021031769 Etelvina Costa Santos Sá Oliveira
- 2020041973 Igor Lacerda Faria da Silva
- 2021031807 Indra Matsiendra Cardoso Dias Ribeiro

============================================================#

#=
------------
 DESCRIÇÃO:
------------
Neste projeto, adotamos a heurística de buscar o subgrafo induzido de peso máximo em um grafo. O algoritmo inicia 
com um conjunto de todos os vértices e, em seguida, aplica uma estratégia gulosa para otimizar o peso total das 
arestas. Este processo envolve a remoção progressiva de vértices que não contribuem para o aumento do peso total 
do subgrafo. O código mantém um registro das arestas e dos vértices envolvidos, gerenciando eficientemente os 
dados do grafo.

O grafo é lido a partir de um arquivo e as arestas são armazenadas em um dicionário para fácil acesso. O peso total 
é calculado considerando todas as arestas que conectam os vértices no subgrafo induzido. A heurística implementada 
garante a busca por um subgrafo que maximize a soma dos pesos das arestas, removendo vértices de forma a otimizar 
este valor.

=#

function LerDadosDoGrafo(caminhoDoArquivo)
    arestas = Dict()
    conjuntoDeVertices = Set()
    open(caminhoDoArquivo, "r") do f
        for linha in eachline(f)
            if startswith(linha, "n")
                continue
            elseif startswith(linha, "e")
                dados = split(linha)
                v1, v2, peso = parse(Int, dados[2]), parse(Int, dados[3]), parse(Float64, dados[4])
                arestas[(v1, v2)] = peso
                push!(conjuntoDeVertices, v1)
                push!(conjuntoDeVertices, v2)
            end
        end
    end
    return arestas, conjuntoDeVertices
end

function CalcularPesoTotal(verticesDoSubgrafo, arestas)
    pesoTotal = 0.0
    for ((v1, v2), peso) in arestas
        if v1 in verticesDoSubgrafo && v2 in verticesDoSubgrafo
            pesoTotal += peso
        end
    end
    return pesoTotal
end

function SubgrafoDePesoMaximo(arestas, vertices)
    verticesDoSubgrafo = copy(vertices)
    pesoTotal = CalcularPesoTotal(verticesDoSubgrafo, arestas)

    melhorando = true
    verticeParaRemover = nothing  # Inicializar a variável aqui

    while melhorando
        melhorando = false
        melhorPeso = pesoTotal

        for vertice in verticesDoSubgrafo
            novosVerticesDoSubgrafo = setdiff(verticesDoSubgrafo, Set([vertice]))
            novoPeso = CalcularPesoTotal(novosVerticesDoSubgrafo, arestas)
            if novoPeso > melhorPeso
                melhorPeso = novoPeso
                verticeParaRemover = vertice
                melhorando = true
            end
        end

        if melhorando
            setdiff!(verticesDoSubgrafo, Set([verticeParaRemover]))
            pesoTotal = melhorPeso
        end
    end

    return pesoTotal, verticesDoSubgrafo
end



arestas, todosOsVertices = LerDadosDoGrafo(ARGS[1]) # Lendo os dados do arquivo e obtendo o conjunto de vértices


pesoMaximo, verticesDoSubgrafo = SubgrafoDePesoMaximo(arestas, todosOsVertices) # Encontrando o maior subgrafo induzido

println("TP2 2021031777: $pesoMaximo")

verticesOrdenados = sort(collect(verticesDoSubgrafo))
for vertice in verticesOrdenados
    print(vertice, "\t")
end

println()
