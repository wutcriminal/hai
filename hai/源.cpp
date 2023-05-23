#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <string>

using namespace std;
const int WORLDSIZE = 102;
const int POINTSIZE = 5;
const int INTERVAL = 5;

// 定义全局变量
__int8 world[WORLDSIZE][WORLDSIZE] = { 0 };	// 定义二维世界
IMAGE imgLive, imgEmpty;		// 定义活细胞和无细胞区域的图案



// 函数声明
void Init();					// 初始化
void SquareWorld();				// 创建一个细胞以方形分布的世界
void RandWorld();				// 创建一个细胞随机分布的世界
void PaintWorld();				// 绘制世界
void Evolution();				// 进化



// 主函数
int main()
{
	Init();
	int Speed = 700;			// 游戏速度（毫秒）

	while (true)
	{
		if (_kbhit() || Speed == 900)
		{
			char c = _getch();

			if (c == ' ' && Speed != 900)
				c = _getch();

			if (c >= '0' && c <= '9')
				Speed = ('9' - c) * WORLDSIZE - 2;

			switch (c)
			{
			case 's':
			case 'S':
				SquareWorld();	// 产生默认的细胞以方形分布的世界
				break;

			case 'r':
			case 'R':
				RandWorld();	// 产生默认的细胞以方形分布的世界
				break;

			case VK_ESCAPE:
				goto END;
			}
		}

		Evolution();			// 进化
		PaintWorld();			// 绘制世界

		if (Speed != 900)		// 速度为 900 时，为按任意键单步执行
			Sleep(Speed);
	}

END:
	closegraph();
	return 0;
}



///
// 函数定义

// 初始化
void Init()
{
	// 创建绘图窗口
	initgraph(1600, 1000);

	// 设置随机种子
	srand((unsigned)time(NULL));

	// 调整世界图案的大小
	Resize(&imgLive, POINTSIZE, POINTSIZE);
	Resize(&imgEmpty, POINTSIZE, POINTSIZE);

	// 绘制有生命世界的图案
	SetWorkingImage(&imgLive);
	setcolor(GREEN);
	setfillstyle(GREEN);
	fillrectangle(0, 0, POINTSIZE, POINTSIZE);

	// 绘制无生命世界的图案
	SetWorkingImage(&imgEmpty);
	setcolor(DARKGRAY);
	rectangle(0, 0, POINTSIZE, POINTSIZE);

	// 恢复对默认窗口的绘图
	SetWorkingImage(NULL);

	// 输出简单说明
	settextstyle(24, 0, _T("黑体"));
	outtextxy(254, 18, _T("生 命 游 戏"));
	RECT r = { 440, 60, 620, 460 };
	settextstyle(12, 0, _T("宋体"));
	//string s = "生命游戏简介：\n　　生命游戏包括一个二维矩形世界，这个世界中的每个方格居住		着一个活着的或死了的细胞。一个细胞在下一个时刻生死取决于相邻八个方格中活着的细胞		的数量。如果一个细胞周围的活细胞数量多于 3 个，这个细胞会因为资源匮乏而在下一个时		刻死去；如果一个位置周围有 3 个活细胞，则该位置在下一个时刻将诞生一个新的细胞；如		果一个位置周围有 2 个活细胞，则该位置的细胞生死状态保持不变；如果一个细胞周围的活		细胞少于 2 个，那么这个细胞会因太孤单而死去。这样整个生命世界才不至于太过荒凉或拥		挤，而是一种动态的平衡。\n\n游戏控制：\n 0-9: 调节速度(慢--快)\n ESC: 退出\n空格: 		暂停|继续\n   S: 创建细胞以方形分布的世界\n   R: 创建细胞随机分布的世界";
		//drawtext(s,
			//&r, DT_WORDBREAK);

	// 产生默认的细胞以方形分布的世界
	SquareWorld();
}

// 创建一个细胞以方形分布的世界
void SquareWorld()
{
	memset(world, 0, WORLDSIZE * WORLDSIZE * sizeof(__int8));

	for (int x = 1; x < WORLDSIZE - 1; x++)
		world[x][1] = world[x][WORLDSIZE - 2] = 1;

	for (int y = 1; y < WORLDSIZE - 1; y++)
		world[1][y] = world[WORLDSIZE - 2][y] = 1;
}

// 创建一个细胞随机分布的世界
void RandWorld()
{
	for (int x = 1; x < WORLDSIZE - 1; x++)
		for (int y = 1; y < WORLDSIZE - 2; y++)
			world[x][y] = rand() % 2;
}

// 绘制世界
void PaintWorld()
{
	for (int x = 1; x < WORLDSIZE - 1; x++)
		for (int y = 1; y < WORLDSIZE - 1; y++)
			putimage(56 + x * INTERVAL, 56 + y * INTERVAL, world[x][y] ? &imgLive : &imgEmpty);
}

// 进化
void Evolution()
{
	__int8 tmp[WORLDSIZE][WORLDSIZE] = { 0 };		// 临时数组
	int sum;

	for (int x = 1; x < WORLDSIZE - 1; x++)
	{
		for (int y = 1; y < WORLDSIZE - 1; y++)
		{
			// 计算周围活着的生命数量
			sum = world[x + 1][y] + world[x + 1][y - 1] + world[x][y - 1] + world[x - 1][y - 1]
				+ world[x - 1][y] + world[x - 1][y + 1] + world[x][y + 1] + world[x + 1][y + 1];

			// 计算当前位置的生命状态
			switch (sum)
			{
			case 3:		tmp[x][y] = 1;				break;
			case 2:		tmp[x][y] = world[x][y];	break;
			default:	tmp[x][y] = 0;				break;
			}
		}
	}

	// 将临时数组恢复为世界
	memcpy(world, tmp, WORLDSIZE * WORLDSIZE * sizeof(__int8));
}