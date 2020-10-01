#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cells.h"
#include <windows.h>

#define TIMESTEP 50

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
}
int CellsNumber = 10;
int SleepTime = 250;
bool ExecFlag = 0;
int Turns = 0;
int Chance = 10;
int ToDoSteps = 0;
bool RightButtomFlag = 0;
int CountTurns = 0;
QPoint RightButtomCoord;
Cells MainCells(0, 40, 40);

void MainWindow ::mousePressEvent(QMouseEvent* pe)
{
    QPoint point;            
    point = pe->pos();
    if(pe->button() == Qt::RightButton )
    {
        RightButtomFlag = 1;
        RightButtomCoord = point;
    }
    if(pe->button() == Qt::LeftButton )
    {
        MainCells.Resurrect(point);
        this->repaint();
    }

}

void MainWindow ::wheelEvent ( QWheelEvent * event )
{
    CellSize +=event->delta()/100;
    if (CellSize < 1)
        CellSize = 1;
   // MainCells.DrawCells(&painter);
    this->repaint();
}

void MainWindow::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    MainCells.DrawCells(&painter);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *pe)
{
    if(pe->button() == Qt::RightButton )
    {
        RightButtomFlag = 0;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *pe)
{
    if (RightButtomFlag)
    {
        QPoint Mpoint = pe->pos();
        int dx = ( Mpoint.x()- RightButtomCoord.x())/35;
        int dy = (Mpoint.y()- RightButtomCoord.y())/35;
        MainCells.MoveCoords(dx, dy);
        //MainCells.DrawCells(&painter);
        this->repaint();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    CellsNumber = arg1;
}

void MainWindow::on_CreateButton_clicked()
{
    MainCells.SetSize(CellsNumber);
    ExecFlag = 0;
    Turns = 0;
    ui->lcdNumber->display(Turns);
    this->repaint();
}

void MainWindow::on_TurnButton_clicked()
{
    MainCells.Turn();
    ui->lcdNumber->display(Turns++ + 1);
    this->repaint();
}

void MainWindow::on_StartButton_clicked()
{
    if (!ExecFlag)
    {
        ExecFlag = 1;
        while(ExecFlag)
        {
            MainCells.Turn();
            QThread::msleep(SleepTime);
            qApp->processEvents();
            ui->lcdNumber->display(Turns++ + 1);
            this->repaint();
        }
    }
}

void MainWindow::on_DefaultLocale_clicked()
{
    MainCells.SetDefaultCells();
    //MainCells.DrawCells(&painter);
    this->repaint();
}


void MainWindow::on_StopButton_clicked()
{
    ExecFlag = 0;
}

void MainWindow::on_FasterButton_clicked()
{
    SleepTime-= TIMESTEP;
    if (SleepTime<=0)
        SleepTime = 50;
}

void MainWindow::on_SlowerButton_clicked()
{
    SleepTime+= TIMESTEP;
}

void MainWindow::on_ChanceBox_valueChanged(int arg1)
{
    Chance = arg1;
}

void MainWindow::on_RandButton_clicked()
{
    MainCells.RandomFullfil(Chance);
    Turns = 0;
    ui->lcdNumber->display(Turns);
    this->repaint();
}

void MainWindow::on_DontPaintButton_clicked()
{
    ExecFlag = 1;
//    LARGE_INTEGER nCnt;
//    LARGE_INTEGER nCnt_1;
//    QueryPerformanceCounter(&nCnt);
    for(int i = 0; i < ToDoSteps; i++)
    {
        MainCells.Turn();
        qApp->processEvents();
        ui->lcdNumber->display(Turns++ + 1);
        if(!ExecFlag)
            break;
    }
//    QueryPerformanceCounter(&nCnt_1);
//    unsigned long nCnt_2 = nCnt.HighPart- nCnt_1.HighPart;
//    QString s;
//    s.sprintf("%lu", nCnt_2);
//    QMessageBox::information(NULL,QObject::tr(""),s);
    ExecFlag = 0;
    this->repaint();
}

void MainWindow::on_TurnBox_valueChanged(int arg1)
{
    ToDoSteps = arg1;
}
