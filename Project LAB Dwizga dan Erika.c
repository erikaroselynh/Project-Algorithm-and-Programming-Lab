#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, j;


void displayBoard(char board[3][3]) {
    printf("\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("-----------\n");
    }
    printf("\n");
}


int checkWinner(char board[3][3], char player) {
    
    for (i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1; 
        }
    }

    
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1; 
	}	
    return 0; 
}


void computerMove(char board[3][3], char computer) {

    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');

    board[row][col] = computer;
}

void updateWinnerList(char winnerList[10][20], char winner[20], int *numWinners) {
    strcpy(winnerList[*numWinners], winner);
    (*numWinners)++;

  
    for (i = 0; i < *numWinners - 1; i++) {
        for (j = i + 1; j < *numWinners; j++) {
            if (strcmp(winnerList[i], winnerList[j]) > 0) {
                char temp[20];
                strcpy(temp, winnerList[i]);
                strcpy(winnerList[i], winnerList[j]);
                strcpy(winnerList[j], temp);
            }
        }
    }
}

int main() {
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char player, computer;
    char winnerList[10][20];
    int numWinners = 0;

    do {
        
        printf("Pilih simbol Anda (X atau O): ");
        scanf(" %c", &player);
        computer = (player == 'X') ? 'O' : 'X';

        printf("Anda: %c\nKomputer: %c\n", player, computer);

        int totalMoves = 0;
        int isPlayerTurn = 1; 

        while (1) {
            displayBoard(board);

            if (isPlayerTurn) {
                
                int row, col;
                printf("Masukkan baris dan kolom (misal: 2 3): ");
                scanf("%d %d", &row, &col);

                
                if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row - 1][col - 1] == ' ') {
                    board[row - 1][col - 1] = player;
                    totalMoves++;
                    isPlayerTurn = 0; 
                } else {
                    printf("Langkah tidak valid. Silakan coba lagi.\n");
                }
            } else {
                
                computerMove(board, computer);
                totalMoves++;
                isPlayerTurn = 1; 
            }

            
            if (checkWinner(board, player)) {
                displayBoard(board);
                printf("Selamat! Anda menang!\n");
                updateWinnerList(winnerList, "Player", &numWinners);
                break;
            } else if (checkWinner(board, computer)) {
                displayBoard(board);
                printf("Komputer menang. Coba lagi!\n");
                updateWinnerList(winnerList, "Computer", &numWinners);
                break;
            }

            
            if (totalMoves == 9) {
                displayBoard(board);
                printf("Permainan seri. Coba lagi!\n");
                updateWinnerList(winnerList, "Draw", &numWinners);
                break;
            }
        }

        printf("\nList Pemenang:\n");
        for (i = 0; i < numWinners; i++) {
            printf("%d. %s\n", i + 1, winnerList[i]);
        }

        printf("\nIngin bermain lagi? (y/n): ");
        char playAgain;
        scanf(" %c", &playAgain);

        if (playAgain != 'y' && playAgain != 'Y') {
            break;
        }

       
        memset(board, ' ', sizeof(board));

    } while (1);

	return 0;
}
