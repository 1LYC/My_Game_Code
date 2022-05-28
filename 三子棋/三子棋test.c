#include "game.h"
void menu()
{
	printf("******************************\n");
	printf("******    1. play        *****\n");
	printf("******    0. exit        *****\n");
	printf("******************************\n");
}

void game()
{
	char board[ROW][COL];//存储数据 - 二维数组

	memset(board, ' ', sizeof(board));//初始化棋盘 - 初始化空格
	DisplayBoard(board, ROW, COL);//打印一下棋盘 - 本质是打印数组的内容

	char ret = 0;//接受游戏状态
	while (1)
	{
		//玩家下棋
		PlayerMove(board, ROW, COL);//玩家下棋
		DisplayBoard(board, ROW, COL);//记录棋盘
		ret = IsWin(board, ROW, COL);//判断玩家是否赢得游戏
		if (ret != 'C') {
			break;
		}
		//电脑下棋
		ComputerMove(board, ROW, COL);//电脑下棋
		DisplayBoard(board, ROW, COL);//记录棋盘
		ret = IsWin(board, ROW, COL);//判断电脑是否赢得游戏
		if (ret != 'C') {
			break;
		}
	}
	if (ret == '*')
	{
		printf("玩家赢了\n");
	}
	else if (ret == '#')
	{
		printf("电脑赢了\n");
	}
	else
	{
		printf("平局\n");
	}
	DisplayBoard(board, ROW, COL);
}

void DisplayBoard(char (* const board)[COL], int row, int col)//打印棋盘的函数
{
	assert(board);
	int i = 0;
	for (i = 0; i < row; i++)
	{
		int j = 0;
		for (j = 0; j < col; j++)  
		{
			printf(" %c ",*(*(board + i) + j));
			if (j < col - 1)
				printf("|");
		}
		printf("\n");
		if (i < row - 1)//相当于一行中有两个列需要完成的打印，
		{
			int j = 0;
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
					printf("|");
			}
			printf("\n");
		}
	}
}

void PlayerMove(char(* const board)[COL], int row, int col)//玩家下棋的函数
{
	assert(board);
	int x = 0;
	int y = 0;
	printf("玩家走:>\n");
	while (1)
	{
		printf("请输入下棋的坐标:>");
		scanf("%d %d", &x, &y);
		//玩家输入的1  1其实在游戏中是0  0
		if (x >= 1 && x <= row && y >= 1 && y <= col)//判断坐标合法性
		{
			if (board[x - 1][y - 1] == ' ')//判断坐标是否被占用
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
			{
				printf("坐标被占用, 请重新输入\n");
			}
		}
		else
		{
			printf("坐标非法, 请重新输入\n");
		}
	}
}

void ComputerMove(char(* const board)[COL], int row, int col)//电脑下棋
{
	assert(board);
	printf("电脑走:>\n");
	while (1)
	{
		int x = rand() % row;//当row为3时，范围在0到2，这样不用判断坐标是否合法
		int y = rand() % col;//当row为3时，范围在0到2，这样不用判断坐标是否合法
		//这里是电脑下的所以不用判断坐标的合法性，因为一定合法
		if (board[x][y] == ' ')//判断坐标是否被占用
		{
			board[x][y] = '#';
			break;
		}
	}
}

int IsFull(char(* const board)[COL], int row, int col)//判断棋盘是否满了
{
	assert(board);
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;//棋盘没满
			}
		}
	}
	return 1;//棋盘满了
}

char IsWin(char(* const board)[COL], int row, int col)//判断游戏是否有输赢函数
{
	assert(board);
	int i = 0;
	//判断三行
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] \
			&& board[i][1] == board[i][2]\
			&& board[i][1] != ' ')
		{
			return  board[i][0];//能返回#或*（随便在一行中观察）
		}
	}

	//判断三列
	for (i = 0; i < col; i++)
	{
		if (board[0][i] == board[1][i]\
			&& board[1][i] == board[2][i] \
			&& board[1][i] != ' ')
		{
			return board[0][i];//能返回#或*（随便在一列中观察）
		}
	}

	//判断对角线
	if (board[0][0] == board[1][1] \
		&& board[1][1] == board[2][2]\
		&& board[1][1] != ' ')
	{
		return board[1][1];
	}
	if (board[0][2] == board[1][1] \
		&& board[1][1] == board[2][0]\
		&& board[1][1] != ' ')
	{
		return board[1][1];
	}

	//判断平局
	//如果棋盘满了返回1， 不满返回0
	int ret = IsFull(board, row, col);
	if (ret == 1)
	{
		return 'Q';//平局
	}
	return 'C';//继续
}
