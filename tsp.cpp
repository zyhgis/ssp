#include "tsp.h"
#include "ui_tsp.h"
#include "mainwindow.h"
#include "iostream"
#include "fstream"
#include "stdio.h"
#include "algorithm"
using namespace std;
static QVector<double> xx(101), yy(101); //全局变量，存储鼠标点
//int temp=1;
QString temp="1";
TSP::TSP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TSP)
{
    ui->setupUi(this);
    ui->label->installEventFilter(this);
    ui->toolboxtree->setColumnCount(1); //设置列数
    ui->toolboxtree->setHeaderLabel(tr("图像选择")); //设置头的标题


    QTreeWidgetItem *imageItem1 = new QTreeWidgetItem(ui->toolboxtree,QStringList(QString("图像1")));
    imageItem1->setIcon(0,QIcon(":images//example.jpg"));
    QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(imageItem1,QStringList(QString("Band1"))); //子节点1
    imageItem1->addChild(imageItem1_1); //添加子节点

    QTreeWidgetItem *imageItem2 = new QTreeWidgetItem(ui->toolboxtree,QStringList(QString("图像2")));
    QTreeWidgetItem *imageItem2_1 = new QTreeWidgetItem(imageItem2,QStringList(QString("Band1"))); //子节点1
    QTreeWidgetItem *imageItem2_2 = new QTreeWidgetItem(imageItem2,QStringList(QString("Band2"))); //子节点2
    imageItem2->addChild(imageItem2_1);  //添加子节点
    imageItem2->addChild(imageItem2_2);
    //    QMenu *helpMenu = menuBar()->addMenu("&Help");
    //    helpMenu->addAction(tr("A&bout"), this, &TSP::toolClick);
    //    helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    connect(ui->obverseaction,SIGNAL(triggered()),this,SLOT(toolClick()));
    connect(ui->readssp,SIGNAL(triggered()),this,SLOT(readsspClick()));
    ui->toolboxtree->expandAll(); //结点全部展开
    connect(ui->toolboxtree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showSelectedImage(QTreeWidgetItem*,int)));
    //    ui->toolboxtree->addTopLevelItem(osloItem);
    connect(ui->toolboxtree,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(getTool(QTreeWidgetItem*,int)));
    //connect(ui->scene,SIGNAL(clicked(bool)),this,SLOT(makeTool(bool)));
    //ui->toolboxtree->setDragEnabled(true);
    //ui->toolboxtree->setDragDropMode(QAbstractItemView::DropOnly);
    //connect(ui->toolboxtree,SIGNAL(startDrag()),this,SLOT(getTool(QTreeWidgetItem*,int)));
    //ui->tool->addAction("dsd",&TSP::toolClick);
    connect(ui->customPlot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(getvalue(QMouseEvent*)));
    connect(ui->customPlot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(getPoint(QMouseEvent*)));
}

