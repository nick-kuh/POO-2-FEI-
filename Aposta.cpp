#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Aposta{
private:
    int valorApostado;
    int valorRecebido;
    int dinheiro;
    int resultado;
    string jogador;

public:

    Aposta() {
        this->valorApostado = valorApostado;
        this->dinheiro = dinheiro;
        this->resultado = resultado;
        this->jogador = jogador;
    }

    Aposta(int dinheiro, int resultado, string jogador) {
        this->valorApostado = valorApostado;
        this->dinheiro = dinheiro;
        this->resultado = resultado;
        this->jogador = jogador;
    }

    Aposta(int valorApostado, int dinheiro, int resultado, string jogador) {
        this->valorApostado = valorApostado;
        this->dinheiro = dinheiro;
        this->resultado = resultado;
        this->jogador = jogador;
    }

    void setAposta(){
        cout << "Qual o valor da aposta? ";
        cin >> valorApostado;
    }
    void calcularValor() {
        if (resultado == 1){ // Ganhou na aposta
            valorRecebido = valorApostado * 2;
        }
        else if (resultado == 2){ // Perdeu na aposta
            valorRecebido = -valorApostado;
        }
        else{ // empatou na aposta
            valorRecebido = valorApostado;
        }
    }
    void pagarAposta() {
        cout << "Dinheiro antes: " << dinheiro << endl;
        dinheiro += valorRecebido;
        cout << "Dinheiro depois: " << dinheiro << endl;
    }
};