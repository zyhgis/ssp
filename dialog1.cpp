#include "dialog1.h"
#include "ui_dialog1.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
//     ui->push1->installEventFilter(this);
    ui->toolboxtree->setColumnCount(1); //设置列数
    ui->toolboxtree->setHeaderLabel(tr("图像选择")); //设置头的标题


    QTreeWidgetItem *imageItem1 = new QTreeWidgetItem(ui->toolboxtree,QStringList(QString("图像1")));
    imageItem1->setIcon(0,QIcon("xxx.png"));
    QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(imageItem1,QStringList(QString("Band1"))); //子节点1
    imageItem1->addChild(imageItem1_1); //添加子节点

    QTreeWidgetItem *imageItem2 = new QTreeWidgetItem(ui->toolboxtree,QStringList(QString("图像2")));
    QTreeWidgetItem *imageItem2_1 = new QTreeWidgetItem(imageItem2,QStringList(QString("Band1"))); //子节点1
    QTreeWidgetItem *imageItem2_2 = new QTreeWidgetItem(imageItem2,QStringList(QString("Band2"))); //子节点2
    imageItem2->addChild(imageItem2_1);  //添加子节点
    imageItem2->addChild(imageItem2_2);

    ui->toolboxtree->expandAll(); //结点全部展开
}

Dialog1::~Dialog1()
{
    delete ui;
}
