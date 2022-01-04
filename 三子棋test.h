//头文件的包含
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//符号的定义
#define ROW 3
#define COL 3

//函数的声明
 void DisplayBoard(char board[ROW][COL], int row, int col);//打印棋盘的函数
 void PlayerMove(char board[ROW][COL], int row, int col);//玩家下棋的函数
 void ComputerMove(char board[ROW][COL], int row, int col);//电脑下棋函数
 char IsWin(char board[ROW][COL], int row, int col);//判断游戏是否有输赢函数

//游戏会出现的四种情况
//1. 玩家赢了 - *
//2. 电脑赢了 - #
//3. 平局 - Q
//4. 游戏继续 - C
