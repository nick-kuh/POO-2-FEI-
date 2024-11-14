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
#include "Aposta.cpp"

using namespace std;

class Jogo {
private:
    Baralho baralho;
    Regras regras;
    vector<Jogador*> jogadores;
    vector<Aposta> apostas;  // Vector to store bets for each player
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
        apostas.emplace_back(dinheiro, 0, nome); // Inicia a aposta para cada jogador
    }

    void adicionarDealer(){
        jogadores.push_back(new Dealer);
        this->qntJogadores++;
    }

    void realizarApostas() {
        for (size_t i = 0; i < jogadores.size(); ++i) {
            if (jogadores[i]->getNome() != "Dealer") {  // Dealer não aposta
                cout << "Jogador " << jogadores[i]->getNome() << ", ";
                
                // Verifica se é um JogadorCPU para apostar automaticamente
                JogadorCPU* jogadorCPU = dynamic_cast<JogadorCPU*>(jogadores[i]);
                if (jogadorCPU) {
                    int aposta = jogadorCPU->apostarAutomaticamente();
                    apostas[i] = Aposta(aposta, jogadores[i]->getDinheiro(), 0, jogadores[i]->getNome());
                    cout << jogadorCPU->getNome() << " apostou automaticamente " << aposta << "." << endl;
                } else {
                    apostas[i].setAposta();  // Prompt para o jogador real
                }
            }
        }
    }

    
    // Mostra os participantes
    void mostrarJogadores() {
        cout << "________________________________________________________________" << endl;
        for (Jogador* jogador : jogadores) {
            cout << jogador->getNome() << " | " << jogador->getDinheiro() << " | Cartas: ";
            if((jogador->getNome() == "Dealer") && (n != qntJogadores)){
                cout << jogador->getCarta(0).toStringCarta() << " ";
                cout << endl;
                continue;
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

    void iniciarJogo() {
        this->adicionarDealer();
        realizarApostas();  // Coletar as apostas no início do jogo

        for (Jogador* jogador : jogadores) {
            int somaCartas = 0;
            int numAses = 0;

            baralho.embaralharCartas();

            for (int i = 0; i < 2; ++i) {
                jogador->receberCarta(baralho.distribuirCarta());
                Carta carta = jogador->getCarta(i);
                int valorCarta = regras.calcularValorCarta(carta);
                somaCartas += valorCarta;
                if (valorCarta == 11) {
                    numAses++;
                }
            }

            somaCartas = regras.calcularMelhorPontuacao(somaCartas, numAses);

            if (somaCartas == 21) {
                jogador->deuBlackJack();
                jogador->deciciuParar();
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


void finalJogo() {
    vector<Jogador*> vencedores;
    vector<Jogador*> empatados;
    vector<Jogador*> perdedores;
    int pontuacaoDealer;

    // Obter a pontuação do Dealer
    for (Jogador* jogador : jogadores) {
        if (jogador->getNome() == "Dealer") {
            pontuacaoDealer = jogador->calcularPontuacao();
            break;
        }
    }

    // Determinar o resultado de cada jogador
    for (Jogador* jogador : jogadores) {
        if (jogador->getNome() == "Dealer") {
            continue;
        }

        int pontuacaoJogador = jogador->calcularPontuacao();

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

    // Processa as apostas e atualiza o saldo dos jogadores
    for (size_t i = 0; i < jogadores.size(); ++i) {
        if (jogadores[i]->getNome() == "Dealer") continue;

        Aposta& aposta = apostas[i];

        // Define o resultado da aposta usando o método setResultado
        if (find(vencedores.begin(), vencedores.end(), jogadores[i]) != vencedores.end()) {
            aposta.setResultado(1);  // Vitória
        } else if (find(empatados.begin(), empatados.end(), jogadores[i]) != empatados.end()) {
            aposta.setResultado(0);  // Empate
        } else {
            aposta.setResultado(2);  // Derrota
        }

        aposta.calcularValor();  // Calcula o valor a ser ajustado com base no resultado
        int valorRecebido = aposta.getValorRecebido();
        jogadores[i]->atualizarDinheiro(valorRecebido);  // Atualiza o saldo do jogador
    }

    // Exibe os resultados com o saldo de cada jogador
    cout << "Vencedores: ";
    for (Jogador* jogador : vencedores) {
        cout << jogador->getNome() << "(" << jogador->getDinheiro() << ") ";
    }
    cout << endl;

    cout << "Empatados: ";
    for (Jogador* jogador : empatados) {
        cout << jogador->getNome() << "(" << jogador->getDinheiro() << ") ";
    }
    cout << endl;

    cout << "Perdedores: ";
    for (Jogador* jogador : perdedores) {
        cout << jogador->getNome() << "(" << jogador->getDinheiro() << ") ";
    }
    cout << endl;
}


};