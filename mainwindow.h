#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "paramdialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setup(QCustomPlot* customPlot);
    void init();

private slots:
    void clickedGraph(QMouseEvent* event);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QCPColorMap *colorMap = nullptr;
    QCPGraph* startPoint = nullptr;
    QCPGraph* curPoint = nullptr;
    ParamDialog* dialog;
};

#endif // MAINWINDOW_H
