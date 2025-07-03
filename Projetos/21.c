// 21 em C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NAIPE 4
#define CARTA 13

enum { COPAS, OUROS, PAUS, ESPADAS };
enum { A, DOIS, TRES, QUATRO, CINCO, SEIS, SETE, OITO, NOVE, DEZ, J, Q, K };

int baralho[NAIPE][CARTA];

void inicializarBaralho() {
    for (int i = 0; i < NAIPE; i++) {
        for (int j = 0; j < CARTA; j++) {
            baralho[i][j] = 0;
        }
    }
}

void sortearCarta(int* naipe, int* carta) {
    do {
        *naipe = rand() % NAIPE;
        *carta = rand() % CARTA;
    } while (baralho[*naipe][*carta] == 1);
    baralho[*naipe][*carta] = 1;
}

int valorCarta(int carta) {
    if (carta == A) return 11;
    else if (carta >= DEZ) return 10;
    else return carta + 1;
}

void imprimirCarta(int naipe, int carta) {
    const char* nomesCartas[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const char* nomesNaipes[] = {"Copas", "Ouros", "Paus", "Espadas"};

    printf("%s de %s", nomesCartas[carta], nomesNaipes[naipe]);
}

int calcularPontos(int cartas[], int total) {
    int pontos = 0;
    int ases = 0;

    for (int i = 0; i < total; i++) {
        int valor = valorCarta(cartas[i]);
        pontos += valor;
        if (cartas[i] == A) ases++;
    }

    while (pontos > 21 && ases > 0) {
        pontos -= 10;
        ases--;
    }

    return pontos;
}

int main() {
    srand(time(NULL));
    inicializarBaralho();

    int jogadorCartas[10];
    int bancaCartas[10];
    int jogadorTotal = 0, bancaTotal = 0;
    int naipe, carta;
    char escolha;

    // Cartas do jogador
    printf("Suas cartas:\n");
    for (int i = 0; i < 2; i++) {
        sortearCarta(&naipe, &carta);
        jogadorCartas[jogadorTotal++] = carta;
        imprimirCarta(naipe, carta);
        printf("\n");
    }

    // Cartas da banca (só mostra a primeira)
    sortearCarta(&naipe, &carta);
    bancaCartas[bancaTotal++] = carta;
    printf("\nCarta visível da banca: ");
    imprimirCarta(naipe, carta);
    printf("\n");

    sortearCarta(&naipe, &carta);
    bancaCartas[bancaTotal++] = carta; // oculta

    // Turno do jogador
    while (1) {
        int pontos = calcularPontos(jogadorCartas, jogadorTotal);
        printf("\nTotal de pontos: %d\n", pontos);

        if (pontos > 21) {
            printf("Você estourou, mas espere o resultado final!\n");
            break;
        }

        printf("Deseja mais uma carta? (s/n): ");
        scanf(" %c", &escolha);
        if (escolha == 'n' || escolha == 'N') break;

        sortearCarta(&naipe, &carta);
        jogadorCartas[jogadorTotal++] = carta;
        imprimirCarta(naipe, carta);
        printf("\n");
    }

    // Turno da banca
    printf("\n--- Turno da banca ---\n");
    int pontosBanca = calcularPontos(bancaCartas, bancaTotal);
    while (pontosBanca < 17) {
        sortearCarta(&naipe, &carta);
        bancaCartas[bancaTotal++] = carta;
        imprimirCarta(naipe, carta);
        printf("\n");
        pontosBanca = calcularPontos(bancaCartas, bancaTotal);
    }
    printf("Turno terminado\n");

    // Mostrar resultados
    int pontosJogador = calcularPontos(jogadorCartas, jogadorTotal);
    pontosBanca = calcularPontos(bancaCartas, bancaTotal);

    printf("\n--- Resultado Final ---\n");

    printf("Suas cartas:\n");
    for (int i = 0; i < jogadorTotal; i++) {
        imprimirCarta(0, jogadorCartas[i]); // naipe irrelevante aqui
        printf("\n");
    }
    printf("Total de pontos: %d\n", pontosJogador);

    printf("\nCartas da banca:\n");
    for (int i = 0; i < bancaTotal; i++) {
        imprimirCarta(0, bancaCartas[i]); // naipe irrelevante aqui
        printf("\n");
    }
    printf("Total de pontos da banca: %d\n", pontosBanca);

    // Lógica de vitória com regra especial
    if (pontosJogador <= 21 && (pontosBanca > 21 || pontosJogador > pontosBanca)) {
        printf("Você venceu!\n");
    }
    else if (pontosBanca <= 21 && (pontosJogador > 21 || pontosBanca > pontosJogador)) {
        printf("A banca venceu.\n");
    }
    else if (pontosJogador > 21 && pontosBanca > 21) {
        int excessoJogador = pontosJogador - 21;
        int excessoBanca = pontosBanca - 21;
        if (excessoJogador < excessoBanca)
            printf("Ambos estouraram, mas você estourou menos. Você venceu!\n");
        else if (excessoBanca < excessoJogador)
            printf("Ambos estouraram, mas a banca estourou menos. A banca venceu.\n");
        else
            printf("Ambos estouraram igualmente. Empate!\n");
    }
    else {
        printf("Empate!\n");
    }

    return 0;
}
