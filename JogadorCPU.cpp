#pragma once
#include "Jogador.cpp"

class JogadorCPU : public Jogador {
public:
    // Construtor que chama o construtor da classe base Jogador
    JogadorCPU(string nome, double dinheiro)
        : Jogador(nome, dinheiro) {
        }

    virtual void pedirCarta(Baralho baralho, int pontuacao) {
        // int pontuacaoAtual = calcularPontuacao();
        if ((!this->getParou()) || (this->getBlackJack())){
            if (pontuacao > 21){
                cout << getNome() << ", você estourou e não pode pegar mais cartas." << endl;
                this->deciciuParar();
                return;
            }

            // Implementação de decisão automática para a CPU
            if (pontuacao < 17) {
                this->receberCarta(baralho);
                cout << getNome() << " decidiu pegar uma carta." << endl;
            } else {
                cout << getNome() << " decidiu parar." << endl;
                this->deciciuParar();
            }
        }
        else{
            cout << this->getNome() << " parou de jogar" << endl;
            return;
        }
    }

        // Método para definir automaticamente a aposta do Jogador CPU
    int apostarAutomaticamente() {
        int aposta = static_cast<int>(getDinheiro() * 0.1);  // 10% do saldo
        if (aposta < 10) {  // Define um valor mínimo para a aposta
            aposta = 10;
        }
        return aposta;
    }
};
