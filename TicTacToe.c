
#include <stdio.h>
#include <stdlib.h>

// Terminal colors
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define MAGENTA "\033[1;35m"

// Initialize the board
void initializeBoard(char board[3][3])
{
    int i, j;

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// Display welcome screen
void welcomeScreen()
{
    int ch;

    system("clear");

    printf(CYAN);
    printf("\n");
    printf("====================================\n");
    printf("                                    \n");
    printf("           TIC TAC TOE              \n");
    printf("        THE CLASSIC X-O GAME        \n");
    printf("                                    \n");
    printf("====================================\n");
    printf(RESET);

    printf("\nPress ENTER to start the game...");

    // Wait until the user presses Enter
    while((ch = getchar()) != '\n' && ch != EOF);
}

// Display game board
void displayBoard(char board[3][3])
{
    int i, j;

    printf(CYAN "\n          GAME BOARD\n" RESET);

    for(i = 0; i < 3; i++)
    {
        printf("        ");

        for(j = 0; j < 3; j++)
        {
            if(board[i][j] == 'X')
                printf(RED "  X  " RESET);
            else if(board[i][j] == 'O')
                printf(YELLOW "  O  " RESET);
            else
                printf("  %d  ", i * 3 + j + 1);

            if(j < 2)
                printf("|");
        }

        printf("\n");

        if(i < 2)
            printf("       -----+-----+-----\n");
    }

    printf("\n");
}

// Get player input and validate position
void playerMove(char board[3][3], char symbol)
{
    int position;
    int row, col;
    int ch;

    while(1)
    {
        printf("Enter your position (1-9): ");

        if(scanf("%d", &position) != 1)
        {
            printf(RED "Invalid input! Enter a number.\n" RESET);

            while((ch = getchar()) != '\n' && ch != EOF);

            continue;
        }

        if(position < 1 || position > 9)
        {
            printf(RED "Invalid position! Try again.\n" RESET);
            continue;
        }

        row = (position - 1) / 3;
        col = (position - 1) % 3;

        if(board[row][col] != ' ')
        {
            printf(RED "Position already occupied! Try again.\n" RESET);
            continue;
        }

        board[row][col] = symbol;
        break;
    }
}

// Check winner
int checkWinner(char board[3][3])
{
    int i;

    // Check rows
    for(i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] &&
           board[i][1] == board[i][2] &&
           board[i][0] != ' ')
        {
            return 1;
        }
    }

    // Check columns
    for(i = 0; i < 3; i++)
    {
        if(board[0][i] == board[1][i] &&
           board[1][i] == board[2][i] &&
           board[0][i] != ' ')
        {
            return 1;
        }
    }

    // Check first diagonal
    if(board[0][0] == board[1][1] &&
       board[1][1] == board[2][2] &&
       board[0][0] != ' ')
    {
        return 1;
    }

    // Check second diagonal
    if(board[0][2] == board[1][1] &&
       board[1][1] == board[2][0] &&
       board[0][2] != ' ')
    {
        return 1;
    }

    return 0;
}

// Check draw condition
int checkDraw(char board[3][3])
{
    int i, j;

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(board[i][j] == ' ')
            {
                return 0;
            }
        }
    }

    return 1;
}

// Display scoreboard
void displayScore(int xWins, int oWins, int draws)
{
    printf(MAGENTA);
    printf("\n====================================\n");
    printf("             SCOREBOARD             \n");
    printf("====================================\n");
    printf(RESET);

    printf(GREEN "Player X Wins : %d\n" RESET, xWins);
    printf(YELLOW "Player O Wins : %d\n" RESET, oWins);
    printf(CYAN "Total Draws   : %d\n" RESET, draws);

    printf("====================================\n");
}

// Main function
int main()
{
    char board[3][3];
    char symbol, choice;

    int xWins = 0;
    int oWins = 0;
    int draws = 0;

    // Display welcome screen
    welcomeScreen();

    do
    {
        initializeBoard(board);

        symbol = 'X';

        while(1)
        {
            system("clear");

            displayBoard(board);

            if(symbol == 'X')
                printf(RED "Player 1 (X) turn\n" RESET);
            else
                printf(YELLOW "Player 2 (O) turn\n" RESET);

            playerMove(board, symbol);

            // Check winner
            if(checkWinner(board))
            {
                system("clear");

                displayBoard(board);

                printf(GREEN "\n====================================\n" RESET);

                if(symbol == 'X')
                {
                    printf(GREEN "       PLAYER 1 (X) WINS!\n" RESET);
                    xWins++;
                }
                else
                {
                    printf(GREEN "       PLAYER 2 (O) WINS!\n" RESET);
                    oWins++;
                }

                printf(GREEN "====================================\n" RESET);

                break;
            }

            // Check draw
            if(checkDraw(board))
            {
                system("clear");

                displayBoard(board);

                printf(CYAN "\n          GAME DRAW!\n" RESET);

                draws++;

                break;
            }

            // Switch player
            if(symbol == 'X')
                symbol = 'O';
            else
                symbol = 'X';
        }

        // Display scoreboard
        displayScore(xWins, oWins, draws);

        printf("\nPlay again? (Y/N): ");

        if(scanf(" %c", &choice) != 1)
            break;

    } while(choice == 'Y' || choice == 'y');

    // Exit screen
    system("clear");

    printf(GREEN);
    printf("\n====================================\n");
    printf("       THANK YOU FOR PLAYING!       \n");
    printf("====================================\n");
    printf(RESET);

    return 0;
}
