# Jogo de Cartas - Blackjack

Este projeto é uma implementação simples do jogo Blackjack, onde um jogador humano pode competir contra um jogador controlado por CPU. O código é escrito em C++ e demonstra conceitos de programação orientada a objetos, como herança e polimorfismo. Este projeto foi desenvolvido como parte de um trabalho na FEI.

## Objetivo do Jogo

O objetivo do Blackjack é obter uma mão de cartas que some o mais próximo possível de 21, sem ultrapassar esse valor. O jogador compete contra a CPU, e o vencedor é aquele que tiver a maior pontuação sem estourar (ultrapassar 21).

## Como Jogar

1. **Início do Jogo**: Ao iniciar o programa, o jogador humano será solicitado a fazer uma aposta inicial. A CPU fará uma aposta automaticamente com base em seu saldo.

2. **Distribuição das Cartas**: O jogador e a CPU recebem duas cartas cada um. As cartas são representadas por valores numéricos, onde as cartas de 2 a 10 valem seu valor nominal, as cartas de figura (J, Q, K) valem 10, e o Ás pode valer 1 ou 11, dependendo da situação.

3. **Turno do Jogador**: O jogador humano terá a opção de:
   - **Pedir Carta**: Solicitar uma nova carta para tentar aumentar sua pontuação.
   - **Parar**: Manter sua pontuação atual e passar a vez para a CPU.

4. **Turno da CPU**: A CPU tomará decisões automaticamente com base em sua pontuação atual, seguindo a regra de parar se a pontuação for 17 ou mais.

5. **Resultado do Jogo**: Após ambos os jogadores completarem seus turnos, o vencedor será determinado com base nas pontuações finais. O jogador que tiver a maior pontuação sem estourar vence a rodada.

## Estrutura do Projeto

O projeto contém as seguintes classes principais:

### Classe `Jogador`

A classe `Jogador` é a classe base que representa um jogador genérico. Ela contém atributos e métodos comuns a todos os jogadores, como:

- **Atributos**:
  - `dinheiro`: O saldo do jogador, que representa a quantidade de dinheiro que ele tem para apostar.
  - `mao`: Um vetor que armazena as cartas na mão do jogador.
  
- **Métodos**:
  - `pedirCarta()`: Método que permite ao jogador pegar uma nova carta.
  - `parar()`: Método que define que o jogador decidiu parar de pedir cartas.
  - `calcularPontuacao()`: Método que calcula a pontuação atual do jogador com base nas cartas na mão.

### Classe `JogadorCPU`

A classe `JogadorCPU` herda da classe `Jogador` e implementa a lógica para a tomada de decisões da CPU. As principais funcionalidades incluem:

- **Método `pedirCarta`**: Este método é responsável por decidir se a CPU deve pegar uma nova carta ou parar com base na pontuação atual. A CPU seguirá a regra de parar se a pontuação for 17 ou mais e pegará uma carta se a pontuação for inferior a 17.

- **Método `apostarAutomaticamente`**: Este método calcula o valor da aposta da CPU como 10% do seu saldo. Se a aposta calculada for inferior a 10, ela será ajustada para 10.

### Classe `Jogo`

A classe `Jogo` gerencia o fluxo do jogo e a interação entre os jogadores. Ela contém métodos para:

- **Iniciar o jogo**: Configura o jogo e distribui as cartas iniciais.
- **Gerenciar turnos**: Alterna entre o jogador humano e a CPU, permitindo que cada um tome suas decisões.
- **Determinar o vencedor**: Avalia as pontuações finais e determina o vencedor da rodada.

## Como Executar no Terminal

Compilar: g++ main.cpp
Executar: ./a.out
   