//Name: Md Akibul Islam Alvee
//Reg. No: 2017331049

#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>

using namespace std;

const int windowWidth = 1000, windowHeight = 1000;

struct point
{
    double x,y;

    point(){}
    point(double a,double b)
    {
        x=a;y=b;
    }

    bool operator < (const point & p) const
    {
        return x < p.x;
    }
};


struct Edge{

    double y_min,y_max, x_with_y_min, m_inv;
    Edge(){};
    Edge(double a , double b, double c , double d)
    {
        y_min=a;
        y_max=b;
        x_with_y_min=c;
        m_inv=d;
    }
    bool operator < (const Edge &p) const
    {
        return y_min<p.y_min;
    }

};

point convertPixel (point p)
{
    p.x += windowWidth/2;
    p.y = -p.y;
    p.y += windowHeight/2;

    return p;

}


void drawAxis()
{
    for (int i=0; i<windowHeight; i++)
        putpixel(windowWidth/2,i,WHITE);

    for (int i=0; i<windowWidth; i++)
        putpixel(i,windowHeight/2,WHITE);
}

void drawPixel(point p, int color)
{
    delay(0.1);
    p = convertPixel(p);
    putpixel(p.x, p.y, color);
}

void drawLine(point a, point b,int color)
{
    if(a.x > b.x) swap(a, b);

    ///horizontal

    if(a.y == b.y)
    {
        if(a.x>b.x) swap(a,b);
        for(int x = a.x; x <= b.x; x++)
        {
            drawPixel({x, a.y}, color);
        }
    }

    ///vertical

    else if(a.x == b.x)
    {
        if(a.y > b.y) swap(a, b);
        for(int y = a.y; y <= b.y; y++)
        {
            drawPixel(point{a.x, y}, color);
        }
    }

    else
    {
        double m = (double)(b.y-a.y)/(double)(b.x-a.x);
        double m_inv= 1.0/m;

        if(fabs(m)<=1.0)
        {
            if(a.x>b.x) swap(a,b);
            while(a.x<=b.x)
            {
                drawPixel(a,color);
                a.x+=1;
                a.y+=m;
            }

        }
        else{
            if(a.y>b.y) swap(a,b);
            while(a.y<=b.y)
            {
                drawPixel(a,color);
                a.x+=m_inv;
                a.y+=1;
            }
        }
    }
}

void drawPolygon(vector<point> points,int color)
{
    int n = points.size();
    for(int i=0; i<n; i++)
    {

        drawLine(points[i], points[(i+1)%n],color);
    }
}

void scanLine(vector<point> points,int color)
{
    vector<Edge> edges;

    int n=points.size();
    double st=1e15 , en =-1e15 ;

    unordered_map<double,int>mp;


    for(int i=0;i<n;i++)
    {
        point a =points[i];
        point b =points[(i+1)%n];
        if(a.y==b.y) continue;

        Edge temp;
        temp.y_min=min(a.y,b.y);
        temp.y_max=max(a.y,b.y);
        temp.x_with_y_min=a.y < b.y ? a.x : b.x;
        temp.m_inv=(b.x-a.x) / (b.y -a.y);

        st = min(st,temp.y_min);
        en = max(en,temp.y_max);

        mp[temp.y_min] =1;

        edges.push_back(temp);
    }

    n=edges.size();
    sort(edges.begin(),edges.end());

    for(int i=0;i<n;i++)
    {
        if(mp[edges[i].y_max]) edges[i].y_max--;
    }

    /// loop on y
    for(double y=st;y<=en;y++)
    {
        vector<point> int_points;
        for(int i=0;i<n;i++)
        {
            if(y>=edges[i].y_min && y<=edges[i].y_max)
            {
                point temp;
                temp.x=edges[i].x_with_y_min;
                temp.y=y;
                edges[i].x_with_y_min+=edges[i].m_inv;
                int_points.push_back(temp);
            }
        }

        sort(int_points.begin(),int_points.end());
        for(int i=0;i<int_points.size()-1;i+=2)
        {
            drawLine(int_points[i],int_points[i+1],RED);
        }
    }
}

int main()
{
    initwindow(windowWidth,windowHeight);
    drawAxis();

    vector<point> poly;

    poly.push_back({100,-50});
    poly.push_back({200,50});
    poly.push_back({50,150});
    poly.push_back({-100,150});
    poly.push_back({-100,-50});

    drawPolygon(poly,RED);
    scanLine(poly,RED);

    getchar();
    return 0;
}
