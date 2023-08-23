#include<stdio.h>
#include<stdlib.h>
#include <linux/fb.h>
#include <linux/input.h>//事件结构体头文件
#include "taiji.h"
#include "slide.h"
#include "sheet.h"
 
int main()
{
    //读取胜利次数
    FILE* fd1=fopen("./1.txt","r");
    if(fd1==NULL)
    {
        perror("error\n");
    }
    fseek(fd1,6,SEEK_SET);
    char victory1=getc(fd1);
    fseek(fd1,7,SEEK_CUR);
    char victory2=getc(fd1);
    fclose(fd1);
    //初始化
    lcd_init();
    nothing:
    //主界面
    draw_picture(0,0,"./start.bmp");
    while (1)
    {
        if(direction()==0)
        {
            again:
            //画出棋盘和相关按钮
            draw_background(0xffffff);
            draw_picture(0,0,"./checkerboard.bmp");
            draw_picture(500,0,"./what.bmp");
            draw_picture(700,380,"./huitui.bmp");
            draw_picture(480,400,"./gameagain.bmp");
            draw_picture(720,0,"./surrender.bmp");
            checkerboard();

            //黑棋先下
            draw_round1(600,140,30,0x000000);
            draw_round2(600,140,30,0x000000);
            int num=0;//记录下子数
            int sum1=0,sum2=0;//记录连子数
            while (direction()==0)
            { 
                //返回主界面
                if(end_x<800 && end_y>380 &&end_x>700 &&end_y<480)
                {
                    chess_again();
                    goto nothing;
                }
                //重开
                else if(end_x<560 && end_y>380 &&end_x>480 &&end_y<480)
                {
                    chess_again();
                    goto again;
                }
                //投降
                else if(end_x<800 && end_y>0 &&end_x>720 &&end_y<80)
                {
                    //判断谁投降，另一个胜利
                    if(num%2==0)
                    {
                        draw_taiji();   
                        draw_picture(50,120,"./bai.bmp");
                        victory2++;
                        break; 
                    }
                    else if (num%2==1)
                    {
                        draw_taiji();
                        draw_picture(650,120,"./hei.bmp");
                        victory1++;
                        break;
                    }
                }
                //循环交替下子
                else
                {
                    if(num%2==0)
                    {
                        num=chess(0x000000,0xffffff,num);
                        sum1=AWin(sum1);
                        //连子数为5，胜利，退出循环
                        if(sum1==5)
                        {
                            draw_taiji();
                            draw_picture(650,120,"./hei.bmp");
                            victory1++;
                            break;
                        }
                    }
                    else if(num%2==1)
                    {
                        num=chess(0xffffff,0x000000,num);
                        sum2=BWin(sum2);
                        if(sum2==5)
                        {
                            draw_taiji();   
                            draw_picture(50,120,"./bai.bmp");
                            victory2++;
                            break;             
                        }
                    }
                }
            }

            //把胜利次数保存到“1.txt”文件中
            FILE *fd=fopen("1.txt","w");
            // char buf[256]={};
            // fprintf(buf,"黑棋胜利：%c,白棋胜利：%c\n",victory1,victory2);
            // fputs(buf,fd);
            fputs("black:",fd);
            fputc(victory1,fd);
            fputc('\n',fd);
            fputs("white:",fd);
            fputc(victory2,fd);
            fclose(fd);

            //清空数组，棋盘清理
            chess_again();
            click_one:
            if(direction()==0)
            {
                //返回主界面
                if(end_x<100 && end_y>380 &&end_x>0 &&end_y<480)
                {
                    draw_picture(0,0,"./start.bmp");
                }
                //退出游戏
                else if(end_x<800 && end_y>0 &&end_x>700 &&end_y<100)
                {
                    draw_background(0x000000);
                    exit(0);
                }
                //重开
                else if(end_x<100 && end_y>0 &&end_x>0 &&end_y<100)
                {
                    //返回棋盘位置
                    goto again;
                }
                //排行榜
                else if(end_x<800 && end_y>400 &&end_x>600 &&end_y<480)
                {
                    //画出排行榜界面
                    draw_background(0xffffff);
                    draw_picture(300,0,"./ban.bmp");
                    draw_picture(760,0,"./backstart.bmp");
                    //画出每个人的胜利次数
                    leaderboard(victory1,victory2);

                    click_two:
                    if(direction()==0)
                    {
                        //重开
                        if(end_x<100 && end_y>380 &&end_x>0 &&end_y<480)
                        goto again;
                        //返回主界面
                        else if(end_x<800 && end_y>0 &&end_x>700 &&end_y<60)
                        goto nothing;
                        //点击其他区域重新获取点击
                        else
                        goto click_two;
                    }
                }
                else
                {
                    //点击其他区域再次获取点击
                    goto click_one;
                }
            }
        }
    }
}
