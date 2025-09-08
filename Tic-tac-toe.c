#include <stdio.h>
#include <stdlib.h>

char** initialize_board(int size);
void display_board(char** board, int size);

int main()
{
    int board_size;
    char** board;

    printf("Enter board size(3 <= size <= 10): ");
    scanf("%d", &board_size);

    if(board_size < 3 || board_size > 10)
    {
        printf("Invalid board size\n");
        return 1;
    }

    board = initialize_board(board_size);
    display_board(board, board_size);


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
    for(int i = 0; i < size; i++)
    {
        printf("%d", i);
        printf("|\t");
    }
}
