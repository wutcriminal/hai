#include"main.h"



WORLD::WORLD()
{
	// ������ͼ����
	initgraph(1600, 1000, EX_SHOWCONSOLE);

	// �����������
	srand((unsigned)time(NULL));

	// ��������ͼ���Ĵ�С
	Resize(&imgLive, POINTSIZE, POINTSIZE);
	Resize(&imgEmpty, POINTSIZE, POINTSIZE);

	// ���������������ͼ��
	SetWorkingImage(&imgLive);
	setcolor(GREEN);
	setfillstyle(GREEN);
	fillrectangle(0, 0, POINTSIZE, POINTSIZE);

	// ���������������ͼ��
	SetWorkingImage(&imgEmpty);
	setcolor(DARKGRAY);
	rectangle(0, 0, POINTSIZE, POINTSIZE);
	// �ָ���Ĭ�ϴ��ڵĻ�ͼ
	SetWorkingImage(NULL);

	// �����˵��
	settextstyle(24, 0, _T("����"));
	outtextxy(254, 18, _T("�� �� �� Ϸ"));
	RECT r = { 440, 60, 620, 460 };
	settextstyle(12, 0, _T("����"));
	// ����Ĭ�ϵ�ϸ���Է��ηֲ�������
	SquareWorld();
}

// ����һ��ϸ���Է��ηֲ�������
void WORLD::SquareWorld()
{
	memset(world, 0, WORLDSIZE * WORLDSIZE * sizeof(__int8));

	for (int x = 1; x < WORLDSIZE - 1; x++)
		world[x][1] = world[x][WORLDSIZE - 2] = 1;

	for (int y = 1; y < WORLDSIZE - 1; y++)
		world[1][y] = world[WORLDSIZE - 2][y] = 1;
}

// ����һ��ϸ������ֲ�������
void WORLD::RandWorld()
{
	for (int x = 1; x < WORLDSIZE - 1; x++)
		for (int y = 1; y < WORLDSIZE - 2; y++)
			world[x][y] = rand() % 2;
}

// ��������
void WORLD::PaintWorld()
{
	for (int x = 1; x < WORLDSIZE - 1; x++)
		for (int y = 1; y < WORLDSIZE - 1; y++)
			putimage(APEX[0] + x * INTERVAL, APEX[1] + y * INTERVAL, world[x][y] ? &imgLive : &imgEmpty);
}

// ����
void WORLD::Evolution()
{
	__int8 tmp[WORLDSIZE][WORLDSIZE] = { 0 };		// ��ʱ����
	int sum;

	for (int x = 1; x < WORLDSIZE - 1; x++)
	{
		for (int y = 1; y < WORLDSIZE - 1; y++)
		{
			// ������Χ���ŵ���������
			sum = world[x + 1][y] + world[x + 1][y - 1] + world[x][y - 1] + world[x - 1][y - 1]
				+ world[x - 1][y] + world[x - 1][y + 1] + world[x][y + 1] + world[x + 1][y + 1];

			// ���㵱ǰλ�õ�����״̬
			switch (sum)
			{
			case 3:		tmp[x][y] = 1;				break;
			case 2:		tmp[x][y] = world[x][y];	break;
			default:	tmp[x][y] = 0;				break;
			}
		}
	}

	// ����ʱ����ָ�Ϊ����
	memcpy(world, tmp, WORLDSIZE * WORLDSIZE * sizeof(__int8));
}





//��ť��Ĺ��캯��
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
	// ����ַ�����MBCS �ַ�����
	settextstyle(24, 0, _T("����"));

	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;

	outtextxy(tx, ty, text);
	return 1;
}

