#include"main.h"
void menu()
{
   printf("**************************\n");
   printf("*****1.play***0.exit******\n");
   printf("**************************\n");
}

void progress_bar()
{
   int i = 0;
    char bar[102];
    memset(bar, 0 ,sizeof(bar));
    const char *lable="|/-\\";
    printf("游戏正在加载中，请稍后...\n");
    while(i <= 100 ){
        printf("[%-100s][%d%%][%c]\r", bar, i, lable[i%4]);
        fflush(stdout);
        bar[i++] = '#';
        usleep(30000);
    }
    printf("\n");
}

void game()
{
  int board[ROW][COL];
  memset(board,0,sizeof(board));
  int result = CONTINUE;
  //这里需要再加上一个正在加载中的代码
  progress_bar();
  int ret = rand() % 2+1;
  do{
    //游戏中
    //这里我用时间戳随机设置谁先开始
    playmove(board,ROW,COL,ret);
    result = IsOver(board,ROW,COL);
    if(result != CONTINUE ){
        break;
    }
    if(ret != player1){
      playmove(board,ROW,COL,player1);
      result = IsOver(board,ROW,COL);
      if(result != CONTINUE){
        break;
      }
    }
    else{
      playmove(board,ROW,COL,player2);
      result = IsOver(board,ROW,COL);
      if(result != CONTINUE ){
        break;
      }
    }
  }while(1);
  //游戏结束
      show(board,ROW,COL);
  switch(result)
  {
    case PLAYER1_WIN:
      printf("恭喜玩家1获胜\n");
      break;
    case PLAYER2_WIN:
      printf("恭喜玩家2获胜\n");
      break;
    case DRAW:
      printf("平局\n");
      break;
    default:
      //do nothing
      break;
  }
}

int x,y;//全局每个函数都能访问

void playmove(int board[][COL],int row,int col,int who)
{
  show(board,ROW,COL);
  while(1){  
    printf("请玩家%d下棋\n",who);
    scanf("%d%d",&x,&y);
    //判断坐标合法性
    if(x<0||x>col-1||y<0||y>row-1)
    {
      printf("坐标不合法\n");
      continue;
    }
    //判断坐标是否被占用
    else if(board[x][y]!=0)
    {
      printf("坐标已被占用\n");
      continue;
    }
    else{
    board[x][y]=who;
    break;
    }
  }
}

int chessboard(int board[][COL],enum dir d)
{
  int x_ = x;
  int y_ = y;
  int count = 0;
  while(1)
  {  
    switch(d)
    {
      case LEFT:
        y_--;
        break;
      case RIGHT:
        y_++;
        break;
      case UP:
        x_--;
        break;
      case DOWN:
        x_++;
        break;
      case LEFT_UP:
        y_--;x_--;
        break;
      case RIGHT_DOWN:
        y_++;x_++;
        break;
      case RIGHT_UP:
        y_++;x_--;
        break;
      case LEFT_DOWN:
        y_--;x_++;
        break;
    }
    if(x_<0||x_>COL-1||y<0||y_>ROW-1){
      break;
    }
    if(board[x][y] == board[x_][y_]){
      count++;
    }
    else{
      break;
    }
  }
  return count;
}

int IsOver(int board[][COL],int row,int col)
{
  int count1 = chessboard(board,LEFT)+chessboard(board,RIGHT)+1;
  int count2 = chessboard(board,UP)+chessboard(board,DOWN)+1;
  int count3 = chessboard(board,LEFT_UP)+chessboard(board,RIGHT_DOWN)+1;
  int count4 = chessboard(board,RIGHT_UP)+chessboard(board,LEFT_UP)+1;
  if(count1>4||count2>4||count3>4||count4>4){
    if(board[x][y] == player1){
      return PLAYER2_WIN;
    }
    else{
      return PLAYER2_WIN;
    }
  }
  //判断是否平局
  int i = 0;
  for(i = 0;i < row;i++)
  {
    int j = 0;
    for(j = 0;j < col;j++){
      if(board[i][j]==0){
        return CONTINUE;
      }
    }
  }
  return DOWN;
}

void show(int board[][COL],int row,int col)
{
  printf("\e[1;1H\e[2J");  
  printf(" ");
  int i = 0;
  for(i = 0;i < col;i++){
    printf(" %d ",i);
  }
  printf("\n");
  for(i = 0;i<row;i++)
  {
    printf("%d",i);
    int j = 0;
    for(j = 0;j<col;j++)
    {
      if(board[i][j] == player1){
        printf(" # ");
      }
      else if(board[i][j] == player2){
        printf(" * ");
      }
      else{  
        printf(" . ");
      }
    }
    printf("\n");
  }
}
