#ifndef PARAMDIALOG_H
#define PARAMDIALOG_H

#include <QDialog>
#include "UserFunction.h"
#include "UserCriterion.h"
#include "UserMethod.h"
namespace Ui {
class ParamDialog;
}

class ParamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParamDialog(QWidget *parent = 0);
    ~ParamDialog();

private slots:
    void on_buttonBox_accepted();

    void on_numOfIter_clicked();

    void on_funcVal_clicked();

private:
    Ui::ParamDialog *ui;
    QString listFunc[2] = {"f(x,y)=(1-x)^2 + 100(y-x^2)^2", "g(x,y)=..."};
    QString funcChoice = "f(x,y)=(1-x)^2 + 100(y-x^2)^2";
    double leftX = -1.0;
    double rightX = 1.0;
    double leftY = -1.0;
    double rightY = 1.0;
    int critChoice = 1;//1 or 2
    int num = 100;
    double eps = 10e-6;
    int methodChoice = 1;//1 or 2
    double alpha = 1.0;
    double beta = 1.0;
    double gamma = 1.0;
    double p = 0.5;

};

#endif // PARAMDIALOG_H
