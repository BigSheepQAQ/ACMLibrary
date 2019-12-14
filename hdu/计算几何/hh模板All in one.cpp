#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<string>
#include<algorithm>
#define N 52000
#define M 250
#define INF 0xFFFFFFF
using namespace std;
const double eps = 1e-8;
const double inf = 10000;
const int maxP = 1100;
const double PI = acos(-1.0);

inline double sqr(double d) {
    return d * d;
}
inline int dcmp(double d) {
    return d < -eps ? -1 : d > eps;
}

struct Point {
    double x , y;
    Point() {
    }
    Point(const double &_x, const double &_y) :
        x(_x), y(_y) {
    }
    bool operator ==(const Point &p) const {
        return ( dcmp(x - p.x) == 0 && dcmp(y - p.y) == 0 );
    }
    bool operator <(const Point &p) const {
		return y + eps < p.y || 
		( y < p.y + eps && x + eps < p.x );
	}
    Point operator +(const Point &p) const {
        return Point(x + p.x, y + p.y);
    }
    Point operator -(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    Point operator *(const double &k) const {
        return Point(x * k, y * k);
    }
    Point operator /(const double &k) const {
        return Point(x / k, y / k);
    }
    double operator *(const Point &p) const {
        return x * p.y - y * p.x;
    }
    double operator /(const Point &p) const {
        return x * p.x + y * p.y;
    }
    double len2() {
        return x * x + y * y;
    }
    double len() {
        return sqrt(x * x + y * y);
    }
    Point scale(const double &k) {
        return dcmp(len()) ? ( *this ) * ( k / len() ) : ( *this );
    }
    Point turnLeft() {
        return Point(-y, x);
    }
    Point turnRight() {
        return Point(y, -x);
    }
    void input() {
        scanf("%lf%lf", &x, &y);
    }
    void output() {
        printf("%.2lf %.2lf\n", x + eps, y + eps);
    }

    double Distance(Point p) {
        return sqrt(sqr(p.x - x) + sqr(p.y - y));
    }

    Point rotate(const Point &p, double angle, double k = 1){
        Point vec = ( *this ) - p;
        double Cos(cos(angle) * k) , Sin(sin(angle) * k);
        return p + Point(vec.x * Cos - vec.y * Sin, vec.x * Sin + vec.y * Cos);
    }
};

struct Line {
    Point a , b;
    Line() {
    }
    Line(const Point &_a, const Point &_b) :
        a(_a), b(_b) {
    }
    Line(double c, double d, double e, double f) :
        a(Point(c, d)), b(Point(e, f)) {
    }
    double operator *(const Point &p) const {
        return ( b - a ) * ( p - a );
    }
    double operator /(const Point &p) const {
        return ( p - a ) / ( p - b );
    }
    void input() {
        a.input(), b.input();
    }
    void output() {
        a.output(), b.output();
    }
    double len() {
        return a.Distance(b);
    }
    bool parallel(Line v) {
        return !dcmp(( b - a ) * ( v.b - v.a ));
    }

    bool SegCrossSeg(const Line &v, Point &p) {
        double s1 = v * a , s2 = v * b;
        if ( dcmp(s2 - s1) == 0 ) return false;
        p = ( a * s2 - b * s1 ) / ( s2 - s1 );
        return ( dcmp(v / p) <= 0 && dcmp(( *this ) / p) <= 0 );
    }
    int SegCrossSeg(const Line &v) {
        int d1 = dcmp(( *this ) * v.a);
        int d2 = dcmp(( *this ) * v.b);
        int d3 = dcmp(v * a);
        int d4 = dcmp(v * b);
        if ( ( d1 ^ d2 ) == -2 && ( d3 ^ d4 ) == -2 ) return 2;
        return ( ( d1 == 0 && dcmp(( *this ) / v.a) <= 0 ) 
        || ( d2 == 0 && dcmp(( *this ) / v.b) <= 0 )
        || ( d3 == 0 && dcmp(v / a) <= 0 ) 
        || ( d4 == 0 && dcmp(v / b) <= 0 ) );
    }
    int LineCrossSeg(const Line &v) {
        int d1 = dcmp(( *this ) * v.a) , d2 = dcmp(( *this ) * v.b);
        if ( ( d1 ^ d2 ) == -2 ) return 2;
        return ( d1 == 0 || d2 == 0 );
    }
    int LineCrossLine(const Line &v) {
        if ( ( *this ).parallel(v) ) {
            return ( dcmp(v * a) == 0 );
        }
        return 2;
    }

