#ifndef MKEWINDOW_H
#define MKEWINDOW_H

#include <QMainWindow>
#include <equation.h>
#include <qcustomplot.h>
#include "iostream"
#include "string"


namespace Ui {
class MKEWindow;
}

class MKEWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MKEWindow(QWidget *parent = 0);
    ~MKEWindow();

private slots:
    void on_boundaryLeft_currentIndexChanged(int index);

    void on_boundaryRight_currentIndexChanged(int index);

    void on_GoButton_clicked();

private:
    Ui::MKEWindow *ui;
    QCustomPlot *customPlot;    // Объявляем графическое полотно
    QCPGraph *graphic;          // Объявляем график
};

#endif // MKEWINDOW_H
