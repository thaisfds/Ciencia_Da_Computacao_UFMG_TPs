#=
Grupo de 4 Alunos:
- Thaís Ferreira da Silva 2021092571
- Ana Luisa Araujo Bastos 
- Lucas Almeira Santos de Souza 2021092563
=#

function formataEntrada(nome_arquivo)
	arquivo = open(nome_arquivo, "r")
	n = 0
	ng = [[]]

	for l in eachline(arquivo)
		q = split(l, "\t")

		if q[1] == "n"
			n = parse(Int64, q[2])
			ng = [[] for i=1:n]
		elseif q[1] == "e"
			v = parse(Int64, q[2])
			u = parse(Int64, q[3])
			push!(ng[v], u)
			push!(ng[u], v)
		end
	end
	return n, ng
end	

# ---------------------------------------------------------------

n, ng = formataEntrada(ARGS[1])

# ng = Lista de adjacâncias do grafo

function calcula(n, ng)
	# ordena os vertices pelo menor grau (tamanho da lista de adjacências)
	# e imprime o grau de cada vértice
	graus = [(length(ng[i]), i) for i=1:n]
	sort!(graus)

	solucao = []

	while length(graus) > 0
		# pega o vértice de menor grau
		v = graus[1][2]
		# remove o vértice v da lista de adjacências de todos os seus vizinhos
		# e adiciona v à solução
		for u in ng[v]
			ng[u] = filter(x -> x != v, ng[u])
			# remove os vizinhos de v de graus
			graus = filter(x -> x[2] != u, graus)
		end
		push!(solucao, v)
		# remove v de graus
		graus = filter(x -> x[2] != v, graus)
	end

	sort!(solucao)
	nVertices = length(solucao)

	println("TP2 2021092571 = ", nVertices)

	for i in solucao
		print(i, "\t")
	end
	println()
end

calcula(n, ng)