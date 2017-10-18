#include "mkewindow.h"
#include "ui_mkewindow.h"

MKEWindow::MKEWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MKEWindow)
{
    ui->setupUi(this);
    ui->BLEq->setAlignment(Qt::AlignRight);
    ui->BREq->setAlignment(Qt::AlignRight);

    ui->evenStepRadio->setChecked(true);

    customPlot = new QCustomPlot(); // Инициализируем графическое полотно
    ui->gridLayout->addWidget(customPlot,0,0,1,1);  // Устанавливаем customPlot в окно проложения

    customPlot->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
    customPlot->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
    customPlot->axisRect()->setRangeDrag(Qt::Horizontal);   // Включаем перетаскивание только по горизонтальной оси
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal);   // Включаем удаление/приближение только по горизонтальной оси

    ui->BLEq->setText("V(x = ");
    ui->leftValue->setText("");
    ui->leftValue->setEnabled(true);

    ui->BREq->setText("dV/dx(x = ");
    ui->rightValue->setText("");
    ui->rightValue->setEnabled(true);
}

MKEWindow::~MKEWindow()
{
    delete ui;
}

void MKEWindow::on_GoButton_clicked()
{
    static int graphNumber;
    double k2 = atof(ui->V2->text().toUtf8().constData());
    double k1 = atof(ui->V1->text().toUtf8().constData());
    double k0 = atof(ui->V0->text().toUtf8().constData());
    double cons = atof(ui->Constant->text().toUtf8().constData());

    QVector<BoundaryCondition> BC;
    double point1 =atof(ui->leftEnd->text().toUtf8().constData());
    double value1 =atof(ui->leftValue->text().toUtf8().constData());
    double point2 =atof(ui->rightEnd->text().toUtf8().constData());
    double value2 =atof(ui->rightValue->text().toUtf8().constData());
    BC.push_front(BoundaryCondition(0, point1, value1));
    BC.push_back(BoundaryCondition(1, point2, value2));

    Equation eq(k2, k1, k0, cons, point1, point2);

    eq.setBC(BC);
    //std::cout << ui->evenStepRadio->isChecked() << '\n';
        int steps = atoi(ui->evenStepsNum->text().toUtf8().constData());
        eq.simpleStep(steps);
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
    graphic->setPen(QPen(QColor(graphNumber % 3 == 2 ? 255 - graphNumber / 3 * 50 : 0,graphNumber % 3 == 0 ? 255 - graphNumber / 3 * 50 : 0,graphNumber % 3 == 1 ? 255 - graphNumber / 3 * 50 : 0))); // Устанавливаем цвет графика

    // Заполняем график значениями

    graphic->setData(eq.getXValues(), eq.getYValues()); // Устанавливаем данные
    QVector<double> Xval;
    Xval.append(eq.getXValues());
    QVector<double> Yval;
    Yval.append(eq.getYValues());
    for(int i = 0; i < Xval.size(); i++) {
        double temp = 0.0625 * (20 * Xval[i] + 25 * exp(-4*Xval[i]) - 25 / exp(24) - 104);
        std::cerr << Xval[i] << '\t' << Yval[i] << '\t' << temp << '\t' << fabs(Yval[i] - temp) << '\n';
    }
    customPlot->rescaleAxes();      // Масштабируем график по данным
    customPlot->replot();           // Отрисовываем график

    graphNumber++;
}
