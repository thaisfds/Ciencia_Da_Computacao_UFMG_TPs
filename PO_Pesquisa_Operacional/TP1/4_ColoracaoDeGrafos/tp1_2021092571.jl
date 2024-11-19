#=
Questao 4 da prova -> Colora¸c˜ao de Grafos
Dado um grafo G = (V, E), uma colora¸c˜ao pr´opria ´e uma atribui¸c˜ao de cores aos v´ertices do
grafo de tal forma que v´ertices adjacentes recebem cores diferentes. Desejamos determinar
o menor n´umero de cores necess´arias para colorir de maneira pr´opria um grafo dado de
entrada..
=#

using JuMP
using HiGHS

mutable struct CoberturaDeGrafos
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
	return CoberturaDeGrafos(n,ng)
end

function printSolution(data, x, y)
    #imprimir as cores utilizadas e os vertices que pertencem a cada cor
    for k=1:data.n
        if value(y[k]) > 0.5
            print("Cor $k: ")
            for i=1:data.n
                if value(x[i,k]) > 0.5
                    print("$i  ")
                end
            end
            println()
        end
    end
end

model = Model(HiGHS.Optimizer)

file = open(ARGS[1], "r")

data = readData(file)

@variable(model, x[1:data.n, 1:data.n], Bin) # se i tem a cor k
@variable(model, y[1:data.n], Bin) # se a cor j foi usada

for i=1:data.n
    @constraint(model, sum(x[i,k] for k=1:data.n) == 1) # cada vertice tem uma cor
end

# Restrição @constraint(model, x[i,k] + x[j,k] <= y[k])
for k=1:data.n
    for i=1:data.n
        for j in data.ng[i]
            @constraint(model, x[i,k] + x[j,k] <= y[k])
        end
    end
end

@objective(model, Min, sum(y[k] for k=1:data.n))

print(model)

optimize!(model)

sol = objective_value(model)
println("TP1 2021092571 = ", sol)

#printSolution(data, x, y)