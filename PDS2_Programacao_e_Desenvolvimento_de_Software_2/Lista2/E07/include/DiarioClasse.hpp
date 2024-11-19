#ifndef DIARIOCLASSE_H
#define DIARIOCLASSE_H

class ExcecaoNotaSemestreInvalida {};

class ExcecaoNotaEspecialInvalida {};

class ExcecaoFrequenciaInvalida {};

class DiarioClasse {
    
    public:
        bool determinarAprovacao(double notaSemestre, double notaEspecial, double frequencia);

};

#endif
