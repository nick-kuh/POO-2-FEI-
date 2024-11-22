#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <iomanip>  // Para usar std::setw
#include <fstream> // Para trabalhar com arquivos (como: log.txt)
#include "Baralho.cpp"
#include "Jogador.cpp"
#include "JogadorReal.cpp"
#include "JogadorCPU.cpp"
#include "Dealer.cpp"
#include "Regras.cpp"
#include "Aposta.cpp"

using namespace std;

// Classe principal que gerencia o jogo
class Jogo {
private:
    Baralho baralho;              // Chama a classe Baralho
    Regras regras;                // Chama a classe Regras
    vector<Jogador*> jogadores;   // Vetor de ponteiros para jogadores (reais, CPU ou Dealer)
    vector<Aposta> apostas;       // Vetor de apostas feitas pelos jogadores
    int qntJogadores = 0;         // Quantidade de jogadores na partida
    int n = 0;                    // Contador auxiliar (número de jogadores que pararam)

public:

    Jogo(){} // Construtor padrão

    // Função para escrever mensagens de log em um arquivo
    void escreverLog(const std::string& mensagem) {
        // Abrindo o arquivo em modo de adição (append)
        std::ofstream arquivoLog("log.txt", std::ios::app);

        // Verificando se o arquivo foi aberto corretamente
        if (arquivoLog.is_open()) {
            arquivoLog << mensagem << std::endl;
            arquivoLog.close(); // Fechando o arquivo após escrever
        } 
        else {
            std::cerr << "Não foi possível abrir o arquivo de log." << std::endl;
        }
    }

    void limparLog(const std::string& nomeArquivo) {
        std::ofstream arquivo(nomeArquivo, std::ios::trunc); // Abre o arquivo no modo truncate
        if (arquivo.is_open()) {
            arquivo.close(); // Fecha o arquivo imediatamente após truncá-lo
        } else {
            std::cerr << "Erro ao tentar limpar o arquivo de log." << std::endl;
    }
}

    // Adiciona jogadores ao jogo (real ou CPU)
    void adicionarJogador(string nome, int dinheiro, string tipo){
        if(tipo == "real"){
            jogadores.push_back(new JogadorReal(nome, dinheiro)); // Cria jogador real
            escreverLog("Jogador real " + nome + " adicionado");

        }
        else if (tipo == "cpu"){
            jogadores.push_back(new JogadorCPU(nome, dinheiro)); // Cria jogador CPU
            escreverLog("Jogador CPU " + nome + " adicionado");

        }
        this->qntJogadores++; // Incrementa o número de jogadores
        apostas.emplace_back(dinheiro, 0, nome); // Inicia a aposta para cada jogador
    }

    void adicionarDealer(){ // Adiciona o Dealer no Jogo
        jogadores.push_back(new Dealer);
        this->qntJogadores++; // Incrementa o número de jogadores
        escreverLog("Dealer adicionado");
    }

