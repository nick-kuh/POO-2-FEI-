#pragma once
#include <iostream>
using namespace std;

class Carta{
private:
    string valor;
    int vValor;
    int vNaipe;
    string naipe;

public:

        // Construtor padrão
    Carta() : vValor(0), vNaipe(0) {}

    // Construtor parametrizado para inicializar valor e naipe
    Carta(int vValor, int vNaipe) : vValor(vValor), vNaipe(vNaipe) {
        // Inicializamos o `naipe` com base em valores `vNaipe`
        if (vNaipe == 0){
            naipe = "♥"; // Copas
        }
        else if (vNaipe == 1){
            naipe = "♠"; // Espadas
        }
        else if (vNaipe == 2){
            naipe = "♦"; // Ouros
        }
        else if (vNaipe == 3){
            naipe = "♣"; // Paus
        }
        else{
            naipe = ' ';
        }

        // Aqui também tem a mudança de valor para cartas nobres 
        if (vValor == 1){
            valor = 'A'; // Ás
        }
        else if (vValor == 11){
            valor = 'J'; // Valete
        }
        else if (vValor == 12){
            valor = 'Q'; // Rainha
        }
        else if (vValor == 13){
            valor = 'K';  // Rei
        }
        else{ 
            valor = to_string(vValor); // Conversão para números 2-10
        }
    }
    
    // Método para pegar o valor da carta, para depois calcular a pontuação da mão de um jogador
    int getValor(){
        return vValor;
    }

    // Método que ajuda a tranformar a carta em uma strint, para depois poder imprimir no terminal
    string toStringCarta(){
        return "(" + valor + " , " + naipe + ")";
    }
};