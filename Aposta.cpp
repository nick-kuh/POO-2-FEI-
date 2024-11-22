#pragma once
#include <iostream>

using namespace std;

class Aposta{
private:
    int valorApostado;
    int valorRecebido;
    int dinheiro;
    int resultado;
    string jogador;

public:

    // Construtor sem Parametros 
    Aposta() {
        this->valorApostado = valorApostado;
        this->dinheiro = dinheiro;
        this->resultado = resultado;
        this->jogador = jogador;
    }

    // Construtor com parametros 
    Aposta(int valorApostado, int dinheiro, string jogador) {
        this->valorApostado = valorApostado;
        this->dinheiro = dinheiro;
        this->resultado = resultado;
        this->jogador = jogador;
    }

    // Método para pegar o valor apostado
    int getValorApostado() {
        return valorApostado;
    }

    // Aqui define o valor apostado
    void setAposta(double dinheiro) {
        cout << "Tem " << dinheiro << " disponível para apostar." << endl;
        while(true){
            cout << "Qual o valor da aposta? ";
            cin >> valorApostado;
            // Verifica se a entrada é válida
            if (cin.fail()) {
                cout << "\033[2A"; // Move o cursor 3 linhas para cima 
                cout << "\033[J"; // Limpa tudo abaixo da linha atual 
                cin.clear(); // Limpa o estado de erro
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora a linha de entrada
                cout << "Aposta inválida! É preciso que coloque um número." << endl;
            } 
            // Verifica se a entrada é válida com o quanto de dinheiro que vc tem
            else if (valorApostado > dinheiro || valorApostado <= 0) {
                cout << "\033[2A"; // Move o cursor 3 linhas para cima 
                cout << "\033[J"; // Limpa tudo abaixo da linha atual 
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


    // Método para definir o resultado
    void setResultado(int res) {
        resultado = res;
    }

    // Método para pegar o valor recebido
    int getValorRecebido() {
        return valorRecebido;
    }

    // Quando acabar dinheiro, garantir que o jogador não aposte nada
    void valorApostadoZero() {
        valorApostado = 0;
    }
};