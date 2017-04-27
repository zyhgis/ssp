#include "observer.h"
#include "ui_observer.h"
#include "QStandardItemModel"
#include "observerinput.h"
#include "QMessageBox"
#include "QFile"
#include "QTextStream"
#include "QFileDialog"
#include "QVector"
QStandardItemModel  *model = new QStandardItemModel();
QStandardItemModel *spotmodel=new QStandardItemModel();
Observer::Observer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Observer)
{

    ui->setupUi(this);

    model->setColumnCount(6);
    //    model->setHeaderData();
    model->setHeaderData(0,Qt::Horizontal,QString::fromStdString("点号"));//检波点号
    model->setHeaderData(1,Qt::Horizontal,QString::fromStdString("孔深"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromStdString("孔高"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromStdString("倾角"));
    model->setHeaderData(4,Qt::Horizontal,QString("方位"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromStdString("跑间距检波点桩号"));//跑间距检波点桩号
    //    model->setHeaderData(6,Qt::Horizontal,QString::fromLocal8Bit("xingming"));
    //    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("xingming"));
    ui->detecttableView->setModel(model);



    spotmodel->setColumnCount(7);
    spotmodel->setHeaderData(0,Qt::Horizontal,QString::fromStdString("炮号"));//检波点号
    spotmodel->setHeaderData(1,Qt::Horizontal,QString::fromStdString("药量"));
    spotmodel->setHeaderData(2,Qt::Horizontal,QString::fromStdString("孔深"));
    spotmodel->setHeaderData(3,Qt::Horizontal,QString::fromStdString("孔高"));
    spotmodel->setHeaderData(4,Qt::Horizontal,QString::fromStdString("倾角"));
    spotmodel->setHeaderData(5,Qt::Horizontal,QString::fromStdString("方位"));
    spotmodel->setHeaderData(6,Qt::Horizontal,QString::fromStdString("炮距"));
    ui->spottableView->setModel(spotmodel);

    //    ui->obsystem->
    ui->obserorder->setText("R");
    ui->radius->setText("16");
    ui->spotdis->setText("1.5");
    ui->dectectnum->setText("1");
    ui->spotorder->setText("D");
    ui->dectectid->setText("TKM+997");
    ui->spotnum->setText("24");
    ui->minspotdis->setText("20");
    ui->subnum->setText("3");
}

Observer::~Observer()
{
    delete ui;
}

void Observer::on_editButton_clicked()
{
    obinmodel =new observerinput(this);
    obinmodel->show();
}

void Observer::on_saveButton_clicked()
{
    QString leftorright= ui->obserorder->text();
    QString radl=ui->radius->text();
    QString shotspace=ui->spotdis->text();
    QString geophs=ui->dectectnum->text();
    QString order=ui->spotorder->text();
    QString geophone=ui->dectectid->text();
    QString shot=ui->spotnum->text();
    QString minoffset=ui->minspotdis->text();
    QString component=ui->subnum->text();

    //    for(int i = 0; i < 3; i++)
    //    {
    //        model->setItem(i,0,new QStandardItem("2009441676"));
    //        //设置字符颜色
    //        model->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));
    //        //设置字符位置
    //        model->item(i,0)->setTextAlignment(Qt::AlignCenter);
    //        model->setItem(i,1,new QStandardItem(QString::fromStdString("哈哈")));
    //    }
    int data[12][7]={{1,50,2,1.4,0,90,20},{2,50,2,1.4,0,90,21.5},
                     {3,50,2,1.4,0,90,23},{4,50,2,1.4,0,90,24.5},
                     {5,50,2,1.4,0,90,26},{6,50,2,1.4,0,90,27.5},
                     {7,50,2,1.4,0,90,29},{8,50,2,1.4,0,90,30.5},
                     {9,50,2,1.4,0,90,31.5},{10,50,2,1.4,0,90,33},
                     {11,50,2,1.4,0,90,34.5},{12,50,2,1.4,0,90,36}};

    QVector<QVector<double>> data1(shot.toInt());
    //    for(int i=0; i<shot.toInt(); i++)
    //            data1[i].resize(7);//里层容器大小设置为7
    //    QString data1[shot][7]={};
    if(order=='D'){
        for(int i=0;i<shot.toInt();i++){
            data1[i].append(i+1);
            data1[i].append(data[0][1]);
            data1[i].append(data[0][2]);
            data1[i].append(data[0][3]);
            data1[i].append(data[0][4]);
            data1[i].append(data[0][5]);
            data1[i].append(minoffset.toInt()+(shot.toInt()-i-1)*(shotspace.toDouble()));
            //            data1[i][0]=(i+1);
            //            data1[i][1]=(data[1][1]);
            //            data1[i][2]=data[1][2];
            //            data1[i][3]=data[1][3];
            //            data1[i][4]=data[1][4];
            //            data1[i][5]=data[1][5];
            //            data1[i][6]= minoffset.toInt()+(shot.toInt()-i-1)*(shotspace.toInt());
        }
        for(int i = 0; i < shot.toInt(); i++)
        {
            for(int j=0; j<6;j++){
                spotmodel->setItem(i,j,new QStandardItem(QString::number(data1[i][j],10,0)));
                //            QMessageBox::information(this,tr("Word not found"),
                //                                     QString::number(data1[i][j],10));//执行对应操作
                //            model->setItem(i,1,new QStandardItem(QString::fromStdString("哈哈")));
            }
            spotmodel->setItem(i,6,new QStandardItem(QString::number(data1[i][6],10,2)));
        }
    }
    if (geophs=="2"){
        QString datar[2][6]={{'1','2','1.4','0','90','0'},
                             {'2','2','2','0','90','0'}};
        for(int i = 0; i < 2; i++)
        {
            for(int j=0; j<6;j++){
                model->setItem(i,j,new QStandardItem(datar[i][j]));

                //            model->setItem(i,1,new QStandardItem(QString::fromStdString("哈哈")));
            }
        }
    }
    else if(geophs=="1"){
        double datar[6]={1,2,1.4,0,90,0};
        for(int i = 0; i < 6; i++)
        {
            model->setItem(0,i,new QStandardItem(QString::number(datar[i],10,2)));

        }
    }
}

void Observer::on_buttonBox_2_accepted()
{
    QString leftorright= ui->obserorder->text();
    QString radl=ui->radius->text();
    QString shotspace=ui->spotdis->text();
    QString geophs=ui->dectectnum->text();
    QString order=ui->spotorder->text();
    QString geophone=ui->dectectid->text();
    QString shot=ui->spotnum->text();
    QString minoffset=ui->minspotdis->text();
    QString component=ui->subnum->text();
    QString file_path = QFileDialog::getExistingDirectory(this,"请选择模板保存路径...","./");
    QVector<QVector<double>> data1(7);

    QAbstractItemModel *modessl = ui->detecttableView->model();
    int columncount=modessl->columnCount();
    int rowcount=modessl->rowCount();
    for(int i=0;i<rowcount;i++){
        for(int j=0;j<columncount;j++){
            QModelIndex indextemp = modessl->index(i,j);//遍历第一行的所有列
            data1[i].append(modessl->data(indextemp).toDouble());
        }
    }
    if(leftorright=="R"){
        if(file_path.isEmpty())
        {
            return;
        }else{

            QString filename=file_path+"/"+"receiver_geo1.txt";
            QMessageBox::information(this,tr("Word not found"),
                                     filename);//执行对应操作
            QFile file(filename);
            if ( file.open(QIODevice::ReadWrite) )
            { QTextStream stream( &file );
                for(int i=0;i<rowcount;i++){

                    stream.setFieldAlignment(QTextStream::AlignRight);
                    stream.setFieldWidth(6);
                    stream << QString::number(data1[i][0],10,0);
                    stream.setFieldWidth(14);
                    stream<<QString::number(data1[i][5],10,2);
                    double temp=-radl.toDouble()-data1[i][1];
                    stream<<QString::number(temp,10,2);
                    stream<<QString::number(data1[i][2],10,2);
                    stream<<QString::number(0,10,2);

                }
                if(geophs=="2"){
                    QMessageBox::information(this,tr("Word not found"),
                                             filename);//执行对应操作
                    QFile file(filename);
                    if ( file.open(QIODevice::ReadWrite) )
                    {
                        stream.setFieldAlignment(QTextStream::AlignRight);
                        stream.setFieldWidth(6);
                        stream << QString::number(data1[1][0],10,0);
                        stream.setFieldWidth(14);
                        stream<<QString::number(data1[1][5],10,2);
                        double temp=radl.toDouble()+data1[1][1];
                        stream<<QString::number(temp,10,2);
                        stream<<QString::number(data1[1][2],10,2);
                        stream<<QString::number(0,10,2);
                    }
                }
            }
        }
    }
    else if(leftorright=="L"){
        QString filename=file_path+"/"+"receiver_geo1.txt";
        QMessageBox::information(this,tr("Word not found"),
                                 filename);//执行对应操作
        QFile file(filename);
        if ( file.open(QIODevice::ReadWrite) )
        {  QTextStream stream( &file );
            for(int i=0;i<rowcount;i++){

                stream.setFieldAlignment(QTextStream::AlignRight);
                stream.setFieldWidth(6);
                stream << QString::number(data1[i][0],10,0);

                stream.setFieldWidth(14);
                stream<<QString::number(data1[i][5],10,2);
                double temp=radl.toDouble()+data1[i][1];
                stream<<QString::number(temp,10,2);
                stream<<QString::number(data1[i][2],10,2);
                stream<<QString::number(0,10,2);

            }
            if(geophs=="2"){
                QMessageBox::information(this,tr("Word not found"),
                                         filename);//执行对应操作
//                QFile file(filename);
                if ( file.open(QIODevice::ReadWrite) )
                {
                    stream.setFieldAlignment(QTextStream::AlignRight);
                    stream.setFieldWidth(6);
                    stream << QString::number(data1[1][0],10,0);
                    stream.setFieldWidth(14);
                    stream<<QString::number(data1[1][5],10,2);
                    double temp=-radl.toDouble()-data1[1][1];
                    stream<<QString::number(temp,10,2);
                    stream<<QString::number(data1[1][2],10,2);
                    stream<<QString::number(0,10,2);
                }
            }

        }
    }
    //    QModelIndex indextemp = modessl->index(1,1);//遍历第一行的所有列
    //    QString datatemp = modessl->data(indextemp).toString();
    //    QMessageBox::information(this,tr("Word not found"),
    //                             datatemp);//执行对应操作

    QVector<QVector<double>> data2(24);
    QAbstractItemModel *modelspot = ui->spottableView->model();
    int modelspotcolumncount=modelspot->columnCount();
    int modelspotrowcount=modelspot->rowCount();
    for(int i=0;i<modelspotrowcount;i++){
        for(int j=0;j<modelspotcolumncount;j++){
            QModelIndex indextemp = modelspot->index(i,j);//遍历第一行的所有列
            data2[i].append(modelspot->data(indextemp).toDouble());
        }
    }
    if(leftorright=="R"){
        if(file_path.isEmpty())
        {
            return;
        }else{

            QString filename=file_path+"/"+"source_geo1.txt";
            QMessageBox::information(this,tr("Word not found"),
                                     filename);//执行对应操作
            QFile file(filename);
            if ( file.open(QIODevice::ReadWrite) )
            {
                for(int i=0;i<modelspotrowcount;i++){
                    QTextStream stream( &file );
                    stream.setFieldAlignment(QTextStream::AlignRight);
                    stream.setFieldWidth(6);
                    stream << QString::number(data2[i][0],10,0);
                    stream.setFieldWidth(14);
                    stream<<QString::number(data2[i][6],10,2);
                    double temp=-radl.toDouble()-data2[i][2];
                    stream<<QString::number(temp,10,2);
                    stream<<QString::number(data2[i][3],10,2);
                    stream<<QString::number(0,10,2);
                    stream.setFieldWidth(0);
                    stream<<endl;
                }
            }
        }
    }
    else if(leftorright=="L"){
        QString filename=file_path+"/"+"source_geo1.txt";
        QMessageBox::information(this,tr("Word not found"),
                                 filename);//执行对应操作
        QFile file(filename);
        if ( file.open(QIODevice::ReadWrite) )
        {
            for(int i=0;i<modelspotrowcount;i++){
                QTextStream stream( &file );
                stream.setFieldAlignment(QTextStream::AlignRight);
                stream.setFieldWidth(6);
                stream << QString::number(data2[i][0],10,0);
                stream.setFieldWidth(14);
                stream<<QString::number(data2[i][6],10,2);
                double temp=radl.toDouble()+data2[i][2];
                stream<<QString::number(temp,10,2);
                stream<<QString::number(data2[i][3],10,2);
                stream<<QString::number(0,10,2);
                stream.setFieldWidth(0);
                stream<<endl;
            }
        }
    }
    //    QModelIndex indextemp = modessl->index(1,1);//遍历第一行的所有列
    //    QString datatemp = modessl->data(indextemp).toString();
    //    QMessageBox::information(this,tr("Word not found"),
    //                             datatemp);//执行对应操作

    QString filename=file_path+"/"+"recording_geo1.txt";
    QMessageBox::information(this,tr("Word not found"),
                             filename);//执行对应操作
    QFile file(filename);
    if ( file.open(QIODevice::ReadWrite) )
    {
        for(int i=0;i<modelspotrowcount;i++){
            QTextStream stream( &file );
            stream.setFieldAlignment(QTextStream::AlignRight);
            stream.setFieldWidth(6);
            stream << QString::number(data2[i][0],10,0);
            stream<<QString::number(1,10,2);
            stream<<QString::number(geophs.toDouble(),10,2);
            stream<<QString::number(data2[i][0],10,2);
            stream.setFieldWidth(0);
            stream<<endl;
        }
    }

//    if(file_path.isEmpty())
//    {
//        return;
//    }else{

//        QString filename=file_path+"/"+"Data.txt";
//        QMessageBox::information(this,tr("Word not found"),
//                                 filename);//执行对应操作
//        QFile file( filename );
//        if ( file.open(QIODevice::ReadWrite) )
//        {
//            QTextStream stream( &file );
//            stream << "dsdsds" << endl;
//        }
//    }
//    QString filename="Data.txt";
//    QFile file( filename );
//    if ( file.open(QIODevice::ReadWrite) )
//    {
//        QTextStream stream( &file );
//        stream << "dsdsds" << endl;
//    }
}
