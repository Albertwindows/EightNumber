#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
struct Point { int x, y; };
Point dis2[9] = { { 2,2 },{ 0,0 },{ 0,1 },{ 0,2 },{ 1,0 },{ 1,1 },{ 1,2 },{ 2,0 },{ 2,1 } };
Point dis1[9] = { { 1,1 },{ 0,0 },{ 0,1 },{ 0,2 },{ 1,2 },{ 2,2 },{ 2,1 },{ 2,0 },{ 1,0 } };
Point* dis = dis1;
const int sg[3][3] = { { 1,2,3 },{ 8,0,4 },{ 7,6,5 } };//目标值
const int maxn = 1000;
stack <int> path;
static const int col = 3;
static const int row = 3;
struct Label
{
	int index;
	int fn;
};
vector <Label> open, close;//use find() and distance() to get index of certain node
class Node {

public:
	int pn;
	int fn;
	int father;
	int index;//index in G
	int data[3][3];
	int dep;

	int x0, y0;
	//Dn 是当前节点的深度。
	int getDn() {
		return dep;
	}
	//Wn 是不考虑空格，错位的棋牌个数
	int getWn() {
		int cnt = 0;
		for (int i = 0; i<row; i++)
			for (int j = 0; j<col; j++) if (data[i][j] != sg[i][j]) { if (data[i][j] != 0)cnt++; }
		return cnt;
	}
	//改进后的w(n)->p(n) 变成了错位棋牌在不受阻拦的情况下，
	//移动到目标状态相应位置所需走步（移动次数）的总和

	int getPn()
	{
		int res = 0;
		for (int i = 0; i<row; i++) {
			for (int j = 0; j<col; j++) {
				int a = data[i][j];
				if (a == 0)
					continue;
				res += abs(dis[a].x - i) + abs(dis[a].y - j);
			}
		}
		return res;
	}

	inline int getFn()
	{
		return getDn() + getPn();
	}

	Node(int dd[][3], int index, int father, int dep) {
		for (int i = 0; i<row; i++) {
			for (int j = 0; j<col; j++) {
				data[i][j] = dd[i][j];
				if (data[i][j] == 0) {
					x0 = i; y0 = j;
				}
			}
		}
		this->index = index;
		this->father = father;
		this->dep = dep;
		this->fn = this->getFn();
		this->pn = this->getPn();
	}
	Node() {
		for (int i = 0; i<row; i++) {
			for (int j = 0; j<col; j++) {
				data[i][j] = 0;
			}
		}
	}

	void print() {
		for (int i = 0; i<row; i++) {
			for (int j = 0; j<col; j++) {
				printf("%d ", data[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
};
vector <Node> G;
int ig = 0;//Global index of G
bool isEqual(const int a[][3], const int b[][3]) {
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			if (a[i][j] != b[i][j])
				return false;
		}
	}
	return true;
}
void getPath(int s)
{
	Node* g = NULL;
	while (s != -1) {
		path.push(s);
		g = &G.at(s);
		s = g->father;
	}
}
void printPath()
{
	Node* n = NULL;
	while (!path.empty()) {
		n = &G.at(path.top());
		n->print();
		path.pop();
	}
}
void eval(int a[][3], int b[][3]) {
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++)
			a[i][j] = b[i][j];
	}
}
//向上 下 左 右
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
bool cmp(Label a, Label b) {
	if (a.fn == b.fn) return a.index<b.index;
	return (a.fn > b.fn);
}
bool isExpandable(int n[][row]) {
	for (size_t i = 0; i < G.size(); i++) {
		if (isEqual(n, G.at(i).data))
			return false;
	}
	return true;
}
int getReverse(const int data[][col])
{
	int res = 0;
	int t[row*col] = { 0 }; int k = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			t[k++] = data[i][j];
		}
	}
	for (int i = 0; i < k; i++) {
		if (t[i] == 0) continue;
		for (int j = 0; j < i; j++) {
			if (t[j] > t[i]) res++;
		}
	}
	return res;
}
int main() {
	//初始化 一些测试数据
	int init[3][3] = { { 2,8,3 },{ 1,0,4 },{ 7,6,5 } };
	int test1[3][3] = { { 1,0,3 },{ 7,2,4 },{ 6,8,5 } };
	int test2[3][3] = { { 3,6,5 },{ 1,7,8 },{ 4,0,2 } };//can't calculate it
	int test3[3][3] = { { 1,7,8 },{ 0,2,3 },{ 4,6,5 } };
	int test4[3][3] = { { 2,4,7 },{ 3,5,8 },{ 1,0,6 } };
	int test5[3][3] = { { 2,3,1 },{ 4,6,7 },{ 0,8,5 } };

	Node s0(test5, 0, -1, 0);
	G.push_back(s0);
	open.push_back({ s0.index,s0.getFn() });
	//判断是不是能得出结果
	if ((getReverse(s0.data) & 1) != (getReverse(sg) & 1)) {
		printf("NO ANSWER\n");
		return 0;
	}
	while (!open.empty()) {
		sort(open.begin(), open.end(), cmp);
		//get the number in the end, so sort in descending order
		Label X = open.back();
		int x = X.index;
		open.pop_back();
		close.push_back(X);

		if (G.at(x).getPn() == 0) {
			getPath(x);
			printf("一共 %d 步\n", path.size());
			printPath();
			break;
		}

		//if (!isExpandable(G.at(x)))
		//	continue;
		int x0 = G.at(x).x0;
		int y0 = G.at(x).y0;
		for (int i = 0; i <= 3; i++) {
			int tx = x0 + dx[i];
			int ty = y0 + dy[i];
			if (tx<0 || tx>2 || ty<0 || ty>2)
				continue;
			int t[3][3] = { 0 };
			eval(t, G.at(x).data);
			t[x0][y0] = t[tx][ty];
			t[tx][ty] = 0;

			if (isExpandable(t)) {
				Node ni(t, ++ig, G.at(x).index, G.at(x).dep + 1);
				G.push_back(ni);
				open.push_back({ ni.index,ni.getFn() });
			}
		}

	}
	system("pause");
	return 0;
}
