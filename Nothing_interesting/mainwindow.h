#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QRectF rect;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void mousePressEvent(QMouseEvent* pe);
    virtual void wheelEvent ( QWheelEvent * event );
    virtual void paintEvent(QPaintEvent *pe);
    virtual void mouseReleaseEvent(QMouseEvent *pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_CreateButton_clicked();

    void on_TurnButton_clicked();


    void on_StartButton_clicked();


    void on_DefaultLocale_clicked();


    void on_StopButton_clicked();

    void on_FasterButton_clicked();

    void on_SlowerButton_clicked();

    void on_ChanceBox_valueChanged(int arg1);

    void on_RandButton_clicked();

    void on_DontPaintButton_clicked();

    void on_TurnBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
