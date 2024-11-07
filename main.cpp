#include "Jogo.cpp"

int main() {

    Jogo jogo;
    jogo.adicionarJogadorReal("Nick", 100);
    jogo.adicionarJogadorCPU("Viny", 1000);
    jogo.adicionarJogadorCPU("Dereck", 500);
    
    jogo.iniciarJogo();
    jogo.mostrarJogadores();
    jogo.rodadas();
    jogo.mostrarJogadores();

    return 0;
}
