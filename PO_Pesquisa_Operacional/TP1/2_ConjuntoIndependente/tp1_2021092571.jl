#=
Questao 2 da prova -> Conjunto Independente
Dado um grafo G = (V, E), um conjunto independente ´e um conjunto de v´ertices dois a
dois n˜ao adjacentes, ou seja, sem arestas entre eles. Desejamos determinar um conjunto
independente de cardinalidade m´axima (maior tamanho em n´umero de v´ertices).
=#

using JuMP
using HiGHS

mutable struct ConjuntoIndependente
    n::Int #numero de vertices
    ng::Array{Array{Int}} #vizinhancas
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
			push!(ng[v], u)
			push!(ng[u], v)
		end
	end
	return ConjuntoIndependente(n,ng)
end

function printSolution(data, x)
    for i = 1: data.n
		if value(x[i]) > 0.5
			print("$i  ")
		end
	end
	println()
end

model = Model(HiGHS.Optimizer)

file = open(ARGS[1], "r")

data = readData(file)

@variable(model, x[1:data.n], Bin) # 1 se o vertice pertence ao conjunto independente

for v=1:data.n
    for u in data.ng[v]
        @constraint(model, x[v] + x[u] <= 1)
    end
end

@objective(model, Max, sum(x[v] for v=1:data.n))

print(model)

optimize!(model)

sol = objective_value(model)
println("TP1 2021092571 = ", sol)

#printSolution(data, x)