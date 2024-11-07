#pragma once
#include <iostream>
#include <thread>
#include "Baralho.cpp"
#include "Jogador.cpp"
#include "JogadorReal.cpp"
#include "JogadorCPU.cpp"
#include "Dealer.cpp"
#include "Regras.cpp"


using namespace std;

class Jogo {
private:
    Baralho baralho;
    Regras regras;
    vector<Jogador*> jogadores;
    int qntJogadores = 0, n = 0;

public:

    Jogo(){}

    // Adiciona Jogador
    void adicionarJogador(string nome, int dinheiro, string tipo){
        if(tipo == "real"){
            jogadores.push_back(new JogadorReal(nome, dinheiro));
        }
        else if (tipo == "cpu"){
            jogadores.push_back(new JogadorCPU(nome, dinheiro));
        }
        this->qntJogadores++;
    }

    void adicionarDealer(){
        jogadores.push_back(new Dealer);
        this->qntJogadores++;
    }

    // Mostra os participantes
    void mostrarJogadores() {
        cout << "________________________________________________________________" << endl;
        for (Jogador* jogador : jogadores) {
            cout << jogador->getNome() << " | " << jogador->getDinheiro() << " | Cartas: ";
            if((jogador->getNome() == "Dealer") && (n != qntJogadores)){
                cout << jogador->getCarta(0).toStringCarta() << " ";
            }
            else{
                jogador->mostrarMao();
                cout << " | Pontuação: " << jogador->calcularPontuacao();
            }
            if(jogador->getBlackJack()){
                cout << " | BLACK JACK!";
            }
            cout << endl;
        }
        cout << "________________________________________________________________" << endl;

    }

 // Método para iniciar o jogo
    void iniciarJogo() {
        this->adicionarDealer();
        for (Jogador* jogador : jogadores) {

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

            // mostrarJogadores();

            if (somaCartas == 21) {
                jogador->deuBlackJack();
            } 
            // else if (somaCartas > 21) {
            //     cout << "Você estourou!" << endl;
            // } 
            // else {
            //     cout << "Soma das cartas: " << somaCartas << endl;
            // }

            // cout << "Cartas restantes no baralho: " << baralho.cartasRestantes() << endl;
            // cout << "________________________________________________________________" << endl;
        }
    }

    void rodadas(){
        int pontuacaoAtual;
        int rodadas = 1;
        while (true){
            n = 0; 
            cout << "Rodada " << rodadas++ << endl;
            for (Jogador* jogador : jogadores) {
                pontuacaoAtual = jogador->calcularPontuacao();
                jogador->pedirCarta(baralho.distribuirCarta(), pontuacaoAtual);
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