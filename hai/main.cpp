
#include <stdio.h>
//#include <graphics.h>
//#include <conio.h>
//#include <time.h>
//#include <string>
//#include <easyx.h>
#include "main.h"


using namespace std;
//�����С
//const int WORLDSIZE = 102;
////������Ĵ�С
//const int POINTSIZE = 8;
////��֮��ľ���
//const int INTERVAL = POINTSIZE;
////��������Ͻ�����(x,y)
//const int APEX[2] = { 56,56 };


////��ť��
//class BUTTON{
//private:
//public:
//	int x;
//	int y;
//	int w;
//	int h;
//	const wchar_t* text;
//
//	BUTTON(int x, int y, int w, int h, const wchar_t* text,void (* func)(BUTTON* p));
//	~BUTTON();
//	void paint();        //���ư�ť
//	//void (*buttonclicked)(int x = this->x, int y = this->y, int w = this->w, int h = this->h, const wchar_t* text = this->text, BUTTON* p = this->p);//��ť��Ӧ�¼�
//	void (*buttonclicked)(BUTTON* s);
//};
//
////������
//class WORLD {
//public:
//	__int8 world[WORLDSIZE][WORLDSIZE] = { 0 };
//	IMAGE imgLive, imgEmpty;
//	WORLD();
//	void SquareWorld();				// ����һ��ϸ���Է��ηֲ�������
//	void RandWorld();				// ����һ��ϸ������ֲ�������
//	void PaintWorld();				// ��������
//	void Evolution();				// ����
//};
//
//// ����ȫ�ֱ���
////__int8 world[WORLDSIZE][WORLDSIZE] = { 0 };	// �����ά����
////IMAGE imgLive, imgEmpty;		// �����ϸ������ϸ�������ͼ��
//bool isPause = false;			// �Ƿ�����ͣ״̬
//bool isStep = false;			// �Ƿ��ڵ���״̬
//bool isgoPainted = false;		// go��ť�Ƿ��Ѿ�����
//
//
//// ��������
////void Init();					// ��ʼ��
////void SquareWorld();				// ����һ��ϸ���Է��ηֲ�������
////void RandWorld();				// ����һ��ϸ������ֲ�������
////void PaintWorld();				// ��������
////void Evolution();				// ����
//WORLD _world;
//void func_test(BUTTON* p);		// ��ť�Ĳ��Թ���
//void func_pause(BUTTON* p);		// ��ͣ����
//void func_go(BUTTON* p);		// ����״̬����һ��
//void func_step(BUTTON* p);		// �л��������Զ�����
//
//
//

