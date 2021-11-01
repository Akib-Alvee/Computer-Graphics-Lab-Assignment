//Name: Md Akibul Islam Alvee
//Reg. No: 2017331049

#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>

using namespace std;

const int windowWidth = 1000, windowHeight = 1000;

struct point
{
    int x;
    int y;
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

void drawLine(point a, point b)
{
    if(a.x > b.x) swap(a, b);

    ///horizontal

    if(a.y == b.y)
    {
        for(int x = a.x; x <= b.x; x++)
        {
            drawPixel({x, a.y}, YELLOW);
        }
    }

    ///vertical

    else if(a.x == b.x)
    {
        if(a.y > b.y) swap(a, b);
        for(int y = a.y; y <= b.y; y++)
        {
            drawPixel({a.x, y}, YELLOW);
        }
    }

    else
    {
        double m = (double)(b.y-a.y)/(double)(b.x-a.x);
        double c = (double)a.y - m*(double)a.x;
        for(int x = a.x; x <= b.x; x++)
        {
            int y = round(m*(double)x + c);

            drawPixel({x, y}, YELLOW);
        }
    }
}

void drawPolygon(vector<point> points)
{
    int n = points.size();
    for(int i=0; i<n; i++)
    {
        drawLine(points[i], points[(i+1)%n]);
    }
}

void BoundaryFill(point currPixel, int boundaryColor, int fillColor)
{
    point pixel = convertPixel(currPixel);
    int currColor = getpixel(pixel.x, pixel.y);
    if(currColor == boundaryColor || currColor == fillColor)
    {
        return;
    }

    drawPixel(currPixel, fillColor);

    BoundaryFill({currPixel.x, currPixel.y+1}, boundaryColor, fillColor);
    BoundaryFill({currPixel.x, currPixel.y-1}, boundaryColor, fillColor);
    BoundaryFill({currPixel.x+1, currPixel.y}, boundaryColor, fillColor);
    BoundaryFill({currPixel.x-1, currPixel.y}, boundaryColor, fillColor);
}

void FloodFill(point currPixel, int oldcolor, int fillColor)
{
    point pixel = convertPixel(currPixel);
    int currColor = getpixel(pixel.x, pixel.y);
    if(currColor != oldcolor )
    {
        return;
    }

    drawPixel(currPixel, fillColor);

    FloodFill({currPixel.x, currPixel.y+1}, oldcolor, fillColor);
    FloodFill({currPixel.x, currPixel.y-1}, oldcolor, fillColor);
    FloodFill({currPixel.x+1, currPixel.y}, oldcolor, fillColor);
    FloodFill({currPixel.x-1, currPixel.y}, oldcolor, fillColor);

}

int main()
{
    initwindow(windowWidth,windowHeight);
    drawAxis();

    vector<point> poly;

    poly.push_back({10,10});
    poly.push_back({110,10});
    poly.push_back({110,90});
    poly.push_back({60,90});
    poly.push_back({60,140});
    poly.push_back({10,140});
    poly.push_back({10,10});

    drawPolygon(poly);

    vector<point> poly2;
    poly2.push_back({-10,-10});
    poly2.push_back({-110,-10});
    poly2.push_back({-110,-90});
    poly2.push_back({-60,-90});
    poly2.push_back({-60,-140});
    poly2.push_back({-10,-140});
    poly2.push_back({-10,-10});

    drawPolygon(poly2);

    BoundaryFill({30, 30}, YELLOW, RED);
    FloodFill({-30,-30}, BLACK, RED);

    getchar();
    return 0;
}
