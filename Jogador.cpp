#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Carta.cpp"
#include "Regras.cpp"
//#include "Baralho.cpp"

using namespace std;

class Jogador {
private:
    string nome;
    double dinheiro;
    vector<Carta> mao;   // Cartas na mão do jogador
    int qnt_cartas;      // Quantidade de cartas na mão
    Regras regras;
    bool parou;
    bool blackJack = false;
    int pontuacao;

public:
    // Construtor (Não precisa declarar a quantidade de cartas)
    Jogador(string nome, double dinheiro) : nome(nome), dinheiro(dinheiro), qnt_cartas(0){}
    // Jogador(string nome, double dinheiro, bool parou) : nome(nome), dinheiro(dinheiro), qnt_cartas(0), parou(parou) {}


    string getNome(){
        return nome;
    }

    double getDinheiro(){
        return dinheiro;
    }

    // Método para atualizar o saldo do jogador com o valor ganho ou perdido
    void atualizarDinheiro(double valor) {
        dinheiro += valor;
    }

    Carta getCarta(int posicao){
        return mao[posicao];
    }

    bool deciciuParar(){
        this->parou = true;
        return true;
    }

    bool getParou(){
        return parou;
    }

    bool getBlackJack(){
        return this->blackJack;
    }

    bool deuBlackJack(){
        this->blackJack = true;
        return true;
    }

    bool resetBlackJack(){
        this->blackJack = false;
        return this->blackJack;
    }

    bool resetParou(){
        this->parou = false;
        return this->parou;
    }
    
    int resetQntCarta(){
        this->qnt_cartas = 0;
        return this->qnt_cartas;
    }

    // Método para adicionar uma carta à mão do jogador
    void receberCarta(Baralho baralho) {
        mao.push_back(baralho.distribuirCarta());
        qnt_cartas++;  // Atualiza a quantidade de cartas na mão
    }

    // Método para calcular a pontuação total das cartas na mão
    int calcularPontuacao() {
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
            cout << carta.toStringCarta() << " ";  // Usa toStringCarta() para representar a carta como string
        }

    }

    //crio o método que deixa os jogadores sem cartas na mão e seto a sua pontuação como 0 para que não conte na próxima rodada
    void limparMao(){ 
        mao.clear();
        pontuacao = 0;   
    } 

    virtual void pedirCarta(Baralho baralho, int pontuacao) {
        if (pontuacao > 21){
            parou = true;
            return;
        }
        else{
            this->receberCarta(baralho);
        }
    }
};