    Point CrossPoint(const Line &v) {
        double s1 = v * a , s2 = v * b;
        return ( a * s2 - b * s1 ) / ( s2 - s1 );
    }

    double DisPointToSeg(Point p) {
        if ( a == b ) return a.Distance(p);
        Point q = p + ( a - b ).turnLeft();
        if ( ( ( p - a ) * ( q - a ) ) * ( ( p - b ) * ( q - b ) ) > 0 ) {
            return min(p.Distance(a), p.Distance(b));
        }
        return fabs(( *this ) * p) / a.Distance(b);
    }
    Point PointToSeg(Point p) {
        if ( a == b ) return a;
        Point q = p + ( a - b ).turnLeft();
        if ( ( ( p - a ) * ( q - a ) ) * ( ( p - b ) * ( q - b ) ) > 0 ) {
            return p.Distance(a) < p.Distance(b) ? a : b;
        }
        return CrossPoint(Line(p, q));
    }
    double DisPointToLine(const Point &p) {
        return fabs(( *this ) * p) / a.Distance(b);
    }
    Point PointToLine(const Point &p) {
        return CrossPoint(Line(p, p + ( a - b ).turnLeft()));
    }
    Point SymPoint(const Point &p) {
        return PointToLine(p) * 2 - p;
    }
    void Move(const double &d) {//向法线方向平移d
        Point t = ( b - a ).turnLeft().scale(d);
        a = a + t, b = b + t;
    }
};
//三角剖分
double areaTriangle(Point &a, Point &b, Point &c, Point d) {
    Point z(0, 0);
    Point p[3];
    int len = 0;
    Line AB(a, b) , CD(c, d) , ZA(z, a) , ZB(z, b) , ZC(z, c) , ZD(z, d);
    int ab = dcmp(a * b) , ac = dcmp(a * c) , ad = dcmp(a * d);
    int bc = dcmp(b * c) , bd = dcmp(b * d) , cd = dcmp(c * d);
    if ( ( ab == ac && bc == -ab ) || ( ac == 0 && dcmp(a / c) > 0 ) || ( bc == 0 && dcmp(b / c) > 0 ) ) {
        if ( ZC.SegCrossSeg(AB, p[len]) ) len ++;
        else p[len ++] = c;
    }
    if ( ( ab == ad && bd == -ab ) || ( ad == 0 && dcmp(a / d) > 0 ) || ( bd == 0 && dcmp(b / d) > 0 ) ) {
        if ( ZD.SegCrossSeg(AB, p[len]) ) len ++;
        else p[len ++] = d;
    }
    if ( ac == -cd && ad == cd ) {
        if ( ZA.SegCrossSeg(CD, p[len]) ) len ++;
        else p[len ++] = a;
    }
    if ( bc == -cd && bd == cd ) {
        if ( ZB.SegCrossSeg(CD, p[len]) ) len ++;
        else p[len ++] = b;
    }
    if ( AB.SegCrossSeg(CD, p[len]) ) len ++;
    if ( len == 3 ) return fabs(p[0] * p[2]) * 0.5 + fabs(p[1] * p[2]) * 0.5;
    if ( len == 2 ) return fabs(p[0] * p[1]) * 0.5;
    return 0;
}
struct Polygon {
    int n;
    Point p[maxP];
    void input() {
        for ( int i = 0 ; i < n ; i ++ )
            p[i].input();
    }
    void push(const Point &pp) {
        p[n ++] = pp;
    }
    void getConvex(Polygon &c) {
        sort(p, p + n);
        c.n = n;
        if ( n == 0 ) return;
        c.p[0] = p[0];
        if ( n == 1 ) return;
        c.p[1] = p[1];
        if ( n == 2 ) return;
        int &top = c.n;
        top = 1;
        for ( int i = 2 ; i < n ; i ++ ) {
            while ( top && dcmp(( c.p[top] - p[i] ) * ( c.p[top - 1] - p[i] )) >= 0 )
                top --;
            c.p[++ top] = p[i];
        }
        int temp = top;
        c.p[++ top] = p[n - 2];
        for ( int i = n - 3 ; i >= 0 ; i -- ) {
            while ( top != temp && dcmp(( c.p[top] - p[i] ) * ( c.p[top - 1] - p[i] )) >= 0 )
                top --;
            c.p[++ top] = p[i];
        }
    }
    bool isConvex() {
        bool s[3] = { false , false , false };
        p[n] = p[0], p[n + 1] = p[1];
        for ( int i = 0 ; i < n ; i ++ ) {
            s[dcmp(( p[i + 1] - p[i] ) * ( p[i + 2] - p[i] )) + 1] = true;
            if ( s[0] && s[2] ) return false;
        }
        return true;
    }
    bool InsertConvex(const Point &P) {
        bool s[3] = { false , false , false };
        p[n] = p[0];
        for ( int i = 0 ; i < n ; i ++ ) {
            s[dcmp(( p[i + 1] - P ) * ( p[i] - P )) + 1] = true;
            if ( s[0] && s[2] ) return false;
            if ( s[1] ) return true;//边上算
        }
        return true;
    }

