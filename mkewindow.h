#ifndef MKEWINDOW_H
#define MKEWINDOW_H

#include <QMainWindow>
#include <equation.h>
#include <qcustomplot.h>
#include "iostream"
#include "string"
#include <boundarycondition.h>
#include <QVector>
#include <unevenstep.h>


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

    void on_GoButton_clicked();

private:
    Ui::MKEWindow *ui;
    QVector<BoundaryCondition> bounCond;
    QVector<UnevenStep> unevStep;
    QCustomPlot *customPlot;    // Объявляем графическое полотно
    QCPGraph *graphic;          // Объявляем график
};

#endif // MKEWINDOW_H
