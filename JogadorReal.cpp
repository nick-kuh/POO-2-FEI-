#pragma once
#include "Jogador.cpp"
#include <iostream>

using namespace std;

// Definição da classe JogdorReal, que herda de Jogador
class JogadorReal : public Jogador
{
public:
  JogadorReal(string nome, double dinheiro)
      : Jogador(nome, dinheiro) {}

  virtual void pedirCarta(Baralho baralho, int pontuacao){
    if (!(this->getParou())){
      if (pontuacao > 21){
        cout << getNome() << ", você estourou e não pode pegar mais cartas." << endl;
        this->deciciuParar();
        return;
      }

      char ch;
      cout << "+1 carta? (Sim -> 's'  |  Não -> qualquer letra)" << endl;
      cin >> ch;
      if (ch == 'S' || ch == 's'){
        this->receberCarta(baralho);
      }
      else{
        this->deciciuParar();
      }
    }
    else{
      cout << this->getNome() << " parou de jogar" << endl;
      return;
    }
  }
};