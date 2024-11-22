#pragma once
#include "Jogador.cpp"

class JogadorCPU : public Jogador { // A classe JogadorCPU herda da classe base Jogador
public:
    // Construtor que chama o construtor da classe base Jogador
    JogadorCPU(string nome, double dinheiro)
        : Jogador(nome, dinheiro) {} // Inicializa o JogadorCPU com um nome e uma quantia de dinheiro
        
    // Sobrescreve o método pedirCarta da classe base Jogador
    virtual void pedirCarta(Carta carta, int pontuacao) {
        if ((!this->getParou()) || (this->getBlackJack())){ // Verifica se o jogador não decidiu parar ou se possui um BlackJack
            if (pontuacao > 21){ // Se a pontuação for maior que 21, o jogador "estoura"
                cout << getNome() << ", você estourou e não pode pegar mais cartas." << endl;
                this->deciciuParar(); // Marca que o jogador decidiu parar
                return; // Garante que o método encerre
            }

            // Implementação de decisão automática para a CPU
            if (pontuacao < 17) {
                this->receberCarta(carta);
                cout << getNome() << " decidiu pegar uma carta." << endl;
            } 
            else {
                cout << getNome() << " decidiu parar." << endl;
                this->deciciuParar();
            }
            cout << "\033[1B"; // Move o cursor para linha de baixo (operação para formatação de saída no terminal)

        }
        else{
            cout << this->getNome() << " parou de jogar" << endl; // Se o jogador já parou, exibe uma mensagem informando isso
            return;
        }
    }

    // Método para definir automaticamente a aposta do Jogador CPU
    int apostarAutomaticamente() {
        int aposta = static_cast<int>(getDinheiro() * 0.1);  // Calcula a aposta como 10% do saldo do jogador
        if (aposta < 10) {  // Define um valor mínimo para a aposta
            aposta = 10;
        }
        return aposta;
    }
};
