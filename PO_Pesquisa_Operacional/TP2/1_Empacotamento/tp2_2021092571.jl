#=
Grupo de 4 Alunos:
- Thaís Ferreira da Silva 2021092571
- Ana Luisa Araujo Bastos 
- Lucas Almeira Santos de Souza 2021092563
=#

global somaParcial
global nCaixas

function formataEntrada(nome_arquivo)
	arquivo = open(nome_arquivo, "r")
	n = 0
	C = 20
	w = []
	i = 1
	for l in eachline(arquivo)
		q = split(l, "\t")
		num = parse(Int64, q[2])
		if q[1] == "n"
			n = num
			w = zeros(n)
		elseif q[1] == "o"
			w[i] = parse(Float64, q[3])
			i = i + 1
		end	
	end	
	return n, C, w
end	

# ---------------------------------------------------------------

n, C, w = formataEntrada(ARGS[1])
# C = Capacidade das caixas
# w = Peso dos objetos

function calcula(n, C, w)
    w = sort(w, rev=true)

    nCaixas = 0
    somaParcial = 0
    caixas = zeros(Int64, n)

    for i in 1:n
        if somaParcial + w[i] <= C
            somaParcial += w[i]
            caixas[i] = nCaixas
        else
            nCaixas += 1
            somaParcial = w[i]
            caixas[i] = nCaixas
        end
    end

    println("TP2 2021092571 = ", nCaixas)

    for i in 1:nCaixas
        for j in 1:n
            if caixas[j] == i
                print(j, "\t")
            end
        end
        println()
    end
end

calcula(n, C, w)