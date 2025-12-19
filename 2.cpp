#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char palos[4] = {'o', 'c', 'e', 'b'}; // 'o' = oro, 'c' = copa, 'e' = espadas, 'b' = basto

typedef struct {
    int numero;
    char palo;
} Carta;

// Función para limpiar la pantalla
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Función para imprimir una carta
void imprimirCarta(Carta carta) {
    printf("%d de %c\n", carta.numero, carta.palo);
}

// Función para comparar cartas y calcular puntaje
int compararCartas(Carta carta1, Carta carta2) {
    if (carta1.numero == carta2.numero || carta1.palo == carta2.palo) {
        return 10;  // 10 puntos si coinciden en número o palo
    }
    if (abs(carta1.numero - carta2.numero) == 1) {
        return 5;   // 5 puntos si la diferencia es 1
    }
    if (abs(carta1.numero - carta2.numero) == 2) {
        return 3;   // 3 puntos si la diferencia es 2
    }
    return 0;       // 0 puntos en cualquier otro caso
}

int main() {
    srand(time(NULL));  // Inicializa la semilla para la generación de números aleatorios

    // Declaración de estructuras
    Carta mazo[40];    // El mazo de 40 cartas
    Carta naipes[3];   // Las 3 cartas mostradas por el Solitario
    Carta jugada[3];   // Las 3 cartas que el jugador elige para comparar

    int numCartas = 40;    // Total de cartas en el mazo
    int indice = 0;        // Índice para las cartas del mazo

    // Llenar el mazo de cartas
    for (int i = 0; i < 4; i++) {
        for (int numero = 1; numero <= 7; numero++) {
            mazo[indice++] = (Carta){numero, palos[i]};
        }
        for (int numero = 10; numero <= 12; numero++) {
            mazo[indice++] = (Carta){numero, palos[i]};
        }
    }

    // Barajar el mazo aleatoriamente
    for (int i = 0; i < 40; i++) {
        int j = rand() % 40;
        Carta temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }

    // Inicializar los puntajes
    int puntajes[3] = {0}; 
    int puntajeMax = 0, ganador = -1;

    // Mostrar que el mazo está siendo mezclado
    printf("Mezclando el mazo...\n");
    printf("El mazo ha sido mezclado. Se han sacado las siguientes cartas para jugar:\n");

    // Sacar 3 cartas del mazo para mostrar como "naipes" (cartas del solitario)
    for (int i = 0; i < 3; i++) {
        naipes[i] = mazo[--numCartas];  // Obtener carta del final del mazo
        imprimirCarta(naipes[i]);
    }

    // Jugadores (máquina y 2 humanos)
    for (int jugador = 0; jugador < 3; jugador++) {
        printf("\nTurno del Jugador %d:\n", jugador + 1);
        printf("El jugador debe seleccionar 3 cartas para comparar con las cartas del Solitario.\n");

        // Los jugadores seleccionan 3 cartas
        for (int i = 0; i < 3; i++) {
            // Mostrar las cartas disponibles y preguntar si el jugador quiere sacar una carta
            printf("\nCarta %d disponible: numero: %d, palo: %c\n", i + 1, mazo[0].numero, mazo[0].palo);
            printf("¿Vas a sacar esta carta? (s/n): ");
            char respuesta;
            scanf(" %c", &respuesta);

            if (respuesta == 's' || respuesta == 'S') {
                jugada[i] = mazo[0];  // El jugador elige la carta
                // Reemplazar la carta elegida por la última del mazo
                mazo[0] = mazo[numCartas - 1];  
                numCartas--;  
            } else {
                printf("No seleccionaste la carta, intenta con otra.\n");
                i--;  // Si no se selecciona, vuelve a pedir una carta
            }
        }

        // Calcular el puntaje de las cartas jugadas
        int puntaje = 0;
        for (int i = 0; i < 3; i++) {
            // Compara las cartas jugadas con las cartas de la máquina
            puntaje += compararCartas(naipes[i], jugada[i]);
        }

        puntajes[jugador] = puntaje;
        printf("\nPuntaje del Jugador %d: %d puntos\n", jugador + 1, puntaje);

        if (jugador < 2) { // Limpiar pantalla solo si no es el último jugador
            limpiarPantalla();
        }
    }

    // Mostrar los resultados finales
    printf("\nResultados de la partida:\n");
    for (int i = 0; i < 3; i++) {
        printf("Jugador %d: %d puntos\n", i + 1, puntajes[i]);
        if (puntajes[i] > puntajeMax) {
            puntajeMax = puntajes[i];
            ganador = i;
        }
    }

    // Anunciar al ganador
    printf("\nEl ganador es el Jugador %d con %d puntos.\n", ganador + 1, puntajeMax);

    return 0;
}

