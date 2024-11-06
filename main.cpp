#include "Jogo.cpp"

int main() {

    Jogo jogo;
    jogo.adicionarJogadorReal("Nick", 100);
    jogo.adicionarJogadorCPU("Viny", 1000);
    jogo.adicionarJogadorCPU("Dereck", 500);
    
    jogo.iniciarJogo();
    jogo.mostrarJogadores();
    jogo.rodada();
    jogo.mostrarJogadores();
    // jogo.rodada();
    // jogo.mostrarJogadores();
    // jogo.rodada();
    // jogo.mostrarJogadores();




    // Inicializa o jogo com um jogador chamado "Alice" e um saldo inicial de 100
    // Jogo jogo("Alice", 100.0);

    // Inicia o jogo
    // jogo.iniciarJogo();

    return 0;
}
