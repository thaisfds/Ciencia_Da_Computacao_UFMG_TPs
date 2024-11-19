
#=
Grupo de 3 Alunos:
- Ana Luisa Araujo Bastos  2021031459
- Lucas Almeira Santos de Souza 2021092563
- Thaís Ferreira da Silva 2021092571
=#

function formataEntrada(nome_arquivo)
	arquivo = open(nome_arquivo, "r")
	n = 0
	ng = zeros(Float64, 0, 0)

	for l in eachline(arquivo)
		q = split(l, "\t")

		if q[1] == "n"
			n = parse(Int64, q[2])
			ng = zeros(Float64, n, n)
		elseif q[1] == "e"
			v = parse(Int64, q[2])
			u = parse(Int64, q[3])
			ng[v, u] = parse(Float64, q[4])
			ng[u, v] = parse(Float64, q[4])
		end
	end
	return n, ng
end	

# ---------------------------------------------------------------

n, ng= formataEntrada(ARGS[1])
# n = numero de vertices
# ng = matriz de adjacencia com pesos


function calcula(n, ng)
	
	temNegativo = true
	verticeNegativo = -1

	#svertor solucao de tamanho n e elementos de 1 a n
	solucao = collect(1:n)

	#ordenar solucao em ordem crescente da soma dos pesos
	solucao = sort(solucao, by = x -> sum(ng[x, :]))


	#Enquanto tiver numero negativo roda o while

	while temNegativo

		#se o primeiro elemento for negativo remove da solucao
		if sum(ng[solucao[1], :]) < 0
			verticeNegativo = solucao[1]
			solucao = solucao[2:end]
		end

		#modifica ng para que toda peso que tenha verticeNegativo como destino ou origem seja 0
		for i in 1:n
			ng[verticeNegativo, i] = 0.0
			ng[i, verticeNegativo] = 0.0
		end

		#ordenar solucao em ordem crescente da soma dos pesos
		solucao = sort(solucao, by = x -> sum(ng[x, :]))

		#se o primeiro elemento for negativo temNegativo = true
		if sum(ng[solucao[1], :]) < 0
			temNegativo = true
		else
			temNegativo = false
		end

	end

	#soma todos os pesos da solucao
	somaPesos = 0

	for i in solucao
		somaPesos += sum(ng[i, :])
	end

	#ordena as solucoes em ordem crescente
	solucao = sort(solucao)

	println("TP2 2021092571 = ", somaPesos/2)

	for i in solucao
		print(i, "\t")
	end

	println()
end

calcula(n, ng)