    void realizarApostas() { // Realiza as apostas para todos os jogadores
        for (size_t i = 0; i < jogadores.size(); ++i) { 
            if ((jogadores[i]->getDinheiro()) <= 0) { // Verifica se o jogador está sem dinheiro
                jogadores[i]->semDinheiro();
                cout << "==========| " << jogadores[i]->getNome() << " |==========" << endl;
                cout << "Não poderá mais jogar, acabou todo o dinheiro" << endl;
                cout << "===================================" << endl;
                cout << "\033[4A"; // Move o cursor 4 linhas para cima (Operação para personalização do terminal)
                cout << "\033[J"; // Limpa tudo abaixo da linha atual 
                this_thread::sleep_for(chrono::seconds(2));
                escreverLog(jogadores[i]->getNome() + " parou de jogar porque ficou sem dinheiro.");
            }

            if (!(jogadores[i]->getParou())) { // Se o jogador ainda estiver na partida
                if (jogadores[i]->getNome() != "Dealer") {  // Dealer não aposta
                    cout << "==========| " << jogadores[i]->getNome() << " |==========" << endl;

                    // Verifica se é um JogadorCPU para apostar automaticamente
                    JogadorCPU* jogadorCPU = dynamic_cast<JogadorCPU*>(jogadores[i]);
                    if (jogadorCPU) {
                        double aposta = jogadorCPU->apostarAutomaticamente();
                        apostas[i] = Aposta(aposta, jogadores[i]->getDinheiro(), jogadores[i]->getNome());
                        cout << "Apostou automaticamente " << aposta << "." << endl;

                        // Log atualizado para incluir detalhes da aposta e saldo atual
                        escreverLog(jogadores[i]->getNome() + " apostou automaticamente " + to_string(aposta) + ". Dinheiro restante: " + 
                            to_string(jogadores[i]->getDinheiro() - aposta));
                    } 
                    else {
                        // Jogadores reais fazem suas apostas manualmente
                        apostas[i].setAposta(jogadores[i]->getDinheiro());  // Prompt para o jogador real
                        double quantia = apostas[i].getValorApostado();
                        double dindin = jogadores[i]->getDinheiro();
                        double valor = dindin - quantia;

                        // Log para jogadores reais
                        escreverLog(jogadores[i]->getNome() + " apostou manualmente " + to_string(quantia) + ". Dinheiro restante: " + 
                            to_string(valor));
                    }

                    cout << "===================================" << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    cout << "\033[4A"; // Move o cursor 4 linhas para cima (Operação para personalização do terminal)
                    cout << "\033[J"; // Limpa tudo abaixo da linha atual 
                }
            }
        }
    }

    // Inicializa o jogo e distribui as cartas iniciais
    void iniciarJogo(int r) {
        int a=0; // Indice para aposta
        n = 0; // Contador auxiliar (número de jogadores que pararam)
        Aposta aposta;

        if (r == 0){
            this->adicionarDealer(); // Adiciona o Dealer apenas uma vez
        }

        for (Jogador* jogador : jogadores) { // Verifica jogadores sem dinheiro
            if (jogador->getDinheiro() <= 0){
                jogador->semDinheiro();
                Aposta& aposta = apostas[a];
                aposta.valorApostadoZero(); // Não pode apostar
                a++;
            }
        }

        escreverLog("");
        escreverLog("==================");
        escreverLog("Jogadores Apostando");
        escreverLog("==================");

        realizarApostas();  // Jogadores fazem suas apostas
        baralho.reiniciaBaralho(); // Garante o inicio da posição do baralho
        baralho.embaralharCartas(); // Embaralha as cartas

        escreverLog("");
        escreverLog("==================");
        escreverLog("Baralho embaralhado e jogo iniciado"); // LOG ADICIONADO
        escreverLog("==================");
        escreverLog("");
        escreverLog("==================");
        escreverLog("Distribuindo cartas"); // LOG ADICIONADO
        escreverLog("==================");

        // Distribui duas cartas para cada jogador
        for (Jogador* jogador : jogadores) {
            int somaCartas = 0;
            int numAses = 0;

            if ((jogador->getDinheiro() == 0) && (jogador->getParou())){
                continue; // Ignora jogadores sem dinheiro e fora do jogo
            }
            for (int i = 0; i < 2; ++i) {
                jogador->receberCarta(baralho.distribuirCarta());
                Carta carta = jogador->getCarta(i);
                escreverLog(jogador->getNome() + " recebeu uma carta: " + jogador->getCarta(i).toStringCarta()); // LOG ADICIONADO

                int valorCarta = regras.calcularValorCarta(carta);
                somaCartas += valorCarta;
                if (valorCarta == 11) {
                    numAses++;
                }
            }

            somaCartas = regras.calcularMelhorPontuacao(somaCartas, numAses);

            // Verifica se o jogador conseguiu um Blackjack
            if (somaCartas == 21) {
                jogador->deuBlackJack();
                jogador->deciciuParar();
                escreverLog(jogador->getNome() + " conseguiu um BLACKJACK!"); // LOG ADICIONADO
            } 
        }
    }

