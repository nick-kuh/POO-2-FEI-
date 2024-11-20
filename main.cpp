#include "Jogo.cpp"

int main() {
    system("clear"); // Apagar o texto (limpar a tela)

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

    while (true) {
        cout << "Quantos jogadores no total? (Pode no máximo 6)" << endl;

        // Validação de entrada para números
        if (!(cin >> qJogadores) || qJogadores <= 0 || qJogadores > 6) {
            cout << "Por favor, insira um número válido entre 1 e 6!" << endl;
            cin.clear(); // Limpa o estado de erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora qualquer entrada inválida
            continue; // Volta para a próxima iteração
        }

        while (true) {
            cout << "Quantos jogadores Reais?" << endl;

            if (!(cin >> qReal) || qReal < 0 || qReal > qJogadores) {
                cout << "Por favor, insira um número válido entre 0 e " << qJogadores << "!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            for (int i = 0; i < qReal; i++) {
                cout << "Digite o nome do jogador " << i + 1 << ":" << endl;
                cin >> nome;
                jogo.adicionarJogador(nome, 1000, "real");
            }
            break;
        }
        break;
    }

    for (int i=0; i<(qJogadores - qReal); i++){
        jogo.adicionarJogador(nomes[rand() % 14], 1000, "cpu");
    }
    
//_____________________________________________________________________________________________________________
// Iniciando o jogo
    int n = 0; // Quantos jogos já aconteceu, iniciando pelo 0

    while(true){
        system("clear"); // Apagar o texto (limpar a tela)
        cout << "\033[1;1H"; // Garantindo que o texto será impresso na primeira linha da tela
        jogo.iniciarJogo(n++);
        // jogo.mostrarJogadores();
        jogo.exibirTabela();
        jogo.rodadas();
        // jogo.mostrarJogadores();
        jogo.exibirTabela();
        jogo.finalJogo();
        char ch;
        cout << "Quer continuar jogar (Sim -> 's'  |  Não -> qualquer letra): " << endl;
        cin >> ch;
        if (!(ch == 'S' || ch == 's')){
            break;
        }
        // Como o print vai ate 23 linhas, então começara a apagar a partir do 24
        for (int i = 24; i < 75; i++){               
            cout << "\033[" << i << ";1H";   //
            cout << "\033[2K";  // Limpa a linha atual onde estava o "apertouuuu!"
            
        }
    }
}
