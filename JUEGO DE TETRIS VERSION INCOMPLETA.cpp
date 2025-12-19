#include <stdio.h>
#include <stdlib.h>

// Prototipos de funciones
void mostrarMenuPrincipal();
void mostrarSubmenuJugadores();
void iniciarJuego(int dificultad, int jugadores);
void mostrarOpcionesDespuesDePartida();

int main() {
    int opcionMenuPrincipal;

    while (1) {
        mostrarMenuPrincipal();
        printf("Selecciona una opción: ");
        scanf("%d", &opcionMenuPrincipal);

        switch (opcionMenuPrincipal) {
            case 1:
                iniciarJuego(1, 0); // Modo fácil
                break;
            case 2:
                iniciarJuego(2, 0); // Modo intermedio
                break;
            case 3:
                iniciarJuego(3, 0); // Modo difícil
                break;
            case 4:
                exit(0); // Salir
                break;
            default:
                printf("Opción no válida, intenta de nuevo.\n");
        }
    }

    return 0; // Esta es la línea de retorno correcta
}

void mostrarMenuPrincipal() {
    system("cls"); // Para Windows, usar "clear" en Unix
    printf("***** TETRIS *****\n");
    printf("1. Fácil\n");
    printf("2. Intermedio\n");
    printf("3. Difícil\n");
    printf("4. Salir del juego\n");
}

void iniciarJuego(int dificultad, int jugadores) {
    system("cls");
    mostrarSubmenuJugadores();
    // Aquí se implementará la lógica del juego dependiendo de la dificultad y el número de jugadores
    mostrarOpcionesDespuesDePartida();
}

void mostrarSubmenuJugadores() {
    int opcionSubmenu;
    printf("Selecciona el número de jugadores:\n");
    printf("1. 1 Jugador (contra la máquina)\n");
    printf("2. 2 Jugadores\n");
    printf("3. Volver al menú principal\n");
    scanf("%d", &opcionSubmenu);

    // Aquí se manejarán las opciones del submenu de jugadores
}

void mostrarOpcionesDespuesDePartida() {
    printf("La partida ha terminado. Selecciona una opción:\n");
    printf("1. Volver al menú de Tetris\n");
    printf("2. Volver al menú principal\n");
    printf("3. Salir\n");
    // Aquí se manejarán las opciones después de la partida
}

