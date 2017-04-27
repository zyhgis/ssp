#include "modelbuilder.h"
#include "ui_modelbuilder.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QRadioButton>

modelbuilder::modelbuilder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modelbuilder)
{
    ui->setupUi(this);

    ui->push1->installEventFilter(this);


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

    connect(ui->toolboxtree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(settool(QTreeWidgetItem*,int)));
//    QVBoxLayout *vbox = new QVBoxLayout(this);
//    ui->widget->setLayout(vbox);
}

modelbuilder::~modelbuilder()
{
    delete ui;
}

void modelbuilder::settool(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem *parent = item->parent();
    if(NULL==parent) //注意：最顶端项是没有父节点的，双击这些项时注意(陷阱)
        return;
    int col = parent->indexOfChild(item); //item在父项中的节点行号(从0开始)

    if(0==col) //Band1
    {
//        ui->label->setText(tr("dsds"));
        QMessageBox::information(this,tr("Word not found"),
                                 "Band1"); //执行对应操作
    }
    if(1==col) //Band2
    {
        QMessageBox::information(this,tr("Word not found"),
                                 "Band2");//执行对应操作
    }
    setupMenus();
}

void modelbuilder::setupMenus()
{

    QRadioButton *radio1 = new QRadioButton(tr("&Radio button 1"));
ui->gridLayout->addWidget(radio1);
//    vbox->addWidget(radio1);
//    QWidget *centerWindow = new QWidget(this);
//    this->setCentralWidget(centerWindow);
//    centerWindow->setLayout(vbox);
   QPushButton *pushbutton= new QPushButton("&Download", this);
   ui->gridLayout->addWidget(pushbutton);

}


void modelbuilder::dragEnterEvent(QDragEnterEvent *event)
{
//    if (event->mimeData()->hasFormat(modelbuilder::puzzleMimeType()))
//        event->accept();
//    else
//        event->ignore();
    event->accept();
    QMessageBox::information(this,tr("Word not found"),
                             "dragEnterEvent");//执行对应操作
}

void modelbuilder::dragMoveEvent(QDragMoveEvent *event)
{
//    if (event->mimeData()->hasFormat(modelbuilder::puzzleMimeType())) {
//        event->setDropAction(Qt::MoveAction);
//        event->accept();
//    } else {
//        event->ignore();
//    }
    event->accept();
    QMessageBox::information(this,tr("Word not found"),
                             "dragMoveEvent");//执行对应操作
}

void modelbuilder::dropEvent(QDropEvent *event)
{
//    if (event->mimeData()->hasFormat(modelbuilder::puzzleMimeType())) {
//        QByteArray pieceData = event->mimeData()->data(modelbuilder::puzzleMimeType());
//        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
//        QPixmap pixmap;
//        QPoint location;
//        dataStream >> pixmap >> location;

//        addPiece(pixmap, location);

//        event->setDropAction(Qt::MoveAction);
//        event->accept();
//    } else {
//        event->ignore();
//    }
//    QByteArray pieceData = event->mimeData()->data(modelbuilder::puzzleMimeType());
//    QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
//    QPixmap pixmap;
//    QPoint location;
//    dataStream >> pixmap >> location;

//    addPiece(pixmap, location);

    event->setDropAction(Qt::MoveAction);
    event->accept();
    QMessageBox::information(this,tr("Word not found"),
                             "dropEvent");//执行对应操作
}


void modelbuilder::startDrag(Qt::DropActions /*supportedActions*/)
{
    QMessageBox::information(this,tr("Word not found"),
                             "startDrag");//执行对应操作
//    QTreeWidgetItem *item = currentItem();

//    QByteArray itemData;
//    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
//    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
//    QPoint location = item->data(Qt::UserRole+1).toPoint();

//    dataStream << pixmap << location;

//    QMimeData *mimeData = new QMimeData;
//    mimeData->setData(PiecesList::puzzleMimeType(), itemData);

//    QDrag *drag = new QDrag(this);
//    drag->setMimeData(mimeData);
//    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
//    drag->setPixmap(pixmap);

//    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
//        delete takeItem(row(item));
}


bool modelbuilder::eventFilter(QObject *, QEvent *evt)
{
    static QPoint lastPnt;
    static bool isHover = false;
    // 鼠标按下
    if(evt->type() == QEvent::MouseButtonPress)
    {
    QMouseEvent* e = static_cast<QMouseEvent*>(evt);
    if(ui->push1->rect().contains(e->pos()) && //is the mouse is clicking the key
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
    ui->push1->move(ui->push1->x()+dx,ui->push1->y()+dy);
    }else if(evt->type() == QEvent::MouseButtonRelease && isHover)
    {
    isHover = false;
    }
    return false;
}
//void modelbuilder::dragEnterEvent(QDragEnterEvent *event){
//     event->accept();
//     QMessageBox::information(this,tr("Word not found"),
//                              "Band2");//执行对应操作
//}
