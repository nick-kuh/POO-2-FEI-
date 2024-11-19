#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <iomanip>  // Para usar std::setw
#include "Baralho.cpp"
#include "Jogador.cpp"
#include "JogadorReal.cpp"
#include "JogadorCPU.cpp"
#include "Dealer.cpp"
#include "Regras.cpp"
#include "Aposta.cpp"

using namespace std;

class Jogo {
private:
    Baralho baralho;
    Regras regras;
    vector<Jogador*> jogadores;
    vector<Aposta> apostas;  // Vector to store bets for each player
    int qntJogadores = 0, n = 0;

public:

    Jogo(){}

    // Adiciona Jogador
    void adicionarJogador(string nome, int dinheiro, string tipo){
        if(tipo == "real"){
            jogadores.push_back(new JogadorReal(nome, dinheiro));
        }
        else if (tipo == "cpu"){
            jogadores.push_back(new JogadorCPU(nome, dinheiro));
        }
        this->qntJogadores++;
        apostas.emplace_back(dinheiro, 0, nome); // Inicia a aposta para cada jogador
    }

    void adicionarDealer(){
        jogadores.push_back(new Dealer);
        this->qntJogadores++;
    }

    void realizarApostas() {
        for (size_t i = 0; i < jogadores.size(); ++i) {
            if (!(jogadores[i]->getParou())) {
                if (jogadores[i]->getNome() != "Dealer") {  // Dealer não aposta
                    cout << "Jogador " << jogadores[i]->getNome() << ", ";
                    
                    // Verifica se é um JogadorCPU para apostar automaticamente
                    JogadorCPU* jogadorCPU = dynamic_cast<JogadorCPU*>(jogadores[i]);
                    if (jogadorCPU) {
                        int aposta = jogadorCPU->apostarAutomaticamente();
                        apostas[i] = Aposta(aposta, jogadores[i]->getDinheiro(), 0, jogadores[i]->getNome());
                        cout << jogadorCPU->getNome() << " apostou automaticamente " << aposta << "." << endl;
                    } else {
                        apostas[i].setAposta(jogadores[i]->getDinheiro());  // Prompt para o jogador real
                    }
                }
            }
        }
    }

    void iniciarJogo(int r) {
        int a=0;
        n = 0;
        Aposta aposta;
        if (r == 0){
            this->adicionarDealer();
        }
        for (Jogador* jogador : jogadores) {
            if (jogador->getDinheiro() <= 0){
                jogador->semDinheiro();
                Aposta& aposta = apostas[a];
                aposta.valorApostadoZero(); // Não pode apostar
                a++;
                
            }
        }
        realizarApostas();  // Coletar as apostas no início do jogo
        baralho.reiniciaBaralho();
        baralho.embaralharCartas();

        for (Jogador* jogador : jogadores) {
            int somaCartas = 0;
            int numAses = 0;

            if ((jogador->getDinheiro() == 0) && (jogador->getParou())){
                continue;
            }
            for (int i = 0; i < 2; ++i) {
                jogador->receberCarta(baralho.distribuirCarta());
                Carta carta = jogador->getCarta(i);
                int valorCarta = regras.calcularValorCarta(carta);
                somaCartas += valorCarta;
                if (valorCarta == 11) {
                    numAses++;
                }

            }

            somaCartas = regras.calcularMelhorPontuacao(somaCartas, numAses);

            if (somaCartas == 21) {
                jogador->deuBlackJack();
                jogador->deciciuParar();
            } 
        }
    }

    void rodadas(){
        int pontuacaoAtual;
        int rodadas = 1;
        while (true){
            n = 0;
            cout << "Rodada " << rodadas++ << endl;
            for (Jogador* jogador : jogadores) {
                pontuacaoAtual = jogador->calcularPontuacao();
                if (jogador->getParou()){
                    n++;
                }
                else{ // Garantindo que o jogador não peça carta
                    jogador->pedirCarta(baralho.distribuirCarta(), pontuacaoAtual);
                }
            }
            this_thread::sleep_for(chrono::milliseconds(500));
            //! mostrarJogadores();
            exibirTabela();
            if (n == qntJogadores){
                break;
            } 
        }
    }


void finalJogo() {
    vector<Jogador*> vencedores;
    vector<Jogador*> empatados;
    vector<Jogador*> perdedores;
    int pontuacaoDealer;

    // Obter a pontuação do Dealer
    for (Jogador* jogador : jogadores) {
        if (jogador->getNome() == "Dealer") {
            pontuacaoDealer = jogador->calcularPontuacao();
            break;
        }
    }

    // Determinar o resultado e retirar as cartas da mão de cada jogador 
    for (Jogador* jogador : jogadores) {
        if (jogador->getNome() == "Dealer") {
            continue;
        }
        
        int pontuacaoJogador = jogador->calcularPontuacao();

        if (pontuacaoJogador > 21) {
            perdedores.push_back(jogador);
        } 
        else if (pontuacaoJogador > pontuacaoDealer) {
            vencedores.push_back(jogador);
        } 
        else if(pontuacaoDealer > 21){
            vencedores.push_back(jogador);
        }
        else if (pontuacaoJogador == pontuacaoDealer) {
            if (jogador->getBlackJack()){
                if(jogador->getNome() == "Dealer" && jogador->getBlackJack()){
                    empatados.push_back(jogador);
                }
                else{
                    vencedores.push_back(jogador);
                }
            }
            empatados.push_back(jogador);
        } 
        else {
            perdedores.push_back(jogador);
        }
    }

    // Processa as apostas e atualiza o saldo dos jogadores
    for (size_t i = 0; i < jogadores.size(); ++i) {
        if (jogadores[i]->getNome() == "Dealer") continue;

        Aposta& aposta = apostas[i];
        // ! Ver quando a pessoa nao tem dinheiro e nao pode receber dinheiro
        // Define o resultado da aposta usando o método setResultado
        if (find(vencedores.begin(), vencedores.end(), jogadores[i]) != vencedores.end()) {
            if (jogadores[i]->getBlackJack()){
                aposta.setResultado(3); // BlackJack
            }
            else{
                aposta.setResultado(1);  // Vitória
            }
        } else if (find(empatados.begin(), empatados.end(), jogadores[i]) != empatados.end()) {
            aposta.setResultado(0);  // Empate
        } else {
            aposta.setResultado(2);  // Derrota
        }

        aposta.calcularValor();  // Calcula o valor a ser ajustado com base no resultado
        int valorRecebido = aposta.getValorRecebido();
        jogadores[i]->atualizarDinheiro(valorRecebido);  // Atualiza o saldo do jogador
    }

    // Exibe os resultados com o saldo de cada jogador
    cout << "Vencedores: ";
    for (Jogador* jogador : vencedores) {
        cout << jogador->getNome() << "(" << jogador->getDinheiro() << ") ";
    }
    cout << endl;

    cout << "Empatados: ";
    for (Jogador* jogador : empatados) {
        cout << jogador->getNome() << "(" << jogador->getDinheiro() << ") ";
    }
    cout << endl;

    cout << "Perdedores: ";
    for (Jogador* jogador : perdedores) {
        cout << jogador->getNome() << "(" << jogador->getDinheiro() << ") ";
    }
    cout << endl;

    // Fim de jogo, tira as cartas da mao
    for (Jogador* jogador : jogadores) {
        jogador->tirarCartasMao();
    }
}

