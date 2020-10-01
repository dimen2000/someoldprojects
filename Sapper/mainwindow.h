#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>
//#include <QSound>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    virtual void mousePressEvent(QMouseEvent* pe);
    virtual void wheelEvent ( QWheelEvent * event );
    virtual void paintEvent(QPaintEvent *pe);
    virtual void mouseReleaseEvent(QMouseEvent *pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);
    virtual void mouseDoubleClickEvent(QMouseEvent *pe);
    QMessageBox* LoserBox;
    QMessageBox* WinnerBox;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_RestartButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
