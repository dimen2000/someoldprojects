#include "saperfield.h"
extern int CellSize(20);

SaperField::SaperField()
{
    x = 0;
    y = 0;
   size = 0;
   arr = 0;
   NumberList[0] = new QImage(":/bomb2.png");
   NumberList[1] = new QImage(":/1Number.jpg");
   NumberList[2] = new QImage(":/2Number.jpg");
   NumberList[3] = new QImage(":/3Number.jpg");
   NumberList[4] = new QImage(":/4Number.jpg");
   NumberList[5] = new QImage(":/5Number.jpg");
   NumberList[6] = new QImage(":/6Number.jpg");
   NumberList[7] = new QImage(":/7Number.jpg");
   NumberList[8] = new QImage(":/8Number.jpg");
   NumberList[9] = new QImage(":/flag.png");
}

SaperField::SaperField(int s, int x_, int y_)
{
    x = x_;
    y = y_;
    size = s;
    NumberList[0] = new QImage(":/bomb2.png");
    NumberList[1] = new QImage(":/1Number.jpg");
    NumberList[2] = new QImage(":/2Number.jpg");
    NumberList[3] = new QImage(":/3Number.jpg");
    NumberList[4] = new QImage(":/4Number.jpg");
    NumberList[5] = new QImage(":/5Number.jpg");
    NumberList[6] = new QImage(":/6Number.jpg");
    NumberList[7] = new QImage(":/7Number.jpg");
    NumberList[8] = new QImage(":/8Number.jpg");
    NumberList[9] = new QImage(":/flag.png");
    arr = new unsigned char*[size+2];
    for(int i = 0; i < size + 2; i++)
    {
        arr[i] = new unsigned char[size+2];
        for(int j = 0; j < size+2; j++)
        {
            arr[i][j] = 0x02;
        }
    }
}

void SaperField::SetSize(int s)
{
    if(arr)
    {
        for(int i = 0; i < size+2; i++)
        {
            delete[]arr[i];
        }
        delete[] arr;
    }
    size = s;
    arr = new unsigned char*[size+2];
    for(int i = 0; i < size+2; i++)
    {
        arr[i] = new unsigned char[size+2];
        for(int j = 0; j < size+2; j++)
        {
            arr[i][j] = 0x02;
        }
    }
}

void SaperField::SetCoords(int _x, int _y)
{

    x = _x;
    y = _y;
}

void SaperField::MoveCoords(int dx, int dy)
{
    x += dx;
    y += dy;
}

void SaperField::ClearSquare(QPoint point)
{
    int a = point.x();
    int b = point.y();
    if ((a < (x + (size+2)*CellSize))&&(b < (y + (size+2)*CellSize)))
    {
        int k = (int)((a - x + CellSize)/CellSize);
        int l = (int)((b - y + CellSize)/CellSize);
        arr[l][k] = arr[l][k] & 0xFE;
        arr[l+1][k+1] = arr[l+1][k+1]&0xFE;
        arr[l+1][k] = arr[l+1][k]&0xFE;
        arr[l+1][k-1] = arr[l+1][k-1]&0xFE;
        arr[l][k-1] = arr[l][k-1]&0xFE;
        arr[l-1][k-1] = arr[l-1][k-1]&0xFE;
        arr[l-1][k] =  arr[l-1][k]&0xFE;
        arr[l-1][k+1] = arr[l-1][k+1]&0xFE;
        arr[l][k+1] = arr[l][k+1]&0xFE;
    }
}

char SaperField::OpenSquare(QPoint point)
{
    int a = point.x();
    int b = point.y();
    if ((a < (x + (size+2)*CellSize))&&(b < (y + (size+2)*CellSize)))
    {
        int k = (int)((a - x + CellSize)/CellSize);
        int l = (int)((b - y + CellSize)/CellSize);
        return OpenCell (l,k) |
        OpenCell(l+1,k+1) |
        OpenCell(l+1,k) |
        OpenCell(l+1,k-1) |
        OpenCell(l,k-1)  |
        OpenCell(l-1,k-1)|
        OpenCell(l-1,k) |
        OpenCell(l-1,k+1)|
        OpenCell(l,k+1);
    }
    return 0;
}

