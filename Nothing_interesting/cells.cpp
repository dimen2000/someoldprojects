#include "cells.h"

extern int CellSize(10);

Cells::Cells()
{
    x = 0;
    y = 0;
   size = 0;
   arr = 0;
}

Cells::Cells(int s, int x_, int y_)
{
    x = x_;
    y = y_;
   // int a = x_;
  //  int b = y_;
    size = s;
    arr = new unsigned char*[size];
    for(int i = 0; i < size; i++)
    {
        arr[i] = new unsigned char[size];
        for(int j = 0; j < size; j++)
        {
            arr[i][j] = 0;
        }
    }
}

void Cells::SetSize(int s)
{
    if(arr)
    {
        for(int i = 0; i < size; i++)
        {
            delete[]arr[i];
        }
        delete[] arr;
    }
    size = s;
    arr = new unsigned char*[size];
    for(int i = 0; i < size; i++)
    {
        arr[i] = new unsigned char[size];
        for(int j = 0; j < size; j++)
        {
            arr[i][j] = 0;
        }
    }
}

void Cells::SetCoords(int _x, int _y)
{
    x = _x;
    y = _y;
}

void Cells::MoveCoords(int dx, int dy)
{
    x += dx;
    y += dy;
}

void Cells::DrawCells(QPainter *painter)
{
    int a = x;
    int b = y;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            (*painter).drawRect(a, b, CellSize, CellSize);
            if(arr[i][j])
            {
                (*painter).fillRect(QRect(a, b, CellSize, CellSize), Qt::blue);
            }
            a+=CellSize;
        }
        a = x;
        b+=CellSize;
    }
}

void Cells::Resurrect(QPoint point)
{
    int a = point.x();
    int b = point.y();
    if ((a < (x + size*CellSize))&&(b < (y + size*CellSize)))
    {
        int k = (int)((a - x)/CellSize);
        int l = (int)((b - y)/CellSize);
        arr[l][k]=!arr[l][k];
    }
}

void Cells::SetDefaultCells()
{
    x = 40;
    y = 40;
    CellSize = 10;
}

unsigned char Cells::CountNeighbours(int a, int b)
{
//    int upA = a + 1;
//    if (upA > size-1)
//        upA = 0;
    int upA = (a + 1) * !((a + 1)/size);
//    int upB = b + 1;
//    if (upB > size-1)
//        upB = 0;
    int upB = (b + 1) * !((b + 1)/size);
//    int downA = a - 1;
//    if (downA < 0)
//        downA = size - 1;
    int downA = a + size*(((size - a)/size)) - 1;
//    int downB = b - 1;
//    if (downB < 0)
//        downB = size - 1;
     int downB = b + size*(((size - b)/size)) - 1;
    unsigned char count = 0;
    count+=(arr[upA][upB]&0x01);
    count+=(arr[upA][b]&0x01);
    count+=(arr[upA][downB]&0x01);
    count+=(arr[a][upB]&0x01);
    count+=(arr[a][downB]&0x01);
    count+=(arr[downA][upB]&0x01);
    count+=(arr[downA][b]&0x01);
    count+=(arr[downA][downB]&0x01);
    return count;
}

unsigned char Cells::CountNeighboursBody(int a, int b)
{
    int upA = a + 1;
    int upB = b + 1;
    int downA = a - 1;
    int downB = b - 1;
    unsigned char count = 0;
    count+=(arr[upA][upB]&0x01);
    count+=(arr[upA][b]&0x01);
    count+=(arr[upA][downB]&0x01);
    count+=(arr[a][upB]&0x01);
    count+=(arr[a][downB]&0x01);
    count+=(arr[downA][upB]&0x01);
    count+=(arr[downA][b]&0x01);
    count+=(arr[downA][downB]&0x01);
    return count;
}

unsigned char Cells::CountNeighboursUpLeft()
{
    int a = 0;
    int b = 0;
    int upA = 1;
    int upB = 1;
    int downA = size-1;
    int downB = size-1;
    unsigned char count = 0;
    count+=(arr[upA][upB]&0x01);
    count+=(arr[upA][b]&0x01);
    count+=(arr[upA][downB]&0x01);
    count+=(arr[a][upB]&0x01);
    count+=(arr[a][downB]&0x01);
    count+=(arr[downA][upB]&0x01);
    count+=(arr[downA][b]&0x01);
    count+=(arr[downA][downB]&0x01);
    return count;
}

unsigned char Cells::CountNeighboursUpRight()
{
    int a = 0;
    int b = size-1;
    int upA = 1;
    int upB = 0;
    int downA = size-1;
    int downB = size-2;
    unsigned char count = 0;
    count+=(arr[upA][upB]&0x01);
    count+=(arr[upA][b]&0x01);
    count+=(arr[upA][downB]&0x01);
    count+=(arr[a][upB]&0x01);
    count+=(arr[a][downB]&0x01);
    count+=(arr[downA][upB]&0x01);
    count+=(arr[downA][b]&0x01);
    count+=(arr[downA][downB]&0x01);
    return count;
}

unsigned char Cells::CountNeighboursUp(int b)
{
    int a = 0;
    int upA = 1;
    int upB = b+1;
    int downA = size-1;
    int downB = b-1;
    unsigned char count = 0;
    count+=(arr[upA][upB]&0x01);
    count+=(arr[upA][b]&0x01);
    count+=(arr[upA][downB]&0x01);
    count+=(arr[a][upB]&0x01);
    count+=(arr[a][downB]&0x01);
    count+=(arr[downA][upB]&0x01);
    count+=(arr[downA][b]&0x01);
    count+=(arr[downA][downB]&0x01);
    return count;
}

