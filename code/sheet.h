#ifndef __SHEET_H__
#define __SHEET_H__

//下子
int chess(int color1,int color2,int num);

//创建棋盘
void create_sheet(char sheet[][16]);

//打印棋盘
void check_win(int sum1, int sum2, int num, char sheet[][16]);

//判断A是否连成五子
int AWin(int sum1);

//判断B是否连成五子
int BWin(int sum2);

//数组重新置为空
void chess_again();

#endif