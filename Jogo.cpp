#pragma once
#include <iostream>
#include "Baralho.cpp"
#include "Jogador.cpp"
#include "Regras.cpp"

using namespace std;

class Jogo {
private:
    Baralho baralho;
    Regras regras;
    Jogador jogador;

public:
    // Construtor que inicializa o jogo com um jogador
    Jogo(const string& nomeJogador, double dinheiroInicial)
        : jogador(nomeJogador, dinheiroInicial) {}

    // Método para iniciar o jogo
    void iniciarJogo() {
        cout << "Iniciando o jogo para " << jogador.getNome() << "!" << endl;

        int somaCartas = 0;
        int numAses = 0;

        // Distribuir duas cartas iniciais para o jogador
        for (int i = 0; i < 2; ++i) {
            Carta carta = baralho.distribuirCarta();
            int valorCarta = regras.calcularValorCarta(carta);
            somaCartas += valorCarta;
            if (valorCarta == 11) numAses++;  // Contabiliza Áses
            jogador.receberCarta(carta);
            cout << "Carta " << i + 1 << ": Valor = " << carta.getValor() << ", Naipe = " << carta.getNaipe() << endl;
        }

        // Ajusta a pontuação se necessário
        somaCartas = regras.calcularMelhorPontuacao(somaCartas, numAses);

        if (somaCartas == 21) {
            cout << "Você tem um Blackjack!" << endl;
        } else if (somaCartas > 21) {
            cout << "Você estourou!" << endl;
        } else {
            cout << "Soma das cartas: " << somaCartas << endl;
        }

        cout << "Cartas restantes no baralho: " << baralho.cartasRestantes() << endl;
    }
};
