#=
Questao 3 da prova ->Lotsizing com Backlog
Estamos auxiliando um produtor a planejar sua produ¸c˜ao. Essa produtor quer que planejemos sua 
produ¸c˜ao para um horizonte de tempo com n per´ıodos. O produtor produz um
´unico produto, conhece as demandas dos clientes para cada per´ıodo de tempo i (di), o custo
de produzir uma unidade do produto no tempo i(ci) e o custo de armazenar uma unidade do
tempo i para o tempo i + 1(hi). Entretanto, devido a sazonalidade de seu produto, pode ser
que os pedidos dos clientes n˜ao sejam satisfeitos em um per´ıodo, esse caso, podemos entregar
o produto atrasado para o cliente, mas pagamos uma multa de pi por unidade de produto
pedida pelo cliente e ainda n˜ao entregue no per´ıodo i.
=#

using JuMP
using HiGHS

mutable struct LotSizingBacklog
    n::Int #numero de periodos
    c::Array{Int} #custo de produção
    d::Array{Int} #demandas dos clientes
    s::Array{Int} #custo de estocagem
    p::Array{Int} #multa por atraso
end

function readData(file)
	n = 0
	c = []
	d = []
	s = []
    p = []
	for l in eachline(file)
		q = split(l, "\t")
		num = parse(Int64, q[2])
		if q[1] == "n"
			n = num
			c = [0 for i=1:n]
			d = [0 for i=1:n]
			s = [0 for i=1:n]
            p = [0 for i=1:n]
		elseif q[1] == "c"
			num = parse(Int64, q[2])
			c[num] = parse(Float64, q[3])
		elseif q[1] == "d"
			num = parse(Int64, q[2])
			d[num] = parse(Float64, q[3])									
		elseif q[1] == "s"
			num = parse(Int64, q[2])
			s[num] = parse(Float64, q[3])
        elseif q[1] == "p"
			num = parse(Int64, q[2])
			p[num] = parse(Float64, q[3])
		end
	end
	return LotSizingBacklog(n,c,d,s,p)
end

function printSolution(data, x)
	println("Esquema de produção:")
	for i = 1: data.n
		println("No periodo $i é produzido $(value(x[i]))")
	end
	println()
end

model = Model(HiGHS.Optimizer)

file = open(ARGS[1], "r")

data = readData(file)

@variable(model, x[i=1:data.n] >= 0) #quantidade produzida no periodo i
@variable(model, e[i=1:data.n] >= 0) #quantidade estocada no periodo i
@variable(model, a[i=1:data.n] >= 0) #quantidade atrasada no periodo i

#Quantidade produzida no periodo 1
@constraint(model, x[1] == data.d[1] + e[1] - a[1])

#Estoque e atraso
for i=2:data.n
	@constraint(model, e[i-1] - a[i-1] + x[i] == data.d[i] + e[i] - a[i])
end

#Não ha estoque nem atraso
@constraint(model, e[data.n] == 0)
@constraint(model, a[data.n] == 0)

#Não negatividade
for i=1:data.n
	@constraint(model, x[i] >= 0)
    @constraint(model, e[i] >= 0)
    @constraint(model, a[i] >= 0)
end

@objective(model, Min, sum(data.c[i]*x[i] + data.s[i]*e[i] + data.p[i]*a[i]  for i=1:data.n))

print(model)

optimize!(model)

sol = objective_value(model)
println("TP1 2021092571 = ", sol)

#printSolution(data, x)