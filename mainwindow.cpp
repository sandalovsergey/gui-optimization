#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dialog = new ParamDialog(this);

    setup(ui->customPlot);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), SLOT(clickedGraph(QMouseEvent*)));
}

MainWindow::~MainWindow()
{
    delete startPoint;
    delete curPoint;
    delete colorMap;
    delete dialog;
    delete ui;
}

void MainWindow::setup(QCustomPlot *customPlot) {
    //customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    customPlot->axisRect()->setupFullAxesBox(true);
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    if(colorMap != nullptr)
    {

        delete colorMap;
    }

    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(colorMap);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny);
    colorMap->data()->setRange(QCPRange(0, 2), QCPRange(-1, 1));

    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        z = (1-x)*(1-x) + 100*(y-x*x)*(y - x*x);
        colorMap->data()->setCell(xIndex, yIndex, z);
      }
    }


    QCPColorScale *colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Magnitude");


    colorMap->setGradient(QCPColorGradient::gpPolar);

    colorMap->rescaleDataRange();

    QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
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
    startPoint = new QCPGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(startPoint);
    startPoint->setAdaptiveSampling(false);
    startPoint->removeFromLegend();
    startPoint->setLineStyle(QCPGraph::lsNone);
    startPoint->setScatterStyle(QCPScatterStyle::ssCircle);
    startPoint->setPen(QPen(QBrush(Qt::green),2));

    curPoint = new QCPGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(curPoint);
    curPoint->setAdaptiveSampling(false);
    curPoint->removeFromLegend();
    curPoint->setLineStyle(QCPGraph::lsNone);
    curPoint->setScatterStyle(QCPScatterStyle::ssCircle);
    curPoint->setPen(QPen(QBrush(Qt::red),2));
}

void MainWindow::clickedGraph(QMouseEvent *event)
{


    QPoint point = event->pos();

    startPoint->clearData();
    startPoint->addData(ui->customPlot->xAxis->pixelToCoord(point.x()),
                   ui->customPlot->yAxis->pixelToCoord(point.y()));

    curPoint->clearData();
    curPoint->addData(ui->customPlot->xAxis->pixelToCoord(point.x()) - 0.1,
                      ui->customPlot->yAxis->pixelToCoord(point.y()) - 0.1);
    curPoint->addData(ui->customPlot->xAxis->pixelToCoord(point.x()) + 0.1,
                      ui->customPlot->yAxis->pixelToCoord(point.y()) + 0.1);

    ui->customPlot->replot();
}


void MainWindow::on_pushButton_clicked()
{
    dialog->show();
}
