#define _CRT_SECURE_NO_WARNINGS
//ͷ�ļ��İ���
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//���ŵĶ���
#define ROW 3
#define COL 3

//����������
void InitBoard(char board[ROW][COL], int row, int col);//��ʼ�����̵ĺ���
void DisplayBoard(char board[ROW][COL], int row, int col);//��ӡ���̵ĺ���
void PlayerMove(char board[ROW][COL], int row, int col);//�������ĺ���
void ComputerMove(char board[ROW][COL], int row, int col);//�������庯��
char IsWin(char board[ROW][COL], int row, int col);//�ж���Ϸ�Ƿ�����Ӯ����
//��Ϸ����ֵ��������
//1. ���Ӯ�� - *
//2. ����Ӯ�� - #
//3. ƽ�� - Q
//4. ��Ϸ���� - C