#include "Jogador.cpp"

class JogadorCPU : public Jogador {
private:
    bool parou;

public:
    // Construtor que chama o construtor da classe base Jogador
    JogadorCPU(string nome, double dinheiro)
        : Jogador(nome, dinheiro) {}

    virtual void pedirCarta(Carta carta) {
        // Implementação de decisão automática para a CPU
        if (calcularPontuacao() < 17) {
            this->receberCarta(carta);
            cout << getNome() << " decidiu pegar uma carta." << endl;
        } else {
            cout << getNome() << " decidiu parar." << endl;
            parou = true;
        }
    }
};
