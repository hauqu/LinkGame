#include"Graph.h"
#include<conio.h>
#include<graphics.h>
/*
下一步使用鼠标逻辑测试
测试完毕
算法全部正常

*/

using namespace std;
const int K = 60;
const int MapW = 10;
const int MapH = 10;
Graph test = Graph(MapW, MapH, K);
void DrawGame(void);
const int cateNumber = 10;
IMAGE picture[cateNumber];
IMAGE win;
void load();
int main()
{

	initgraph(MapW*K, MapH*K);
	load();
	setlinecolor(RGB(128, 128, 128));
	setorigin(K / 2, K / 2);
	test.readMap("wfy.txt");
	test.creatMap(cateNumber, K);
	putimage(0, 0, &win);

	int x1,y1;
	int x2, y2;
	int falg = 0;
	vector<node>t;
	DrawGame();
	while (true)
	{
		MOUSEMSG ms = GetMouseMsg();

		if (ms.mkLButton || ms.mkRButton)
		{
			int w = ms.x / K;
			int h = ms.y / K;
			if (ms.mkLButton == true && test.g[w][h].d != 0)
			{

				if (falg == 0)
				{
					x1 = w;
					y1 = h;
					falg = 1;
				}
				else if (falg == 1 || falg == 2)
				{
					x2 = w;
					y2 = h;
					if (x1 == x2 && y1 == y2)
					{
						falg = 1;
					}
					else
					{
						falg = 2;
					}

				}


			}
			if (ms.mkRButton == true)
				{
					if (falg == 0)
					{
						//do nothing
					}
					else if (falg == 1)
					{
						falg = 0;
					}
					else if (falg == 2)
					{
						falg = 1;
					}

				}
				//绘制图片
			DrawGame();
				//绘制选中框
			setlinecolor(RED);
			switch (falg)
				{
				case 0:
					// do nothing
					break;
				case 1:
					rectangle(test.g[x1][y1].x - K / 2, test.g[x1][y1].y - K / 2,
						test.g[x1][y1].x + K / 2, test.g[x1][y1].y + K / 2);

					break;
				case 2:
					rectangle(test.g[x1][y1].x - K / 2, test.g[x1][y1].y - K / 2,
						test.g[x1][y1].x + K / 2, test.g[x1][y1].y + K / 2);
					rectangle(test.g[x2][y2].x - K / 2, test.g[x2][y2].y - K / 2,
						test.g[x2][y2].x + K / 2, test.g[x2][y2].y + K / 2);
					break;
				default:
					break;
				}
			setlinecolor(RGB(128, 128, 128));
			if (falg == 2)
				{
					t.clear();
					if (test.remove(x1, y1, x2, y2, t))
					{
						
						test.g[x1][y1].d = 0;
						test.g[x2][y2].d = 0;
						for (int i = 0; i < t.size() - 1; i++)
						{
							int tx = t[i].x;
							int ty = t[i].y;
							Sleep(200);
							line(tx, ty, t[i + 1].x, t[i + 1].y);
						}
						Sleep(200);
						cleardevice();
						DrawGame();
						falg = 0;
						if (test.winGame())
						{
							goto Gameover;
						}
					}
				}
			}
		}


	Gameover:
		putimage(0, 0, &win);

	_getch();
	return 0;
}
void DrawGame(void)
{
	int w = test.g.size();
	int h = test.g[0].size();

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			int d = test.g[i][j].d;
			int x = test.g[i][j].x;
			int y = test.g[i][j].y;
			RECT r = { x - K / 2, y - K / 2, x + K / 2, y + K / 2 };
			char c = d+'0';
			rectangle(x - K / 2, y - K / 2, x + K / 2, y + K / 2);
			if (d != 0) {

				drawtext(c, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE); 
				putimage(x-K/2, y-K/2, &picture[d]);
				
			}
			
		}
	}
}
void load()
{
	loadimage(&picture[0], "0.jpg", K, K);
	loadimage(&picture[1], "1.jpg", K, K);
	loadimage(&picture[2], "2.jpg", K, K);
	loadimage(&picture[3], "3.jpg", K, K);
	loadimage(&picture[4], "4.jpg", K, K);
	loadimage(&picture[5], "5.jpg", K, K);
	loadimage(&picture[6], "6.jpg", K, K);
	loadimage(&picture[7], "7.jpg", K, K);
	loadimage(&picture[8], "8.jpg", K, K);
	loadimage(&picture[9], "9.jpg", K, K);
	
	loadimage(&win, "win.jpg", MapW * K, MapH * K);
}