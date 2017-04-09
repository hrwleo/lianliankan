#include <graphics.h>//图形库
#include "stdio.h"
#include <time.h> //随机数
#include <mmsystem.h> //放音乐
#pragma comment(lib, "WINMM.LIB")     //需要的库

/*
1.连连看部分
加载图片
数组部分 ---1.随机 2.成对出现
图片贴进去-----用数组 二维数组  xy图片贴的位置 元素的值 表示贴什么图片
获取用户点击
判断能否消除
2.表白部分
有背景图片
写出需要说的话
弹窗部分
*/

//窗口大小640*480
IMAGE img[9];
int map[8][6];  //数组大小8*6  1.窗口大小 2.图片大小 80*80
int arr[8 * 6];
int win;

//函数声明
void loadImg(); // 加载图片
void init(); // 数组赋值
void draw(); // 贴图
int GetClickPos(); //获取用户点击
void handleClick(); //处理鼠标点击

void lo(); //表白部分

//函数定义部分
void loadImg(){

	initgraph(640, 480);  //创建一个窗口
	loadimage(&img[0], "1.jpg", 80, 80); //loadimage加载图片，从图片文件获取图像
	loadimage(&img[1], "2.jpg", 80, 80);
	loadimage(&img[2], "3.jpg", 80, 80);
	loadimage(&img[3], "4.jpg", 80, 80);
	loadimage(&img[4], "5.jpg", 80, 80);
	loadimage(&img[5], "6.jpg", 80, 80);
	loadimage(&img[6], "7.jpg", 80, 80);
	loadimage(&img[7], "8.jpg", 80, 80);
	loadimage(&img[8], "背景.jpg", 640, 480); //窗口大小和背景图片一样大
}

void init()
{
	//1.map 赋值  每张图片放的位置以及放什么图片
	//map随机赋值 成对出现  保证每个都有
	//用arr数组先处理下地图
	int arr[8 * 6] = { 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2, 2,
		3, 3, 3, 3, 3, 3,
		4, 4, 4, 4, 4, 4,
		5, 5, 5, 5, 5, 5,
		6, 6, 6, 6, 6, 6,
		7, 7, 7, 7, 7, 7 };  //初始地图

	//把arr中的数组打乱，然后放入map中
	//使用随机数打乱
	srand((unsigned)time(NULL)); //生成随机数
	int lenth = 48; // arr长度
	int temp;
	//给map赋值
	for (int i = 0; i < 8;i++)
	{
		for (int j = 0; j < 6;j++)
		{
			//随机取出arr数组中的一个赋给map[i][j]
			temp = rand() % lenth;
			map[i][j] = arr[temp]; //取出的数字不能再用

			//去除数字,后面的数往前移
			for (int k = temp; k < lenth - 1;k++)
			{
				arr[k] = arr[k + 1]; 
			}
			lenth--;
		}
	}
	win = 48; // 记录当前图片的个数
	//map被打乱后，根据每个元素值贴图
}

void draw(){
	BeginBatchDraw();
	//背景 -- 贴背景
	putimage(0, 0, &img[8]);

	//再贴别的图片
	for (int i = 0; i < 8;i++)
	{
		for (int j = 0; j < 6;j++)
		{
			//遍历数组的值 放入图片
			switch (map[i][j])
			{
			case 0://贴第一张图
				putimage(80 * i, 80 * j, &img[0]); break; //putimage()绘制图像，参数是x,y的位移，要绘制的 IMAGE 对象指针
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
	//图形库函数
	//1.鼠标信息
	MOUSEMSG msg; // 存储鼠标信息
	msg = GetMouseMsg(); // 获取鼠标信息

	//根据鼠标位置来判断 鼠标信息
	switch (msg.uMsg){
	case WM_LBUTTONDOWN:
		//msg x,y 例：第一张图片 0<msg.x<80  0<msg.y<80
		//返回坐标值  map[msg.x / 80][msg.y / 80]
		return (msg.x / 80) * 10 + msg.y / 80;

		break;
	}
	return -1;
}

void handleClick(){
	//获取两次鼠标点击  1.两次鼠标点击都要有效
	int i = 0;
	int point1, point2; // 获取到两次鼠标点击的位置
	
	while ((point1 = GetClickPos()) == -1 || map[point1 / 10][point1 % 10] == -1); //获取到一个坐标(如果等于-1说明一直没获取到坐标,则一直循环)
		//outtextxy(point1 / 10 * 80, point1 % 10 * 80, 'A');
	setlinecolor(RED);
	rectangle(point1 / 10 * 80, point1 % 10 * 80, point1 / 10 * 80 + 80, point1 % 10 * 80 + 80);
			//根据坐标判断
			//1.是不是已经获取到了坐标 point1 = GetClickPos()!=-1
			//2.是不是已经赋值内容 map[point1/10][point1%10]!=-1
			//消掉部分 = -1
	while ((point2 = GetClickPos()) == -1 || map[point2 / 10][point2 % 10] == -1);
		
			//可以消除或不可以消除
			//可以消除 1.坐标不一样 2.图片一样
	if (point1 != point2 && map[point1 / 10][point1 % 10] == map[point2 / 10][point2 % 10])
	{
		//连线部分
		line(point1 / 10*80 +40, point1 % 10*80+40, point2 / 10*80+40, point2 % 10*80+40); //需要两个坐标
		Sleep(500);
		map[point1 / 10][point1 % 10] = -1; //图片和数组是挂钩的 -1无对应图片 0~7有图片
		map[point2 / 10][point2 % 10] = -1;
		win -= 2;
	}
	else{
			//没有消掉
	}

		

	
}

void lo(){
	mciSendString("play BGM.mp3 repeat", 0, 0, 0);

	settextcolor(LIGHTGRAY);//字体颜色
	settextstyle(30, 0, "黑体");
	setbkmode(TRANSPARENT); //设置文字背景透明

	char poem[2][50] = { "I will love you more than yesterday", "less than tomorrow" };
	//outtextxy(0, 0, poem[0]);
	//outtextxy(0, 30, poem[1]);
	//文字一个个出现,循环输出
	for (int i = 0; i < 2;i++)
	{
		for (int j = 0; j < 50;j++)
		{
			outtextxy(13 * j, 30*i, poem[i][j]);
			Sleep(200);
		}
	}
	//弹窗内容
	HWND hwnd = GetHWnd(); // 获取当前窗口句柄
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
	//表白部分
	//内容
	initgraph(640, 480);
	loadimage(&img[8], "背景.jpg", 640, 480);
	putimage(0, 0, &img[8]);
	//loadimage(NULL, "背景.jpg", 640, 480);
	lo();
	system("pause");
	return 0;
}






