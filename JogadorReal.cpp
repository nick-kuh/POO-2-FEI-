#include "Jogador.cpp" 
#include <iostream>

using namespace std; 

// Definição da classe Desumidificador, que herda de Atuador
class JogadorReal : public Jogador {
private:
  bool parou;
public:
  // Construtor da classe Desumidificador, que chama o construtor da classe base Atuador
  JogadorReal(string nome, double dinheiro)
    : Jogador(nome, dinheiro) {}

  virtual void pedirCarta(Carta carta){
    int pontuacaoAtual = calcularPontuacao();
    if (pontuacaoAtual > 21) {
      cout << getNome() << ", você estourou e não pode pegar mais cartas." << endl;
      parou = true;
      return;
    }

    char ch;
    cout << "+1 carta? (Sim -> 's'  |  Não -> qualquer letra)" << endl;
    cin >> ch;
    if (ch == 'S' || ch == 's'){
      this->receberCarta(carta);
    }
    else{
      parou = true;
    }
  }
};

