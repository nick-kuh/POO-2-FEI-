#include "Jogo.cpp"
//#include "Jogador.cpp"

int main() {

//__________________________________________________________________________________________________________
// Incializando o programa

    int qJogadores, qReal, dinheiro;
    string nome;
    string nomes[15] = {
        "Nick", "Viny", "Dereck", "Gustavo", "Beatriz", "Laura",
        "Sophia", "Pedro", "Mariana", "Rafael", "Lucas",
        "Matheus", "Leticia", "Daniel", "Bruno"
    };

    srand(time(0)); // Garante que o número gerado será diferente a cada execução.

    Jogo jogo;

//__________________________________________________________________________________________________________
// Adicionando os jogadores no jogo

    cout << "Quantos jogadores no total?" << endl;
    cin >> qJogadores;

    cout << "Quantos jogadores Reais?" << endl;
    cin >> qReal;

    for (int i=0; i<qReal; i++){
        cout << "Nome do jogador " << i+1 << ": ";
        cin >> nome;
        jogo.adicionarJogador(nome, 1000, "real");
    }

    for (int i=0; i<(qJogadores - qReal); i++){
        jogo.adicionarJogador(nomes[rand() % 14], 1000, "cpu");
    }
    
//_____________________________________________________________________________________________________________
// Iniciando o jogo
    jogo.adicionarDealer();

   for (int rod = 0; rod < 2; rod++){
        int numero_rodada = rod + 1;
        cout<<"======================"<<endl;
        cout<< "Início da mão "<<numero_rodada<<endl;
        cout<<"======================"<<endl;

        jogo.iniciarJogo();
        jogo.mostrarJogadores();
        jogo.rodadas();
        //jogo.mostrarJogadores();
        jogo.finalJogo();

        cout<<"======================"<<endl;
        cout<< "Fim da mão "<<numero_rodada<<endl;
        cout<<"======================"<<endl;
        cout <<""<<endl;

        numero_rodada += numero_rodada;
        //return 0
    }
}
