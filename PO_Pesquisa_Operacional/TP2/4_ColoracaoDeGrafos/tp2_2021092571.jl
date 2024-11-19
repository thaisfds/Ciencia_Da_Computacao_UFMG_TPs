#=
Grupo de 4 Alunos:
- Thaís Ferreira da Silva 2021092571
- Ana Luisa Araujo Bastos 
- Lucas Almeira Santos de Souza 2021092563
=#

function ler_grafo(nome_arquivo)
    arquivo = open(nome_arquivo, "r")
    
    # Lê o número de vértices
    num_vertices = parse(Int, readline(arquivo)[3:end])
    
    # Inicializa a matriz de adjacência
    grafo = zeros(Int, num_vertices, num_vertices)
    
    # Lê as arestas e preenche a matriz de adjacência
    for linha in eachline(arquivo)
        if linha[1] == 'e'
            _, v, u = split(linha)
            v, u = parse(Int, v), parse(Int, u)
            grafo[v, u] = 1
            grafo[u, v] = 1
        end
    end
    
    close(arquivo)
    return grafo
end

function coloracao_grafos(grafo)
    num_vertices = size(grafo, 1)
    cores = zeros(Int, num_vertices)
    
    for vertice in 1:num_vertices
        vizinhos = findall(x -> x == 1, grafo[vertice, :])
        cores_vizinhos = Set(cores[vizinhos])
        
        # Encontra a menor cor não utilizada pelos vizinhos
        cor = 1
        while cor in cores_vizinhos
            cor += 1
        end
        
        cores[vertice] = cor
    end
    
    return cores
end

function escrever_certificado(cores)
    cores_por_classe = Dict()

    for (vertice, cor) in enumerate(cores)
        if haskey(cores_por_classe, cor)
            push!(cores_por_classe[cor], vertice)
        else
            cores_por_classe[cor] = [vertice]
        end
    end

    num_cores = length(unique(cores))
    println("$num_cores CORES")

    for cor in sort(collect(keys(cores_por_classe)))
        vertices = sort(cores_por_classe[cor])
        println("$cor COR: $(join(vertices, '\t'))")
    end
end

# Uso
nome_arquivo = ARGS[1]  # O nome do arquivo é passado como argumento na linha de comando
grafo = ler_grafo(nome_arquivo)
cores = coloracao_grafos(grafo)
escrever_certificado(cores)
