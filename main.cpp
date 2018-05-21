#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
using namespace std;
struct Point{int x,y;};
//坐标是从0开始的
Point dis[9]={{1,1},{0,0},{0,1},{0,2},{1,2},{2,2},{2,1},{2,0},{1,0}};
//st储存的是标准的状态值或者目标值
const int st[3][3]={{1,2,3},{8,0,4},{7,6,5}};
class Note{
	static const int len=3;
	int d[3][3];
	static int dn;
	int father;
	class Note * next[4];

public:
    //Dn 是当前节点的深度。

    int getDn(){
        return dn;
    }
	//Wn 是不考虑空格，错位的棋牌个数
    int getWn(){
        int cnt=0;
        for(int i=0;i<len;i++)
			for (int j=0;j<len;j++) if (d[i][j]!=st[i][j] ){ if (d[i][j]!=0)cnt++;}
        return cnt;
    }
    //改进后的w(n)->p(n) 变成了错位棋牌在不受阻拦的情况下，
    //移动到目标状态相应位置所需走步（移动次数）的总和

    int getPn()
    {
		int res=0;
		for(int i=0;i<len;i++){
			for (int j=0;j<len;j++){
				int a=d[i][j];
				if (a==0)
					continue;
				res+=abs(dis[a].x-i)+abs(dis[a].y-j);
			}
		}
		return res;
    }

	int getFn()
	{
		return getDn()+getWn();
		//return getDn()+getPn();
	}

    Note(int dd[][3]){
        for(int i=0;i<len;i++){
			for (int j=0;j<len;j++){
				d[i][j]=dd[i][j];
			}
		}
    }
    Note(){
		for(int i=0;i<len;i++){
			for (int j=0;j<len;j++){
				d[i][j]=0;
			}
		}
	}
    void print(){
	    for(int i=0;i<len;i++){
			for (int j=0;j<len;j++){
				printf("%d ",d[i][j]);
			}
			printf("\n");
		}
	}
};
void nextFloor()
{

}
int main(){
	int init[3][3]={{1,0,3},{7,2,4},{6,5,8}};
	int init1[3][3]={{3,6,5},{1,7,8},{4,0,2}};
	Note n(init1);
	Note nn[100];
	n.print();
	cout<<n.getWn()<<endl;
	cout<<n.getPn()<<endl;
	return 0;
}
