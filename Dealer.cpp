#pragma once
#include "JogadorCPU.cpp"

class Dealer : public JogadorCPU {
public:
    // Construtor que chama o construtor da classe base Jogador
    Dealer()
        : JogadorCPU("Dealer", 1000000000) {}

    virtual void pedirCarta(Baralho baralho, int pontuacao) {
        // int pontuacaoAtual = calcularPontuacao();
        if ((!this->getParou()) || (this->getBlackJack())){
            if (pontuacao > 21){
                this->deciciuParar(); // É porque estourou, então obrigatoriamente deve parar
                return;
            }

            // Implementação de decisão automática para a CPU
            if (pontuacao < 17) {
                this->receberCarta(baralho);
            } else {
                this->deciciuParar();
            }
        }
    }
};
