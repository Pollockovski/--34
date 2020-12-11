#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> 
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib") 
#include <string.h>
#include <cstdlib>
#include <time.h>
#define randint(x,y) (rand()%(x)+y)

using namespace std;
void gotoxy(int, int);

using namespace std;

void gotoxy(int x, int y)//自定义跳转函数
{
	CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;
	HANDLE    hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void spawnworld()//生成游戏界面
{
	printf("############################################################"); //打印顶端
	gotoxy(0, 29);
	printf("############################################################"); //打印底端
	gotoxy(70, 0);
	printf("装弹进度:");
	gotoxy(70, 5);
	printf("分数:");
	gotoxy(70,10);
	printf("生命值:");
	gotoxy(70, 15);
	printf("生命数:");
	gotoxy(70, 20);
	printf("载弹量(85mmBR-365):");
	gotoxy(70, 25);
	printf("子弹携带量(7.62x39mm):");
	int printx=1, printy=1;
	for (int printy=0; printy <=29; ++printy )
	{
		gotoxy(0, printy);
		printf("#");
	}
	for (int printy = 0; printy <= 29; ++printy)
	{
		gotoxy(60, printy);
		printf("#");
	}
}

void unshow()//隐藏控制台光标
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);
}

void gameover()
{
	system("cls");
	printf("************          ***                **          **          ************   \n");
	printf("*                    ** **              ****        ****         **             \n");
	printf("*                   **   **            **  **      **  **        **             \n");
	printf("*                  **     **          **    **    **    **       ************   \n");
	printf("*      *****      ***********        **      **  **      **      **             \n");
	printf("*          *     **         **      **        ****        **     **             \n");
	printf("************    **           **    **          **          **    ************   \n\n\n\n");
	printf("************    **           **    ************        **********\n");
	printf("**        **     **         **     **                 **       **\n");
	printf("**        **      **       **      **                 **       **\n");
	printf("**        **       **     **       ************       ***********\n");
	printf("**        **        **   **        **                  ***     **\n");
	printf("**        **         ** **         **                ***       **\n");
	printf("************          ***          ************    ***         **\n\n\n\n");
}

void cls()//清屏
{
	for (int printy = 1; printy <= 28; ++printy)
	{
		gotoxy(1, printy);
		printf("                                                           ");
	}
}