    int PointInsert(const Point &P) {
        p[n] = p[0];
        for ( int i = 0 ; i < n ; i ++ ) {
            if ( dcmp(( p[i] - P ) * ( p[i + 1] - P )) == 0 && dcmp(( P - p[i] ) / ( P - p[i + 1] )) <= 0 ) {
                if ( p[i] == P || p[i + 1] == P ) return 3;
                return 2;
            }
        }
        int cnt = 0;
        p[n] = p[0];
        for ( int i = 0 ; i < n ; i ++ ) {
            int k = dcmp(( p[i] - P ) * ( p[i + 1] - P ));
            int u = dcmp(p[i].y - P.y);
            int v = dcmp(p[i + 1].y - P.y);
            if ( k > 0 && u < 0 && v >= 0 ) cnt ++;
            if ( k < 0 && v < 0 && u >= 0 ) cnt --;
        }
        return ( cnt != 0 );
    }

    double CalcCircumference() {
        if ( n == 1 ) return 0;
        double sum = p[0].Distance(p[n - 1]);
        for ( int i = 1 ; i < n ; i ++ )
            sum += p[i].Distance(p[i - 1]);
        return sum;
    }
    double CalcArea() {
        double sum = 0;
        for ( int i = 1 ; i < n - 1 ; i ++ )
            sum += ( p[i] - p[0] ) * ( p[i + 1] - p[0] );
        return sum * 0.5;
    }
    Point CalcBary() {
        Point ret(0, 0);
        double area = 0;
        p[n] = p[0];
        for ( int i = 0 ; i < n ; i ++ ) {
            double temp = p[i] * p[i + 1];
            if ( dcmp(temp) == 0 ) continue;
            area += temp;
            ret = ret + ( p[i] + p[i + 1] ) * ( temp / 3 );
        }
        if ( dcmp(area) ) return ret / area;
        return ret;
    }
    double CalcArecom(Polygon pb){
        p[n]=p[0];
        pb.p[pb.n]=pb.p[0];
        double sum=fabs(CalcArea())+fabs(pb.CalcArea());
        for(int i=0;i<n;i++){
            int d1=dcmp(p[i]*p[i+1]);
            if(d1==0) continue;
            for(int j=0; j < pb.n; j++){
                int d2=dcmp(pb.p[j]*pb.p[j+1]);
                if(d2==0) continue;
                sum -= d1 * d2 * areaTriangle(p[i], p[i + 1], pb.p[j], pb.p[j + 1]);
            }
        }
        return sum;
    }
};
struct HalfPlane: public Line {
    double angle;
    HalfPlane() {
    }
    HalfPlane(const Point &_a, const Point& _b) {
        a = _a, b = _b, angle = atan2(b.y - a.y, b.x - a.x);
    }
    bool operator <(const HalfPlane &b) const {
        return angle < b.angle;
    }
};

struct HalfPlanes {
    int n;
    HalfPlane hp[maxP];

