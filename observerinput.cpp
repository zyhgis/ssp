#include "observerinput.h"
#include "ui_observerinput.h"
#include "QFile"
#include "QMessageBox"
#include "QTextStream"
observerinput::observerinput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::observerinput)
{
    ui->setupUi(this);
}

observerinput::~observerinput()
{
    delete ui;
}

void observerinput::on_buttonBox_accepted()
{

//    QMessageLogger
    QMessageBox::information(this,tr("Word not found"),
                             "Band2");//执行对应操作
    QVector<QString> inputstr(9);
    inputstr[0]=ui->dectectnum->text();
    inputstr[1]=ui->spotnum->text();
    inputstr[2]=ui->subnum->text();
    inputstr[3]=ui->dectectid->text();
    inputstr[4]=ui->spotdis->text();
    inputstr[5]=ui->minspotdis->text();
    inputstr[6]=ui->spotorder->text();
    inputstr[7]=ui->obserorder->text();
    inputstr[8]=ui->radius->text();
    QMessageBox::information(this,tr("Word not found"),
                             inputstr[0]);//执行对应操作

}
