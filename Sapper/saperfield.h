#ifndef SAPERFIELD_H
#define SAPERFIELD_H

#include <QtGui>
#include "time.h"


extern int CellSize;

class SaperField
{
protected:
    int size;
    int x;
    int y;
    QImage* NumberList[10];
    unsigned char **arr;
public:
    SaperField();
    SaperField(int, int, int);
    void SetSize(int);
    void SetCoords(int,int);
    void MoveCoords(int, int);
    void ClearSquare(QPoint);
    char OpenSquare(QPoint);
    void SetFlag(QPoint);
    char OpenCell(int, int);
    char Win();
    char OpenCell(QPoint);
    void DrawField(QPainter*);
    void RandomFullfil(QPoint, int bomb);
    unsigned char CountNeighbours(int, int);
    ~SaperField();

};

#endif // SAPERFIELD_H