int main()//主程序
{
	int press = 0;
	int scores = 0;//分数
	int blood = 200;//血量
	int lives = 5;//生命值
	int hurt = 100;//伤害
	float gun_hurt = 0.1;
	int shell_load = 56; //在弹药架上装填弹药
	int bullet_load = 2394;//装载子弹
	int shelltoleft = 0;//左正蹬
	int shelltorigght = 0;//右勾拳
	int shelldown = 0;//下鞭
	int shellup = 0;//上鞭
	int shootleft = 0;//左开枪
	int shootright = 0;//右开枪
	int shootup = 0;//上开枪
	int shootdown = 0;//下开枪
	int lockedblood = 0;//关闭锁血
	int unlimitedammo = 0;//关闭无限弹药
	unshow();
	int exitg = 0;
	spawnworld();
	int shell_recharging_time = 0;//所以说开局还要装弹
	srand(unsigned(time(0)));
	int t34x = rand() % 59 + 1;
	int t34y = rand() % 28 + 1;
	int fpanzerblood = 100;//假坦克血量
	srand(unsigned(time(0)+1.5));
	int fpanzerx = rand() % 59 + 1;
	int fpanzery = rand() % 28 + 1;
	while (exitg != 1)
	{
		//假坦克
		if (fpanzerblood <= 0)//生成假坦克
		{
			srand(unsigned(time(0)));
			fpanzerx = rand() % 59 + 1;
			fpanzery = rand() % 28 + 1;
			fpanzerblood = 100;
		}
		//打假
		if (shellup == 1 and t34x == fpanzerx and t34y >= fpanzery)
		{
			fpanzerblood -= hurt;
			scores += 50;
		}
		if (shelldown == 1 and t34x == fpanzerx and t34y <= fpanzery)
		{
			fpanzerblood -= hurt;
			scores += 50;
		}
		if (shelltoleft == 1 and t34y == fpanzery and t34x >= fpanzerx)
		{
			fpanzerblood -= hurt;
			scores += 50;
		}
		if (shelltorigght == 1 and t34y == fpanzery and t34x <= fpanzerx)
		{
			fpanzerblood -= hurt;
			scores += 50;
		}
		//打假
		//假坦克
		//无限弹药
		int ammoshell = shell_load;
		int ammogun = bullet_load;
		if (unlimitedammo == 1)
		{
			shell_load = ammoshell;
			bullet_load = ammogun;
		}
		//无限弹药
		//锁血
		int bloodbackup = blood;
		if (lockedblood == 1)
		{
			blood = bloodbackup;
			bloodbackup = blood;
		}
		//锁血
		char cheat[] = "a";//你渴望力量吗？作弊码助你一臂之力
		if (blood <= 0)
		{
			blood = 200;
			lives -= 1;
		}
		if (shell_recharging_time <= 99)//差不多五秒一发，神仙车组
		{
			shell_recharging_time += 1;
		}
		cls();
		gotoxy(81, 0);
		printf("         ");
		gotoxy(77, 5);
		printf("         ");
		gotoxy(79, 10);
		printf("         ");
		gotoxy(79, 15);
		printf("         ");
		gotoxy(91, 20);
		printf("         ");
		gotoxy(94, 25);
		printf("         ");
		//显示模块
		gotoxy(81, 0);
		cout << shell_recharging_time << "%" << endl;
		gotoxy(77, 5);
		cout << scores;
		gotoxy(79, 10);
		cout << blood;
		gotoxy(79, 15);
		cout << lives;
		gotoxy(91, 20);
		cout << shell_load;
		gotoxy(94, 25);
		cout << bullet_load;
		gotoxy(t34x, t34y);
		printf("O");
		gotoxy(fpanzerx, fpanzery);
		printf("H");
		//显示模块
		Sleep(50);//限制游戏速度

		shelltoleft = 0;//左正蹬
		shelltorigght = 0;//右勾拳
		shelldown = 0;//下鞭
		shellup = 0;//上鞭

		//按键控制
		if (_kbhit())
		{
			int press = _getch();
			if (press == 27)
			{
				exitg = 1;
			}
			if (press == 87 or press == 119 and t34y != 1)//上
			{
				t34y = t34y - 1;
			}
			if (press == 65 or press == 97 and t34x != 1)//左
			{
				t34x = t34x - 1;
			}
			if (press == 83 or press == 115 and t34y != 28)//下
			{
				t34y = t34y + 1;
			}
			if (press == 68 or press == 100 and t34x != 59)//右
			{
				t34x = t34x + 1;
			}
			if (press == 67 or press == 99)
			{
				gotoxy(1, 1);
				cout << "请输入作弊码:";
				cin >> cheat;
			}
			if (press == 72 and shell_recharging_time == 100 and shell_load > 0)//上开火
			{
				shell_load -= 1;
				shell_recharging_time = 0;
				shellup = 1;
			}
			if (press == 80 and shell_recharging_time == 100 and shell_load > 0)//下开火
			{
				shell_load -= 1;
				shell_recharging_time = 0;
				shelldown = 1;
			}
			if (press == 75 and shell_recharging_time == 100 and shell_load > 0)//左开火
			{
				shell_load -= 1;
				shell_recharging_time = 0;
				shelltoleft = 1;
			}
			if (press == 77 and shell_recharging_time == 100 and shell_load > 0)//右开火
			{
				shell_load -= 1;
				shell_recharging_time = 0;
				shelltorigght = 1;
			}
			if (press == 72 and bullet_load > 0)//上开火i
			{
				bullet_load -= 1;
				shootup = 1;
			}
			if (press == 80 and bullet_load > 0)//下开火k
			{
				bullet_load -= 1;
				shootdown = 1;
			}
			if (press == 75 and bullet_load > 0)//左开火j
			{
				bullet_load -= 1;
				shootleft = 1;
			}
			if (press == 77 and bullet_load > 0)//右开火l
			{
				bullet_load -= 1;
				shootright = 1;
			}
		}
		//按键控制
		//作弊码识别
		const char* cht = cheat;
		if (strcmp(cht,"pobeda")==0)
		{
		scores = 1000000;
		}
		if (strcmp(cht, "aspirin") == 0)
		{
			blood += 100;
		}
		if (strcmp(cht, "nepreoborimeiy") == 0)
		{
			lockedblood = 1;
		}
		if (strcmp(cht, "nepobedimoy") == 0)
		{
			blood = 100000000;
		}
		if (strcmp(cht, "ura") == 0)
		{
			hurt += 10000;
			gun_hurt += 10000;
		}
		if (strcmp(cht, "zaxixayu moskvu") == 0)
		{
			lives += 900;
		}
		if (strcmp(cht, "bitva pod kurskom") == 0)
		{
			lives = 5128;
		}
		if (strcmp(cht, "rokkosovski") == 0)
		{
			blood = 2 * blood;
		}
		if (strcmp(cht, "zavod") == 0)
		{
			unlimitedammo = 1;
			shell_load = 56;
			bullet_load = 2394;
		}
		if (strcmp(cht, "hcn") == 0)
		{
			blood -= 100;
		}
		if (strcmp(cht, "kill") == 0)
		{
			blood = 0;
		}
		if (strcmp(cht, "gameover") == 0)
		{
			goto gameover;
		}
		/*
		if (strcmp(cht, "") == 0)
		{

		}
		*/
		//作弊码识别
		if (lives < 0)
		{
			Sleep(100);
			goto gameover;
		}
	}
gameover:
	gameover();
}