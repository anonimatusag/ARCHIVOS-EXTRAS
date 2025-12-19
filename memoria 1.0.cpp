#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CARTAS 16 // Total de cartas (8 pares)
#define FILAS 4
#define COLUMNAS 4

// Prototipos de funciones
void mezclar_cartas(int cartas[]);
void mostrar_cartas_completas(int cartas[]);
void limpiar_buffer();
void mostrar_tablero(int tablero[][COLUMNAS]);
void jugar(int modo, char nombre1[], char nombre2[]);
int elegir_posicion(int tablero[][COLUMNAS]);
int validar_posicion(int x, int y, int tablero[][COLUMNAS]);

// Función principal
int main() {
    int modo;
    char nombre1[50], nombre2[50];

    printf("Juego de Memoria\n");
    printf("Selecciona el modo de juego:\n");
    printf("1. 1 Jugador\n");
    printf("2. 2 Jugadores\n");
    printf("Opción: ");
    scanf("%d", &modo);
    limpiar_buffer();

    if (modo == 1) {
        printf("Ingresa tu nombre: ");
        fgets(nombre1, sizeof(nombre1), stdin);
        nombre1[strcspn(nombre1, "\n")] = '\0'; // Eliminar el salto de línea al final del nombre
    } else if (modo == 2) {
        printf("Ingresa el nombre del Jugador 1: ");
        fgets(nombre1, sizeof(nombre1), stdin);
        nombre1[strcspn(nombre1, "\n")] = '\0';

        printf("Ingresa el nombre del Jugador 2: ");
        fgets(nombre2, sizeof(nombre2), stdin);
        nombre2[strcspn(nombre2, "\n")] = '\0';
    } else {
        printf("Opción inválida. Saliendo...\n");
        return 0;
    }

    jugar(modo, nombre1, nombre2);
    return 0;
}

// Función para limpiar el buffer del teclado
void limpiar_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Función para mezclar las cartas
void mezclar_cartas(int cartas[]) {
    for (int i = 0; i < CARTAS; i++) {
        cartas[i] = (i / 2) + 1; // Asignar pares de cartas con valores de 1 a 8
    }
    srand(time(NULL));
    for (int i = 0; i < CARTAS; i++) {
        int j = rand() % CARTAS;
        int temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }
}

// Función para mostrar las cartas completas (al principio del juego)
void mostrar_cartas_completas(int cartas[]) {
    printf("\nCartas completas (solo para ver antes de jugar):\n");
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("[%d] ", cartas[i * COLUMNAS + j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Función para mostrar el tablero de juego (con cartas descubiertas o ocultas)
void mostrar_tablero(int tablero[][COLUMNAS]) {
    printf("\nTablero de juego:\n");
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == 0) {
                printf("[ ] ");
            } else {
                printf("[%d] ", tablero[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Función para jugar el juego
void jugar(int modo, char nombre1[], char nombre2[]) {
    int cartas[CARTAS];
    int tablero[FILAS][COLUMNAS] = {0}; // 0 significa que la carta está oculta
    int turno = 1; // 1 para jugador 1, 2 para jugador 2
    int aciertos1 = 0, aciertos2 = 0;

    mezclar_cartas(cartas);

    // Mostrar las cartas completas antes de empezar (solo para el jugador)
    mostrar_cartas_completas(cartas);

    // Limpiar la pantalla después de mostrar las cartas
    printf("Las cartas se van a ocultar ahora...\n");
    printf("Presiona Enter para continuar...");
    getchar();  // Espera a que el jugador presione Enter
    system("clear || cls");  // Limpia la pantalla (en Windows usa "cls")

    while (1) {
        mostrar_tablero(tablero);

        int x1, y1, x2, y2;
        printf("Turno de %s\n", turno == 1 ? nombre1 : nombre2);
        printf("Selecciona la primera carta (fila columna): ");
        scanf("%d %d", &x1, &y1);
        limpiar_buffer();
        x1--; y1--; // Ajustar para que las posiciones sean de 0 a 3

        if (validar_posicion(x1, y1, tablero)) {
            tablero[x1][y1] = cartas[x1 * COLUMNAS + y1];
            mostrar_tablero(tablero);

            printf("Selecciona la segunda carta (fila columna): ");
            scanf("%d %d", &x2, &y2);
            limpiar_buffer();
            x2--; y2--; // Ajustar para que las posiciones sean de 0 a 3

            if (validar_posicion(x2, y2, tablero)) {
                tablero[x2][y2] = cartas[x2 * COLUMNAS + y2];
                mostrar_tablero(tablero);

                if (cartas[x1 * COLUMNAS + y1] == cartas[x2 * COLUMNAS + y2]) {
                    printf("¡Coincidencia!\n");
                    if (turno == 1) aciertos1++;
                    else aciertos2++;
                    tablero[x1][y1] = tablero[x2][y2] = 0; // Desactivar las cartas
                } else {
                    printf("No hay coincidencia. Intentemos de nuevo.\n");
                    tablero[x1][y1] = tablero[x2][y2] = 0; // Ocultar las cartas nuevamente
                }

                // Cambiar de turno
                turno = (turno == 1) ? 2 : 1;
            }
        }

        // Verificar si todos los pares han sido encontrados
        int pares_restantes = 0;
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                if (tablero[i][j] != 0) pares_restantes++;
            }
        }

        if (pares_restantes == 0) {
            printf("¡Juego terminado!\n");
            if (modo == 1) {
                printf("¡Has acertado %d pares!\n", aciertos1);
            } else {
                printf("%s acertó %d pares.\n", nombre1, aciertos1);
                printf("%s acertó %d pares.\n", nombre2, aciertos2);
                if (aciertos1 > aciertos2)
                    printf("¡%s ha ganado!\n", nombre1);
                else if (aciertos2 > aciertos1)
                    printf("¡%s ha ganado!\n", nombre2);
                else
                    printf("Es un empate.\n");
            }
            break;
        }
    }
}

// Validar si la posición es válida y la carta está oculta
int validar_posicion(int x, int y, int tablero[][COLUMNAS]) {
    if (x < 0 || x >= FILAS || y < 0 || y >= COLUMNAS) {
        printf("Posición fuera de rango. Intenta de nuevo.\n");
        return 0;
    }
    if (tablero[x][y] != 0) {
        printf("La carta ya está descubierta. Elige otra posición.\n");
        return 0;
    }
    return 1;
}

