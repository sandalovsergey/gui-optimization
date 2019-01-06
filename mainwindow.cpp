#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paramdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dialog = new ParamDialog(this);
    dialog->initMembers(&f, &domain, &criterion, &method);

    setup(ui->customPlot, dialog);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), SLOT(clickedGraph(QMouseEvent*)));
    connect(dialog, SIGNAL(okClicked(ParamDialog*)),this, SLOT(draw(ParamDialog*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw(ParamDialog* dialog)
{
    ui->customPlot->xAxis->setRange(dialog->getLeftX(), dialog->getRightX());
    ui->customPlot->yAxis->setRange(dialog->getLeftY(), dialog->getRightY());
    dialog->initMembers(&f, &domain, &criterion, &method);
    ui->customPlot->removePlottable(colorMap);
    ui->customPlot->removePlottable(startPoint);
    ui->customPlot->removePlottable(endPoint);
    ui->customPlot->removePlottable(curPoint);
    startPoint = nullptr;
    endPoint = nullptr;
    curPoint = nullptr;
    ui->customPlot->plotLayout()->remove(colorScale);
    ui->customPlot->axisRect()->removeEventFilter(marginGroup);

    setup(ui->customPlot, dialog);
}

void MainWindow::setup(QCustomPlot *customPlot, ParamDialog* dialog) {
    customPlot->axisRect()->setupFullAxesBox(true);
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(colorMap);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny);

    colorMap->data()->setRange(QCPRange(dialog->getLeftX(), dialog->getRightX()),
                               QCPRange(dialog->getLeftY(), dialog->getRightY()));

    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        std::vector<double> coord = {x,y};
        UserPoint tmp(coord);
        z = f->apply(tmp); //(1-x)*(1-x) + 100*(y-x*x)*(y - x*x);
        colorMap->data()->setCell(xIndex, yIndex, z);
      }
    }


    colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale);
    colorScale->setType(QCPAxis::atRight);
    colorMap->setColorScale(colorScale);
    colorScale->axis()->setLabel("Magnitude");


    colorMap->setGradient(QCPColorGradient::gpPolar);

    colorMap->rescaleDataRange();

    marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    customPlot->rescaleAxes();
    setWindowTitle("QCustomPlot: ");
    statusBar()->clearMessage();

    if(startPoint == nullptr)
        init();

    ui->customPlot->replot();
}

void MainWindow::init()
{
    curPoint = new QCPGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(curPoint);
    curPoint->setAdaptiveSampling(false);
    curPoint->removeFromLegend();
    curPoint->setLineStyle(QCPGraph::lsNone);
    curPoint->setScatterStyle(QCPScatterStyle::ssCrossCircle);
    curPoint->setPen(QPen(QBrush(Qt::red),1));

    startPoint = new QCPGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(startPoint);
    startPoint->setAdaptiveSampling(false);
    startPoint->removeFromLegend();
    startPoint->setLineStyle(QCPGraph::lsNone);
    startPoint->setScatterStyle(QCPScatterStyle::ssCircle);
    startPoint->setPen(QPen(QBrush(Qt::green),2));

    endPoint = new QCPGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(endPoint);
    endPoint->setAdaptiveSampling(false);
    endPoint->removeFromLegend();
    endPoint->setLineStyle(QCPGraph::lsNone);
    endPoint->setScatterStyle(QCPScatterStyle::ssCircle);
    endPoint->setPen(QPen(QBrush(Qt::yellow),2));
}

void MainWindow::clickedGraph(QMouseEvent *event)
{
    startPoint->clearData();
    curPoint->clearData();
    endPoint->clearData();
    QPoint qPoint = event->pos();
    double startX = ui->customPlot->xAxis->pixelToCoord(qPoint.x());
    double startY = ui->customPlot->yAxis->pixelToCoord(qPoint.y());

    if(startX < dialog->getLeftX() || startX > dialog->getRightX()
            || startY < dialog->getLeftY() || startY > dialog->getRightY())
        return;

    drawPath(qPoint.x(), qPoint.y());

    startPoint->addData(startX, startY);

    printInformation();
    
    ui->customPlot->replot();
}

void MainWindow::drawPath(int pxlX, int pxlY) {
    
    std::vector<double> coords = {ui->customPlot->xAxis->pixelToCoord(pxlX),
                                  ui->customPlot->yAxis->pixelToCoord(pxlY)};

    UserPoint* startPointDouble = new UserPoint(coords);
    
    dialog->initMembers(&f, &domain, &criterion, &method);
    
    method->start(startPointDouble);
    method->step();

    vector<UserPoint> pathToGoal = method->getPathToGoal();
    for(int i = 0; i < pathToGoal.size(); ++i)
    {
        curPoint->addData(pathToGoal[i].getX()[0],
                pathToGoal[i].getX()[1]);
    }

    endPoint->addData(pathToGoal[pathToGoal.size() - 1].getX()[0],
            pathToGoal[pathToGoal.size() - 1].getX()[1]);
}

void MainWindow::printInformation() {
    QString text1 = "Num of iteration: ";
    text1.append(QString("%1").arg(method->getNumOfIter()));

    QString text2 = "x*: ";
    QString qstr = QString::fromStdString(method->getEndPoint()->toString());
    text2+=qstr;

    QString text3 = "f(x*): ";
    text3.append(QString("%1").arg(method->getFEnd()));

    ui->informLabel1->setText(text1);
    ui->informLabel2->setText(text2);
    ui->informLabel3->setText(text3);
}


void MainWindow::on_pushButton_clicked(){
    
    dialog->show();
}