    // 
    void rodadas(){
        int pontuacaoAtual;
        int rodadas = 1;

        escreverLog("");
        escreverLog("==================");
        escreverLog("Início da Rodada 1");
        escreverLog("==================");
        
        while (true){
            n = 0;
            cout << "\033[1;36m" << "Rodada " << rodadas++ << "\033[0m" << endl; // Personalizando o terminal

            
            for (Jogador* jogador : jogadores) {
                pontuacaoAtual = jogador->calcularPontuacao(); // Calcula a pontuação do jogador
                if (jogador->getParou()){ 
                    n++; // Conta mais um, caso o jogador pare de jogar
                }
                else{ // Garantindo que o jogador não peça carta
                    if (jogador->getNome() == "Dealer" ){
                        jogador->pedirCarta(baralho.distribuirCarta(), pontuacaoAtual);
                        escreverLog("Dealer pediu uma carta"); // LOG ADICIONADO
                        continue; // Ignora o Dealer
                    }
                    cout << "_________________| " << jogador->getNome() << " |_________________" << endl;
                    jogador->pedirCarta(baralho.distribuirCarta(), pontuacaoAtual);
                    cout << "_______________________________________________________" << endl;
                    cout << "\033[4A"; // Move o cursor 4 linhas para cima (Operação para personalização do terminal)
                    cout << "\033[J"; // Limpa tudo abaixo da linha atual 
                    
                    if(jogador->getParou() == true){
                        escreverLog(jogador->getNome() + " parou. Pontuação atual: " + to_string(jogador->calcularPontuacao())); // LOG ADICIONADO
                    }
                    else{
                        escreverLog(jogador->getNome() + " pediu uma carta. Pontuação atual: " + to_string(jogador->calcularPontuacao())); // LOG ADICIONADO
                    }
                    this_thread::sleep_for(chrono::seconds(1));

                }
            }
            this_thread::sleep_for(chrono::milliseconds(300));
            exibirTabela(); // Imprime os jogadores, suas cartas e sua situação no jogo
            if (n == qntJogadores){ // Se o contador n tiver a mesma quantidade de jogadores, acaba o jogo
                break;
            } 
                escreverLog("");
                escreverLog("==================");
                escreverLog("Início da Rodada " + to_string(rodadas));
                escreverLog("==================");

        }
        escreverLog("Todos os jogadores decidiram parar, rodada encerrada."); // LOG ADICIONADO
    }

    // Método para ajudar a finalizar o jogo, define quem ganha e quem perde
    void finalJogo() {
        vector<Jogador*> vencedores;
        vector<Jogador*> empatados;
        vector<Jogador*> perdedores;
        int pontuacaoDealer;
        escreverLog("");
        escreverLog("==================");
        escreverLog("Resultados!!!"); // LOG ADICIONADO
        escreverLog("==================");

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
                continue; // Ignora o Dealer 
            }
            
            int pontuacaoJogador = jogador->calcularPontuacao();

