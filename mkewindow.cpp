#include "mkewindow.h"
#include "ui_mkewindow.h"

MKEWindow::MKEWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MKEWindow)
{
    ui->setupUi(this);
    ui->boundaryLeft->addItem("Константа");
    ui->boundaryLeft->addItem("Производная");
    ui->boundaryRight->addItem("Константа");
    ui->boundaryRight->addItem("Производная");
    ui->BLEq->setAlignment(Qt::AlignRight);
    ui->BREq->setAlignment(Qt::AlignRight);

    customPlot = new QCustomPlot(); // Инициализируем графическое полотно
    ui->gridLayout->addWidget(customPlot,0,0,1,1);  // Устанавливаем customPlot в окно проложения

    customPlot->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
    customPlot->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
    customPlot->axisRect()->setRangeDrag(Qt::Horizontal);   // Включаем перетаскивание только по горизонтальной оси
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal);   // Включаем удаление/приближение только по горизонтальной оси
}

MKEWindow::~MKEWindow()
{
    delete ui;
}

void MKEWindow::on_boundaryLeft_currentIndexChanged(int index)
{
    if(index) {
        ui->BLEq->setText("dV/dx(x = ");
    } else {
        ui->BLEq->setText("V(x = ");
    }
}

void MKEWindow::on_boundaryRight_currentIndexChanged(int index)
{
    if(index) {
        ui->BREq->setText("dV/dx(x = ");
    } else {
        ui->BREq->setText("V(x = ");
    }
}

void MKEWindow::on_GoButton_clicked()
{
    static int graphNumber;
    double k2 = atof(ui->V2->text().toUtf8().constData());
    double k1 = atof(ui->V1->text().toUtf8().constData());
    double k0 = atof(ui->V0->text().toUtf8().constData());
    double cons = atof(ui->Constant->text().toUtf8().constData());
    //std::cerr << ui->boundaryLeft->currentIndex() << "\n";
    //std::cerr << ui->boundaryRight->currentIndex() << "\n";
    bool type1 = (ui->boundaryLeft->currentIndex()) && 1;
    bool type2 = (ui->boundaryRight->currentIndex()) && 1;
    //std::cerr << type1 << "\n";
    //std::cerr << type2 << "\n";
    double point1 =atof(ui->leftEnd->text().toUtf8().constData());
    double value1 =atof(ui->leftValue->text().toUtf8().constData());
    double point2 =atof(ui->rightEnd->text().toUtf8().constData());
    double value2 =atof(ui->rightValue->text().toUtf8().constData());
    int steps = atoi(ui->stepsNum->text().toUtf8().constData());
    Equation eq(k2, k1, k0, cons, value1, value2);
    eq.setBCCount(2);
    eq.setBC(0, type1, point1, value1);
    eq.setBC(1, type2, point2, value2);
    eq.simpleStep(steps);
    eq.prepSolution();
    eq.solution();




    // Настраиваем шрифт по осям координат
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

    // Автоматическое масштабирование тиков по Оси X
    customPlot->xAxis->setAutoTickStep(true);

    customPlot->yAxis->setTickLabelColor(QColor(0,0,0)); // Красный цвет подписей тиков по Оси Y
    customPlot->legend->setVisible(true);   //Включаем Легенду графика
    // Устанавливаем Легенду в левый верхний угол графика
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    // Инициализируем график и привязываем его к Осям
    graphic = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(graphic);  // Устанавливаем график на полотно
    graphic->setName("График № " + QString::number(graphNumber + 1));       // Устанавливаем
    graphic->setPen(QPen(QColor(graphNumber % 3 == 0 ? 255 - graphNumber / 3 * 50 : 0,graphNumber % 3 == 1 ? 255 - graphNumber / 3 * 50 : 0,graphNumber % 3 == 2 ? 255 - graphNumber / 3 * 50 : 0))); // Устанавливаем цвет графика

    // Заполняем график значениями

    graphic->setData(eq.getXValues(), eq.getYValues()); // Устанавливаем данные
    customPlot->rescaleAxes();      // Масштабируем график по данным
    customPlot->replot();           // Отрисовываем график

    graphNumber++;
}
