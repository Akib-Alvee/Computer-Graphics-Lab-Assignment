#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>

using namespace std;

const int windowWidth = GetSystemMetrics(SM_CXSCREEN), windowHeight = 1000;

struct point
{
    double x,y;

    point() {}
    point(double a,double b)
    {
        x=a;
        y=b;
    }

    bool operator < (const point & p) const
    {
        return x < p.x;
    }
};

void drawPixel(point p, int color)
{
    //delay(0.1);
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
        else
        {
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

void BoundaryFill(point currPixel, int boundaryColor, int fillColor)
{
    point pixel = currPixel;
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

void drawBox(point a)
{
    point b = {(a.x+80),a.y};
    point c = {b.x,(b.y+50)};
    point d = {a.x,c.y};
    drawLine(a,b,WHITE);
    drawLine(b,c,WHITE);
    drawLine(c,d,WHITE);
    drawLine(a,d,WHITE);

}

bool pointInsideCircle(point c, point pt, int r )
{
    double d = sqrt(pow((pt.x-c.x),2) + pow((pt.y-c.y),2));
    if (d< r) return TRUE;
    else return FALSE;
}

bool pointInsideBox(point a,point b)
{
    if(a.x>b.x && a.x<(b.x+80) && a.y>b.y && a.y<(b.y+50))
        return TRUE;
    else
        return FALSE;
}

int main()
{
    cout<<"Number of Collision Detection\n\n"<<endl;
    int x,y=40,t=windowHeight,c=1,r=40;
    initwindow(windowWidth,windowHeight,"Collision");
    point pt ;
    bool circFilled = FALSE;
    bool boxFilled = FALSE;
    int cnt=0;
    for(x=0; x+r<=windowWidth; x+=5)
    {

        BressenhamCircle({x+r,y},r);
        drawBox({x,windowHeight/2});
        if(y>(windowHeight/2-16)&&(y<(windowHeight/2+16)))
            cnt++;
        delay(60);
        if (GetAsyncKeyState(VK_RBUTTON))
        {
            POINT cursorPos;
            GetCursorPos(& cursorPos);
            ScreenToClient(GetForegroundWindow(), &cursorPos);
            pt = point({cursorPos.x, cursorPos.y});
            //pt = convertPixel(pt);
            //cout<<pt.x<<"    "<<pt.y<<endl;

            if (pointInsideCircle({x,y}, pt, r))
            {
                circFilled = (!circFilled);
            }

            if (pointInsideBox(pt, {x,windowHeight/2}))
                boxFilled = (!boxFilled);
        }

        if(circFilled)
            BoundaryFill({x+r,y}, GREEN, WHITE);
        if(boxFilled)
            BoundaryFill({x+1,(windowHeight/2)+1},WHITE,YELLOW);

        if(y>windowHeight-20)
        {
            c=0;
            t=t-20;
        }
        if(y<=(windowHeight-t))
        {
            c=1;
        }
        if(t>=40)
            y=y+(c? 15:-15);
        cleardevice();
        //Exit upon keypress
        if(kbhit())
            break;
    }
    cout<<"Total Number of Collision: "<<cnt<<endl;
}
