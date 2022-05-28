#pragma once
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>

#define ROW 10
#define COL 10

#define player1 1
#define player2 2

enum result_
{
  CONTINUE,
  PLAYER1_WIN,
  PLAYER2_WIN,
  DRAW,
};

//定义8个反向
enum dir
{
  LEFT,
  RIGHT,
  UP,
  DOWN,
  LEFT_UP,
  RIGHT_DOWN,
  RIGHT_UP,
  LEFT_DOWN,
};

void menu();
void game();

void progress_bar();
int IsOver(int board[][COL],int row,int col);
void show(int board[][COL],int row,int col);
void playmove(int board[][COL],int row,int col,int who);
int chessboard(int board[][COL],enum dir d);