TSP::~TSP()
{
    delete ui;
}
void TSP::toolClick(){
    obmodel =new Observer(this);
    //    model->setModal(false);
    obmodel->show();

}
void TSP::readsspClick(){
    int aa = 1;
    char b = 'c';
    double c = 2;
    QFile writeFile("1.dat");
    writeFile.open(QIODevice::WriteOnly);
    QDataStream out(&writeFile);
    out.writeRawData((char *)&aa, sizeof(int));
    out.writeRawData((char *)&b, sizeof(char));
    out.writeRawData((char *)&c, sizeof(double));
    writeFile.close();
    float aa1;
    float b1 ;
    float c1 ;
    //读文件
    QVector<float> result;
    QFile readFile("E:\\Qt\\data\\r-x.ssp");
    readFile.open(QIODevice::ReadOnly);
    QDataStream in(&readFile);
    int amount=readFile.size();
    for(int i=0;i<amount/sizeof(float);i++){
        in.readRawData((char *)&aa1, sizeof(float));
        result.append(aa1);
        //        in.readRawData((char *)&b1, sizeof(float));
        //        in.readRawData((char *)&c1, sizeof(float));
    }
    readFile.close();
    float lenone=floor(result[29]);
    float lendate=floor(result[29]);
    qDebug()<<lendate;
    float si=result[18];
    if(si==0){
        QMessageBox::information(this,"si=0","si=0");
    }

    float endtim=si*lendate;
    QVector<double> z;
    for(int i;;i++){
        if((si+si*i)<endtim){
            z.append(si+si*i);}
        else
            break;
    }
    int ntracea=0;
    float ntrace=result.size()/(60+lendate);
    QVector<int> pda;
    for(int i=0;i<ntrace;i++){
        pda.append(0);
    }
//    QDataStream in2(&readFile);
    QVector<QVector<double>> headissall(ntrace);
    QVector<QVector<double>> xx(lendate);
    //    for(int i=0;i<ntrace;i++){
    //        for(int j=0;j<60;j++){
    //            xx[i].append(0);
    //        }

    //    }
    QVector<double> x;
    float maxx;
    for(int i=0;i<ntrace;i++){
        for(int j=0;j<60;j++){
            headissall[i].append(result[j+(60+lendate)*i]);
        }
        if(headissall[i][19]>0)
        {
            ntracea++;
            pda[i]=1;
        }
        for(int k=0;k<lendate;k++){
            x.append(result[(lendate+60)*i+60+k]);
            xx[i].append(result[(lendate+60)*i+60+k]);
        }
        //        maxx=max_element(x);
//        maxx=*std::max_element(x.constBegin(),x.constEnd());
    }
    //    float maxmy1;
    //    maxmy1=*std::max_element(xx.constBegin(),xx.constEnd());

//    for(int i=0;i<ntrace;i++){
//        QString filename22="Data22.txt";
//        QFile file( filename22 );
//        for(int k=0;k<lendate;k++){

//            if ( file.open(QIODevice::ReadWrite) )
//            {
//                QTextStream stream( &file );
//                stream << xx[i][k] <<"  "<< endl;

//            }

//        }
//        file.close();

//    }

    QVector<float> absx;
    for(int i=0;i<ntrace;i++){
        for(int k=0;k<lendate;k++){
            x.append(xx[i][k]);
            absx.append(qAbs(x[k]));
        }

        maxx=*std::max_element(absx.constBegin(),absx.constEnd());
        for(int k=0;k<lendate;k++){
            x[k]=x[k]/maxx+i;
        }





//        QString filename22="Data.txt";
//        QFile file( filename22 );
//        if ( file.open(QIODevice::ReadWrite) )
//        {
//            QTextStream stream( &file );
//            for(int kk=0;kk<x.size();kk++){
//                stream << x[kk] <<"  "<< endl;
//            }
//        }
//        file.close();





        ui->customPlot->addGraph();
        ui->customPlot->graph()->setData(x, z);
        ui->customPlot->replot();
    }
    //    ui->customPlot->xAxis->setRange(-1, 1);
    ui->customPlot->yAxis->setRange(0, endtim);
    ui->customPlot->setInteraction(QCP::iRangeDrag,true);
    ui->customPlot->setInteraction(QCP::iRangeZoom,true);
    ui->customPlot->setInteraction(QCP::iMultiSelect,true);
    ui->customPlot->setInteraction(QCP::iSelectPlottables,true);
    //    ui->customPlot->setInteraction(QCP::);
    //ui->customPlot->legend->setVisible(true);
    qDebug()<<amount << aa1;

}

