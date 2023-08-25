# gec6818-backgammon
基于gec6818的五子棋游戏
#### 概述

这是一个基于Linux Framebuffer的五子棋游戏。主要功能有:

- 实现简单的开始界面
- 实现五子棋游戏的基本规则
- 实现胜负判断和计分
- 实现排行榜功能
- 排行榜输出到文件"1.txt"

#### **开发环境**

​	**vscode，ubuntu，gec6818**

#### 游戏流程

1. 初始化屏幕

   使用Linux Framebuffer接口完成屏幕的初始化,主要步骤是:

   - 打开Framebuffer设备文件:/dev/fb0
   - 通过ioctl系统调用获取屏幕信息:分辨率、色深等
   - 计算需要的内存大小,调用mmap完成内存映射
   - 获取内存首地址指针,用于后续像素访问

   相关代码在taiji.c中的lcd_init函数。

2. 图形绘制

   基于内存映射的指针,可以直接对内存进行读写操作,实现像素级的访问。

   例如draw_pixel函数可以画单个像素。draw_background可以设置整个屏幕的背景色。

   基于像素级操作,实现了各种图形的绘制,如圆形、图片等。

   例如draw_round可以画圆,draw_picture可以绘制bmp图片。

3. 接收玩家输入位置

   sheet.c中实现了简单的棋盘和棋子的逻辑。

   使用二维数组sheet记录每个位置的棋子情况。

   chess函数可以在指定位置画棋子。

4. 检查胜负

   遍历整个棋盘，当寻找到对应的棋子时开始判断。

   1.分别定义两个整数计数A和B的相连棋子个数，为了方便之后的调用，定义在主函数中。

   2.判读棋子之后的横向棋子是否相等，相等计数等于相连棋子数，不相等计数清零。

   3.当计数达到5时，判定为胜利，计数不为零则返回计数位。不为5时计数位为0

   4.如果当前棋子投降，判定为另一方胜利。

5. 计算排行榜

   记录双方获胜次数,显示在排行榜界面。

   获胜次数同时保存在外置文件“1.txt"中。

#### 功能模块

主要分为以下几个模块:

- main.c:

  - main(): 主函数,实现程序的整体流程控制

  - lcd_init(): 初始化屏幕,实现Framebuffer的设置

  - draw_pixel(): 画一个像素点

  - draw_background(): 设置全屏背景色 

  - draw_round1()/draw_round2(): 画圆形的两半

  - draw_picture(): 绘制bmp图片

  - draw_taiji(): 画太极图案

  - checkerboard(): 画棋盘格子

  - leaderboard(): 显示胜负排行榜

  slide.c:

  - open_file(): 打开触摸屏输入设备文件

  - direction(): 读取触摸事件,判断滑动方向

  sheet.c:

  - chess(): 在指定位置画棋子

  - AWin()/BWin(): 判断黑白棋是否获胜

  - chess_again(): 棋盘数据清零

  taiji.c:

  - lcd_init(): 初始化屏幕

  - draw_pixel(): 画单个像素

  - draw_background(): 填充背景

  - draw_round1/2(): 画圆形

  - draw_picture(): 画图片 

  - draw_taiji(): 画太极图案

  - checkerboard(): 画棋盘

  - leaderboard(): 显示排行榜

#### 主要函数

- **lcd_init()**

  这个函数完成了Framebuffer的初始化,主要步骤包括:

  1. 打开Framebuffer设备文件:/dev/fb0

  2. 通过ioctl系统调用,获取屏幕信息,如分辨率、色深等

  3. 计算需要的内存大小

  4. 通过mmap内存映射机制,映射Framebuffer显存

  5. 获取内存映射的首地址指针,用于后续的像素访问

  这样通过内存映射,我们就可以直接读写Framebuffer显存,实现像素级的屏幕访问。

  **draw_pixel()**

  这个函数用于画单个像素点,参数包括:

  - x: 水平坐标
  - y: 垂直坐标  
  - color: 要设定的颜色值

  根据坐标,直接设置对应显存位置的颜色值,就可以画出一个像素点。

  **chess()** 

  这个函数实现下棋逻辑,参数包括:

  - color1/color2: 棋子的两种颜色
  - num: 记录当前是第几步


函数利用循环遍历棋盘的每个位置,判断点击位置是否有效,如果有效就在该位置画一个棋子,并记录到棋盘数组中。

交替调用该函数,就可以实现黑白棋子的落子。

**AWin()/BWin()**

这两个函数用来判断黑白棋是否达成五子连线,并返回连线数。

基本思路是遍历数组,找到己方棋子后,判断四个方向是否有相连的五子。
![IMG_20230823_111709](https://github.com/shengye2413/gec6818-backgammon/assets/73319935/d62f7f4b-bea8-4b23-8f1c-8cf46bccd35e)
![IMG_20230823_111730](https://github.com/shengye2413/gec6818-backgammon/assets/73319935/db34d756-e7aa-4ce4-a0f9-c20c600b2bf9)
![IMG_20230823_111543](https://github.com/shengye2413/gec6818-backgammon/assets/73319935/bfa46716-7152-478d-999d-aa03f32ccfdd)

![IMG_20230823_111659](https://github.com/shengye2413/gec6818-backgammon/assets/73319935/e4e32864-f769-451a-a009-af02ed65f5a4)

