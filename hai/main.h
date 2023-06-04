#pragma once
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <string>
#include <easyx.h>

const int WORLDSIZE = 102;
//单个点的大小
const int POINTSIZE = 8;
//点之间的距离
const int INTERVAL = POINTSIZE;
//世界的左上角坐标(x,y)
const int APEX[2] = { 56,56 };

static bool isPause = false;			// 是否处于暂停状态
static bool isStep = false;			// 是否处于单步状态
static bool isgoPainted = false;		// go按钮是否已经绘制

//按钮类
class BUTTON {
public:
	int x;
	int y;
	int w;
	int h;
	const wchar_t* text;

	BUTTON(int x, int y, int w, int h, const wchar_t* text, void (*func)(BUTTON* p));
	~BUTTON();
	int paint();        //绘制按钮
	//void (*buttonclicked)(int x = this->x, int y = this->y, int w = this->w, int h = this->h, const wchar_t* text = this->text, BUTTON* p = this->p);//按钮响应事件
	void (*buttonclicked)(BUTTON* s);
};

void func_test(BUTTON* p);		// 按钮的测试功能
void func_pause(BUTTON* p);		// 暂停功能
void func_go(BUTTON* p);		// 单步状态下走一步
void func_step(BUTTON* p);		// 切换单步和自动功能

//世界类
class WORLD {
public:
	__int8 world[WORLDSIZE][WORLDSIZE] = { 0 };
	IMAGE imgLive, imgEmpty;
	WORLD();
	void SquareWorld();				// 创建一个细胞以方形分布的世界
	void RandWorld();				// 创建一个细胞随机分布的世界
	void PaintWorld();				// 绘制世界
	void Evolution();				// 进化
};




