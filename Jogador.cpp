#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Carta.cpp"
#include "Regras.cpp"

using namespace std;

class Jogador {
private:
    string nome;             // Nome do jogador
    double dinheiro;         // Saldo do jogador
    vector<Carta> mao;       // Cartas na mão do jogador
    int qnt_cartas;          // Quantidade de cartas na mão
    Regras regras;           // Objeto para calcular regras do jogo
    bool parou;              // Indica se o jogador decidiu parar
    bool blackJack = false;  // Indica se o jogador conseguiu BlackJack

public:
    // Construtor para inicializar nome e saldo do jogador
    Jogador(string nome, double dinheiro) : nome(nome), dinheiro(dinheiro), qnt_cartas(0){}

    // Pega o nome do jogador
    string getNome(){
        return nome;
    }

    // Pega o quanto de dinheiro o jogador tem 
    double getDinheiro(){
        return dinheiro;
    }

    // pega a quantidade de cartas que tem em sua mão
    int getQntCartas(){
        return qnt_cartas;
    }

    // Método para atualizar o saldo do jogador com o valor ganho ou perdido
    void atualizarDinheiro(double valor) {
        dinheiro += valor;
    }

    // Pega uma das cartas que tem na mão de um jogador
    Carta getCarta(int posicao){
        return mao[posicao];
    }

    // Define que o jogador decidiu parar
    bool deciciuParar(){
        this->parou = true;
        return true;
    }

    // Verifica se o jogador decidiu parar
    bool getParou(){
        return parou;
    }

    // Verifica se o jogador conseguiu BlackJack
    bool getBlackJack(){
        return this->blackJack;
    }

    // Define que o jogador conseguiu BlackJack
    bool deuBlackJack(){
        this->blackJack = true;
        return true;
    }

    // Método para adicionar uma carta à mão do jogador
    void receberCarta(Carta carta) {
        mao.push_back(carta);
        qnt_cartas++;  // Atualiza a quantidade de cartas na mão
    }

    // Método para calcular a pontuação total das cartas na mão
    int calcularPontuacao() {
        int somaCartas = 0;
        int numAses = 0;

        // Calcula o valor total da mão, considerando o valor dos Ases
        for (Carta carta : mao) {
            int valorCarta = regras.calcularValorCarta(carta); // Calcula o Valor da carta
            somaCartas += valorCarta;
            if (valorCarta == 11) numAses++;  // Contabiliza Áses
        }

        return regras.calcularMelhorPontuacao(somaCartas, numAses); // Ajusta o valor dos Áses, se necessário, para evitar ultrapassar 21
    }

    // Método para tomar decisão: retorna true se o jogador quer outra carta, false se quer parar
    bool tomarDecisao() {
        int pontuacaoAtual = calcularPontuacao();
        return pontuacaoAtual < 17;  // Exemplo: jogador pede carta se a pontuação for menor que 17
    }

    // Mostra as cartas da mão do jogador
    void mostrarMao(int i) { 
        cout << mao[i].toStringCarta() << " ";  // Usa toStringCarta() para representar a carta como string
    }

    // Lógica de pedir carta, que considera a pontuação
    virtual void pedirCarta(Carta carta, int pontuacao) {
        if (pontuacao > 21){
            parou = true; // Se pontuação ultrapassar 21, jogador deve parar
            return; // Garante que o método encerre corretamente
        }
        else{
            this->receberCarta(carta);  // Caso contrário, recebe a carta
        }
    }

    // Remove todas as cartas da mão do jogador, reiniciando seu estado
    void tirarCartasMao(){
        parou = false;
        blackJack = false;
        qnt_cartas = 0;
        mao.clear(); // Remove todas as cartas
    }

    // Define que o jogador ficou sem dinheiro e não pode mais jogar
    void semDinheiro(){
        this->deciciuParar(); // Jogador é forçado a parar
        dinheiro = 0;
    }
};
