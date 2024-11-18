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

    void setAposta(double dinheiro) {
        cout << "Você tem " << dinheiro << " disponível para apostar." << endl;
        while(true){
            cout << "Qual o valor da aposta? ";
            cin >> valorApostado;
            // Verifica se a entrada é válida
            if (cin.fail()) {
                cin.clear(); // Limpa o estado de erro
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora a linha de entrada
                cout << "Aposta inválida! É preciso que coloque um número." << endl;
            } 
            else if (valorApostado > dinheiro) {
                cout << "Aposta inválida! Você não pode apostar mais do que o valor disponível (" << dinheiro << ")." << endl;
            } 
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa a entrada restante
                break; // Se tudo estiver certo, sai do loop
            }
        }
    }

    void calcularValor() {
        if (resultado == 1) {  // Ganhou na aposta
            valorRecebido = valorApostado;  // O jogador recebe o dobro da aposta inicial
        } 

        else if (resultado == 2) {  // Perdeu na aposta
            valorRecebido = -valorApostado;  // O jogador perde o valor apostado
        } 

        else if (resultado == 3) {  // BlackJack na aposta
            valorRecebido = valorApostado * 1.5;  // O jogador recebe 1.5x o valor Apostado
        } 
        
        else {  // Empate
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

    void valorApostadoZero() {
        valorApostado = 0;
    }
};