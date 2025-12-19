#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char palos[4] = {'o', 'c', 'e', 'b'}; // 'o' = oro, 'c' = copa, 'e' = espadas, 'b' = basto

typedef struct {
    int numero;
    char palo;
} Carta;

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void imprimirCarta(Carta carta) {
    printf("%d de %c\n", carta.numero, carta.palo);
}

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

    Carta mazo[40];
    int numCartas = 40;
    int indice = 0;

    // Rellenar el mazo de cartas
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
    Carta naipes[3]; // Cartas de la máquina
    Carta jugada[3]; // Cartas jugadas por los jugadores

    // La máquina (jugador 1) obtiene las primeras 3 cartas
    for (int i = 0; i < 3; i++) {
        naipes[i] = mazo[i];  // La máquina recibe las primeras 3 cartas
    }

    // Mostrar las cartas de la máquina
    printf("\nCartas de la maquina:\n");
    for (int i = 0; i < 3; i++) {
        printf("Carta %d: numero: %d, palo: %c\n", i + 1, naipes[i].numero, naipes[i].palo);
    }

    // Jugadores 2 y 3 (humanos)
    for (int jugador = 1; jugador < 3; jugador++) {
        printf("\nCartas del Jugador %d:\n", jugador + 1);
        
        // Los jugadores seleccionan 3 cartas
        for (int i = 0; i < 3; i++) {
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

    // La máquina juega después, comparando con las cartas de los jugadores
    int puntajeMaquina = 0;
    printf("\nResultados de la Máquina:\n");
    for (int i = 0; i < 3; i++) {
        printf("Carta %d: numero: %d, palo: %c\n", i + 1, naipes[i].numero, naipes[i].palo);
    }

    // La máquina compara sus cartas con las cartas de los jugadores
    for (int jugador = 1; jugador < 3; jugador++) {
        for (int i = 0; i < 3; i++) {
            // Comparar las cartas de la máquina con las cartas de los jugadores
            puntajeMaquina += compararCartas(naipes[i], mazo[i + jugador * 3]);
        }
    }

    puntajes[0] = puntajeMaquina;  // Almacenar puntaje de la máquina

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

