#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>  // Para cambiar colores en Windows

#define SIZE 3

char palos[4] = {'b', 'c', 'e', 'o'};

typedef struct {
    int numero;
    char palo;
} Carta;

char board[SIZE][SIZE];
char currentPlayer;
char player1Name[50], player2Name[50];
int singlePlayer = 0;
char solitarioPlayerName[50];

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    currentPlayer = 'X';
}

void printBoard() {
    system("cls"); // Usar "clear" para sistemas UNIX
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 'X') {
                setColor(12);  // Rojo para 'X'
            } else if (board[i][j] == 'O') {
                setColor(9);  // Azul para 'O'
            } else {
                setColor(15);  // Blanco para espacios vacíos
            }
            printf("  %c  ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) {
            setColor(15);  // Blanco para las líneas
            for (int j = 0; j < SIZE; j++) {
                printf("-----");
                if (j < SIZE - 1) printf("|");
            }
            printf("\n");
        }
    }
    setColor(15); // Restablecer color a blanco
}

void makeMove() {
    int row, col;
    printf("%s (Jugador %c), ingresa tu movimiento (fila y columna): ", currentPlayer == 'X' ? player1Name : player2Name, currentPlayer);
    scanf("%d %d", &row, &col);

    row--; col--; // Ajustar índice a base 0

    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
        board[row][col] = currentPlayer;
    } else {
        printf("Movimiento inválido. Inténtalo de nuevo.\n");
        makeMove();
    }
}

void makeMachineMove() {
    srand(time(0));
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (board[row][col] != ' ');

    printf("La máquina (Jugador O) ha hecho su movimiento.\n");
    board[row][col] = 'O';
}

int checkWin() {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) return 1;
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) return 1;
    }
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) return 1;
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) return 1;
    return 0;
}

int checkDraw() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void ticTacToe() {
    int gameOver = 0;
    initializeBoard();
    while (!gameOver) {
        printBoard();
        if (singlePlayer && currentPlayer == 'O') {
            makeMachineMove();
        } else {
            makeMove();
        }
        if (checkWin()) {
            printBoard();
            printf("%s (Jugador %c) gana!\n", currentPlayer == 'X' ? player1Name : player2Name, currentPlayer);
            gameOver = 1;
        } else if (checkDraw()) {
            printBoard();
            printf("Es un empate!\n");
            gameOver = 1;
        } else {
            switchPlayer();
        }
    }
    printf("\n1. Volver al menú de Tic-Tac-Toe\n");
    printf("2. Volver al menú principal\n");
    printf("3. Salir\n");
    int option;
    scanf("%d", &option);
    switch (option) {
        case 1:
            return; // Volver al menú de Tic-Tac-Toe
        case 2:
            return; // Volver al menú principal
        case 3:
            exit(0);
            break;
        default:
            printf("Opción no válida.\n");
            exit(1);
    }
}

void displayTicTacToeMenu() {
    setColor(14); // Amarillo para el título
    printf("************************************\n");
    printf("*         TIC-TAC-TOE MENU         *\n");
    printf("************************************\n");
    setColor(15); // Blanco para el texto del menú
    printf("1. Un jugador vs Máquina\n");
    printf("2. Dos jugadores\n");
    printf("3. Volver al menú principal\n");
    printf("Selecciona un modo: ");
}

void ticTacToeGame() {
    int mode;
    while (1) { // Bucle para el menú de Tic-Tac-Toe
        system("cls"); // Limpiar pantalla
        displayTicTacToeMenu();
        scanf("%d", &mode);
        if (mode == 3) {
            break; // Volver al menú principal
        }
        printf("Jugador 1, ingresa tu nombre: ");
        scanf("%s", player1Name);
        if (mode == 1) {
            singlePlayer = 1;
            snprintf(player2Name, sizeof(player2Name), "Máquina");
        } else if (mode == 2) {
            singlePlayer = 0;
            printf("Jugador 2, ingresa tu nombre: ");
            scanf("%s", player2Name);
        } else {
            printf("Opción no válida.\n");
            continue; // Volver a mostrar el menú de Tic-Tac-Toe
        }
        ticTacToe();
    }
}

