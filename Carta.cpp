// #pragma once
#include <iostream>
using namespace std;

class Carta{
private:
    int valor;
    char naipe;

public:

    Carta() : valor(0), naipe(0) {} // Initializes with default values
    
    int getValor(){
        return valor;
    }

    char getNaipe(){
        return naipe;
    }
};