    void exibirTabela() {
        cout << "\033[2J";

        cout << "\033[1;1H"; // Inicia na primeira linha

        int larguraColuna = 140/qntJogadores; // Largura fixa para cada coluna

        // Imprime os cabeçalhos
        for (Jogador* jogador : jogadores) {
            if(jogador->getNome() == "Dealer"){
                cout << left << setw(larguraColuna) << jogador->getNome();
                continue;
            }
            cout << left << setw(larguraColuna) << jogador->getNome() << " | ";
        }
        cout << endl;

        cout << string((larguraColuna + 3) * qntJogadores - 2, '-') << endl;


        // Determina o número máximo de cartas entre todos os jogadores
        int maxCartas = 0;
        for (Jogador* jogador : jogadores) {
            maxCartas = max(maxCartas, jogador->getQntCartas());
        }

        // Exibe as cartas de cada jogador em linhas
        for (int i = 0; i < maxCartas; ++i) {
            for (Jogador* jogador : jogadores) {
                if (i < jogador->getQntCartas()) {
                    if((jogador->getNome() == "Dealer") && (n != qntJogadores)){
                        if (i == 0){
                            cout << setw(larguraColuna) << jogador->getCarta(0).toStringCarta();
                        }
                        continue;
                    }

                    cout << setw(larguraColuna);
                    jogador->mostrarMao(i,1);
                    cout << "  | ";
                } 
                else {
                    if(jogador->getNome() == "Dealer"){
                        cout << setw(larguraColuna) << " ";
                        continue;
                    }
                    cout << setw(larguraColuna) << " " << " | "; // Espaço vazio se não houver carta
                }
            }
            cout << endl;
        }

        // Linha de separação
        cout << string((larguraColuna + 3) * qntJogadores - 2, '-') << endl;

        // Exibe a pontuação de cada Jogador
        for (Jogador* jogador : jogadores) {
            if((jogador->getNome() == "Dealer") && (n != qntJogadores)){
                // cout << endl;
                continue;
            }
            cout << setw(larguraColuna) << jogador->calcularPontuacao() << " | ";
        }
        cout << endl;

        cout << string((larguraColuna + 3) * qntJogadores - 2, '-') << endl;
        
        // Vai mostrar quem parou ou fez Black jack
        for (Jogador* jogador : jogadores){
            if(jogador->getNome() == "Dealer"){
                continue;
            }
            if(jogador->getBlackJack()){
                cout << setw(larguraColuna) << "BLACK JACK!" << " | ";
            }
            else if(jogador->getParou()){
                cout << setw(larguraColuna) << "PAROU DE JOGAR!" << " | ";
            }
            else{
                cout << setw(larguraColuna) << " " << " | "; // Espaço vazio se estiver jogando
            }
        }
        cout << endl;


        // Linha de separação
        cout << string((larguraColuna + 3) * qntJogadores - 2, '=') << endl;
        // cout << "\033[" << maxCartas + 2  << ";1H" << endl;
    }

    // Mostra os participantes
    void mostrarJogadores() {
        cout << "________________________________________________________________" << endl;
        for (Jogador* jogador : jogadores) {
            cout << jogador->getNome() << " | " << jogador->getDinheiro() << " | Cartas: ";
            if((jogador->getNome() == "Dealer") && (n != qntJogadores)){
                cout << jogador->getCarta(0).toStringCarta() << " ";
                cout << endl;
                continue;
            }

            jogador->mostrarMao(10, 0);
            cout << " | Pontuação: " << jogador->calcularPontuacao();

            if(jogador->getBlackJack()){
                cout << " | BLACK JACK!";
            }
            cout << endl;
        }
        cout << "________________________________________________________________" << endl;
    }
};