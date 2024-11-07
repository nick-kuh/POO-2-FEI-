#include "Jogador.cpp"

class JogadorCPU : public Jogador {
public:
    // Construtor que chama o construtor da classe base Jogador
    JogadorCPU(string nome, double dinheiro)
        : Jogador(nome, dinheiro) {
        }

    virtual void pedirCarta(Carta carta, int pontuacao) {
        // int pontuacaoAtual = calcularPontuacao();
        if(!this->getParou()){
            if (pontuacao > 21){
                cout << getNome() << ", você estourou e não pode pegar mais cartas." << endl;
                this->deciciuParar();
                return;
            }

            // Implementação de decisão automática para a CPU
            if (pontuacao < 17) {
                this->receberCarta(carta);
                cout << getNome() << " decidiu pegar uma carta." << endl;
            } else {
                cout << getNome() << " decidiu parar." << endl;
                this->deciciuParar();
            }
        }
    }
};
