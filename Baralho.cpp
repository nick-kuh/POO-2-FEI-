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
    int posicao = 0; // Variável que mantém a posição atual da próxima carta a ser distribuída

public:
    // Contrutor do Baralho
    Baralho(){
        // Preenche o baralho com todas as combinações possíveis de valores e naipes
        for (int i=0; i<13; i++){ // Valores de 1 a 13 (Ás a Rei)
            for (int n=0; n<4; n++){ // Valores do Naipe 
                cartas[i*4+n] = Carta(i+1, n);
            }
        }
    }

    // Método para embaralhar as cartas do baralho
    void embaralharCartas(){
        // Gerador de números aleatórios
        random_device rd; // Obtém um valor aleatório
        mt19937 g(rd());  // Inicializa o gerador com o valor aleatório
        // Misturando a lista
        shuffle(cartas, cartas + 52, g);
    }

    // Método para distribuir uma carta do baralho
    Carta distribuirCarta() {
        if (posicao < 52) {
            return cartas[posicao++]; // Retorna a carta na posição atual e avança para a próxima
        } 
        else {
            cout << "Todas as cartas foram distribuídas!" << endl;
            return Carta(); // É uma garantia que todas as cartas foram distribuidas
        }
    }

    // Quando inicia novo jogo, garante que a posição no baralho reinicie 
    void reiniciaBaralho(){
        posicao = 0;
    }
};