void TSP::getvalue(QMouseEvent *event){
    double x = ui->customPlot->xAxis->pixelToCoord(event->pos().x());
    double y = ui->customPlot->yAxis->pixelToCoord(event->pos().y());
    double z=x+y;
    QString message=QString("%1 , %2 , %3").arg(x).arg(y).arg(z);
    ui->statusBar->showMessage(message, 2500);
}
void TSP::getPoint(QMouseEvent *event){
    if(temp==2){
        double x = ui->customPlot->xAxis->pixelToCoord(event->pos().x());
        double y = ui->customPlot->yAxis->pixelToCoord(event->pos().y());
        xx.append(x);
        yy.append(y);

        //    ui->customPlot->graph()->setData(xx, yy);
        ui->customPlot->graph()->addData(x,y);
    }
}
void TSP::on_pushButton_clicked()
{
    model =new modelbuilder(this);
    //    model->setModal(false);
    model->show();

    // generate some data:
    QVector<double> x(101), y(101),z(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        z[i] = x[i]*x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:



    ui->customPlot->addGraph();
    ui->customPlot->graph()->setData(x, y);
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setData(x, z);
    //    ui->customPlot->graph(1)->setData(x, z);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(-1, 1);
    ui->customPlot->yAxis->setRange(0, 1);

    ui->customPlot->setInteraction(QCP::iRangeDrag,true);
    ui->customPlot->setInteraction(QCP::iRangeZoom,true);
    ui->customPlot->setInteraction(QCP::iMultiSelect,true);
    ui->customPlot->setInteraction(QCP::iSelectPlottables,true);
    //    ui->customPlot->setInteraction(QCP::);
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->replot();





    //    MainWindow window;
    //    window.loadImage(QStringLiteral(":/images/example.jpg"));
    //    window.show();
    //    return app.exec();
    //    MainWindow dialog;

    //   if(dialog.exec() != MainWindow::Accepted)//如果是取消就返回
    //   {
    //       window.loadImage(QStringLiteral(":/images/example.jpg"));
    //       window.show();
    //   return;
    //   }

}


bool TSP::eventFilter(QObject *, QEvent *evt)
{
    static QPoint lastPnt;
    static bool isHover = false;
    // 鼠标按下
    if(evt->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(evt);
        if(ui->label->rect().contains(e->pos()) && //is the mouse is clicking the key
                (e->button() == Qt::LeftButton)) //if the mouse click the right key
        {
            lastPnt = e->pos();
            isHover = true;
        }
    }
    // 鼠标移动
    else if(evt->type() == QEvent::MouseMove && isHover)
    {
        // 鼠标位置
        QMouseEvent* e = static_cast<QMouseEvent*>(evt);
        int dx = e->pos().x() - lastPnt.x();
        int dy=e->pos().y()-lastPnt.y();
        // 修改对象位置
        ui->label->move(ui->label->x()+dx,ui->label->y()+dy);
    }else if(evt->type() == QEvent::MouseButtonRelease && isHover)
    {
        isHover = false;
    }
    return false;
}

void TSP::makeTool(bool a){
    QMessageBox::information(this,tr("Word not found"),
                             "Band2");//执行对应操作
    if(temp!="1")
    {
        QMessageBox::information(this,tr("Word not found"),
                                 "Band2");//执行对应操作
        ui->label->setText(tr("dsd"));
    }
}

void TSP::getTool(QTreeWidgetItem *item, int column){
    QTreeWidgetItem *parent = item->parent();
    if(NULL==parent) //注意：最顶端项是没有父节点的，双击这些项时注意(陷阱)
        return;
    int col = parent->indexOfChild(item); //item在父项中的节点行号(从0开始)

    if(0==col) //Band1
    {
        temp="Band1";

    }
    if(1==col) //Band2
    {
        //        QMessageBox::information(this,tr("Word not found"),
        //                                 "Band2");//执行对应操作
        temp="Band2";
    }
}

void TSP::showSelectedImage(QTreeWidgetItem *item, int column)
{
    //    QString strcolumn=QString::number(column);
    //    QMessageBox::information(this,tr("Word not found"),
    //                             strcolumn); //执行对应操作

    QTreeWidgetItem *parent = item->parent();
    if(NULL==parent) //注意：最顶端项是没有父节点的，双击这些项时注意(陷阱)
        return;
    int col = parent->indexOfChild(item); //item在父项中的节点行号(从0开始)

    if(0==col) //Band1
    {
        ui->label->setText(tr("dsds"));
        QMessageBox::information(this,tr("Word not found"),
                                 "Band1"); //执行对应操作
    }
    if(1==col) //Band2
    {
        QMessageBox::information(this,tr("Word not found"),
                                 "Band2");//执行对应操作
    }
}
