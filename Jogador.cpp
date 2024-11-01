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
    // Construtor
    Jogador(const string& n, double d) : nome(n), dinheiro(d), qnt_cartas(0) {}

    // Método para adicionar uma carta à mão do jogador
    void receberCarta(const Carta& carta) {
        mao.push_back(carta);
        qnt_cartas++;  // Atualiza a quantidade de cartas na mão
    }

    // Método para calcular a pontuação total das cartas na mão
    int calcularPontuacao() const {
        int somaCartas = 0;
        int numAses = 0;

        // Calcula o valor total da mão, considerando o valor dos Ases
        for (const Carta& carta : mao) {
            int valorCarta = regras.calcularValorCarta(carta);
            somaCartas += valorCarta;
            if (valorCarta == 11) numAses++;  // Contabiliza Áses
        }

        return regras.calcularMelhorPontuacao(somaCartas, numAses);
    }

    // Método para tomar decisão: retorna true se o jogador quer outra carta, false se quer parar
    bool tomarDecisao() const {
        int pontuacaoAtual = calcularPontuacao();
        return pontuacaoAtual < 17;  // Exemplo: jogador pede carta se a pontuação for menor que 17
    }

    // Exibe as informações do jogador
    void exibirInfo() const {
        cout << "Nome: " << nome << ", Dinheiro: " << dinheiro 
             << ", Pontuação: " << calcularPontuacao() 
             << ", Quantidade de Cartas: " << qnt_cartas << endl;
    }

    string getNome() const {
        return nome;
    }
};
