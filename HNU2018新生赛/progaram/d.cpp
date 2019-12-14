#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>
#include<map>
#define ll long long
using namespace std;
const int maxn=1e5+10;
ll a[maxn],b[maxn];
struct Point{
    ll x,y;
    Point(int _x=0,int _y=0){
        x=_x;y=_y;
    }
    void input(){scanf("%lld%lld",&x,&y);}
};
typedef Point Vector;
Vector operator - (const Point &p1,const Point &p2){
    return Point(p1.x-p2.x,p1.y-p2.y);
}
ll Cross(Vector v1,Vector v2){
    return v1.x*v2.y-v1.y*v2.x;
}
ll area(Point p1,Point p2,Point p3){
    return abs(Cross(p2-p1,p3-p1));
}
int main(){
    ll n,dandan;
    scanf("%lld",&n);
    Point p1,p2,p3;
    for(int i=0;i<n;i++){
        scanf("%lld",&a[i]);
        if(i==0)dandan=a[i];
        p1.input();
        p2.input();
        p3.input();
        b[i]=area(p1,p2,p3);
    }
    sort(a,a+n);
    sort(b,b+n);
    for(int i=0;i<n;i++)
    if(a[i]==dandan){
        printf("%lld\n",b[i]);return 0;
    }
    return 0;
}
