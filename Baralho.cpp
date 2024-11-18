#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Carta.cpp"

using namespace std;

class Baralho{
private:
    Carta cartas[52];
    int posicao = 0;

public:
    // Baralho(Carta cartas[52]){};
    Baralho(){
        for (int i=0; i<13; i++){
            for (int n=0; n<4; n++){
                cartas[i*4+n] = Carta(i+1, n);
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

    // Eu mudei aqui, pois tinha codigo nada a ver, só simplifiquei !!!!
    Carta distribuirCarta() {
        if (posicao < 52) {
            return cartas[posicao++];
        } 
        else {
            cout << "Todas as cartas foram distribuídas!" << endl;
            return Carta(); // É uma garantia que todas as cartas foram distribuidas
        }
    }

    // Retorna o número de cartas restantes no baralho
    int cartasRestantes() {
        return 52 - posicao;
    }

    void reiniciaBaralho(){
        posicao = 0;
    }
};