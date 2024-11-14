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
        cout << "Você tem " << dinheiro << " disponível para apostar." << endl;
        cout << "Qual o valor da aposta? ";
        cin >> valorApostado;
    }

    void calcularValor() {
        if (resultado == 1) {  // Ganhou na aposta
            valorRecebido = valorApostado;  // O jogador recebe o dobro da aposta inicial
        } else if (resultado == 2) {  // Perdeu na aposta
            valorRecebido = -valorApostado;  // O jogador perde o valor apostado
        } else {  // Empate
            valorRecebido = 0;  // Em caso de empate, não há ganho nem perda
        }
    }


    // Novo método para definir o resultado
    void setResultado(int res) {
        resultado = res;
    }

    int getValorRecebido() const {
        return valorRecebido;
    }

    // void pagarAposta() {
    //     cout << "Dinheiro antes: " << dinheiro << endl;
    //     dinheiro += valorRecebido;
    //     cout << "Dinheiro depois: " << dinheiro << endl;
    // }
};