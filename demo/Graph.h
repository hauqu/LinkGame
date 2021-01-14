#include<vector>
#include<string>
#include<fstream>

using namespace std;

/*

对于一个外部接口来说，给定两点需要判定是否能消除。


*/
class node
{
public:
	int d;// 0代表无
	int x;
	int y;
	node(int data, int X, int Y)
		:d(data),
		x(X),
		y(Y)
	{

	}
	node() :
		d(0),
		x(0),
		y(0)
	{

	}

};
class Graph
{
public:

	vector<vector<node>>g;
	/*
	00 10 20 30 40 ** n0
	01 11 21 31 41 ** n1
	** ** ** ** ** ** **
	0n 1n 2n 3n 4n ** nn
	*/
	Graph(int w, int h, int k);
	bool readMap(string name);
	void creatMap(int mx,int K);
	bool search_direct(int x1, int y1, int x2, int y2);//直接连接
	bool search_vertical(int x1, int y1, int x2, int y2);//竖直无障碍
	bool search_horizontal(int x1, int y1, int x2, int y2);//水平无障碍
	vector<node> search_one_inflection(int x1, int y1, int x2, int y2);//一拐点
	vector<node> search_two_inflection(int x1, int y1, int x2, int y2);//两拐点

	bool remove(int x1, int y1, int x2, int y2, vector<node>& t);
private:
	int max(int a, int b)
	{
		if (a > b)return a;
		else return b;
	}
	int min(int a, int b)
	{
		if (a < b)return a;
		else return b;
	}
};
Graph::Graph(int w, int h, int k)
{
	g.resize(w);
	for (int i = 0; i < w; i++)
	{
		g[i].resize(h);
	}
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			g[i][j] = node(0, i * k, j * k);
		}
	}
}


bool Graph::readMap(string name)
{
	int w = g.size();
	int h = g[0].size();
	ifstream file(name, ios::in);
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			char c = file.get();
			if (c == '\n')
			{
				j--;
				continue;
			}
			g[j][i].d = c - '0';
		}
	}
	file.close();
	return true;
}




bool Graph::search_direct(int x1, int y1, int x2, int y2)
{
	//直接相邻
	if (x1 == x2)
	{
		if (y1 == y2 + 1 || y1 == y2 - 1)
		{
			if (g[x1][y1].d == g[x2][y2].d)
			{
				return true;
			}
		}
	}
	else if (y1 == y2)
	{
		if (x1 == x2 + 1 || x1 == x2 - 1)
		{
			if (g[x1][y1].d == g[x2][y2].d)
			{
				return true;
			}
		}
	}

	return false;


}

bool Graph::search_vertical(int x1, int y1, int x2, int y2)
{

	if (x1 == x2)
	{
		if (y1 > y2)
		{
			for (int i = y2 + 1; i < y1; i++)
			{
				if (g[x1][i].d != 0) {
					return false;
				}
			}
		}
		else if (y1 < y2)
		{
			for (int i = y1 + 1; i < y2; i++)
			{
				if (g[x1][i].d != 0) {
					return false;
				}
			}
		}
	}
	else return false;
	return true;
}


bool Graph::search_horizontal(int x1, int y1, int x2, int y2)
{
	if (y1 == y2)
	{
		if (x1 > x2)
		{
			for (int i = x2 + 1; i < x1; i++)
			{
				if (g[i][y1].d != 0)
					return  false;
			}

		}
		else if (x1 < x2)
		{
			for (int i = x1 + 1; i < x2; i++)
			{
				if (g[i][y1].d != 0)
					return false;
			}
		}
	}
	else  return false;
	return true;
}

vector<node>Graph::search_one_inflection(int x1, int y1, int x2, int y2)
{

	vector<node>t;
	node c1 = g[x1][y2];
	node c2 = g[x2][y1];
	if (c1.d == 0)
	{
		if (search_vertical(x1, y2, x1, y1) == true)
		{
			if (search_horizontal(x1, y2, x2, y2) == true)
			{
				t.push_back(c1);
				return t;
			}
		}
	}
	else if (c2.d == 0)
	{
		if (search_horizontal(x2, y1, x1, y1) == true)
		{
			if (search_vertical(x1, y2, x2, y2) == true)
			{
				t.push_back(c2);
				return t;
			}
		}
	}

	return t;
}

vector<node> Graph::search_two_inflection(int x1, int y1, int x2, int y2)
{
	//两个拐点
	//找到一条直线使得 目标点能够线性连接该直线
	//一个拐点可以看做直线一端与目标点重合
	vector<node>t;
	node c1;
	node c2;
	int xl = min(x1, x2);
	int xh = max(x1, x2);

	int gw = g.size();
	int gh = g[0].size();

	//寻找竖直线 
	int x=0;
	for ( x = 0; x < gw; x++)
	{
		c1 = g[x][y1];
		c2 = g[x][y2];
		if (c1.d == 0&&c2.d==0)
		{
			if (search_horizontal(x, y1, x1, y1))
			{
				if (search_horizontal(x, y2, x2, y2))
				{
					if (search_vertical(x, y1, x, y2))
					{
						t.push_back(g[x1][y1]);
						t.push_back(c1);
						t.push_back(c2);
						t.push_back(g[x2][y2]);
						return t;
					}
				}
			}
		}
	}
	int y = 0;

	for ( y = 0; y < gh; y++)
	{
		c1 = g[x2][y];
		c2 = g[x1][y];
		if (c1.d == 0 && c2.d == 0)
		{
			if (search_vertical(x2,y,x2,y2))
			{
				if (search_vertical(x1, y, x1, y1))
				{
					if(search_horizontal(x2,y,x1,y))
					{
						t.push_back(g[x1][y1]);
						t.push_back(c1);
						t.push_back(c2);
						t.push_back(g[x2][y2]);
						return t;
					}
				}
			}
		}
	}


	
	return t;

}



bool Graph::remove(int x1, int y1, int x2, int y2, vector<node>& t)
{
	if (g[x1][y1].d != g[x2][y2].d) return false;
	if (g[x1][y1].d ==0|| g[x2][y2].d==0) return false;
	if (x1 == x2 && y1 == y2) return false;

	if (search_horizontal(x1, y1, x2, y2) == true ||
		search_vertical(x1, y1, x2, y2) == true)
	{
		t.push_back(g[x1][y1]);
		t.push_back(g[x2][y2]);

		return true;
	}

	t = search_one_inflection(x1, y1, x2, y2);
	if (t.empty() != true)
	{
		node temp = t.back();
		t.clear();
		t.push_back(g[x1][y1]);
		t.push_back(temp);
		t.push_back(g[x2][y2]);

		return true;
	}
	t.clear();
	t = search_two_inflection(x1, y1, x2, y2);
	if (t.empty())
	{
		return false;
	}
	else {


		return true;
	}

	return false;
}

inline void Graph::creatMap(int mx,int K)
{
	int w = g.size();
	int h = g[0].size();
	
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			g[i][j].d = rand() % mx;
			g[i][j].x = i * K;
			g[i][j].y = j * K;
		}
	}
	
	
}