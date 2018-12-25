#include "paramdialog.h"
#include "ui_paramdialog.h"
#include "mainwindow.h"

ParamDialog::ParamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamDialog)
{
    ui->setupUi(this);

    ui->funcChoice->addItem(listFunc[0]);
    ui->funcChoice->addItem(listFunc[1]);
    ui->funcChoice->setCurrentIndex(0);

    ui->leftX->setValue(leftX);
    ui->rightX->setValue(rightX);
    ui->leftY->setValue(leftY);
    ui->rightY->setValue(rightY);

    ui->numOfIter->setChecked(true);
    ui->num->setValue(num);

    ui->eps->setEnabled(false);
    ui->epsLabel->setEnabled(false);
    ui->eps->setValue(eps);

    ui->nmMethod->setChecked(true);
    ui->alpha->setValue(alpha);
    ui->beta->setValue(beta);
    ui->gamma->setValue(gamma);

    ui->probLabel->setEnabled(false);
    ui->prob->setEnabled(false);
    ui->prob->setValue(p);



}

ParamDialog::~ParamDialog()
{
    delete ui;
}

double ParamDialog::getLeftX() {
    return ui->leftX->value();
}

double ParamDialog::getRightX() {
    return ui->rightX->value();
}

double ParamDialog::getLeftY() {
    return ui->leftY->value();
}

double ParamDialog::getRightY() {
    return ui->rightY->value();
}

void ParamDialog::initMembers(UserFunction **f, UserDomain **domain,
                              UserCriterion **criterion, UserMethod **method) {
//    if(*f != nullptr)
//        delete *f;
//    if(*domain != nullptr)
//        delete *domain;
//    if(*criterion != nullptr)
//        delete criterion;
//    if(*method != nullptr)
//        delete method;


    if(ui->funcChoice->currentIndex() == 0)
        *f = new RosenbrockFunction();

    if(ui->funcChoice->currentIndex() == 1)
        *f = new TwoDimensionFunction();

    std::vector<double> leftBorders = {ui->leftX->value(), ui->leftY->value()};
    std::vector<double> rightBorders = {ui->rightX->value(), ui->rightY->value()};
    *domain = new UserDomain(leftBorders, rightBorders);
    (*f)->setDomain(*domain);

    //bool b1 = ui->numOfIter->isChecked();
    //int val = ui->num->value();
    if(ui->numOfIter->isChecked() == true)
        *criterion = new NumberOfIterationCriterion(ui->num->value());
    else
        *criterion = new FunctionValueCriterion(ui->eps->value());

   // bool b2 = ui->nmMethod->isChecked();
    if(ui->nmMethod->isChecked() == true)
        *method = new NelderMeadMethod(*f, *criterion, ui->alpha->value(), ui->beta->value(), ui->gamma->value());
    else
        *method = new RandomSearchMethod(*f, *criterion, ui->prob->value());
}



void ParamDialog::on_numOfIter_clicked()
{
    ui->num->setEnabled(true);
    ui->numLabel->setEnabled(true);
    ui->eps->setEnabled(false);
    ui->epsLabel->setEnabled(false);
}

void ParamDialog::on_funcVal_clicked()
{
    ui->eps->setEnabled(true);
    ui->epsLabel->setEnabled(true);
    ui->num->setEnabled(false);
    ui->numLabel->setEnabled(false);
}

void ParamDialog::on_nmMethod_clicked()
{
    ui->alpha->setEnabled(true);
    ui->alphaLabel->setEnabled(true);
    ui->beta->setEnabled(true);
    ui->betaLabel->setEnabled(true);
    ui->gamma->setEnabled(true);
    ui->gammaLabel->setEnabled(true);

    ui->prob->setEnabled(false);
    ui->probLabel->setEnabled(false);
}

void ParamDialog::on_rsMethod_clicked()
{
    ui->alpha->setEnabled(false);
    ui->alphaLabel->setEnabled(false);
    ui->beta->setEnabled(false);
    ui->betaLabel->setEnabled(false);
    ui->gamma->setEnabled(false);
    ui->gammaLabel->setEnabled(false);

    ui->prob->setEnabled(true);
    ui->probLabel->setEnabled(true);
}

void ParamDialog::on_okButton_clicked()
{
    emit okClicked(this);
    this->close();

}

void ParamDialog::on_cancelButton_clicked()
{
    this->close();
}