void solitario() {
    srand(time(NULL));

    Carta mazo[40];
    int numCartas = 40;

    for (int i = 0; i < 40; i++) {
        mazo[i].numero = (i % 10) + 1;
        if (mazo[i].numero > 7) {
            mazo[i].numero += 2;
        }
        mazo[i].palo = palos[i / 10];
    }

    Carta naipes[3];

    for (int i = 0; i < 3; i++) {
        int indiceAleatorio = rand() % numCartas;
        naipes[i] = mazo[indiceAleatorio];
        mazo[indiceAleatorio] = mazo[numCartas - 1];
        numCartas--;
    }

    printf("\n  cartas de la máquina \n");
    for (int i = 0; i < 3; i++) {
        printf(" carta %d: numero: %d, palo: %c\n", i + 1, naipes[i].numero, naipes[i].palo);
    }

    Carta jugada[3];
    int puntajes[3] = {0};
    int puntajeMax = 0, ganador = -1;

    // Ahora jugamos para 3 jugadores
    for (int jugador = 0; jugador < 3; jugador++) {
        printf("\n cartas del jugador %d: \n", jugador + 1);

        for (int i = 0; i < 3; i++) {
            printf("\n carta %d disponible: numero: %d, palo: %c\n", i + 1, mazo[0].numero, mazo[0].palo);
            printf(" vas a sacar la carta? (s/n): ");
            char respuesta;
            scanf(" %c", &respuesta);

            if (respuesta == 's' || respuesta == 'S') {
                jugada[i] = mazo[0];
                mazo[0] = mazo[numCartas - 1];
                numCartas--;
            } else {
                printf("no seleccionaste la carta, agarra otra \n");
                i--;
            }
        }

        int puntaje = 0;
        for (int i = 0; i < 3; i++) {
            if (naipes[i].numero == jugada[i] == ' ') {
            printf("  carta %d disponible: numero: %d, palo: %c\n", i + 1, mazo[0].numero, mazo[0].palo);
            printf("  vas a sacar la carta? (s/n): ");
            char respuesta;
            scanf(" %c", &respuesta);

            if (respuesta == 's' || respuesta == 'S') {
                jugada[i] = mazo[0];
                mazo[0] = mazo[numCartas - 1];
                numCartas--;
            } else {
                printf("  no seleccionaste la carta, agarra otra \n");
                i--;
            }
        }

        int puntaje = 0;
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

        printf("\n  puntaje del jugador %d: %d puntos\n", jugador + 1, puntaje);

        if (jugador < 2)  // Limpiamos pantalla solo si no es el último jugador
        {
            system("cls"); // Usar "clear" para sistemas UNIX
        }
    }

    int puntajeMaquina = 0;
    printf("\n cartas de la maquina \n");
    for (int i = 0; i < 3; i++) {
        printf("carta %d: numero: %d, palo: %c\n", i + 1, naipes[i].numero, naipes[i].palo);
    }

    // Puntuar la máquina, comparando con las cartas jugadas por los jugadores
    for (int i = 0; i < 3; i++) {
        if (naipes[i].numero == naipes[i].numero || naipes[i].palo == naipes[i].palo) {
            puntajeMaquina += 10;
        }
    }

    puntajes[2] = puntajeMaquina;

    printf("\n resultados de la partida \n");
    for (int i = 0; i < 3; i++) {
        printf("jugador %d: %d puntos\n", i + 1, puntajes[i]);
        if (puntajes[i] > puntajeMax) {
            puntajeMax = puntajes[i];
            ganador = i;
        }
    }

    printf("\n el que gano la partida es  %d con %d puntos.\n", ganador + 1, puntajeMax);
}

void displaySolitarioMenu() {
    setColor(14); // Amarillo para el título
    printf("************************************\n");
    printf("*          SOLITARIO MENU          *\n");
    printf("************************************\n");
    setColor(15); // Blanco para el texto del menú
    printf("1. Jugar\n");
    printf("2. Volver al menú principal\n");
    printf("Selecciona una opción: ");
}

void solitarioGameMenu() {
    int option;
    while (1) { // Bucle para el menú de Solitario
        system("cls"); // Limpiar pantalla
        displaySolitarioMenu();
        scanf("%d", &option);
        if (option == 2) {
            break; // Volver al menú principal
        } else if (option == 1) {
            printf("Jugador, ingresa tu nombre: ");
            scanf("%s", solitarioPlayerName);
            solitario();
        } else {
            printf("Opción no válida.\n");
        }
    }
}

void displayMainMenu() {
    setColor(14); // Amarillo para el título
    printf("************************************\n");
    printf("*          JUEGOS CLASICOS         *\n");
    printf("************************************\n");
    setColor(15); // Blanco para el texto del menú
    printf("1. Tic-Tac-Toe\n");
    printf("2. Tetris\n");
    printf("3. Solitario\n");
    printf("4. Juego de Memoria\n");
    printf("5. Ahorcado\n");
    printf("6. Pong\n");
    printf("7. Juego de Adivinanzas\n");
    printf("8. Salir\n");
    printf("Selecciona un juego: ");
}

void tetris() {
    setColor(11); // Cyan
    printf("Iniciando Tetris...\n");
}

void solitario() {
    solitarioGameMenu();
}

void juegoDeMemoria() {
    setColor(13); // Magenta
    printf("Iniciando juego de Memoria...\n");
}

void ahorcado() {
    setColor(12); // Rojo
    printf("Iniciando Ahorcado...\n");
}

void pong() {
    setColor(9); // Azul
    printf("Iniciando Pong...\n");
}

void juegoDeAdivinanzas() {
    setColor(14); // Amarillo
    printf("Iniciando juego de Adivinanzas...\n");
}

int main() {
    int choice;
    while (1) {
        system("cls"); // Limpiar pantalla
        displayMainMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                ticTacToeGame();
                break;
            case 2:
                tetris();
                break;
            case 3:
                solitario();
                break;
            case 4:
                juegoDeMemoria();
                break;
            case 5:
                ahorcado();
                break;
            case 6:
                pong();
                break;
            case 7:
                juegoDeAdivinanzas();
                break;
            case 8:
                exit(0);
                break;
            default:
                printf("Opción no válida.\n");
        }
    }
    return 0;
}

