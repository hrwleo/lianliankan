#include <graphics.h>//ͼ�ο�
#include "stdio.h"
#include <time.h> //�����
#include <mmsystem.h> //������
#pragma comment(lib, "WINMM.LIB")     //��Ҫ�Ŀ�

/*
1.����������
����ͼƬ
���鲿�� ---1.��� 2.�ɶԳ���
ͼƬ����ȥ-----������ ��ά����  xyͼƬ����λ�� Ԫ�ص�ֵ ��ʾ��ʲôͼƬ
��ȡ�û����
�ж��ܷ�����
2.��ײ���
�б���ͼƬ
д����Ҫ˵�Ļ�
��������
*/

//���ڴ�С640*480
IMAGE img[9];
int map[8][6];  //�����С8*6  1.���ڴ�С 2.ͼƬ��С 80*80
int arr[8 * 6];
int win;

//��������
void loadImg(); // ����ͼƬ
void init(); // ���鸳ֵ
void draw(); // ��ͼ
int GetClickPos(); //��ȡ�û����
void handleClick(); //���������

void lo(); //��ײ���

//�������岿��
void loadImg(){

	initgraph(640, 480);  //����һ������
	loadimage(&img[0], "1.jpg", 80, 80); //loadimage����ͼƬ����ͼƬ�ļ���ȡͼ��
	loadimage(&img[1], "2.jpg", 80, 80);
	loadimage(&img[2], "3.jpg", 80, 80);
	loadimage(&img[3], "4.jpg", 80, 80);
	loadimage(&img[4], "5.jpg", 80, 80);
	loadimage(&img[5], "6.jpg", 80, 80);
	loadimage(&img[6], "7.jpg", 80, 80);
	loadimage(&img[7], "8.jpg", 80, 80);
	loadimage(&img[8], "����.jpg", 640, 480); //���ڴ�С�ͱ���ͼƬһ����
}

void init()
{
	//1.map ��ֵ  ÿ��ͼƬ�ŵ�λ���Լ���ʲôͼƬ
	//map�����ֵ �ɶԳ���  ��֤ÿ������
	//��arr�����ȴ����µ�ͼ
	int arr[8 * 6] = { 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2, 2,
		3, 3, 3, 3, 3, 3,
		4, 4, 4, 4, 4, 4,
		5, 5, 5, 5, 5, 5,
		6, 6, 6, 6, 6, 6,
		7, 7, 7, 7, 7, 7 };  //��ʼ��ͼ

	//��arr�е�������ң�Ȼ�����map��
	//ʹ�����������
	srand((unsigned)time(NULL)); //���������
	int lenth = 48; // arr����
	int temp;
	//��map��ֵ
	for (int i = 0; i < 8;i++)
	{
		for (int j = 0; j < 6;j++)
		{
			//���ȡ��arr�����е�һ������map[i][j]
			temp = rand() % lenth;
			map[i][j] = arr[temp]; //ȡ�������ֲ�������

			//ȥ������,���������ǰ��
			for (int k = temp; k < lenth - 1;k++)
			{
				arr[k] = arr[k + 1]; 
			}
			lenth--;
		}
	}
	win = 48; // ��¼��ǰͼƬ�ĸ���
	//map�����Һ󣬸���ÿ��Ԫ��ֵ��ͼ
}

void draw(){
	BeginBatchDraw();
	//���� -- ������
	putimage(0, 0, &img[8]);

	//�������ͼƬ
	for (int i = 0; i < 8;i++)
	{
		for (int j = 0; j < 6;j++)
		{
			//���������ֵ ����ͼƬ
			switch (map[i][j])
			{
			case 0://����һ��ͼ
				putimage(80 * i, 80 * j, &img[0]); break; //putimage()����ͼ�񣬲�����x,y��λ�ƣ�Ҫ���Ƶ� IMAGE ����ָ��
			case 1:
				putimage(80 * i, 80 * j, &img[1]); break;
			case 2:
				putimage(80 * i, 80 * j, &img[2]); break;
			case 3:
				putimage(80 * i, 80 * j, &img[3]); break;
			case 4:
				putimage(80 * i, 80 * j, &img[4]); break;
			case 5:
				putimage(80 * i, 80 * j, &img[5]); break;
			case 6:
				putimage(80 * i, 80 * j, &img[6]); break;
			case 7:
				putimage(80 * i, 80 * j, &img[7]); break;
			default:
				break;
			}
		}
	}
	EndBatchDraw();
}

