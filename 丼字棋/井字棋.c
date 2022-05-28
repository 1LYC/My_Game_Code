//KiKi和BoBo玩 “井”字棋。也就是在九宫格中，只要任意行、列，或者任意对角线上面出现三个连续相同的棋子，
//就能获胜。请根据棋盘状态，判断当前输赢。
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
int winner(char who)//判断获胜者
{
    
    if (who == 'K')
    {
        printf("KiKi wins!");
    }
    else
    {
        printf("BoBo wins!");
    }
    return 0;
}

void is_win(char board[3][3])//判断输赢
{
    int ret = 1;
    int i = 0;
    int j = 0;
    for (i = 0;i < 3;i++)
    {
        //判断三行
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 'O')
        {
            ret = winner(board[i][0]);
        }
        //判断三列
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 'O')
        {
            ret = winner(board[0][i]);
        }
    }
    //判断对角线
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != 'O')
    {
        ret = winner(board[1][1]);
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != 'O')
    {
        ret = winner(board[1][1]);
    }
    if (ret == 1)
    {
        printf("No winner!");
    }
}

int main()
{
    char board[3][3] = { 0 };
    memset(board, 'O', sizeof(board));
    int i = 0;
    int j = 0;
    for (i = 0;i < 3;i++)
    {
        for (j = 0;j < 3;j++)
        {
            scanf(" %c", &board[i][j]);
        }
    }
    is_win(board);
    return 0;
}
