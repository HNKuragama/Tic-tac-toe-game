#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define Log_File "Tic_Tac_toe_Log.txt"

int SelectMode();
void Two_player_mode(int* row, int* column, char** board, int size);
void Player_vs_computer(int* row, int* column, char** board,char current_player, int size);
char** initialize_board(int size);
void display_board(char** board, int size);
void getPlayerMove(int* row, int* column, char** board, int size);
bool validateMove(int row, int column, char** board, int size);
void GenerateComputerMove(int* row, int* column, char** board, int size);
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
    int selection_No;

    selection_No = SelectMode();

    while(true)                                                                             //Game mode selection
    {
        if(selection_No < 1 || selection_No > 2)
        {
            printf("Invalid selection No -> Please select number from 1 to 2\n");
            selection_No = SelectMode();

        }
        else
            break;

    }

    printf("Enter board size(3 <= size <= 10): ");
    scanf("%d", &board_size);

    while(true)                                                                             //Getting board size
    {
        if(board_size < 3 || board_size > 10)
        {
            printf("Invalid board size...!\n");
            printf("Enter size from 3 to 10...\n");
            scanf("%d", &board_size);
        }
        else
        {
            board = initialize_board(board_size);
            break;

        }


    }


    while(true)
    {
        display_board(board, board_size);

        if(selection_No == 1)
        {
            printf("Player %c 's turn", current_Player);
            Two_player_mode(&row, &column, board, board_size);

        }
        else if(selection_No == 2)
        {
            Player_vs_computer(&row, &column, board, current_Player, board_size);

        }

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

        if(selection_No == 1)
        {
            current_Player = (current_Player == 'X')? 'O' : 'X';

        }
        else if(selection_No == 2)
        {
            current_Player = (current_Player == 'X')? 'O' : 'X';
        }


    }

    for(int i = 0; i < board_size; i++)
    {
        free(board[i]);
    }
    free(board);

}

int SelectMode()
{
    int selection;

    printf("Select game mode ---->\n\n");
    printf("\t1. Two Player\n");
    printf("\t2. Player vs Computer\n");

    scanf("%d", &selection);

    return selection;

}

void Two_player_mode(int* row, int* column, char** board, int size)                         //Two player mode
{
    getPlayerMove(row, column, board, size);
}

void Player_vs_computer(int* row, int* column, char** board, char current_Player, int size) //Player vs computer mode
{
    if(current_Player == 'X')
    {
        printf("Player %c 's turn\n", current_Player);
        getPlayerMove(row, column, board, size);

    }
    else if(current_Player == 'O')
    {
        printf("Computer's turn\n");
        GenerateComputerMove(row, column, board, size);

    }
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

void GenerateComputerMove(int* row, int* column, char** board, int size)
{
    srand(time(NULL));

    do
    {
        *row = rand() % size;
        *column = rand() % size;
    }
    while(board[*row][*column] != ' ');

    printf("Computer move\n");
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