int GetClickPos(){
	//ͼ�ο⺯��
	//1.�����Ϣ
	MOUSEMSG msg; // �洢�����Ϣ
	msg = GetMouseMsg(); // ��ȡ�����Ϣ

	//�������λ�����ж� �����Ϣ
	switch (msg.uMsg){
	case WM_LBUTTONDOWN:
		//msg x,y ������һ��ͼƬ 0<msg.x<80  0<msg.y<80
		//��������ֵ  map[msg.x / 80][msg.y / 80]
		return (msg.x / 80) * 10 + msg.y / 80;

		break;
	}
	return -1;
}

void handleClick(){
	//��ȡ���������  1.�����������Ҫ��Ч
	int i = 0;
	int point1, point2; // ��ȡ�������������λ��
	
	while ((point1 = GetClickPos()) == -1 || map[point1 / 10][point1 % 10] == -1); //��ȡ��һ������(�������-1˵��һֱû��ȡ������,��һֱѭ��)
		//outtextxy(point1 / 10 * 80, point1 % 10 * 80, 'A');
	setlinecolor(RED);
	rectangle(point1 / 10 * 80, point1 % 10 * 80, point1 / 10 * 80 + 80, point1 % 10 * 80 + 80);
			//���������ж�
			//1.�ǲ����Ѿ���ȡ�������� point1 = GetClickPos()!=-1
			//2.�ǲ����Ѿ���ֵ���� map[point1/10][point1%10]!=-1
			//�������� = -1
	while ((point2 = GetClickPos()) == -1 || map[point2 / 10][point2 % 10] == -1);
		
			//���������򲻿�������
			//�������� 1.���겻һ�� 2.ͼƬһ��
	if (point1 != point2 && map[point1 / 10][point1 % 10] == map[point2 / 10][point2 % 10])
	{
		//���߲���
		line(point1 / 10*80 +40, point1 % 10*80+40, point2 / 10*80+40, point2 % 10*80+40); //��Ҫ��������
		Sleep(500);
		map[point1 / 10][point1 % 10] = -1; //ͼƬ�������ǹҹ��� -1�޶�ӦͼƬ 0~7��ͼƬ
		map[point2 / 10][point2 % 10] = -1;
		win -= 2;
	}
	else{
			//û������
	}

		

	
}

void lo(){
	mciSendString("play BGM.mp3 repeat", 0, 0, 0);

	settextcolor(LIGHTGRAY);//������ɫ
	settextstyle(30, 0, "����");
	setbkmode(TRANSPARENT); //�������ֱ���͸��

	char poem[2][50] = { "I will love you more than yesterday", "less than tomorrow" };
	//outtextxy(0, 0, poem[0]);
	//outtextxy(0, 30, poem[1]);
	//����һ��������,ѭ�����
	for (int i = 0; i < 2;i++)
	{
		for (int j = 0; j < 50;j++)
		{
			outtextxy(13 * j, 30*i, poem[i][j]);
			Sleep(200);
		}
	}
	//��������
	HWND hwnd = GetHWnd(); // ��ȡ��ǰ���ھ��
	MessageBox(hwnd,"I Love You","NAME",MB_OK);
}
//==============================
int main(){
	loadImg();
	init();
	draw();
	//mciSendString("play BGM.mp3 repeat", 0, 0, 0);
	while (win != 0)
	{
		handleClick();
		draw();

	}
	//��ײ���
	//����
	initgraph(640, 480);
	loadimage(&img[8], "����.jpg", 640, 480);
	putimage(0, 0, &img[8]);
	//loadimage(NULL, "����.jpg", 640, 480);
	lo();
	system("pause");
	return 0;
}