unsigned char Cells::CountNeighboursLeft(int a)
{
    int b = 0;
    int upA = a+1;
    int upB = 1;
    int downA = a-1;
    int downB = size-1;
    unsigned char count = 0;
    count+=(arr[upA][upB]&0x01);
    count+=(arr[upA][b]&0x01);
    count+=(arr[upA][downB]&0x01);
    count+=(arr[a][upB]&0x01);
    count+=(arr[a][downB]&0x01);
    count+=(arr[downA][upB]&0x01);
    count+=(arr[downA][b]&0x01);
    count+=(arr[downA][downB]&0x01);
    return count;
}

unsigned char Cells::CountNeighboursRight(int a)
{
    int b = size-1;
    int upA = a+1;
    int upB = 0;
    int downA = a-1;
    int downB = size-2;
    unsigned char count = 0;
    count+=(arr[upA][upB]&0x01);
    count+=(arr[upA][b]&0x01);
    count+=(arr[upA][downB]&0x01);
    count+=(arr[a][upB]&0x01);
    count+=(arr[a][downB]&0x01);
    count+=(arr[downA][upB]&0x01);
    count+=(arr[downA][b]&0x01);
    count+=(arr[downA][downB]&0x01);
    return count;
}

unsigned char Cells::CountNeighboursDown(int b)
{
    int a = size-1;
    int upA = 0;
    int upB = b+1;
    int downA = size-2;
    int downB = b-1;
    unsigned char count = 0;
    count+=(arr[upA][upB]&0x01);
    count+=(arr[upA][b]&0x01);
    count+=(arr[upA][downB]&0x01);
    count+=(arr[a][upB]&0x01);
    count+=(arr[a][downB]&0x01);
    count+=(arr[downA][upB]&0x01);
    count+=(arr[downA][b]&0x01);
    count+=(arr[downA][downB]&0x01);
    return count;
}

unsigned char Cells::CountNeighboursDownRight()
{
    int a = size-1;
    int b = size-1;
    int upA = 0;
    int upB = 0;
    int downA = size-2;
    int downB = size-2;
    unsigned char count = 0;
    count+=(arr[upA][upB]&0x01);
    count+=(arr[upA][b]&0x01);
    count+=(arr[upA][downB]&0x01);
    count+=(arr[a][upB]&0x01);
    count+=(arr[a][downB]&0x01);
    count+=(arr[downA][upB]&0x01);
    count+=(arr[downA][b]&0x01);
    count+=(arr[downA][downB]&0x01);
    return count;
}

unsigned char Cells::CountNeighboursDownLeft()
{
    int a = size-1;
    int b = 0;
    int upA = 0;
    int upB = 1;
    int downA = size-2;
    int downB = size-1;
    unsigned char count = 0;
    count+=(arr[upA][upB]&0x01);
    count+=(arr[upA][b]&0x01);
    count+=(arr[upA][downB]&0x01);
    count+=(arr[a][upB]&0x01);
    count+=(arr[a][downB]&0x01);
    count+=(arr[downA][upB]&0x01);
    count+=(arr[downA][b]&0x01);
    count+=(arr[downA][downB]&0x01);
    return count;
}


void Cells::Destiny(int a, int b, unsigned char c)
{
   // unsigned char c = CountNeighbours(a,b);
    if(arr[a][b]&0x01)
    {
        //if ((c==3)||(c==2))
        //  arr[a][b] = arr[a][b]|0x02;
        unsigned char r = c & 0x02;
        unsigned char m = (unsigned char)(c >> 1) & (unsigned char)0x02;
        r = r & ~m;
        m = (unsigned char)(c >> 2) & (unsigned char)0x02;
        r = r & ~m;
        arr[a][b] = (arr[a][b])|r;
    }
    else if(c==3)
        arr[a][b] = arr[a][b]|0x02;
}

void Cells::Fate(int a, int b)
{
    arr[a][b] = arr[a][b]>>1;

}

void Cells::RandomFullfil(int chance)
{
    srand(time(NULL));
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            arr[i][j] = !(rand()%chance);
        }
    }
}

void Cells::Turn()
{
    int MSize = size-1;

    unsigned char c = CountNeighboursUpLeft();
    Destiny(0,0,c);

    for (int j = 1; j < MSize; j++)
    {
        c = CountNeighboursUp(j);
        Destiny(0,j,c);
    }

    c = CountNeighboursUpRight();
    Destiny(0,MSize,c);

    for(int i = 1; i < MSize; i++)
    {
        c = CountNeighboursLeft(i);
        Destiny(i,0,c);
        for(int j = 1; j < MSize; j++)
        {
            c = CountNeighboursBody(i,j);
            Destiny(i,j,c);
        }
        c = CountNeighboursRight(i);
        Destiny(i,MSize,c);
    }

    c = CountNeighboursDownLeft();
    Destiny(MSize,0,c);

    for (int j = 1; j < MSize; j++)
    {
        c = CountNeighboursDown(j);
        Destiny(MSize,j,c);
    }

    c = CountNeighboursDownRight();
    Destiny(MSize,MSize,c);

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            Fate(i,j);
        }
    }
}

Cells::~Cells()
{
    if(arr)
    {
        for(int i = 0; i < size; i++)
        {
            delete[]arr[i];
        }
        delete[] arr;
    }
}