char SaperField::OpenCell(int l, int k)
{
    if (!(arr[l][k] & 0x02)||(l*k==0)||(l==size+1)||(k==size+1)||(arr[l][k] & 0x04))
        return Win();
    arr[l][k]=arr[l][k] & 0xFD;
    if (arr[l][k]&0x01)
    {
        return 2;
    }
    else if(!(arr[l][k]>>4))
    {
        OpenCell(l+1,k+1);
        OpenCell(l+1,k);
        OpenCell(l+1,k-1);
        OpenCell(l,k-1);
        OpenCell(l-1,k-1);
        OpenCell(l-1,k);
        OpenCell(l-1,k+1);
        OpenCell(l,k+1);
    }
    return Win();
}

char SaperField::Win()
{
    char won  = 1;
    for(int i = 1; i < size+1; i++)
    {
        for(int j = 1; j < size+1; j++)
        {
            won  = won * (!(arr[i][j] & 0x02) + (arr[i][j]&0x01));
        }
    }
    return won;
}

void SaperField::SetFlag(QPoint point)
{
    int a = point.x();
    int b = point.y();
    if ((a < (x + (size+2)*CellSize))&&(b < (y + (size+2)*CellSize)))
    {
        int k = (int)((a - x + CellSize)/CellSize);
        int l = (int)((b - y + CellSize)/CellSize);
        arr[l][k]=arr[l][k] ^ 0x04;
    }
}

char SaperField::OpenCell(QPoint point)
{
    int a = point.x();
    int b = point.y();
    if ((a < (x + (size+2)*CellSize))&&(b < (y + (size+2)*CellSize)))
    {
        int k = (int)((a - x + CellSize)/CellSize);
        int l = (int)((b - y + CellSize)/CellSize);
  //      if (!(arr[l][k] & 0x04))
        return OpenCell(l,k);
    }
    return Win();
}

void SaperField::DrawField(QPainter * painter)
{
    int a = x;
    int b = y;
    for(int i = 1; i < size+1; i++)
    {
        for(int j = 1; j < size+1; j++)
        {
            (*painter).drawRect(a, b, CellSize, CellSize);
            if (arr[i][j]& 0x02)
            {
                (*painter).fillRect(QRect(a +1, b +1, CellSize-1, CellSize-1), Qt:: darkBlue);
                if (arr[i][j]& 0x04)
                  (*painter).drawImage(a+1, b+1, NumberList[9]->scaled(CellSize-2,CellSize-2));
            }
            else if(arr[i][j]& 0x01)
            {              
                (*painter).drawImage(a+1, b+1, NumberList[0]->scaled(CellSize-2,CellSize-2));
            }
            else if ((arr[i][j]>>4) != 0)
            {
                (*painter).drawImage(a +1, b+1, NumberList[(arr[i][j]>>4)]->scaled(CellSize-1,CellSize-1));
            }
            a+=CellSize;
        }
        a = x;
        b+=CellSize;
    }
}


unsigned char SaperField::CountNeighbours(int a, int b)
{
    unsigned char count = 0;
    count+=arr[a+1][b+1]&0x01;
    count+=arr[a+1][b]&0x01;
    count+=arr[a+1][b-1]&0x01;
    count+=arr[a][b-1]&0x01;
    count+=arr[a-1][b-1]&0x01;
    count+=arr[a-1][b]&0x01;
    count+=arr[a-1][b+1]&0x01;
    count+=arr[a][b+1]&0x01;
    return count;
}


void SaperField::RandomFullfil( QPoint point, int bomb)
{
    srand(time(NULL));
    for(int i = 1; i < size+1; i++)
    {
        for(int j = 1; j < size+1; j++)
        {          
            arr[i][j] =  !(rand()%bomb);

        }
    }
    ClearSquare(point);
    for(int i = 1; i < size+1; i++)
    {
        for(int j = 1; j < size+1; j++)
        {
            if (! arr[i][j])
            {
                arr[i][j] = arr[i][j] | ((CountNeighbours(i,j))<<4);
            }
            arr[i][j] = arr[i][j]|0x02;
        }
    }
}

SaperField::~SaperField()
{
    if(arr)
    {
        for(int i = 0; i < size+2; i++)
        {
            delete[]arr[i];
        }
        delete[] arr;
    }
    for (int j = 0; j < 10 ;j++)
        delete NumberList[j];
}


