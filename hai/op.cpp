#include"main.h"



WORLD::WORLD()
{
	// 创建绘图窗口
	initgraph(1600, 1000, EX_SHOWCONSOLE);

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
	// 产生默认的细胞以方形分布的世界
	SquareWorld();
}

// 创建一个细胞以方形分布的世界
void WORLD::SquareWorld()
{
	memset(world, 0, WORLDSIZE * WORLDSIZE * sizeof(__int8));

	for (int x = 1; x < WORLDSIZE - 1; x++)
		world[x][1] = world[x][WORLDSIZE - 2] = 1;

	for (int y = 1; y < WORLDSIZE - 1; y++)
		world[1][y] = world[WORLDSIZE - 2][y] = 1;
}

// 创建一个细胞随机分布的世界
void WORLD::RandWorld()
{
	for (int x = 1; x < WORLDSIZE - 1; x++)
		for (int y = 1; y < WORLDSIZE - 2; y++)
			world[x][y] = rand() % 2;
}

// 绘制世界
void WORLD::PaintWorld()
{
	for (int x = 1; x < WORLDSIZE - 1; x++)
		for (int y = 1; y < WORLDSIZE - 1; y++)
			putimage(APEX[0] + x * INTERVAL, APEX[1] + y * INTERVAL, world[x][y] ? &imgLive : &imgEmpty);
}

// 进化
void WORLD::Evolution()
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





//按钮类的构造函数
BUTTON::BUTTON(int x, int y, int w, int h, const wchar_t* text, void (*func)(BUTTON* p))
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->text = text;
	buttonclicked = func;
	paint();
}

BUTTON::~BUTTON() {
	clearrectangle(x, y, x + w, y + h);
}

int BUTTON::paint() {
	setbkmode(TRANSPARENT);
	setfillcolor(GREEN);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	// 输出字符串（MBCS 字符集）
	settextstyle(24, 0, _T("黑体"));

	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;

	outtextxy(tx, ty, text);
	return 1;
}

