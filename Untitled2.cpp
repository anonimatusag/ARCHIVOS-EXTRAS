#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definir las letras específicas
char palos[4] = {'b', 'c', 'e', 'o'};

typedef struct {
    int numero;
    char palo;
} Carta;

// Función para mezclar las cartas
void mezclar(Carta *cartas, int n) {
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        Carta temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }
}

int main() {
    // Semilla para el generador de números aleatorios
    srand(time(NULL));

    // Crear un array de 40 cartas
    Carta mazo[40];

    // Generar números y palos para cada carta
    for (int i = 0; i < 40; i++) {
        mazo[i].numero = (i % 10) + 1; // Asignar valores del 1 al 10
        if (mazo[i].numero > 7) {
            mazo[i].numero += 2; // Salta del 7 al 10, evitando 8 y 9
        }
        mazo[i].palo = palos[i / 10];  // Asignar los palos 'b', 'c', 'e', 'o'
    }

    // Mezclar las cartas
    printf("La baraja está siendo mezclada...\n");
    mezclar(mazo, 40);

    // Mostrar todas las cartas del mazo mezcladas
    printf("\nCartas mezcladas del mazo:\n");
    for (int i = 0; i < 40; i++) {
        printf("Carta %d: Número: %d, Palo: %c\n", i + 1, mazo[i].numero, mazo[i].palo);
    }

    // Crear un arreglo para las cartas de la máquina (naipes)
    Carta naipes[3];

    // Dar 3 cartas a la máquina y guardarlas en el arreglo
    for (int i = 0; i < 3; i++) {
        naipes[i] = mazo[i]; // Asignar las primeras 3 cartas
    }

    // Mostrar las cartas de la máquina
    printf("\nCartas de la máquina:\n");
    for (int i = 0; i < 3; i++) {
        printf("Carta %d: Número: %d, Palo: %c\n", i + 1, naipes[i].numero, naipes[i].palo);
    }

    // Crear arreglos para la jugada del jugador y calcular el puntaje
    Carta jugada[3];
    int puntajes[2] = {0}; // Dos jugadores humanos
    int puntajeMax = 0, ganador = -1;

    // Cada jugador humano saca 3 cartas y se comparan
    for (int jugador = 0; jugador < 2; jugador++) {
        int puntaje = 0;

        // Mostrar las cartas de la jugada del jugador
        printf("\nCartas del jugador %d:\n", jugador + 1);
        for (int i = 0; i < 3; i++) {
            jugada[i] = mazo[(jugador * 3) + i + 3];
            printf("Carta %d: Número: %d, Palo: %c\n", i + 1, jugada[i].numero, jugada[i].palo);
        }

        // Calcular el puntaje para el jugador
        for (int i = 0; i < 3; i++) {
            if (naipes[i].numero == jugada[i].numero || naipes[i].palo == jugada[i].palo) {
                puntaje += 10;
            }
            if (naipes[i].numero - jugada[i].numero == 1 || jugada[i].numero - naipes[i].numero == 1) {
                puntaje += 5;
            }
            if (naipes[i].numero - jugada[i].numero == 2 || jugada[i].numero - naipes[i].numero == 2) {
                puntaje += 3;
            }
        }

        puntajes[jugador] = puntaje;
    }

    // Mostrar los puntajes finales y el ganador en un apartado separado
    printf("\n--- Puntajes Finales ---\n");
    for (int i = 0; i < 2; i++) { // Solo dos jugadores humanos
        printf("Jugador %d: %d puntos\n", i + 1, puntajes[i]);
        if (puntajes[i] > puntajeMax) {
            puntajeMax = puntajes[i];
            ganador = i;
        }
    }
    printf("\nEl ganador es el Jugador %d con %d puntos.\n", ganador + 1, puntajeMax);

    return 0;
}

