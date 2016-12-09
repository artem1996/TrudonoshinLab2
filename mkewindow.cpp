#include "mkewindow.h"
#include "ui_mkewindow.h"

MKEWindow::MKEWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MKEWindow)
{
    ui->setupUi(this);
    ui->boundaryLeft->addItem("Константа");
    ui->boundaryLeft->addItem("Производная");
    ui->boundaryLeft->addItem("3-й род");
    ui->boundaryRight->addItem("Константа");
    ui->boundaryRight->addItem("Производная");
    ui->boundaryRight->addItem("3-й род");
    ui->apprType->addItem("Линейная");
    ui->apprType->addItem("Квадратичная");
    ui->BLEq->setAlignment(Qt::AlignRight);
    ui->BREq->setAlignment(Qt::AlignRight);

    ui->evenStepRadio->setChecked(true);
    ui->addStep->setDisabled(true);
    ui->delStep->setDisabled(true);
    ui->boundUnevStep->setDisabled(true);
    ui->unevenStepSize->setDisabled(true);
    ui->unevenStepsNum->setDisabled(true);
    ui->unevenDiapNumber->setDisabled(true);

    ui->addPointEdit->setDisabled(true);
    ui->addPoint->setDisabled(true);
    ui->delPoint->setDisabled(true);
    ui->boundAddPoints->setDisabled(true);
    ui->addPointVal->setDisabled(true);

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
    if(index == 1) {
        ui->BLEq->setText("dV/dx(x = ");
        ui->leftValue->setText("");
        ui->leftValue->setEnabled(true);
    } else if(index == 0) {
        ui->BLEq->setText("V(x = ");
        ui->leftValue->setText("");
        ui->leftValue->setEnabled(true);
    } else {
        ui->BLEq->setText("dV/dx(x = ");
        ui->leftValue->setText("V");
        ui->leftValue->setEnabled(false);
    }
}

void MKEWindow::on_boundaryRight_currentIndexChanged(int index)
{
    if(index == 1) {
        ui->BREq->setText("dV/dx(x = ");
        ui->rightValue->setText("");
        ui->rightValue->setEnabled(true);
    } else if(index == 0) {
        ui->BREq->setText("V(x = ");
        ui->rightValue->setText("");
        ui->rightValue->setEnabled(true);
    } else {
        ui->BREq->setText("dV/dx(x = ");
        ui->rightValue->setText("V");
        ui->rightValue->setEnabled(false);
    }
}

