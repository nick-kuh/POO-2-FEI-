#include "Jogo.cpp"

int main() {

    Jogo jogo;
    jogo.adicionarJogador("Nick", 100);
    jogo.adicionarJogador("Viny", 1000);
    jogo.adicionarJogador("Dereck", 500);
    
    jogo.iniciarJogo();
    jogo.mostrarJogadores();



    // Inicializa o jogo com um jogador chamado "Alice" e um saldo inicial de 100
    // Jogo jogo("Alice", 100.0);

    // Inicia o jogo
    // jogo.iniciarJogo();

    return 0;
}
