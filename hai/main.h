#pragma once
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <string>
#include <easyx.h>

const int WORLDSIZE = 102;
//������Ĵ�С
const int POINTSIZE = 8;
//��֮��ľ���
const int INTERVAL = POINTSIZE;
//��������Ͻ�����(x,y)
const int APEX[2] = { 56,56 };

static bool isPause = false;			// �Ƿ�����ͣ״̬
static bool isStep = false;			// �Ƿ��ڵ���״̬
static bool isgoPainted = false;		// go��ť�Ƿ��Ѿ�����

//��ť��
class BUTTON {
public:
	int x;
	int y;
	int w;
	int h;
	const wchar_t* text;

	BUTTON(int x, int y, int w, int h, const wchar_t* text, void (*func)(BUTTON* p));
	~BUTTON();
	int paint();        //���ư�ť
	//void (*buttonclicked)(int x = this->x, int y = this->y, int w = this->w, int h = this->h, const wchar_t* text = this->text, BUTTON* p = this->p);//��ť��Ӧ�¼�
	void (*buttonclicked)(BUTTON* s);
};

void func_test(BUTTON* p);		// ��ť�Ĳ��Թ���
void func_pause(BUTTON* p);		// ��ͣ����
void func_go(BUTTON* p);		// ����״̬����һ��
void func_step(BUTTON* p);		// �л��������Զ�����

//������
class WORLD {
public:
	__int8 world[WORLDSIZE][WORLDSIZE] = { 0 };
	IMAGE imgLive, imgEmpty;
	WORLD();
	void SquareWorld();				// ����һ��ϸ���Է��ηֲ�������
	void RandWorld();				// ����һ��ϸ������ֲ�������
	void PaintWorld();				// ��������
	void Evolution();				// ����
};




