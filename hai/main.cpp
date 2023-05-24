#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <string>
#include <easyx.h>

using namespace std;
//�����С
const int WORLDSIZE = 102;
//������Ĵ�С
const int POINTSIZE = 8;
//��֮��ľ���
const int INTERVAL = POINTSIZE;
//��������Ͻ�����(x,y)
const int APEX[2] = { 56,56 };


//��ť��
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
	void paint();        //���ư�ť
	//void (*buttonclicked)(int x = this->x, int y = this->y, int w = this->w, int h = this->h, const wchar_t* text = this->text, BUTTON* p = this->p);//��ť��Ӧ�¼�
	void (*buttonclicked)(BUTTON* s);
};


// ����ȫ�ֱ���
__int8 world[WORLDSIZE][WORLDSIZE] = { 0 };	// �����ά����
IMAGE imgLive, imgEmpty;		// �����ϸ������ϸ�������ͼ��
bool isPause = false;


// ��������
void Init();					// ��ʼ��
void SquareWorld();				// ����һ��ϸ���Է��ηֲ�������
void RandWorld();				// ����һ��ϸ������ֲ�������
void PaintWorld();				// ��������
void Evolution();				// ����
void func_test(BUTTON* p);
void func_pause(BUTTON* p);


// ������
int main()
{
	Init();
	int Speed = 700;			// ��Ϸ�ٶȣ����룩
	int x = 754, y = 18, w = 150, h = 40;
	int px = 1000, py = 18, pw = 150, ph = 40;
	BUTTON test(x,y,w,h, _T("�������"),func_test);
	BUTTON pause(px, py, pw, ph, _T("��ͣ��ť"), func_pause);
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
		//		SquareWorld();	// ����Ĭ�ϵ�ϸ���Է��ηֲ�������
		//		break;
		//	case 'r':
		//	case 'R':
		//		RandWorld();	// ����Ĭ�ϵ�ϸ���Է��ηֲ�������
		//		break;
		//	case VK_ESCAPE:
		//		goto END;
		//	}
		//}

		if (!isPause) {
			Evolution();			// ����
			PaintWorld();			// ��������
		}

		//��Ӧ���Ĳ���
		while (peekmessage(&m, EM_MOUSE)) {
			switch (m.message) {
			case WM_LBUTTONDOWN: {
				if (m.x >= APEX[0] && m.x <= (APEX[0] + WORLDSIZE * POINTSIZE) && m.y >= APEX[1] && m.y <= (APEX[1] + WORLDSIZE * POINTSIZE)) {
					int index[2] = { (m.x - APEX[0]) / POINTSIZE ,(m.y - APEX[1]) / POINTSIZE };
					world[index[0]][index[1]] = world[index[0]][index[1]] ? 0 : 1;
					putimage(APEX[0] + index[0] * INTERVAL, APEX[1] + index[1] * INTERVAL, world[index[0]][index[1]] ? &imgLive : &imgEmpty);
					
				}
				if (m.x >= test.x && m.x <= test.x + test.w && m.y >= test.y && m.y <= test.y + test.h) {
					test.buttonclicked(&test);
				}
				if (m.x >= pause.x && m.x <= pause.x + pause.w && m.y >= pause.y && m.y <= pause.y + pause.h) {
					pause.buttonclicked(&pause);
				}

			}
			}
		}

		if (Speed != 900)		// �ٶ�Ϊ 900 ʱ��Ϊ�����������ִ��
			Sleep(Speed);
	}

END:
	closegraph();
	return 0;
}



///
// ��������

// ��ʼ��
void Init()
{
	// ������ͼ����
	initgraph(1600, 1000);

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
	//string s = "������Ϸ��飺\n����������Ϸ����һ����ά�������磬��������е�ÿ�������ס		��һ�����ŵĻ����˵�ϸ����һ��ϸ������һ��ʱ������ȡ�������ڰ˸������л��ŵ�ϸ��		�����������һ��ϸ����Χ�Ļ�ϸ���������� 3 �������ϸ������Ϊ��Դ�ѷ�������һ��ʱ		����ȥ�����һ��λ����Χ�� 3 ����ϸ�������λ������һ��ʱ�̽�����һ���µ�ϸ������		��һ��λ����Χ�� 2 ����ϸ�������λ�õ�ϸ������״̬���ֲ��䣻���һ��ϸ����Χ�Ļ�		ϸ������ 2 ������ô���ϸ������̫�µ�����ȥ������������������Ų�����̫��������ӵ		��������һ�ֶ�̬��ƽ�⡣\n\n��Ϸ���ƣ�\n 0-9: �����ٶ�(��--��)\n ESC: �˳�\n�ո�: 		��ͣ|����\n   S: ����ϸ���Է��ηֲ�������\n   R: ����ϸ������ֲ�������";
		//drawtext(s,
			//&r, DT_WORDBREAK);

	// ����Ĭ�ϵ�ϸ���Է��ηֲ�������
	SquareWorld();
}

// ����һ��ϸ���Է��ηֲ�������
void SquareWorld()
{
	memset(world, 0, WORLDSIZE * WORLDSIZE * sizeof(__int8));

	for (int x = 1; x < WORLDSIZE - 1; x++)
		world[x][1] = world[x][WORLDSIZE - 2] = 1;

	for (int y = 1; y < WORLDSIZE - 1; y++)
		world[1][y] = world[WORLDSIZE - 2][y] = 1;
}

// ����һ��ϸ������ֲ�������
void RandWorld()
{
	for (int x = 1; x < WORLDSIZE - 1; x++)
		for (int y = 1; y < WORLDSIZE - 2; y++)
			world[x][y] = rand() % 2;
}

// ��������
void PaintWorld()
{
	for (int x = 1; x < WORLDSIZE - 1; x++)
		for (int y = 1; y < WORLDSIZE - 1; y++)
			putimage(APEX[0] + x * INTERVAL, APEX[1] + y * INTERVAL, world[x][y] ? &imgLive : &imgEmpty);
}

// ����
void Evolution()
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
	// ����ַ�����MBCS �ַ�����
	settextstyle(24, 0, _T("����"));

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
		p->text = _T("��ͣ��ť");
	}
	else {
		p->text = _T("�ָ���ť");
	}
	p->paint();
	isPause = isPause ? false : true;
}