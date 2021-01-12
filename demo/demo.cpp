#include"Graph.h"
#include<conio.h>
#include<graphics.h>
using namespace std;
const int K = 40;
Graph test = Graph(10, 10, K);
void DrawGame(void);
int main()
{

	initgraph(640, 480);
	setorigin(K / 2, K / 2);
	test.readMap("wfy.txt");
	DrawGame();
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
			drawtext(c, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		}
	}
}