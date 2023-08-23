#include<stdio.h>
#include<stdlib.h>
#include"taiji.h"
#include"sheet.h"
#include"slide.h"

//数组棋盘
int sheet[16][16]={0};


//下子
int chess(int color1,int color2,int num)
{
    for(int i=10;i<480;i=i+30)
    {
        for(int j=10;j<480;j=j+30)
        {
            if(abs(end_x-i)<15&& abs(end_y-j)<15)
            {
                int x=i/30;
                int y=j/30;
                if(sheet[x][y]==0)
                {
                    draw_round1(i,j,10,color1);
                    draw_round2(i,j,10,color1);
                    draw_round1(600,140,30,color2);
                    draw_round2(600,140,30,color2);
                    if(color1==0x000000)
                    {
                        sheet[x][y]=1;
                        num++;
                    }
                    else if(color1==0xffffff)
                    {
                        sheet[x][y]=2;
                        num++;
                    }
                }
            }
        }
    }
    return num;
}



//判断A是否连成五子
int AWin(int sum1)
{
    //遍历判断五子
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            //当发现子时寻找周围连成线的四子判断是否相等
            if(sheet[i][j]==1)
            {
                //横
                for(int k=1;k<5;k++)
                {
                    if(sheet[i][j]!=sheet[i][j+k])
                    {
                        sum1=0;
                        break;
                    }
                    else
                    sum1=k+1;
                    if(sum1==5)
                    return sum1;
                }
                //竖
                for(int k=1;k<5;k++)
                {
                    if(sheet[i][j]!=sheet[i+k][j])
                    {
                        sum1=0;
                        break;
                    }
                    else
                    sum1=k+1;
                    if(sum1==5)
                    return sum1;
                }
                //左斜
                for(int k=1;k<5;k++)
                {
                    if(sheet[i][j]!=sheet[i-k][j+k])
                    {
                        sum1=0;
                        break;
                    }
                    else
                    sum1=k+1;
                    if(sum1==5)
                    return sum1;
                }
                //右斜
                for(int k=1;k<5;k++)
                {
                    if(sheet[i][j]!=sheet[i+k][j+k])
                    {
                        sum1=0;
                        break;
                    }
                    else
                    sum1=k+1;
                    if(sum1==5)
                    return sum1;
                }
            }
        }
    }   
    return sum1;
}

//判断B是否连成五子
int BWin(int sum2)
{
    //遍历判断五子
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            //当发现子时寻找周围连成线的四子判断是否相等
            if(sheet[i][j]==2)
            {
                //横
                for(int k=1;k<5;k++)
                {
                    if(sheet[i][j]!=sheet[i][j+k])
                    {
                        sum2=0;
                        break;
                    }
                    else
                    sum2=k+1;
                    if(sum2==5)
                    return sum2;
                }
                //竖
                for(int k=1;k<5;k++)
                {
                    if(sheet[i][j]!=sheet[i+k][j])
                    {
                        sum2=0;
                        break;
                    }
                    else
                    sum2=k+1;
                    if(sum2==5)
                    return sum2;
                }
                //左斜
                for(int k=1;k<5;k++)
                {
                    if(sheet[i][j]!=sheet[i-k][j+k])
                    {
                        sum2=0;
                        break;
                    }
                    else
                    sum2=k+1;
                    if(sum2==5)
                    return sum2;
                }
                //右斜
                for(int k=1;k<5;k++)
                {
                    if(sheet[i][j]!=sheet[i+k][j+k])
                    {
                        sum2=0;
                        break;
                    }
                    else
                    sum2=k+1;
                    if(sum2==5)
                    return sum2;
                }
            }
        }
    }   
    return sum2;
}

//数组重新置为空
void chess_again()
{
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
            sheet[i][j]=0;
    }
    
}

