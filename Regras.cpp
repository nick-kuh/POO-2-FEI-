#pragma once
#include <iostream>
#include "Carta.cpp"
#include "Jogador.cpp"

using namespace std;

class Regras {
public:
    // Calcula o valor individual da carta
    int calcularValorCarta(Carta carta) const {  // Adiciona `const`
        int valor = carta.getValor();
        if (valor > 10) return 10;  // Cartas de rosto valem 10
        if (valor == 1) return 11;  // Ás pode valer 11
        return valor;
    }

    // Ajusta a pontuação total considerando o valor do Ás como 1 ou 11
    int calcularMelhorPontuacao(int somaCartas, int numAses) const {  // Adiciona `const`
        while (somaCartas > 21 && numAses > 0) {
            somaCartas -= 10;  // Ajusta o valor do Ás de 11 para 1
            numAses--;
        }
        return somaCartas;
    }
};
