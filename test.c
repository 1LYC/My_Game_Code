#include"main.h"
int main()
{
  int input = 0;
  do{
    srand((unsigned int)time(NULL));
    menu();
    scanf("%d",&input);
    switch(input)
    {
    case 1:
      game();
      break;
    case 0:
      printf("退出游戏\n");
      break;
    default:
      printf("输入错误请重新输入！\n");
      break;
    }  
  }while(input);
  return 0;
}
