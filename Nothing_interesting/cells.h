#ifndef CELLS_H
#define CELLS_H

#include <QtGui>
#include "time.h"

extern int CellSize;

class Cells
{
private:
    int size;
    int x;
    int y;
    unsigned char **arr;
public:
    Cells();
    Cells(int, int, int);
    void SetSize(int);
    void SetCoords(int,int);
    void MoveCoords(int, int);
    void DrawCells(QPainter*);
    void Resurrect(QPoint);
    void SetDefaultCells();
//    void CellsChanged();
    unsigned char CountNeighbours(int, int);
    unsigned char CountNeighboursBody(int, int);
    unsigned char CountNeighboursUpRight();
    unsigned char CountNeighboursUpLeft();
    unsigned char CountNeighboursUp(int);
    unsigned char CountNeighboursLeft(int);
    unsigned char CountNeighboursRight(int);
    unsigned char CountNeighboursDown(int);
    unsigned char CountNeighboursDownRight();
    unsigned char CountNeighboursDownLeft();
    void Destiny(int, int, unsigned char c);
    void Fate(int, int);
    void RandomFullfil(int);
    void Turn();
    ~Cells();
};

#endif // CELLS_H