    Point p[maxP];
    int que[maxP];
    int st , ed;
    void push(const HalfPlane &temp) {
        hp[n ++] = temp;
    }
    void unique() {
        int m = 1;
        for ( int i = 1 ; i < n ; i ++ )
            if ( dcmp(hp[i].angle - hp[i - 1].angle) ) hp[m ++] = hp[i];
            else if ( dcmp(hp[m - 1] * hp[i].a) > 0 ) hp[m - 1] = hp[i];
        n = m;
    }
    bool HalfPlaneInsert() {
        sort(hp, hp + n);
        unique();
        que[st = 0] = 0, que[ed = 1] = 1;
        p[1] = hp[0].CrossPoint(hp[1]);
        for ( int i = 2 ; i < n ; i ++ ) {
            while ( st < ed && dcmp(hp[i] * p[ed]) < 0 )
                ed --;
            while ( st < ed && dcmp(hp[i] * p[st + 1]) < 0 )
                st ++;
            que[++ ed] = i;
            if ( hp[i].parallel(hp[que[ed - 1]]) ) return false;//平行,则无解
            p[ed] = hp[i].CrossPoint(hp[que[ed - 1]]);
        }
        while ( st < ed && dcmp(hp[que[st]] * p[ed]) < 0 )
            ed --;
        while ( st < ed && dcmp(hp[que[ed]] * p[st + 1]) < 0 )
            st ++;
        if ( st + 1 >= ed ) return false;
        return true;
    }
    void getConvex(Polygon &convex) {
        p[st] = hp[que[st]].CrossPoint(hp[que[ed]]);
        convex.n = ed - st + 1;
        for ( int j = st , i = 0 ; j <= ed ; i ++, j ++ ) {
            convex.p[i] = p[j];
        }
    }
};
struct Circle {
    Point c;
    double r;
    Circle() {
    }
    Circle(const Point &a, const double &b) :
        c(a), r(b) {
    }
    Circle(const double &x, const double &y, const double &b) :
        c(Point(x, y)), r(b) {
    }
    bool operator <(const Circle C) const {
        return r < C.r;
    }
    bool operator ==(const Circle C) const {
        if(c==C.c&&fabs(r-C.r)<eps)
        return 1;
        return 0;
    }
    bool CrossCircle(const Circle &C) {
        double d = c.Distance(C.c);
        return dcmp(r + C.r - d) >= 0 && dcmp(d - fabs(r - C.r)) >= 0;
    }
    void CrossCirclePoint(const Circle &C, Point &p1, Point &p2) {//交点按逆时针排
        double d = c.Distance(C.c);
        double d1 = ( sqr(d) + sqr(r) - sqr(C.r) ) / ( 2 * d );
        double h = sqrt(sqr(r) - sqr(d1));
        Point p = c + ( C.c - c ).scale(d1);
        Point vec = ( C.c - c ).turnLeft().scale(h);
        p1 = p - vec, p2 = p + vec;
    }
    bool CrossLine(Line l) {
        return dcmp(l.DisPointToLine(c) - r) <= 0;
    }
    void CrossLinePoint(Line l, Point &p1, Point &p2) {//交点按向量方向排
        Point p = c + ( l.a - l.b ).turnLeft();
        p = l.CrossPoint(Line(c, p));
        double t = sqrt(sqr(r) - sqr(p.Distance(c))) / l.len();
        Point vec = ( l.b - l.a ) * t;
        p1 = p - vec, p2 = p + vec;
    }
    void TangencyPoint(Point p, Point &p1, Point &p2) {
        Point q = c + ( p - c ).scale(r);
        double d = p.Distance(c);
        double d1 = sqrt(sqr(d) - sqr(r));
        Point vec = q - c;
        double COS(r / d) , SIN(d1 / d);
        p1 = c + Point(vec.x * COS - vec.y * SIN, vec.y * COS + vec.x * SIN);
        p2 = c + Point(vec.x * COS + vec.y * SIN, vec.y * COS - vec.x * SIN);
    }
    double areaCircle(const Circle &C) {
        double d = c.Distance(C.c);
        if ( dcmp(r + C.r - d) <= 0 ) return 0;
        if ( dcmp(r + d - C.r) <= 0 ) return PI * r * r;
        if ( dcmp(C.r + d - r) <= 0 ) return PI * C.r * C.r;
        double d1 = ( sqr(d) + sqr(r) - sqr(C.r) ) / ( 2 * d );
        double d2 = ( sqr(d) + sqr(C.r) - sqr(r) ) / ( 2 * d );
        double h = sqrt(sqr(r) - sqr(d1));
        return acos(d1 / r) * r * r - h * d1 + acos(d2 / C.r) * C.r * C.r - h * d2;
    }
    double arc(const Point &a, const Point &b) {//a到b的有向弧
        double cp = ( a - c ) * ( b - c );
        double ret = atan2(fabs(cp), ( a - c ) / ( b - c ));
        return cp > -eps ? ret : - ret;
    }
    double areaSector(Point a, Point b) {//a到b的有向扇形面积
        return arc(a, b) * r * r * 0.5;
    }
    double areaBow(Point a, Point b) {//a到b的有向弓形面积
        return areaSector(a, b) - ( a - c ) * ( b - c ) * 0.5;
    }
    double areaTriangle(Point a, Point b) {//三角形另一个点是圆心，且圆心是原点
        Point p1 , p2;
        double rr = r * r;
        if ( a.len2() > rr ) {
            if ( b.len2() > rr ) {
                if ( CrossLine(Line(a, b)) ) {
                    CrossLinePoint(Line(a, b), p1, p2);
                    if ( dcmp(( p1 - a ) / ( p1 - b )) < 0 ) return areaSector(a, p1) + ( p1 * p2 ) * 0.5 + areaSector(p2, b);
                    else return areaSector(a, b);
                } else {
                    return areaSector(a, b);
                }
            } else {
                CrossLinePoint(Line(a, b), p1, p2);
//                a.output();b.output();
//                p1.output();p2.output();
//                printf("%lf..%lf  %lf\n",areaSector(a,p1),p1*b*0.5,arc(a,p1));
                return areaSector(a, p1) + ( p1 * b ) * 0.5;
            }
        } else if ( b.len2() > rr ) {
            CrossLinePoint(Line(a, b), p1, p2);
            return ( a * p2 ) * 0.5 + areaSector(p2, b);
        } else {
            return ( a * b ) * 0.5;
        }
    }
};



double r;

double f3(double p , double q) {
    double a, b, c;
    if ( p < 0 ) return -f3( -p , q);
    if ( q < 0 ) return -f3(p , -q);
    if ( p * p + q * q < r * r ) return p * q / 2;
    a = acos(q / sqrt(p * p + q * q));
    b = 0;
    c = 0;
    if ( q < r ) {
        b = acos(q / r);
        c = sqrt(r * r - q * q);
    }
    return ( ( a - b ) * r * r + q * c ) / 2;
}

double f2(double xa , double ya , double xb , double yb) {
    double co, si, xc, yc, dd;
    xc = xb - xa;
    yc = yb - ya;
    dd = sqrt(xc * xc + yc * yc);
    co = xc / dd;
    si = yc / dd;
    return f3(xa * co + ya * si , ya * co - xa * si) - f3(xb * co + yb * si , yb * co - xb * si);
}
//多圆面积
const int maxC = 333;
struct Circles {
    Circle cc[ maxC ];
    int n;
    Circles() {
        n = 0;
    }
    void push(const Circle &c) {
        cc[ n ++ ] = c;
    }
    void clear() {
        n = 0;
    }
    struct Polar {
        Point p;
        double angle;
        int dir;
        Polar() {
        }
        Polar(const Point &a, const double &b, const int &c) :
            p(a), angle(b), dir(c) {
        }
        bool operator <(Polar a) const {
            return angle + eps < a.angle || ( angle < a.angle + eps && dir > a.dir );
        }
    } Po[ maxC * 2 ];

