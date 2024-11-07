#include "Jogo.cpp"

int main() {
    int qJogadores, qReal, dinheiro;
    string nome;
    string nomes[15] = {
        "Nick", "Viny", "Dereck", "Gustavo", "Beatriz", "Laura",
        "Sophia", "Pedro", "Mariana", "Rafael", "Lucas",
        "Matheus", "Leticia", "Daniel", "Bruno"
    };
    srand(time(0)); // Garante que o número gerado será diferente a cada execução.
    Jogo jogo;
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

    // jogo.adicionarJogadorReal("Nick", 100);
    // jogo.adicionarJogadorCPU("Viny", 1000);
    // jogo.adicionarJogadorCPU("Dereck", 500);
    
    jogo.iniciarJogo();
    jogo.mostrarJogadores();
    jogo.rodadas();
    jogo.mostrarJogadores();

    return 0;
}
