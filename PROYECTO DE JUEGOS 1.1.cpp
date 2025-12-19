#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>  // Para cambiar colores en Windows

#define SIZE 3

char board[SIZE][SIZE];
char currentPlayer;
char player1Name[50], player2Name[50];
int singlePlayer = 0;

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
}

void displayTicTacToeMenu() {
    setColor(14); // Amarillo para el título
    printf("************************************\n");
    printf("*         TIC-TAC-TOE MENU         *\n");
    printf("************************************\n");
    setColor(15); // Blanco para el texto del menú
    printf("1. Un jugador vs Máquina\n");
    printf("2. Dos jugadores\n");
    printf("Selecciona un modo: ");
}

void ticTacToeGame() {
    int mode;
    system("cls"); // Limpiar pantalla
    displayTicTacToeMenu();
    scanf("%d", &mode);
    printf("Jugador 1, ingresa tu nombre: ");
    scanf("%s", player1Name);
    if (mode == 1) {
        singlePlayer = 1;
        snprintf(player2Name, sizeof(player2Name), "Máquina");
    } else {
        singlePlayer = 0;
        printf("Jugador 2, ingresa tu nombre: ");
        scanf("%s", player2Name);
    }
    ticTacToe();
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
    printf("Selecciona un juego: ");
}

void tetris() {
    setColor(11); // Cyan
    printf("Iniciando Tetris...\n");
}

void solitario() {
    setColor(10); // Verde
    printf("Iniciando Solitario...\n");
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
        default:
            printf("Opción no válida.\n");
    }
    return 0;
}