    void unique() {
        sort(cc, cc + n);
        int m = 0;
        for ( int i = 0 ; i < n ; i ++ )
            if ( i == 0 || !( cc[ i ] == cc[ i - 1 ] ) ) cc[ m ++ ] = cc[ i ];
        n = m;
    }
    bool interPatch() {//inter speedup ... If return true , then area = 0
        sort(cc, cc + n);
        int m = 0;
        for ( int i = 0 ; i < n ; i ++ ) {
            bool flag = true;
            for ( int j = 0 ; j < i ; j ++ ) {
                double dis = cc[ i ].c.Distance(cc[ j ].c);
                if ( dis < eps || dis + cc[ j ].r < cc[ i ].r + eps ) flag = false;
                if ( dis > cc[ i ].r + cc[ j ].r + eps ) return true;
            }
            if ( flag ) cc[ m ++ ] = cc[ i ];
        }
        m = n;
        return false;
    }
    void unionPatch() {//union speedup
        sort(cc, cc + n);
        int m = 0;
        for ( int i = 0 ; i < n ; i ++ ) {
            bool flag = true;
            for ( int j = i + 1 ; j < n ; j ++ ) {
                double dis = cc[ i ].c.Distance(cc[ j ].c);
                if ( dis < eps || cc[ i ].r + dis < cc[ j ].r + eps ) flag = false;
            }
            if ( flag ) cc[ m ++ ] = cc[ i ];
        }
        n = m;
    }
    double commonArea(int Time = 1) {//Time : 1 ~ n , default Time = 1
        unionPatch();
        double area = 0;
        for ( int i = 0 ; i < n ; i ++ ) {
            int m = 0 , cnt = 1;
            for ( int j = 0 ; j < n ; j ++ ) {
                if ( i == j ) continue;
                double dis = cc[ i ].c.Distance(cc[ j ].c);
                if ( cc[ i ].r + cc[ j ].r < dis + eps ) continue;
                if ( cc[ j ].r + dis < cc[ i ].r + eps ) continue;
                if ( cc[ i ].r + dis < cc[ j ].r + eps && ++ cnt ) continue;
                Point p1 , p2;
                cc[ i ].CrossCirclePoint(cc[ j ], p1, p2);
                double a1 = atan2(p1.y - cc[ i ].c.y, p1.x - cc[ i ].c.x);
                double a2 = atan2(p2.y - cc[ i ].c.y, p2.x - cc[ i ].c.x);

                if ( a1 > a2 + eps ) cnt ++;
                Po[ m ++ ] = Polar(p1, a1, 1);
                Po[ m ++ ] = Polar(p2, a2, -1);
            }
            if ( m == 0 && cnt == Time ) area += PI * cc[ i ].r * cc[ i ].r;
            sort(Po, Po + m);
            for ( int j = 0 ; j < m ; cnt += Po[ j ].dir, j ++ ) {
                if ( cnt == Time ) {
                    int k = j ? j - 1 : m - 1;
                    area += Po[ k ].p * Po[ j ].p / 2;
                    area += cc[ i ].areaBow(Po[ k ].p, Po[ j ].p);
                }
            }
        }
        return area;
    }
};