            if (pontuacaoJogador > 21) {
                perdedores.push_back(jogador);
                escreverLog(jogador->getNome() + " perdeu do Dealer"); // LOG ADICIONADO
            } 
            else if (pontuacaoJogador > pontuacaoDealer) {
                vencedores.push_back(jogador);
                escreverLog(jogador->getNome() + " venceu do Dealer"); // LOG ADICIONADO
            } 
            else if(pontuacaoDealer > 21){
                vencedores.push_back(jogador);
                escreverLog(jogador->getNome() + " venceu do Dealer"); // LOG ADICIONADO
            }
            else if (pontuacaoJogador == pontuacaoDealer) {
                if (jogador->getBlackJack()){
                    if(jogador->getNome() == "Dealer" && jogador->getBlackJack()){
                        empatados.push_back(jogador);
                        escreverLog(jogador->getNome() + " empatou com o Dealer"); // LOG ADICIONADO
                    }
                    else{
                        vencedores.push_back(jogador);
                        escreverLog(jogador->getNome() + " venceu do Dealer"); // LOG ADICIONADO
                    }
                }
                else{
                    empatados.push_back(jogador);
                    escreverLog(jogador->getNome() + " empatou com o Dealer"); // LOG ADICIONADO
                }
            } 
            else {
                perdedores.push_back(jogador);
                escreverLog(jogador->getNome() + " perdeu do Dealer"); // LOG ADICIONADO
            }
        }

        // Processa as apostas e atualiza o saldo dos jogadores
        for (size_t i = 0; i < jogadores.size(); ++i) {
            if (jogadores[i]->getNome() == "Dealer") continue;

            Aposta& aposta = apostas[i];
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
        escreverLog("");
        escreverLog("==================");
        escreverLog("Valores Atualizados:");
        escreverLog("==================");

        cout << "\033[1;32m" << "Vencedores: "; //32m -> Verde (Deixando mais bonito no terminal)
        for (Jogador* jogador : vencedores) {
            cout << jogador->getNome() << "(" << jogador->getDinheiro() << ") ";
            escreverLog(jogador->getNome() + " Novo valor: " + 
                to_string(jogador->getDinheiro()));
        }
        cout << endl;

        cout << "\033[1;33m" << "Empatados: "; //33m -> Amarelo (Deixando mais bonito no terminal)
        for (Jogador* jogador : empatados) {
            cout << jogador->getNome() << "(" << jogador->getDinheiro() << ") ";
            escreverLog(jogador->getNome() + " Novo valor: " + 
                to_string(jogador->getDinheiro()));
        }
        cout << endl;

        cout << "\033[1;31m" << "Perdedores: "; //31m -> Vermelho (Deixando mais bonito no terminal)
        for (Jogador* jogador : perdedores) {
            cout << jogador->getNome() << "(" << jogador->getDinheiro() << ") ";
            escreverLog(jogador->getNome() + " Novo valor: " + 
                to_string(jogador->getDinheiro()));
        }
        cout << "\033[0m" << endl;

        // Fim de jogo, tira as cartas da mao
        for (Jogador* jogador : jogadores) {
            jogador->tirarCartasMao();
        }
    }

    // Exibe os jogadores, as suas cartas e a sua situação no jogo
    void exibirTabela() {
        cout << "\033[2J"; // Garante a limpeza no terminal 

        cout << "\033[1;1H"; // Inicia na primeira linha

        int larguraColuna = 140/qntJogadores; // Largura fixa para cada coluna (dependendo da quantidade de jogadores)

        // Imprime os cabeçalhos
        for (Jogador* jogador : jogadores) {
            if(jogador->getNome() == "Dealer"){
                cout << left << setw(larguraColuna) << jogador->getNome();
                continue;
            }
            cout << left << setw(larguraColuna) << jogador->getNome() << " | ";
        }
        cout << endl;

        cout << string((larguraColuna + 3) * qntJogadores - 2, '-') << endl; // Separador


        // Determina o número máximo de cartas entre todos os jogadores
        int maxCartas = 0;
        for (Jogador* jogador : jogadores) {
            maxCartas = max(maxCartas, jogador->getQntCartas());
        }

        // Exibe as cartas de cada jogador em linhas
        for (int i = 0; i < maxCartas; ++i) {
            for (Jogador* jogador : jogadores) {
                if (i < jogador->getQntCartas()) {
                    if((jogador->getNome() == "Dealer") && (n != qntJogadores)){ // Se for Dealer, mostrar apenas a primeira carta
                        if (i == 0){
                            cout << setw(larguraColuna) << jogador->getCarta(0).toStringCarta();
                        }
                        continue;
                    }
                    if(jogador->getDinheiro() == 0){
                        cout << setw(larguraColuna) << "Sem Dinheiro" << " | ";
                        continue;
                    }

                    cout << setw(larguraColuna);
                    jogador->mostrarMao(i);
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
                continue; // Só mostra a pontuação do Dealer quando todos terminarem
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
    }
};