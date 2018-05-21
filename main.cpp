#include <iostream>
#include <stdio.h>

using namespace std;
struct Point{int x,y;};
//坐标是从0开始的
Point dis[9]={{1,1},{0,0},{0,1},{0,2},{1,2},{2,2},{2,1},{2,0},{1,0}};
class Note{


	int h,w;
	static const int len=3;
	int d[3][3];
	const int st[3][3]={{1,2,3},{8,0,4},{7,6,5}};
	static int dn;
//f(n)=d(n)+w(n)

public:
    //Dn 是当前节点的深度。

    int getDn(){
        return dn;
    }
    int getWn(){
        int cnt=0;
        for(int i=0;i<len;i++)
			for (int j=0;j<len;j++) if (d[i][j]!=st[i][j]){cnt++;}
        return cnt;
    }
    //改进后的w(n)->p(n 变成了错位棋牌在不受阻拦的情况下，
    //移动到目标状态相应位置所需走步（移动次数）的总和

    int getPn()
    {

    }


    Note(const int dd[3][3]){
        for(int i=0;i<len;i++){
			for (int j=0;j<len;j++){
				d[i][j]=dd[i][j];
			}
		}
    }
    Note(int len1=3,int len2=3){
	    h=len1;w=len2;
		for(int i=0;i<h;i++){
			for (int j=0;j<w;j++){
				d[i][j]=0;
			}
		}
	}
    void print(){
	    for(int i=0;i<h;i++){
			for (int j=0;j<w;j++){
				printf("%d ",d[i][j]);
			}
			printf("\n");
		}
	}
};
int main(){
	Note n;
	n.print();
	cout<<n.getWn()<<endl;
	return 0;
}
