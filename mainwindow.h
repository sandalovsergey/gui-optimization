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

    void setup(QCustomPlot* customPlot, ParamDialog* dialog);
    void init();


private slots:
    void clickedGraph(QMouseEvent* event);

    void on_pushButton_clicked();

    void draw(ParamDialog* dialog);


private:
    Ui::MainWindow *ui;
    QCPColorMap *colorMap = nullptr;
    QCPColorScale *colorScale = nullptr;
    QCPMarginGroup *marginGroup = nullptr;
    ParamDialog* dialog;

    QCPGraph* startPoint = nullptr;
    QCPGraph* curPoint = nullptr;
    QCPGraph* endPoint = nullptr;
    UserFunction* f = nullptr;
    UserDomain* domain = nullptr;
    UserCriterion* criterion = nullptr;
    UserMethod* method = nullptr;
    
    void drawPath(int pxlX, int pxlY);
    void printInformation();
};

#endif // MAINWINDOW_H
