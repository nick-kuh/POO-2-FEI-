#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Carta.cpp"
#include "Regras.cpp"

using namespace std;

class Jogador {
private:
    string nome;
    double dinheiro;
    vector<Carta> mao;   // Cartas na mão do jogador
    int qnt_cartas;      // Quantidade de cartas na mão
    Regras regras;

public:

    // Jogador(string nome, int dinheiro){
    //     this->nome = nome;
    //     this->dinheiro = dinheiro;
    //     this->qnt_cartas = 0;
    // }

    // Construtor (Não precisa declarar a quantidade de cartas)
    Jogador(string nome, double dinheiro) : nome(nome), dinheiro(dinheiro), qnt_cartas(0) {}

    string getNome(){
        return nome;
    }

    double getDinheiro(){
        return dinheiro;
    }

    Carta getCarta(int posicao){
        return mao[posicao];
    }

    // Método para adicionar uma carta à mão do jogador
    void receberCarta(Carta carta) {
        mao.push_back(carta);
        qnt_cartas++;  // Atualiza a quantidade de cartas na mão
    }

    // Método para calcular a pontuação total das cartas na mão
    int calcularPontuacao() const {
        int somaCartas = 0;
        int numAses = 0;

        // Calcula o valor total da mão, considerando o valor dos Ases
        for (Carta carta : mao) {
            int valorCarta = regras.calcularValorCarta(carta);
            somaCartas += valorCarta;
            if (valorCarta == 11) numAses++;  // Contabiliza Áses
        }

        return regras.calcularMelhorPontuacao(somaCartas, numAses);
    }

    // Método para tomar decisão: retorna true se o jogador quer outra carta, false se quer parar
    bool tomarDecisao() {
        int pontuacaoAtual = calcularPontuacao();
        return pontuacaoAtual < 17;  // Exemplo: jogador pede carta se a pontuação for menor que 17
    }

    void mostrarMao() {
        for (Carta carta : mao) {
            cout << carta.toString() << " ";  // Usa toString() para representar a carta como string
        }
        cout << endl;
    }

    void pedirCarta(Carta carta) {
        int pontuacaoAtual = this->calcularPontuacao();
        cout << this->getNome() << " : " << pontuacaoAtual << endl;
        if (pontuacaoAtual > 21){
            
            cout << "Estourou, não pode continuar" << endl;
        }
        else{
            this->receberCarta(carta);
        }
    }
};
