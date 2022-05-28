#define _CRT_SECURE_NO_WARNINGS 1
//头文件的包含
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

//符号的定义
#define ROW 3
#define COL 3

//函数的声明
void DisplayBoard(char(* const board)[COL], int row, int col);//打印棋盘的函数
void PlayerMove(char(* const board)[COL], int row, int col);//玩家下棋的函数
void ComputerMove(char(* const board)[COL], int row, int col);//电脑下棋函数
char IsWin(char(* const board)[COL], int row, int col);//判断游戏是否有输赢函数
void menu();
void game();

//游戏会出现的四种情况
//1. 玩家赢了 - *
//2. 电脑赢了 - #
//3. 平局 - Q
//4. 游戏继续 - C
