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

    double getLeftX();
    double getRightX();
    double getLeftY();
    double getRightY();

    void initMembers(UserFunction** f, UserDomain** domain,
                     UserCriterion** criterion, UserMethod** method);


private slots:
    void on_numOfIter_clicked();

    void on_funcVal_clicked();

    void on_nmMethod_clicked();

    void on_rsMethod_clicked();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

signals :
    void okClicked(ParamDialog* dialog);

private:
    Ui::ParamDialog *ui;

    QString listFunc[2] = {"f(x,y)=(1-x)^2 + 100(y-x^2)^2", "g(x,y)=3x^2 + xy + 2y^2 - x - 4y"};
    double leftX = -2.0;
    double rightX = 2.0;
    double leftY = -2.0;
    double rightY = 2.0;
    int critChoice = 1;//1 or 2
    int num = 5000;
    double eps = 10e-5;
    int methodChoice = 1;//1 or 2
    double alpha = 1.0;
    double beta = 1.0;
    double gamma = 1.0;
    double p = 0.5;

};

#endif // PARAMDIALOG_H
