#include "Jogador.cpp" 
#include <iostream>

using namespace std; 

// Definição da classe Desumidificador, que herda de Atuador
class JogadorReal : public Jogador {
public:

  JogadorReal(string nome, double dinheiro)
    : Jogador(nome, dinheiro) {
    }

  virtual void pedirCarta(Carta carta){
    int pontuacaoAtual = calcularPontuacao();
    if(!this->getParou()){
      if (pontuacaoAtual > 21) {
        cout << getNome() << ", você estourou e não pode pegar mais cartas." << endl;
        this->deciciuParar();
        return;
    }

      char ch;
      cout << "+1 carta? (Sim -> 's'  |  Não -> qualquer letra)" << endl;
      cin >> ch;
      if (ch == 'S' || ch == 's'){
        this->receberCarta(carta);
      }
      else{
        this->deciciuParar();

      }
    }
    else{
      cout << this->getNome() <<" parou" << endl;
      return;
    }
  }
};

