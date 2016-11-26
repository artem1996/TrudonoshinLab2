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
    void on_boundaryLeft_currentIndexChanged(int index);

    void on_boundaryRight_currentIndexChanged(int index);

    void on_GoButton_clicked();

    void on_evenStepRadio_clicked();

    void on_unevenStepRadio_clicked();

    void on_addPointsCheck_clicked(bool checked);

    void on_boundUnevStep_currentIndexChanged(int index);

    void on_addPoint_clicked();

    void on_delPoint_clicked();

    void on_boundAddPoints_currentIndexChanged(int index);

    void on_addStep_clicked();

    void on_delStep_clicked();

private:
    Ui::MKEWindow *ui;
    QVector<BoundaryCondition> bounCond;
    QVector<UnevenStep> unevStep;
    QCustomPlot *customPlot;    // Объявляем графическое полотно
    QCPGraph *graphic;          // Объявляем график
};

#endif // MKEWINDOW_H
