#= 
Questao 5 da prova -> Maior Subgrafo Induzido
Dado um grafo G = (V, E) com pesos em suas arestas wij , um subgrafo induzido por um
conjunto de v´ertices S em G ´e definido como sendo o grafo que possui como conjunto de
v´ertices S e como conjunto de arestas, as arestas de G que possuem as duas extremidades
em S, ou seja uv ∈ E tal que u ∈ S e v ∈ S. O peso de um subgrafo induzido ´e definido
como sendo a soma de todos os pesos de suas arestas, desejamos determinar o conjunto de
v´ertices que produz o subgrafo induzido de maior peso em G. Observe que as arestas podem
ter pesos negativos. .
=#

using JuMP
using HiGHS

mutable struct Subgrafo
    n::Int #numero de vertices
    ng::Array{Array{Tuple{Int64, Float64}}} #vizinhancas
end

function readData(file)
    n = 0
	ng = [[]]
	for l in eachline(file)
		q = split(l, "\t")

		if q[1] == "n"
			n = parse(Int64, q[2])
			ng = [[] for i=1:n]
		elseif q[1] == "e"
			v = parse(Int64, q[2])
			u = parse(Int64, q[3])
			e = parse(Float64, q[4])
			push!(ng[v], (u,e))
			push!(ng[u], (v,e))
		end
	end
	return Subgrafo(n,ng)
end

function printSolution(data, x)
	for u in 1:data.n
		for (v, e) in data.ng[u]
			if value(x[u,v]) > 0.5
				print("$(value(u)) , $(value(v)) = $(value(e)) ")
			end
		end
	end
	println()
end

model = Model(HiGHS.Optimizer)

file = open(ARGS[1], "r")

data = readData(file)

@variable(model, x[1:data.n, 1:data.n], Bin) # x[i][j] = 1 se i e j pertencem ao subgrafo induzido, 0 caso contrário
@variable(model, y[1:data.n], Bin) # y[i] = 1 se i pertence ao subgrafo induzido, 0 caso contrário

for u in 1:data.n
	for (v, e) in data.ng[u]
        @constraint(model, x[u,v] <= y[u])
		@constraint(model, x[u,v] <= y[v])
		@constraint(model, x[u,v] + 1 >= y[u] + y[v])
    end
end

#maximizar o peso do subgrafo induzido
@objective(model, Max, sum(x[u,v] * e for u in 1:data.n, (v, e) in data.ng[u]))

print(model)

optimize!(model)

sol = objective_value(model)
println("TP1 2021092571 = ", sol/2)

#printSolution(data, x)