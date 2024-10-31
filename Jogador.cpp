#include <iostream>
//#include Carta.cpp;
using namespace std;

class Jogador{
    private:     
        string nome;
        int dinheiro;
        int qnt_cartas;
    
    public:

        Jogador(string nome, int dinheiro, int qnt_cartas){
            this->nome = nome;
            this->dinheiro = dinheiro;
            this->qnt_cartas = qnt_cartas;
        }

        void receberCarta(){}
        int calcularPontuacao(){}
        void tomarDecisao(){}


};