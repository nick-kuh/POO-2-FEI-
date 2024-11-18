#include "Jogo.cpp"

int main() {

//__________________________________________________________________________________________________________
// Incializando o programa

    int qJogadores, qReal;
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

    while(true){
        cout << "Quantos jogadores no total? (Pode no maximo 6)" << endl;
        cin >> qJogadores;
        if(0 < qJogadores && qJogadores <= 6){
            while (true) {
                cout << "Quantos jogadores Reais?" << endl;
                cin >> qReal;
                if (0 <= qReal && qReal <= qJogadores) {
                    for (int i = 0; i < qReal; i++) {
                        cout << "Digite o nome do jogador " << i + 1 << endl;
                        cin >> nome;
                        jogo.adicionarJogador(nome, 1000, "real");
                    }
                    break;
                }
            }
            break;
        }
    }

    for (int i=0; i<(qJogadores - qReal); i++){
        jogo.adicionarJogador(nomes[rand() % 14], 1000, "cpu");
    }
    
//_____________________________________________________________________________________________________________
// Iniciando o jogo
    int n = 0; // Quantos jogos já aconteceu, iniciando pelo 0

    while(true){
        jogo.iniciarJogo(n++);
        jogo.mostrarJogadores();
        jogo.rodadas();
        jogo.mostrarJogadores();
        jogo.finalJogo();
        char ch;
        cout << "Quer continuar jogar (Sim -> 's'  |  Não -> qualquer letra): " << endl;
        cin >> ch;
        if (!(ch == 'S' || ch == 's')){
            break;
        }
    }
}
