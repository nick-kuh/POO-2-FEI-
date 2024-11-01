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

    void mostrarCartas() {
        for (int i = 0; i < 52; i++) {
            cout << "Carta " << cartas[i].toString() << endl;
        }
    }

    // Retorna o número de cartas restantes no baralho
    int cartasRestantes() {
        return 52 - posicao;
    }
};


// #pragma once
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <random>
// #include "Carta.cpp"

// using namespace std;

// class Baralho{
// private:
//     Carta cartas[52];
//     int indice;


// public:
//     // Baralho(Carta cartas[52]){};
//     Baralho():indice(0){
//         for (int i=0; i<13; i++){
//             for (int n=0; n<4; n++){
//                 cartas[i*4+n] = Carta(i+1, n);
//                 // cartas[i*4+n].setNome("Carta "+to_string(i+1));
//             }
//         }
//         embaralharCartas();
//     }

//     void embaralharCartas(){
//         // Gerador de números aleatórios
//         random_device rd; // Obtém um valor aleatório
//         mt19937 g(rd());  // Inicializa o gerador com o valor aleatório
//         // Misturando a lista
//         shuffle(cartas, cartas + 52, g);
//         indice = 0;
//     }

//     void mostrarCartas() const {
//         for (int i = 0; i < 52; i++) {
//             cout << "Carta " << i + 1 << ": " << cartas[i] << endl;
//         }
//     }

//         // Distribui a próxima carta
//     Carta distribuirCarta() {
//         if (indice < 52) {
//             return cartas[indice++];
//         } else {
//             throw out_of_range("Nenhuma carta restante no baralho.");
//         }
//     }

//     int cartasRestantes() const {
//         return 52 - indice;
//     }

// };



// Versão 2

// #pragma once
// #include <iostream>
// #include <algorithm>
// #include <random>
// #include <vector>
// #include "Carta.cpp"

// using namespace std;

// class Baralho {
// private:
//     vector<Carta> cartas;
//     int indice;  // Índice da próxima carta a ser distribuída

// public:
//     Baralho() : indice(0) {
//         // Inicializa o baralho com 52 cartas (13 valores e 4 naipes)
//         for (int i = 0; i < 13; i++) {
//             for (int n = 0; n < 4; n++) {
//                 cartas.push_back(Carta(i + 1, n));
//             }
//         }
//         embaralharCartas();
//     }

//     // Embaralha as cartas no baralho
//     void embaralharCartas() {
//         random_device rd;
//         mt19937 g(rd());
//         shuffle(cartas.begin(), cartas.end(), g);
//         indice = 0;  // Reinicia o índice
//     }

//     // Distribui a próxima carta do baralho
//     Carta distribuirCarta() {
//         if (indice < cartas.size()) {
//             return cartas[indice++];
//         } else {
//             throw out_of_range("Nenhuma carta restante no baralho.");
//         }
//     }

//     // Retorna o número de cartas restantes no baralho
//     int cartasRestantes() const {
//         return cartas.size() - indice;
//     }
// };
