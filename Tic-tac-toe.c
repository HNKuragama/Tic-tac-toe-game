#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Log_File "Tic_Tac_toe_Log.txt"

char** initialize_board(int size);
void display_board(char** board, int size);
void getPlayerMove(int *row, int *column, char** board, int size);
bool validateMove(int row, int column, char** board, int size);
bool check_Win(char** board, int size, char player_Symbol);
bool check_Draw(char** board, int size);
void logGameState(char** board, int size, int movecount);

int main()
{
    int board_size;
    char** board;
    int row, column;
    int moveCount = 0;
    char current_Player ='X';
    bool win;
    bool draw;

    printf("Enter board size(3 <= size <= 10): ");
    scanf("%d", &board_size);

    if(board_size < 3 || board_size > 10)
    {
        printf("Invalid board size\n");
        return 1;
    }

    board = initialize_board(board_size);

    while(true)
    {
        display_board(board, board_size);
        printf("Player %c 's turn", current_Player);

        getPlayerMove(&row, &column, board, board_size);
        board[row][column] = current_Player;
        moveCount++;

        logGameState(board, board_size, moveCount);

        win = check_Win(board, board_size, current_Player);

        if(win)
        {
            display_board(board, board_size);
            printf("Player '%c' wins!!!\n", current_Player);
            break;
        }

        draw = check_Draw(board, board_size);

        if(draw)
        {
            display_board(board, board_size);
            printf("Game drawn...\n");
            break;

        }

        current_Player = (current_Player == 'X')? 'O' : 'X';

    }

    for(int i = 0; i < board_size; i++)
    {
        free(board[i]);
    }
    free(board);

}

char** initialize_board(int size)
{
    char** board = (char**)malloc(size * sizeof(char*));
    for(int i = 0; i < size; i++)
    {
        board[i] = (char*)malloc(size * sizeof(char));
        for(int j = 0; j < size; j++)
        {
            board[i][j] = ' ';
        }
    }

    return board;

}

void display_board(char** board, int size)
{
    printf("\n");
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            printf(" %c ", board[i][j]);
            if(j < size - 1)
                printf("|");
        }
        printf("\n");

        if(i < size -1)
        {
            for(int j = 0; j < size; j++)
            {
                printf("===");

                if(j < size -1)
                    printf("|");
            }
            printf("\n");

        }


    }

}

void getPlayerMove(int* row, int* column, char** board, int size)
{
    while(true)
    {
        printf("Enter row and column 0 to %d: ", size -1);
        scanf("%d %d", row, column);

        if(validateMove(*row, *column, board, size))
            break;
        printf("Invalid move...Try again!");
    }

}

bool validateMove(int row, int column, char** board, int size)
{
    return row >= 0 && row <= size -1 && column >= 0 && column <= size -1 && board[row][column] == ' ';

}

bool check_Win(char** board, int size, char player_Symbol)
{
    for(int i = 0; i < size; i++)
    {
        bool row_win = true;
        bool column_win = true;

        for(int j = 0; j < size; j++)
        {
            if(board[i][j] != player_Symbol)
                row_win = false;
            if(board[j][i] != player_Symbol)
                column_win = false;
        }
        if(row_win || column_win)
            return true;
    }

    bool diag1_win = true;
    bool diag2_win = true;

    for(int i = 0; i < size; i++)
    {

        if(board[i][i] != player_Symbol)
            diag1_win = false;
        if(board[i][size - i -1] != player_Symbol)
            diag2_win = false;


    }
    return diag1_win || diag2_win;

}

bool check_Draw(char** board, int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(board[i][j] == ' ')
                return false;

        }
    }
    return true;
}

void logGameState(char** board, int size, int movecount)
{
    FILE* logFile = fopen(Log_File, "a");

    if(logFile == NULL)
        return;

    fprintf(logFile,"Move %d\n", movecount);

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            fprintf(logFile," %c ", board[i][j]);
            if(j < size - 1)
                fprintf(logFile,"|");
        }
        fprintf(logFile,"\n");

        if(i < size -1)
        {
            for(int j = 0; j < size; j++)
            {
                fprintf(logFile,"===");

                if(j < size -1)
                    fprintf(logFile,"|");
            }
            fprintf(logFile,"\n");

        }
    }

    fprintf(logFile, "\n");
    fclose(logFile);
}
