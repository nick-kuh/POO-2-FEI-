#pragma once
#include <iostream>
#include <thread>
#include "Baralho.cpp"
#include "Jogador.cpp"
#include "JogadorReal.cpp"
#include "JogadorCPU.cpp"
#include "Regras.cpp"


using namespace std;

class Jogo {
private:
    Baralho baralho;
    Regras regras;
    vector<Jogador*> jogadores;

public:

    Jogo(){}

    // Construtor que inicializa o jogo com um jogador 
    // Jogo(const string& nomeJogador, double dinheiroInicial)
    //     : jogador(nomeJogador, dinheiroInicial) {}

    // Adiciona Jogador
    // void adicionarJogador(string nome, int dinheiro){
    //     jogadores.push_back(new Jogador(nome, dinheiro));
    // }

    // Adiciona um jogador real
    void adicionarJogadorReal(string nome, double dinheiro) {
        jogadores.push_back(new JogadorReal(nome, dinheiro));
    }

    // Adiciona um jogador CPU
    void adicionarJogadorCPU(string nome, double dinheiro) {
        jogadores.push_back(new JogadorCPU(nome, dinheiro));
    }

    // Mostra os participantes
    void mostrarJogadores() {
        cout << "________________________________________________________________" << endl;
        for (int i = 0; i < jogadores.size(); i++) {
            cout << jogadores[i]->getNome() << " | " << jogadores[i]->getDinheiro() << " | Cartas: ";
            jogadores[i]->mostrarMao();
        }
        cout << "________________________________________________________________" << endl;

    }

   

 // Método para iniciar o jogo
    void iniciarJogo() {
        for (Jogador* jogador : jogadores) {
            cout << "Iniciando o jogo para " << jogador->getNome() << "!" << endl;

            int somaCartas = 0;
            int numAses = 0;

            // Embaralha as cartas
            baralho.embaralharCartas();

            // Distribuir duas cartas iniciais para o jogador
            for (int i = 0; i < 2; ++i) {
                jogador->receberCarta(baralho.distribuirCarta());
                Carta carta = jogador->getCarta(i);
                int valorCarta = regras.calcularValorCarta(carta);
                somaCartas += valorCarta;
                if (valorCarta == 11) {
                numAses++;  // Contabiliza Áses
                }
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
            cout << "________________________________________________________________" << endl;
        }
    }

    void rodadas(){
        int n;
        int rodadas = 1;
        while (true){
            n = 0; 
            cout << "Rodada " << rodadas++ << endl;
            for (Jogador* jogador : jogadores) {
                jogador->pedirCarta(baralho.distribuirCarta());
                if (jogador->getParou()){
                    n++;
                }
            }
            this_thread::sleep_for(chrono::milliseconds(500));
            mostrarJogadores();
            if (n == jogadores.size()){
                break;
            } 
        }
    }
};

// Versão anterior
//  // Método para iniciar o jogo
//     void iniciarJogo() {
//         cout << "Iniciando o jogo para " << jogador.getNome() << "!" << endl;

//         int somaCartas = 0;
//         int numAses = 0;

//         // Distribuir duas cartas iniciais para o jogador
//         for (int i = 0; i < 2; ++i) {
//             Carta carta = baralho.distribuirCarta();
//             int valorCarta = regras.calcularValorCarta(carta);
//             somaCartas += valorCarta;
//             if (valorCarta == 11) numAses++;  // Contabiliza Áses
//             jogador.receberCarta(carta);
//             cout << "Carta " << i + 1 << ": Valor = " << carta.getValor() << ", Naipe = " << carta.getNaipe() << endl;
//         }

//         // Ajusta a pontuação se necessário
//         somaCartas = regras.calcularMelhorPontuacao(somaCartas, numAses);

//         if (somaCartas == 21) {
//             cout << "Você tem um Blackjack!" << endl;
//         } else if (somaCartas > 21) {
//             cout << "Você estourou!" << endl;
//         } else {
//             cout << "Soma das cartas: " << somaCartas << endl;
//         }

//         cout << "Cartas restantes no baralho: " << baralho.cartasRestantes() << endl;
//     }