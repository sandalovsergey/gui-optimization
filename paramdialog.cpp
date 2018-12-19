#include "paramdialog.h"
#include "ui_paramdialog.h"

ParamDialog::ParamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamDialog)
{
    ui->setupUi(this);

//    f = new RosenbrockFunction();
//    domain = new UserDomain(*(f->getDomain()));
//    criterion = new NumberOfIterationCriterion(100);
//    method = new NelderMeadMethod(f, criterion);

    //ui->funcChoice->addItem("f(x,y)=...");
    //ui->funcChoice->addItem("g(x,y)=...");

    ui->funcChoice->addItem(listFunc[0]);
    ui->funcChoice->addItem(listFunc[1]);

    ui->leftX->setValue(leftX);
    ui->rightX->setValue(rightX);
    ui->leftY->setValue(leftY);
    ui->rightY->setValue(rightY);

    ui->numOfIter->setChecked(true);
//    ui->epsLabel->setVisible(false);
//    ui->eps->setVisible(false);




}

ParamDialog::~ParamDialog()
{
    delete ui;
}

void ParamDialog::on_buttonBox_accepted()
{
    //leftY = ui->leftY->value();
}



void ParamDialog::on_numOfIter_clicked()
{
//    ui->numLabel->setVisible(true);
//    ui->num->setVisible(true);
//    ui->epsLabel->setVisible(false);
//    ui->eps->setVisible(false);
}

void ParamDialog::on_funcVal_clicked()
{
//    ui->numLabel->setVisible(false);
//    ui->num->setVisible(false);
//    ui->epsLabel->setVisible(true);
//    ui->eps->setVisible(true);
}
