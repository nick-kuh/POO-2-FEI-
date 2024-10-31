// #pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Carta.cpp"

using namespace std;

class Baralho{
private:
    Carta cartas[52];

public:
    // Baralho(Carta cartas[52]){};
    Baralho(){
        for (int i=0; i<13; i++){
            for (int n=0; n<4; n++){
                cartas[i*4+n] = Carta(i+1, n);
                // cartas[i*4+n].setNome("Carta "+to_string(i+1));
            }
        }
    }

    void embaralharCartas(){
        // Gerador de números aleatórios
        random_device rd; // Obtém um valor aleatório
        mt19937 g(rd());  // Inicializa o gerador com o valor aleatório
        // Misturando a lista
        shuffle(cartas, cartas + 52, g);
    }

    void mostrarCartas() {
        for (int i = 0; i < 52; i++) {
            cout << "Carta " << cartas[i] << endl;
        }
    }

};