WORLD _world;
//int main()
//{
//	int Speed = 700;			// ��Ϸ�ٶȣ����룩
//    //BUTTON test(750,18,150,40, _T("�������"),func_test);    //һ���������Եİ�ť
//	BUTTON pause(950, 18, 150, 40, _T("��ͣ��ť"), func_pause);  //��ͣ/�ָ���ť����ʼ��Ϊ��ͣ
//	BUTTON go(1150, 60, 75, 40, _T("����"), func_go);			//����ģʽ�µĸ��°�ť
//	BUTTON step(1150, 18, 75, 40, _T("����"), func_step);		//����/�Զ���ť����ʼ��Ϊ����
//	ExMessage m;
//	while (true)
//	{
//		//if (_kbhit() || Speed == 900)
//		//{
//		//	char c = _getch();
//		//	if (c == ' ' && Speed != 900)
//		//		c = _getch();
//		//	if (c >= '0' && c <= '9')
//		//		Speed = ('9' - c) * 100;
//		//	switch (c)
//		//	{
//		//	case 's':
//		//	case 'S':
//		//		SquareWorld();	// ����Ĭ�ϵ�ϸ���Է��ηֲ�������
//		//		break;
//		//	case 'r':
//		//	case 'R':
//		//		RandWorld();	// ����Ĭ�ϵ�ϸ���Է��ηֲ�������
//		//		break;
//		//	case VK_ESCAPE:
//		//		goto END;
//		//	}
//		//}
//
//		if (!isPause&&!isStep) {
//			_world.Evolution();			// ����
//			_world.PaintWorld();			// ��������
//		}
//
//		//��Ӧ���Ĳ���
//		while (peekmessage(&m, EM_MOUSE)) {
//			switch (m.message) {
//			case WM_LBUTTONDOWN: {
//
//				//���������еĵ㣬�ı�ĳ���������״̬
//				if (m.x >= APEX[0] && m.x <= (APEX[0] + WORLDSIZE * POINTSIZE) && m.y >= APEX[1] && m.y <= (APEX[1] + WORLDSIZE * POINTSIZE)) {
//					int index[2] = { (m.x - APEX[0]) / POINTSIZE ,(m.y - APEX[1]) / POINTSIZE };
//					_world.world[index[0]][index[1]] = _world.world[index[0]][index[1]] ? 0 : 1;
//					putimage(APEX[0] + index[0] * INTERVAL, APEX[1] + index[1] * INTERVAL, _world.world[index[0]][index[1]] ? &_world.imgLive : &_world.imgEmpty);
//					
//				}
//
//				//������԰�ť
//				/*if (m.x >= test.x && m.x <= test.x + test.w && m.y >= test.y && m.y <= test.y + test.h) {
//					test.buttonclicked(&test);
//				}*/
//
//				//�����ͣ/�ָ���ť
//				if (m.x >= pause.x && m.x <= pause.x + pause.w && m.y >= pause.y && m.y <= pause.y + pause.h) {
//					pause.buttonclicked(&pause);
//				}
//
//				//�������/�Զ���ť
//				if (m.x >= step.x && m.x <= step.x + step.w && m.y >= step.y && m.y <= step.y + step.h) {
//					step.buttonclicked(&step);
//				}
//
//				//������°�ť
//				if (m.x >= go.x && m.x <= go.x + go.w && m.y >= go.y && m.y <= go.y + go.h && isStep) {
//					go.buttonclicked(&go);
//				}
//
//			}
//			}
//		}
//
//		if (!isStep) {	// �ٶ�Ϊ 900 ʱ��Ϊ�����������ִ��
//			clearrectangle(go.x, go.y, go.x + go.w, go.y + go.h);
//			Sleep(Speed);
//		}
//		else if (!isgoPainted) {
//			go.paint();
//			isgoPainted = true;
//		}
//	}
//
//END:
//	closegraph();
//	return 0;
//}

void func_test(BUTTON* p) {
	clearrectangle(p->x, p->y, p->x + p->w, p->y + p->h);
	p->y += p->h;
	p->paint();
}

void func_pause(BUTTON* p) {
	if (isPause) {
		p->text = _T("��ͣ��ť");
	}
	else {
		p->text = _T("�ָ���ť");
	}
	p->paint();
	isPause = isPause ? false : true;
}

void func_step(BUTTON* p) {
	if (isStep) {
		p->text = _T("����");
		isgoPainted = false;
	}
	else {
		p->text = _T("�Զ�");
	}
	p->paint();
	isStep = isStep ? false : true;
}

void func_go(BUTTON* p) {
	_world.Evolution();			// ����
	_world.PaintWorld();			// ��������
}

