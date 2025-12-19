#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

struct tcartas {
    int numero;
    char palo;
};

// Declaración de variables globales
char palos;
int num, palo, iguales;
int i = 0, j = 0;
int pos = 0;
int puntos, puntuacion[3] = {0, 0, 0};
int ganador = 0, mejorpunt = 0;

struct tcartas mazo[40];
struct tcartas jugada[3];
struct tcartas naipes[3];

// Función para asignar valores aleatorios a las cartas
void valores() {
    num = rand() % 10;  // Número aleatorio entre 0 y 9
    palo = rand() % 4;  // Palo aleatorio entre 0 y 3

    if (num > 6) {
        num += 3;  // Ajustar números 8 y 9
    } else {
        num += 1;  // Asegurar que el número esté entre 1 y 7
    }

    if (palo == 0) {
        palos = 'O';  // Oro
    } else if (palo == 1) {
        palos = 'E';  // Espadas
    } else if (palo == 2) {
        palos = 'C';  // Copa
    } else if (palo == 3) {
        palos = 'B';  // Bastos
    }
}

// Función para limpiar la pantalla dependiendo del sistema operativo
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux / MacOS
    #endif
}

int main() {
    srand(time(NULL));  // Inicializa la semilla para números aleatorios

    // Mezcla el mazo de cartas
    while (i < 40) {
        iguales = 0;
        valores();  // Asigna valores aleatorios a una carta

        for (j = 0; j < 40; j++) {
            if (num == mazo[j].numero && palos == mazo[j].palo) {
                iguales = 1;  // Evita duplicados en el mazo
            }
        }

        if (iguales == 0) {
            mazo[i].numero = num;
            mazo[i].palo = palos;
            i++;
        }
    }

    // Juego para los 3 jugadores
    for (j = 0; j < 3; j++) {
        // Seleccionar 3 cartas del mazo para las "naipes"
        for (i = 0; i < 3; i++) {
            naipes[i].numero = mazo[pos].numero;
            naipes[i].palo = mazo[pos].palo;
            mazo[pos].numero = 0;
            mazo[pos].palo = ' ';
            pos++;
        }

        // Seleccionar 3 cartas para la jugada del jugador
        for (i = 0; i < 3; i++) {
            jugada[i].numero = mazo[pos].numero;
            jugada[i].palo = mazo[pos].palo;
            mazo[pos].numero = 0;
            mazo[pos].palo = ' ';
            pos++;
        }

        // Mostrar las cartas del "solitario"
        printf("\n\tEs el turno del jugador %d\n", j + 1);
        printf("\n\tCartas del juego:\n");
        for (i = 0; i < 3; i++) {
            printf("\t%i de %c\n", naipes[i].numero, naipes[i].palo);
        }

        // Mostrar las cartas que el jugador ha sacado
        printf("\n\tCartas sacadas por el jugador %d:\n", j + 1);
        for (i = 0; i < 3; i++) {
            printf("\t%i de %c\n", jugada[i].numero, jugada[i].palo);
        }

        // Calcular el puntaje por cada carta jugada
        for (i = 0; i < 3; i++) {
            int mas = jugada[i].numero, menos = jugada[i].numero;

            if (naipes[i].numero == jugada[i].numero || naipes[i].palo == jugada[i].palo) {
                puntos = 10;  // Coincide número o palo
            } else {
                mas++;
                menos--;
                if (naipes[i].numero == mas || naipes[i].numero == menos) {
                    puntos = 5;  // Diferencia de 1
                } else {
                    mas++;
                    menos--;
                    if (naipes[i].numero == mas || naipes[i].numero == menos) {
                        puntos = 3;  // Diferencia de 2
                    } else {
                        puntos = 0;  // Sin puntuación
                    }
                }
            }
            puntuacion[j] += puntos;
        }

        // Mostrar la puntuación obtenida por el jugador
        printf("\n\tLa puntuación obtenida por el jugador %d es: %d\n", j + 1, puntuacion[j]);
        printf("\n\tPara avanzar, presione enter...\n");
        getchar();  // Pausa y espera por la tecla Enter
        limpiarPantalla();  // Limpiar la pantalla para el siguiente jugador
    }

    // Determinar al ganador
    for (j = 0; j < 3; j++) {
        if (puntuacion[j] > mejorpunt) {
            ganador = j + 1;
            mejorpunt = puntuacion[j];
        }
        printf("\n\tPuntuación del jugador %d: %d\n", j + 1, puntuacion[j]);
    }

    // Anunciar al ganador
    printf("\n\n\tEl ganador del juego es el jugador %d con %d puntos.\n", ganador, mejorpunt);

    return 0;
}

