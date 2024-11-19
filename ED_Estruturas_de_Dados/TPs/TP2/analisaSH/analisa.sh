cd /home/thais/Documentos/GitHub/CCOMP-UFMG/ED/TPs/TP2/analisamem
make clean
make bin

cd ..
make clean
make
./bin/run.out -v 2 -k 3 -m 100 -s 10 -i ./entradas/inputAnalise.txt -o ./saidas/output.txt -p ./analisamem/bin/log.out -l

cd analisamem/bin
./analisamem -i log.out -p nomeDoTeste
gnuplot *.gp