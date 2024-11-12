#pragma once
#include <iostream>
#include <thread>
#include <vector>
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
                cout << endl;
                continue; // Vai pular para proxima iteração, ou seja, nao rodar o resto
            }

            jogador->mostrarMao();
            cout << " | Pontuação: " << jogador->calcularPontuacao();

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
                jogador->deciciuParar(); // Deu BlackJack, o jogador automaticamente para o Jogo
            } 
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

    void finalJogo(){
        vector<Jogador*> vencedores;
        vector<Jogador*> empatados;
        vector<Jogador*> perdedores;
        int pontuacaoDealer;

        // Encontra o Dealer na lista de jogadores
        for (Jogador* jogador : jogadores) {
            if (jogador->getNome() == "Dealer") {
                pontuacaoDealer = jogador->calcularPontuacao();
                break;
            }
        }

        for (Jogador* jogador : jogadores) {
            // Se for o Dealer, ele vai pular o Dealer
            if (jogador->getNome() == "Dealer"){
                continue;
            }

            int pontuacaoJogador = jogador->calcularPontuacao();

            // Define o resultado para cada jogador
            if (pontuacaoJogador > 21) {
                perdedores.push_back(jogador);
            } else if (pontuacaoJogador > pontuacaoDealer || pontuacaoDealer > 21) {
                vencedores.push_back(jogador);
            } else if (pontuacaoJogador == pontuacaoDealer) {
                empatados.push_back(jogador);
            } else {
                perdedores.push_back(jogador);
            }
        }

        cout << "Vencedores: ";
        for (Jogador* jogador : vencedores) {
            cout << jogador->getNome() << " ";
        }
        cout << endl;
        cout << "Empatados: ";
        for (Jogador* jogador : empatados) {
            cout << jogador->getNome() << " ";
        }
        cout << endl;
        cout << "Perdedores: ";
        for (Jogador* jogador : perdedores) {
            cout << jogador->getNome() << " ";
        }
        cout << endl;


    }
};