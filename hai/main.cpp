#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <string>
#include <easyx.h>

using namespace std;
//世界大小
const int WORLDSIZE = 102;
//单个点的大小
const int POINTSIZE = 8;
//点之间的距离
const int INTERVAL = POINTSIZE;
//世界的左上角坐标(x,y)
const int APEX[2] = { 56,56 };


//按钮类
class BUTTON{
private:
public:
	int x;
	int y;
	int w;
	int h;
	const wchar_t* text;

	BUTTON(int x, int y, int w, int h, const wchar_t* text,void (* func)(BUTTON* p));
	~BUTTON();
	void paint();        //绘制按钮
	//void (*buttonclicked)(int x = this->x, int y = this->y, int w = this->w, int h = this->h, const wchar_t* text = this->text, BUTTON* p = this->p);//按钮响应事件
	void (*buttonclicked)(BUTTON* s);
};


// 定义全局变量
__int8 world[WORLDSIZE][WORLDSIZE] = { 0 };	// 定义二维世界
IMAGE imgLive, imgEmpty;		// 定义活细胞和无细胞区域的图案
bool isPause = false;			// 是否处于暂停状态
bool isStep = false;			// 是否处于单步状态
bool isgoPainted = false;		// go按钮是否已经绘制


// 函数声明
void Init();					// 初始化
void SquareWorld();				// 创建一个细胞以方形分布的世界
void RandWorld();				// 创建一个细胞随机分布的世界
void PaintWorld();				// 绘制世界
void Evolution();				// 进化
void func_test(BUTTON* p);		// 按钮的测试功能
void func_pause(BUTTON* p);		// 暂停功能
void func_go(BUTTON* p);		// 单步状态下走一步
void func_step(BUTTON* p);		// 切换单步和自动功能



// 主函数
int main()
{
	Init();
	int Speed = 700;			// 游戏速度（毫秒）
	BUTTON test(750,18,150,40, _T("我是你爹"),func_test);    //一个用来测试的按钮
	BUTTON pause(950, 18, 150, 40, _T("暂停按钮"), func_pause);  //暂停/恢复按钮，初始化为暂停
	BUTTON go(1150, 60, 75, 40, _T("更新"), func_go);			//单步模式下的更新按钮
	BUTTON step(1150, 18, 75, 40, _T("单步"), func_step);		//单步/自动按钮，初始化为单步


	ExMessage m;

	while (true)
	{
		//if (_kbhit() || Speed == 900)
		//{
		//	char c = _getch();
		//	if (c == ' ' && Speed != 900)
		//		c = _getch();
		//	if (c >= '0' && c <= '9')
		//		Speed = ('9' - c) * 100;
		//	switch (c)
		//	{
		//	case 's':
		//	case 'S':
		//		SquareWorld();	// 产生默认的细胞以方形分布的世界
		//		break;
		//	case 'r':
		//	case 'R':
		//		RandWorld();	// 产生默认的细胞以方形分布的世界
		//		break;
		//	case VK_ESCAPE:
		//		goto END;
		//	}
		//}

		if (!isPause&&!isStep) {
			Evolution();			// 进化
			PaintWorld();			// 绘制世界
		}

		//响应鼠标的操作
		while (peekmessage(&m, EM_MOUSE)) {
			switch (m.message) {
			case WM_LBUTTONDOWN: {

				//点击世界框中的点，改变某个点的生死状态
				if (m.x >= APEX[0] && m.x <= (APEX[0] + WORLDSIZE * POINTSIZE) && m.y >= APEX[1] && m.y <= (APEX[1] + WORLDSIZE * POINTSIZE)) {
					int index[2] = { (m.x - APEX[0]) / POINTSIZE ,(m.y - APEX[1]) / POINTSIZE };
					world[index[0]][index[1]] = world[index[0]][index[1]] ? 0 : 1;
					putimage(APEX[0] + index[0] * INTERVAL, APEX[1] + index[1] * INTERVAL, world[index[0]][index[1]] ? &imgLive : &imgEmpty);
					
				}

				//点击测试按钮
				if (m.x >= test.x && m.x <= test.x + test.w && m.y >= test.y && m.y <= test.y + test.h) {
					test.buttonclicked(&test);
				}

				//点击暂停/恢复按钮
				if (m.x >= pause.x && m.x <= pause.x + pause.w && m.y >= pause.y && m.y <= pause.y + pause.h) {
					pause.buttonclicked(&pause);
				}

				//点击单步/自动按钮
				if (m.x >= step.x && m.x <= step.x + step.w && m.y >= step.y && m.y <= step.y + step.h) {
					step.buttonclicked(&step);
				}

				//点击更新按钮
				if (m.x >= go.x && m.x <= go.x + go.w && m.y >= go.y && m.y <= go.y + go.h && isStep) {
					go.buttonclicked(&go);
				}


			}
			}
		}

		if (!isStep) {	// 速度为 900 时，为按任意键单步执行
			clearrectangle(go.x, go.y, go.x + go.w, go.y + go.h);
			Sleep(Speed);
		}
		else if (!isgoPainted) {
			go.paint();
			isgoPainted = true;
		}
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
			putimage(APEX[0] + x * INTERVAL, APEX[1] + y * INTERVAL, world[x][y] ? &imgLive : &imgEmpty);
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





//按钮类的构造函数
BUTTON::BUTTON(int x, int y, int w, int h, const wchar_t* text,void (* func)(BUTTON* p))
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

void BUTTON::paint() {
	setbkmode(TRANSPARENT);
	setfillcolor(GREEN);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	// 输出字符串（MBCS 字符集）
	settextstyle(24, 0, _T("黑体"));

	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;

	outtextxy(tx, ty, text);

}

void func_test(BUTTON* p) {
	clearrectangle(p->x, p->y, p->x + p->w, p->y + p->h);
	p->y += p->h;
	p->paint();
}

void func_pause(BUTTON* p) {
	if (isPause) {
		p->text = _T("暂停按钮");
	}
	else {
		p->text = _T("恢复按钮");
	}
	p->paint();
	isPause = isPause ? false : true;
}

void func_step(BUTTON* p) {
	if (isStep) {
		p->text = _T("单步");
		isgoPainted = false;
	}
	else {
		p->text = _T("自动");
	}
	p->paint();
	isStep = isStep ? false : true;
}

void func_go(BUTTON* p) {
	Evolution();			// 进化
	PaintWorld();			// 绘制世界
}
