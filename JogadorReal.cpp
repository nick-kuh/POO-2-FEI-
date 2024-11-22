#pragma once
#include "Jogador.cpp"
#include <iostream>

using namespace std;

// Definição da classe JogdorReal, que herda de Jogador
class JogadorReal : public Jogador
{
public:

  // Construtor da classe JogadorReal, inicializa o jogador real com nome e dinheiro
  JogadorReal(string nome, double dinheiro)
      : Jogador(nome, dinheiro) {}

  virtual void pedirCarta(Carta carta, int pontuacao){ // Permite ao jogador real decidir se deseja pegar outra carta ou parar
    if (!(this->getParou())){ // Verifica se o jogador ainda não parou de jogar
      if (pontuacao > 21){
        cout << "Ultrapassou de 21 pontos e não pode pegar mais cartas." << endl;
        this->deciciuParar(); // Força o jogador a parar
        return; // Garante que encerra
      }

      // Pergunta ao jogador se deseja pegar mais uma carta
      char ch;
      cout << "+1 carta? (Sim -> 's'  |  Não -> qualquer letra)" << endl;
      cin >> ch;  // Recebe a resposta do jogador
      if (ch == 'S' || ch == 's'){
        this->receberCarta(carta); // Se o jogador optar por 's' ou 'S', recebe a carta
      }
      else{
        this->deciciuParar(); // Caso contrário, o jogador decide parar
      }
    }
    else{
      cout << this->getNome() << " parou de jogar" << endl; // Se o jogador já parou, exibe uma mensagem
      return; // Garante que o método se encerre corretamente
    }
  }
};