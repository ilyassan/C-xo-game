#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int getFreeSpacesCount();
int* getFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner( char );
void hashLine();

int main()
{
    resetBoard();
    printBoard();

    srand(time(NULL));
    short int turn = rand()%2;

    while (getFreeSpacesCount() > 0)
    {
        if(turn == 0){
            playerMove();
            turn = 1;
        }
        else{
            computerMove();
            turn = 0;
        }

        hashLine();
        printBoard();

        char winner = checkWinner();
        if (winner != ' ')
        {
            printWinner(winner);
            return 0;
        }
    }

    printf("#### DRAW ####");

    return 0;
}


void resetBoard(){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void printBoard(){
    for (int i = 0; i < 3; i++)
    {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if(i == 2){
            printf("\n");
            break;
        }
        printf("\n---|---|---\n");
    }
}

int getFreeSpacesCount(){
    int count = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(board[i][j] == ' '){
                count++;
            }
        }
    }

    return count;
}

int* getFreeSpaces()
{
    int freeSpacesCount = getFreeSpacesCount();

    if (freeSpacesCount == 0) return NULL;

    int* freeSpacesArray = NULL;
    
    freeSpacesArray = (int *) malloc(freeSpacesCount * 2 * sizeof(int));
    
    int index = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(board[i][j] == ' '){
                freeSpacesArray[index++] = i;
                freeSpacesArray[index++] = j;
            }
        }
    }
    
    return freeSpacesArray;
}

void playerMove(){
    short int row;
    short int column;

    hashLine();
    printf("Its Your Turn\n");

    while (1)
    {
        printf("Enter the row number (1 - 3): ");
        if (scanf("%hd", &row) != 1)
        {
            printf("Invalid number, try again\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Enter the column number (1 - 3): ");
        if (scanf("%hd", &column) != 1)
        {
            printf("Invalid number, try again\n");
            while (getchar() != '\n');
            continue;
        }

        if ((row < 1 || row > 3) || (column < 1 || column > 3))
        {
            printf("Number out of range, try again\n");
            continue;
        }

        row--;
        column--;
        if(board[row][column] == ' '){
            board[row][column] = PLAYER;
            break;
        }
        printf("Cell is already filled !!\n");
    }
}

void computerMove(){
    short int row;
    short int column;

    hashLine();
    printf("Computer turn ");
    fflush(stdout);
    srand(time(NULL));

    int *pFreeSpaces = getFreeSpaces();
    int len = getFreeSpacesCount();

    int randomCellIndex = (rand() % (len / 2)) * 2;
    row = *(pFreeSpaces + randomCellIndex);
    column = *(pFreeSpaces + randomCellIndex + 1);
    
    board[row][column] = COMPUTER;

    free(pFreeSpaces);

    struct timespec ts;
    ts.tv_sec = 1; // seconds
    ts.tv_nsec = 0; // nanoseconds

    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        nanosleep(&ts, NULL); // Sleep for 1 second
    }    
}

char checkWinner(){
    for (int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return board[i][0];
        }
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[0][2] == board[1][1] && board[1][1] == board[2][0]))
    {
        return board[1][1];
    }

    return ' ';
}

void printWinner(char winner){
    printf("\n");
    if (winner == PLAYER)
    {
        printf("Congratulations you win !!");
    }
    else{
        printf("You lost !!");
    }
    printf("\n");
}


void hashLine()
{
    printf("\n###################\n");
}