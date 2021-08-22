#include<iostream>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<String>
using namespace std;
void gotoxy(int x, int y) {//刷新画面清除屏幕内容，重新绘制
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hideCursor() {//防止光标闪烁
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), & cursor_info);
}
int main() {
	//1.初始游戏中的数据
	auto width{ 120 }, height{ 40 };//窗口长宽
	auto ball_x{ width / 2 }, ball_y{ height / 2 }, ball_vec_x{ 0 }, ball_vec_y{ 0 };//球的位置和速度
	auto paddle_w{ 4 }, paddle_h{ 10 };//挡板的长宽
	auto paddle1_x{ 0 }, paddle1_y{ height / 2 - paddle_h / 2 }, paddle1_vec{ 3 };
	auto paddle2_x{ width - paddle_w }, paddle2_y{ height / 2 - paddle_h / 2 }, paddle2_vec{ 3 };
	auto score1{ 0 }, score2{ 0 };



	srand((unsigned)time(0));
	ball_vec_x = rand() % 3 + 1;
	ball_vec_y = rand() % 3 + 1;
	if (rand() % 2 == 1)ball_vec_x = -ball_vec_x;
	if (rand() % 2 == 1)ball_vec_y == -ball_vec_y;


	while (1) {
		//1.处理事件
		char key;
		if (_kbhit()) {
			key = _getch();
			if ((key == 'w') || key == 'W' && paddle1_y > paddle1_vec)
				paddle1_y -= paddle1_vec;
			else if ((key == 's' || key == 'S') && paddle1_y + paddle1_vec + paddle_h < height)
				paddle1_y += paddle1_vec;
			else if(key == 72 && paddle2_y > paddle2_vec)
				paddle2_y -= paddle2_vec;
			else if (key ==80 && paddle2_y + paddle2_vec + paddle_h < height)
				paddle2_y += paddle2_vec;
		}

		//2.更新数据
		ball_x += ball_vec_x;
		ball_y += ball_vec_y;
		if (ball_y < 0 || ball_y >= height)
			ball_vec_y = -ball_vec_y;
		if (ball_x < paddle_w && ball_y >= paddle1_y && ball_y < paddle1_y + paddle_h)
		{//和左挡板相撞,改变水平速度方向
			ball_vec_x = -ball_vec_x;
				score1 += 1;
		}
		else if (ball_x >= width - paddle_w && ball_y >= paddle2_y && ball_y < paddle2_y + paddle_h)
		{
			ball_vec_x = -ball_vec_x;
			score2 += 1;
		}
		
		
		bool is_out{ false };
		if (ball_x < 0) 
		{ score2 += 1; is_out = true; }
		else if (ball_x >width - paddle_w) 
		{ score1 += 1; is_out = true; }
		
		if (is_out) {
			ball_x = width / 2;
			ball_y = height / 2;
			ball_vec_x = rand() % 3 + 1;
			ball_vec_y = rand() % 3 + 1;
			if (rand() % 2 == 1)ball_vec_x = -ball_vec_x;
			if (rand() % 2 == 1)ball_vec_y == -ball_vec_y;

		}
		gotoxy(0, 0);
		hideCursor();
		for (auto x = 0; x <= width; x++)
			cout << '=';
		cout << '\n';
		for (auto y = 0; y <= height; y++) {
			for (auto x = 0; x <= width; x++)

				if (x == ball_x && y == ball_y)cout << 'O';
				else if (y > paddle1_y && y < paddle1_y + paddle_h && x >= paddle1_x && x < paddle1_x + paddle_w) {
					cout << 'Z';
				}
				else if (y > paddle2_y && y < paddle2_y + paddle_h && x >= paddle2_x && x < paddle2_x + paddle_w) {
					cout << 'Z';
				}
				else if (x == 0 || x == width / 2 || x == width)
					cout << '|';
				else cout << ' ';
				
			cout << '\n';

		}
		for (auto x = 0; x <= width; x++)
			cout << '=';
		cout << '\n';
	}
								
}