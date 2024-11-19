#=
Grupo de 4 Alunos:
- Thaís Ferreira da Silva 2021092571
- Ana Luisa Araujo Bastos 
- Lucas Almeira Santos de Souza 2021092563
=#

function formataEntrada(nome_arquivo)
	arquivo = open(nome_arquivo, "r")
	n = 0
	c = []
	d = []
	s = []
	p = []
	for l in eachline(arquivo)
		q = split(l, "\t")
		num = parse(Int64, q[2])
		if q[1] == "n"
			n = num
			c = zeros(n)
			d = zeros(n)
			s = zeros(n)
			p = zeros(n)
		elseif q[1] == "c"
			c[num] = parse(Float64, q[3])
		elseif q[1] == "d"
			d[num] = parse(Float64, q[3])
		elseif q[1] == "s"
			s[num] = parse(Float64, q[3])
		elseif q[1] == "p"
			p[num] = parse(Float64, q[3])
		end	
	end	
	return n, c, d, s, p
end 

# ---------------------------------------------------------------

n, c, d, s, p = formataEntrada(ARGS[1])
# c = Custo de produção no período i
# d = Demanda pelo produto no período i
# s = Custo de estocagem no período i
# p = Valor da multa por atraso no período i

function calcula(n, c, d, s, p)

	custoTotal = 0
	producao = [0 for i=1:n]
	
	for i in 1:n
		menorCusto = c[i]*d[i]
		diaMenorCusto = i
		for j in 1:i-1
			custo = d[i]*(c[j] + sum(s[j:i]))
			if custo < menorCusto
				menorCusto = custo
				diaMenorCusto = j
			end
		end
		for j in i+1:n
			custo = d[i]*(c[j] + sum(p[i:j]))
			if custo < menorCusto
				menorCusto = custo
				diaMenorCusto = j
			end
		end
		custoTotal += menorCusto
		producao[diaMenorCusto] += d[i]
	end

	println("TP2 2021092571 = ", custoTotal)
	for i in producao
		print(i, "\t")
	end
	println()
end

calcula(n, c, d, s, p)