#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int numero;
    char palo;
} Carta;

int main() {
    Carta mazo[40];
    char palos[] = {'O', 'C', 'E', 'B'}; // Oros, Copas, Espadas, Bastos
    int i, j, jugador, puntaje, puntajeMax, ganador;
    Carta naipes[3], jugada[3];
    int puntajes[3] = {0};

    // Inicializar la baraja
    for (i = 0, j = 0; i < 4; i++) {
        for (int num = 1; num <= 7; num++, j++) {
            mazo[j].numero = num;
            mazo[j].palo = palos[i];
        }
        for (int num = 10; num <= 12; num++, j++) {
            mazo[j].numero = num;
            mazo[j].palo = palos[i];
        }
    }

    // Mezclar la baraja
    srand(time(0));
    for (i = 0; i < 40; i++) {
        int r = rand() % 40;
        Carta temp = mazo[i];
        mazo[i] = mazo[r];
        mazo[r] = temp;
    }

    // Mostrar 3 cartas como naipes
    printf("La baraja está siendo mezclada...\n");
    for (i = 0; i < 3; i++) {
        naipes[i] = mazo[i];
        printf("Carta mostrada %d: %d de %c\n", i + 1, naipes[i].numero, naipes[i].palo);
    }

    // Cada jugador saca 3 cartas
    for (jugador = 0; jugador < 3; jugador++) {
        puntaje = 0;
        printf("\nJugador %d, es tu turno.\n", jugador + 1);
        for (i = 0; i < 3; i++) {
            jugada[i] = mazo[(jugador * 3) + i + 3];
            printf("Saca un naipe: %d de %c\n", jugada[i].numero, jugada[i].palo);

            if (naipes[i].numero == jugada[i].numero || naipes[i].palo == jugada[i].palo) {
                puntaje += 10;
            }
            if (naipes[i].numero - jugada[i].numero == 1 || jugada[i].numero - naipes[i].numero == 1) {
                puntaje += 5;
            }
            if (naipes[i].numero - jugada[i].numero == 2 || jugada[i].numero - naipes[i].numero == 2) {
                puntaje += 3;
            }
            printf("Puntaje actual: %d\n", puntaje);
        }
        puntajes[jugador] = puntaje;
    }

    // Mostrar los puntajes finales y el ganador
    puntajeMax = 0;
    ganador = -1;
    for (i = 0; i < 3; i++) {
        printf("Puntaje del jugador %d: %d\n", i + 1, puntajes[i]);
        if (puntajes[i] > puntajeMax) {
            puntajeMax = puntajes[i];
            ganador = i;
        }
    }
    printf("\nEl ganador es el jugador %d con %d puntos.\n", ganador + 1, puntajeMax);

    return 0;
}