void MKEWindow::on_GoButton_clicked()
{
    static int graphNumber;
    double k2 = atof(ui->V2->text().toUtf8().constData());
    double k1 = atof(ui->V1->text().toUtf8().constData());
    double k0 = atof(ui->V0->text().toUtf8().constData());
    double cons = atof(ui->Constant->text().toUtf8().constData());

    QVector<BoundaryCondition> BC;
    if(ui->addPointsCheck->isChecked()) {
        BC.append(bounCond);
        //std::cout << (BC[0] < BC[1]);
        qSort(BC);
    }
    int type1 = ui->boundaryLeft->currentIndex();
    int type2 = ui->boundaryRight->currentIndex();
    double point1 =atof(ui->leftEnd->text().toUtf8().constData());
    double value1 =atof(ui->leftValue->text().toUtf8().constData());
    double point2 =atof(ui->rightEnd->text().toUtf8().constData());
    double value2 =atof(ui->rightValue->text().toUtf8().constData());
    BC.push_front(BoundaryCondition(type1, point1, value1));
    BC.push_back(BoundaryCondition(type2, point2, value2));

    Equation eq(k2, k1, k0, cons, point1, point2);

    eq.setBC(BC);
    //std::cout << ui->evenStepRadio->isChecked() << '\n';
    if(ui->evenStepRadio->isChecked()) {
        int steps = atoi(ui->evenStepsNum->text().toUtf8().constData());
        eq.simpleStep(steps);
    } else {
        qSort(unevStep);
        eq.difficultStep(unevStep);
    }
    if(ui->apprType->currentIndex()) {
        eq.doubleSolution();
    } else {
        eq.solution();
    }

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

void MKEWindow::on_evenStepRadio_clicked()
{
    ui->addStep->setDisabled(true);
    ui->delStep->setDisabled(true);
    ui->boundUnevStep->setDisabled(true);
    ui->unevenStepSize->setDisabled(true);
    ui->unevenStepsNum->setDisabled(true);
    ui->unevenDiapNumber->setDisabled(true);

    ui->evenStepsNum->setDisabled(false);

}

void MKEWindow::on_unevenStepRadio_clicked()
{
    ui->addStep->setDisabled(false);
    ui->delStep->setDisabled(false);
    ui->boundUnevStep->setDisabled(false);
    ui->unevenStepSize->setDisabled(false);
    ui->unevenStepsNum->setDisabled(false);
    ui->unevenDiapNumber->setDisabled(false);

    ui->evenStepsNum->setDisabled(true);
}

void MKEWindow::on_addPointsCheck_clicked(bool checked)
{
    ui->addPointEdit->setDisabled(!checked);
    ui->addPoint->setDisabled(!checked);
    ui->delPoint->setDisabled(!checked);
    ui->boundAddPoints->setDisabled(!checked);
    ui->addPointVal->setDisabled(!checked);
}

void MKEWindow::on_addPoint_clicked()
{
    static int pointNumber;
    double point =atof(ui->addPointEdit->text().toUtf8().constData());
    double value =atof(ui->addPointVal->text().toUtf8().constData());
    bounCond.push_back(BoundaryCondition(0, point, value));

    ui->boundAddPoints->addItem("Точка №" + QString::number(pointNumber + 1));
    ui->boundAddPoints->setCurrentIndex(bounCond.size() - 1);
    pointNumber++;
}

void MKEWindow::on_delPoint_clicked()
{
    int currentIndex = ui->boundAddPoints->currentIndex();
    bounCond.removeAt(currentIndex);
    ui->boundAddPoints->removeItem(currentIndex);
    if(bounCond.size() - 1 < currentIndex) currentIndex--;
    if(currentIndex >= 0) {
        ui->boundAddPoints->setCurrentIndex(currentIndex);
        ui->addPointEdit->setText(QString::number(bounCond[currentIndex].getPoint()));
        ui->addPointVal->setText(QString::number(bounCond[currentIndex].getValue()));
    } else {
        ui->addPointEdit->clear();
        ui->addPointVal->clear();
    }
}

void MKEWindow::on_boundAddPoints_currentIndexChanged(int index)
{
    if(index >= 0) {
        ui->addPointEdit->setText(QString::number(bounCond[index].getPoint()));
        ui->addPointVal->setText(QString::number(bounCond[index].getValue()));
    }
}

void MKEWindow::on_addStep_clicked()
{
    static int stepNumber;
    int numSteps =atoi(ui->unevenStepsNum->text().toUtf8().constData());
    double stepSize =atof(ui->unevenStepSize->text().toUtf8().constData());
    int diapNumber = atoi(ui->unevenDiapNumber->text().toUtf8().constData());
    unevStep.push_back(UnevenStep(numSteps, stepSize, diapNumber));

    ui->boundUnevStep->addItem("Шаги №" + QString::number(stepNumber + 1));
    ui->boundUnevStep->setCurrentIndex(unevStep.size() - 1);
    stepNumber++;
}

void MKEWindow::on_delStep_clicked()
{
    int currentIndex = ui->boundUnevStep->currentIndex();
    unevStep.removeAt(currentIndex);
    ui->boundUnevStep->removeItem(currentIndex);
    if(unevStep.size() - 1 < currentIndex) currentIndex--;
    if(currentIndex >= 0) {
        ui->boundUnevStep->setCurrentIndex(currentIndex);
        ui->unevenStepsNum->setText(QString::number(unevStep[currentIndex].getNumSteps()));
        ui->unevenStepSize->setText(QString::number(unevStep[currentIndex].getStepSize()));
        ui->unevenDiapNumber->setText(QString::number(unevStep[currentIndex].getDiapNumber()));
    } else {
        ui->unevenStepsNum->clear();
        ui->unevenStepSize->clear();
        ui->unevenDiapNumber->clear();
    }
}

void MKEWindow::on_boundUnevStep_currentIndexChanged(int index)
{
    if(index >= 0) {
        ui->unevenStepsNum->setText(QString::number(unevStep[index].getNumSteps()));
        ui->unevenStepSize->setText(QString::number(unevStep[index].getStepSize()));
        ui->unevenDiapNumber->setText(QString::number(unevStep[index].getDiapNumber()));
    }
}
