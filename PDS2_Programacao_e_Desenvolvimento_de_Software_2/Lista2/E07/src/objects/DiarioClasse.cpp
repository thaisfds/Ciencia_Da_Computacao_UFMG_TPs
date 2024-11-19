#include "DiarioClasse.hpp"

bool DiarioClasse::determinarAprovacao(double notaSemestre, double notaEspecial, double frequencia) {

    if(notaSemestre < 0 || notaSemestre > 100)
        throw ExcecaoNotaSemestreInvalida(); 

    if(frequencia > 1 || frequencia < 0)
        throw ExcecaoFrequenciaInvalida(); 

    if(notaEspecial < 0 || notaEspecial > 100)
        throw ExcecaoNotaEspecialInvalida(); 
    
    if(notaSemestre >= 60 && frequencia >= 0.75)
        return true;
    else if(notaSemestre >= 40 && notaSemestre <60 && frequencia >= 0.75)
        if(notaEspecial>=60)
            return true;
    
    return false;

}