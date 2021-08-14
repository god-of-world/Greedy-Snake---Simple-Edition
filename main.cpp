#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include<cstdio>
//宏定义
#define SNAKE_NUM 500

//方向
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
//做界面1.创建一个窗口，图形窗口

//物品
struct Food
{
	int x;
	int y;
	int r;
	bool flag;
	DWORD color;
}food;

//蛇的结构
struct Snake
{
	int size;	//蛇的长度
	int dir;	//蛇的方向
	int speed;	//蛇的移速
	POINT coor[SNAKE_NUM];	//坐标
}snake;

//数据初始化
void GameInit() 
{
	//init 初始化 graph 图形窗口
	initgraph(640, 480, SHOWCONSOLE);
	//GetTickCount()开机到现在所经过的毫秒数
	srand(GetTickCount());
	//蛇的初始化
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	for (int i = 0; i < snake.size; i++)
	{
		snake.coor[i].x = 40 - 10 * i;
		snake.coor[i].y = 10;
		//printf("?%d %d", snake.coor[i].x, snake.coor[i].y);
	}
	food.x = rand() % 635 + 5;
	food.y = rand() % 475 + 5;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}

void GameDraw()
{
	//缓冲
	BeginBatchDraw();
	//设置背景颜色
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	//绘制蛇
	setfillcolor(RED);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//物品
	if (food.flag)
	{
		solidcircle(food.x,food.y,food.r);
	}
	EndBatchDraw();
}

//移动
void SnakeMove()
{
	for (int i = snake.size - 1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir)
	{
		case UP:
			snake.coor[0].y -= snake.speed;
			if (snake.coor[0].y + 10 <= 0)
			{
				MessageBox(NULL, (LPCTSTR)TEXT("Exited"), (LPCTSTR)TEXT("Gameover"), MB_OK);
				exit(0);
			}
			break;
		case DOWN:
			snake.coor[0].y += snake.speed;
			if (snake.coor[0].y + 10 >= 480)
			{
				MessageBox(NULL, (LPCTSTR)TEXT("Exited"), (LPCTSTR)TEXT("Gameover"), MB_OK);
				exit(0);
			}
			break;
		case RIGHT:
			snake.coor[0].x += snake.speed;
			if (snake.coor[0].x - 10 >= 640)
			{
				MessageBox(NULL, (LPCTSTR)TEXT("Exited"), (LPCTSTR)TEXT("Gameover"), MB_OK);
				exit(0);
			}
			break;
		case LEFT:
			snake.coor[0].x -= snake.speed;
			if (snake.coor[0].x <= 0)
			{
				MessageBox(NULL, (LPCTSTR)TEXT("Exited"), (LPCTSTR)TEXT("Gameover"), MB_OK);
				exit(0);
			}
			break;
	}
}

//操作
void KeyContorl() 
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			break;
		}
	}
}

void Eat()
{
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r &&
		snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
}

int main() 
{
	GameInit();
	//GameDraw();
	
	

	while (1)
	{
		GameDraw();
		SnakeMove();
		KeyContorl();
		Eat();
		Sleep(50);
		if (_kbhit())
		{
			if (_getch() == 27)
			{
				exit(0);
			}
		}
	}
	return 0;
}
