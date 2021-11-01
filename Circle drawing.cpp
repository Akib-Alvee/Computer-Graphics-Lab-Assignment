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
    delay(0.5);
    p = convertPixel(p);
    putpixel(p.x, p.y, color);
}


void BressenhamCircle(point a, int r)
{
    int x1 = 0, y1 = r;

    int q = 3  -  (2 * r);

    while(x1 <= y1)
    {
        drawPixel({a.x + x1, a.y + y1}, GREEN);
        drawPixel({a.x - x1, a.y + y1}, GREEN);
        drawPixel({a.x + x1, a.y - y1}, GREEN);
        drawPixel({a.x - x1, a.y - y1}, GREEN);
        drawPixel({a.x + y1, a.y + x1}, GREEN);
        drawPixel({a.x + y1, a.y - x1}, GREEN);
        drawPixel({a.x - y1, a.y + x1}, GREEN);
        drawPixel({a.x - y1, a.y - x1}, GREEN);

        x1++;
        if(q<0)
            q=q + 4*(x1) + 6;
        else
        {
            q=q + 4*(x1 - y1) + 10;
            y1=y1 - 1;
        }
    }
}


void MidPointCircle(point a, int r)
{
    int x1=0, y1=r, q;
    drawPixel ({a.x, a.y+r}, YELLOW);
    drawPixel ({a.x, a.y-r}, YELLOW);
    drawPixel ({a.x-r, a.y}, YELLOW);
    drawPixel ({a.x+r, a.y}, YELLOW);
    q=(5/4)-r;
    while (x1<=y1)
    {
        drawPixel ({a.x+x1, a.y+y1}, YELLOW);
        drawPixel ({a.x-x1, a.y+y1}, YELLOW);
        drawPixel ({a.x+x1, a.y-y1}, YELLOW);
        drawPixel ({a.x-x1, a.y-y1}, YELLOW);
        drawPixel ({a.x+y1, a.y+x1}, YELLOW);
        drawPixel ({a.x+y1, a.y-x1}, YELLOW);
        drawPixel ({a.x-y1, a.y+x1}, YELLOW);
        drawPixel ({a.x-y1, a.y-x1}, YELLOW);
        if(q<0)
            q+= (2*x1)+3;
        else
        {
            q+=(2*(x1-y1))+5;
            y1--;
        }
        x1++;
    }
}
int main()
{
    initwindow(windowWidth,windowHeight);
    drawAxis();

    BressenhamCircle({0,0},250);
    MidPointCircle({100,200},250);

    getchar();
    return 0;
}

