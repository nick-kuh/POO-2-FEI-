#pragma once
#include "JogadorCPU.cpp"

class Dealer : public JogadorCPU { // Classe Dealer, derivada de JogadorCPU, que representa o dealer em um jogo de cartas
public:
    // Construtor que chama o construtor da classe base Jogador
    Dealer()
        : JogadorCPU("Dealer", 1000000000) {}   // Como o Dealer não aposta, então foi colocado um valor altíssimo 

    // Método que define a lógica de o Dealer pedir ou parar de receber cartas
    virtual void pedirCarta(Carta carta, int pontuacao) {
        // Se o Dealer não decidiu parar ou não atingiu BlackJack, deve decidir o que fazer
        if ((!this->getParou()) || (this->getBlackJack())){
            if (pontuacao > 21){
                this->deciciuParar(); // É porque estourou, então obrigatoriamente deve parar
                return; // garante que o método se encerre 
            }
            // Implementação de decisão automática para a CPU
            if (pontuacao < 17) {
                this->receberCarta(carta); // Se for menor que 17, o dealer vai pedir uma carta
            } else {
                this->deciciuParar();
            }
        }
    }
};
