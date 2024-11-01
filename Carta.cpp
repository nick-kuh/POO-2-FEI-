#pragma once
#include <iostream>
using namespace std;

class Carta {
private:
    int valor;
    int naipe;

public:
    Carta() : valor(0), naipe(0) {}
    Carta(int v, int n) : valor(v), naipe(n) {}

    int getValor() const {  // Adiciona `const` aqui
        return valor;
    }

    string getNaipe() const {
        switch (naipe) {
            case 0: return "♥";
            case 1: return "♠";
            case 2: return "♦";
            case 3: return "♣";
            default: return "?";
        }
    }
       friend ostream& operator<<(ostream& os, const Carta& carta) {
        os << "Valor: " << carta.valor << ", Naipe: " << carta.getNaipe();
        return os;
    }
};