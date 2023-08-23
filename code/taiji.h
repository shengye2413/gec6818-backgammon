#ifndef __TAIJI_H__
#define __TAIJI_H__


// 初始化lcd屏幕
void lcd_init();

//显示单个像素点
void draw_pixel(int x,int y,int color);

//设置全屏背景颜色
void draw_background(int color);

//画左半圆,x、y为圆心
void draw_round1(int x,int y,int n,int color);

//画右半圆,x、y为圆心
void draw_round2(int x,int y,int n,int color);

//画图片
void draw_picture(int posx,int posy,const char* pic_path);

void draw_taiji();

void checkerboard();

//排行榜
void leaderboard(int victory1,int victory2);

#endif