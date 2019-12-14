#include<iostream>
#include<queue>
using namespace std;
const int maxn=110;
int mp[maxn][maxn],aimx,aimy,n,m;
int dir[4][2]={1,0,0,1,-1,0,0,-1};
struct node{
    int x,y,s;
    node(int _x=0,int _y=0,int _s=0){
        x=_x;y=_y;s=_s;
    }
}beg,in,out;
int bfs(){
    queue<node>Q;Q.push(node(1,1,0));
    while(!Q.empty()){
        out=Q.front();Q.pop();
        for(int i=0;i<4;i++){
            in.x=out.x+dir[i][0];
            in.y=out.y+dir[i][1];
            in.s=out.s+1;
            if(in.x<1||in.x>n||in.y<1||in.y>m)continue;
            if(mp[in.x][in.y])continue;mp[in.x][in.y]=1;
            if(in.x==aimx&&in.y==aimy)return in.s;
            Q.push(in);
        }
    }
    return -1;
}
int main(){
    cin>>n>>m>>aimx>>aimy;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>mp[i][j];
    cout<<bfs()<<endl;
    return 0;
}