//
//
/////
//// ��������
//
//// ��ʼ��
//WORLD::WORLD()
//{
//	// ������ͼ����
//	initgraph(1600, 1000, EX_SHOWCONSOLE);
//
//	// �����������
//	srand((unsigned)time(NULL));
//
//	// ��������ͼ���Ĵ�С
//	Resize(&imgLive, POINTSIZE, POINTSIZE);
//	Resize(&imgEmpty, POINTSIZE, POINTSIZE);
//
//	// ���������������ͼ��
//	SetWorkingImage(&imgLive);
//	setcolor(GREEN);
//	setfillstyle(GREEN);
//	fillrectangle(0, 0, POINTSIZE, POINTSIZE);
//
//	// ���������������ͼ��
//	SetWorkingImage(&imgEmpty);
//	setcolor(DARKGRAY);
//	rectangle(0, 0, POINTSIZE, POINTSIZE);
//	// �ָ���Ĭ�ϴ��ڵĻ�ͼ
//	SetWorkingImage(NULL);
//
//	// �����˵��
//	settextstyle(24, 0, _T("����"));
//	outtextxy(254, 18, _T("�� �� �� Ϸ"));
//	RECT r = { 440, 60, 620, 460 };
//	settextstyle(12, 0, _T("����"));
//	// ����Ĭ�ϵ�ϸ���Է��ηֲ�������
//	SquareWorld();
//}
//
//// ����һ��ϸ���Է��ηֲ�������
//void WORLD::SquareWorld()
//{
//	memset(world, 0, WORLDSIZE * WORLDSIZE * sizeof(__int8));
//
//	for (int x = 1; x < WORLDSIZE - 1; x++)
//		world[x][1] = world[x][WORLDSIZE - 2] = 1;
//
//	for (int y = 1; y < WORLDSIZE - 1; y++)
//		world[1][y] = world[WORLDSIZE - 2][y] = 1;
//}
//
//// ����һ��ϸ������ֲ�������
//void WORLD::RandWorld()
//{
//	for (int x = 1; x < WORLDSIZE - 1; x++)
//		for (int y = 1; y < WORLDSIZE - 2; y++)
//			world[x][y] = rand() % 2;
//}
//
//// ��������
//void WORLD::PaintWorld()
//{
//	for (int x = 1; x < WORLDSIZE - 1; x++)
//		for (int y = 1; y < WORLDSIZE - 1; y++)
//			putimage(APEX[0] + x * INTERVAL, APEX[1] + y * INTERVAL, world[x][y] ? &imgLive : &imgEmpty);
//}
//
//// ����
//void WORLD::Evolution()
//{
//	__int8 tmp[WORLDSIZE][WORLDSIZE] = { 0 };		// ��ʱ����
//	int sum;
//
//	for (int x = 1; x < WORLDSIZE - 1; x++)
//	{
//		for (int y = 1; y < WORLDSIZE - 1; y++)
//		{
//			// ������Χ���ŵ���������
//			sum = world[x + 1][y] + world[x + 1][y - 1] + world[x][y - 1] + world[x - 1][y - 1]
//				+ world[x - 1][y] + world[x - 1][y + 1] + world[x][y + 1] + world[x + 1][y + 1];
//
//			// ���㵱ǰλ�õ�����״̬
//			switch (sum)
//			{
//			case 3:		tmp[x][y] = 1;				break;
//			case 2:		tmp[x][y] = world[x][y];	break;
//			default:	tmp[x][y] = 0;				break;
//			}
//		}
//	}
//
//	// ����ʱ����ָ�Ϊ����
//	memcpy(world, tmp, WORLDSIZE * WORLDSIZE * sizeof(__int8));
//}
//
//
//
//
//
////��ť��Ĺ��캯��
//BUTTON::BUTTON(int x, int y, int w, int h, const wchar_t* text,void (* func)(BUTTON* p))
//{
//	this->x = x;
//	this->y = y;
//	this->w = w;
//	this->h = h;
//	this->text = text;
//	buttonclicked = func;
//	paint();
//}
//
//BUTTON::~BUTTON() {
//	clearrectangle(x, y, x + w, y + h);
//}
//
//void BUTTON::paint() {
//	setbkmode(TRANSPARENT);
//	setfillcolor(GREEN);
//	fillroundrect(x, y, x + w, y + h, 10, 10);
//	// ����ַ�����MBCS �ַ�����
//	settextstyle(24, 0, _T("����"));
//
//	int tx = x + (w - textwidth(text)) / 2;
//	int ty = y + (h - textheight(text)) / 2;
//
//	outtextxy(tx, ty, text);
//}
//
//void func_test(BUTTON* p) {
//	clearrectangle(p->x, p->y, p->x + p->w, p->y + p->h);
//	p->y += p->h;
//	p->paint();
//}
//
//void func_pause(BUTTON* p) {
//	if (isPause) {
//		p->text = _T("��ͣ��ť");
//	}
//	else {
//		p->text = _T("�ָ���ť");
//	}
//	p->paint();
//	isPause = isPause ? false : true;
//}
//
//void func_step(BUTTON* p) {
//	if (isStep) {
//		p->text = _T("����");
//		isgoPainted = false;
//	}
//	else {
//		p->text = _T("�Զ�");
//	}
//	p->paint();
//	isStep = isStep ? false : true;
//}
//
//void func_go(BUTTON* p) {
//	_world.Evolution();			// ����
//	_world.PaintWorld();			// ��������
//}
