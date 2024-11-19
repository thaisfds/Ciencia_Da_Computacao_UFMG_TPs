#=
Questao 1 da prova -> Empacotamento
Considere um conjunto de objetos O = {o1, o2, . . . , on} cada objeto com um peso wi. 
Dispomos de um v´arias caixas de papel, cada uma delas com o limite de peso 10Kg. 
Desejamos empacotar nossos objetos, utilizando o menor n´umero de caixas poss´ıveis, 
dado que em nenhuma caixa o valor da soma dos pesos dos objetos ultrapasse seu limite de peso.
=#

using JuMP
using HiGHS

mutable struct Empacotamento
    n::Int64 #numero de objetos
    w::Array{Float64} #pesos
    C::Float64
end

function readData(file)
    n = 0
    C = 20
    w = []
    for l in eachline(file)
        q = split(l, "\t")
        num = parse(Int64, q[2])
        if q[1] == "n"
            n = num
            w = [0.0 for i=1:n]
        elseif q[1] == "o"
            w[num+1] = parse(Float64, q[3])
        end
    end
    return Empacotamento(n,w,C)
end

function printSolution(data, x, y)
	println("Objetos na Solução:")
	for j = 1: data.n
        if(value(y[j]) >= 0.5)
            print("CAIXA ", j, ": ")
        end
        for i = 1: data.n
            if(value(x[i,j]) == 1.0)
                print(i)
                print("   ")
            end
        end
        println()
	end
	println()
end

model = Model(HiGHS.Optimizer)

file = open(ARGS[1], "r")

data = readData(file)

# Variáveis de decisão
@variable(model, x[1:data.n, 1:data.n], Bin)
@variable(model, y[1:data.n], Bin)

# Restrições
for i=1:data.n
	@constraint(model, sum(x[i,j] for j in 1:data.n) == 1)
end

for j=1:data.n
	@constraint(model, sum(data.w[i]*x[i,j] for i in 1:data.n) <= data.C * y[j])
end

# Função objetivo
@objective(model, Min, sum(y[j] for j in 1:data.n))

optimize!(model)

sol = objective_value(model)

println("TP1 2021092571 = ", round(sol))

#printSolution(data, x, y)