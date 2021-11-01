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
    delay(10);
    p = convertPixel(p);
    putpixel(p.x, p.y, color);
}

void BressenhamLine(point a, point b)
{

    int x0=a.x,y0=a.y,x1=b.x,y1=b.y;


    int dx = x1-x0;
    int dy = y1-y0;
    double slope = dy/dx;
    int p=0;
    //cout<<slope<<"    "<<dx<<"    "<<dy<<endl;

    if(slope >=0 && slope <= 1)
    {
        /*
        if(x0>x1)
        {
            swap(x0,x1);
            swap(y0,y1);
        }
        */
        p=2*dy-dx;
        //cout<<"here I am"<<endl;
        while(x0!=x1)
        {
            drawPixel({x0,y0},YELLOW);
            x0++;
            if(p<0)
            {
                p+=2*dy;
            }
            else
            {
                p+=2*dy-2*dx;
                if(slope >= -1 && slope <0)
                    y0--;
                else
                    y0++;
            }
        }
    }
    else
    {
        p = 2*dx-dy;
        //cout<<p<<"  hello I am here"<<endl;
        /*
        if(y0>y1)
        {
            swap(x0,x1);
            swap(y0,y1);
        }
        */
        while(y0!=y1)
        {
            drawPixel({x0,y0},YELLOW);
            if(slope>1)
                y0++;
            else
                y0--;
            if(p<0)
            {
                p+=2*dx;
            }
            else
            {
                p+=2*dx-2*dy;
                //cout<<p<<endl;
                x0++;

            }
        }
    }

}


void DDA(point a,point b)
{
    int x0=a.x,y0=a.y,x1=b.x,y1=b.y;
    double dx = x1-x0;
    double dy = y1-y0;

    float steps = max(abs(dx),abs(dy));

    float Xinc=dx/ steps;
    float Yinc=dy/ steps;

    float X=x0,Y=y0;

    for(int i=0; i<steps; i++)
    {
        drawPixel({X,Y},GREEN);
        X+=Xinc;
        Y+=Yinc;
    }
}

int main()
{
    initwindow(windowWidth,windowHeight);
    drawAxis();
    DDA({0,0}, {500,400});
    BressenhamLine({100,300},{200,100});

    getchar();
    return 0;
}
