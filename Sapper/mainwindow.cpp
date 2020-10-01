#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "saperfield.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    LoserBox = new QMessageBox("Бомба","Вы проиграли",QMessageBox::NoIcon,QMessageBox::NoButton, QMessageBox::Ok,QMessageBox::NoButton | QMessageBox::Escape);
    WinnerBox = new QMessageBox("Победа","Все бомбы обезврежены",QMessageBox::NoIcon,QMessageBox::NoButton, QMessageBox::Ok,QMessageBox::NoButton | QMessageBox::Escape);
    ui->setupUi(this);
}

bool RightButtomFlag = 0;
bool GeneratedFlag = 0;
int CurSize = 10;
int chance = 5;
QPoint RightButtomCoord;
SaperField MainField(10, 40, 40);
//QAudioFormat format;
//QAudioOutput *audio;


void MainWindow ::mousePressEvent(QMouseEvent* pe)
{
    QPoint point;
    point = pe->pos();

    if(pe->button() == Qt::RightButton )
    {
        MainField.SetFlag(point);
        RightButtomFlag = 1;
        RightButtomCoord = point;
        this->repaint();
    }
    else if(pe->button() == Qt::LeftButton )
    {        
        if (!GeneratedFlag)
        {
            GeneratedFlag = 1;
            MainField.RandomFullfil(point, chance);
        }
//        format.setSampleRate(8000);
//        format.setChannelCount(1);
//        format.setSampleSize(8);
//        format.setCodec("audio/pcm");
//        format.setByteOrder(QAudioFormat::LittleEndian);
//        format.setSampleType(QAudioFormat::UnSignedInt);
//        audio = new QAudioOutput( format, this);

//        QFile inputFile;
//        inputFile.setFileName(":/Skid.wav");
//        inputFile.open(QBuffer::ReadOnly);


//        audio->start(&inputFile);
//        inputFile.close();
//        delete audio;

        //QSound::play(":/Skid.wav");

        if (MainField.OpenCell(point) & 0x02)
        {
           LoserBox->exec();
           MainField.SetSize(CurSize);
           GeneratedFlag = 0;
        }
        else if(MainField.OpenCell(point))
        {
            WinnerBox->exec();
            MainField.SetSize(CurSize);
            GeneratedFlag = 0;
        }
        this->repaint();
    }

}

void MainWindow ::wheelEvent ( QWheelEvent * event )
{
    CellSize +=event->delta()/100;
    if (CellSize < 3)
        CellSize = 3;
    this->repaint();
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
        MainField.MoveCoords(dx, dy);
        this->repaint();
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *pe)
{
    QPoint point;
    point = pe->pos();
    if(pe->button() == Qt::LeftButton )
    {
        if (MainField.OpenSquare(point) & 0x02)
        {
            LoserBox->exec();
            MainField.SetSize(CurSize);
            GeneratedFlag = 0;
        }
        else if (MainField.OpenSquare(point))
        {
            WinnerBox->exec();
            MainField.SetSize(CurSize);
            GeneratedFlag = 0;
        }
    }
    this->repaint();
}

void MainWindow::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    MainField.DrawField(&painter);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete LoserBox;
    delete WinnerBox;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        MainField.SetSize(10);
        CurSize = 10;
        break;
    case 1:
        MainField.SetSize(20);
        CurSize = 20;
        break;
    case 2:
        MainField.SetSize(35);
        CurSize = 35;
        break;
    case 3:
        MainField.SetSize(50);
        CurSize = 50;
        break;
    case 4:
        MainField.SetSize(100);
        CurSize = 100;
        break;
    default:
        break;
    }
    GeneratedFlag = 0;
    this->repaint();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        chance = 20;
        break;
    case 1:
        chance = 10;
        break;
    case 2:
        chance = 5;
        break;
    case 3:
        chance = 4;
        break;
    case 4:
        chance = 2;
        break;
    default:
        break;
    }
}

void MainWindow::on_RestartButton_clicked()
{
    MainField.SetSize(CurSize);
    GeneratedFlag = 0;
    this->repaint();
}
