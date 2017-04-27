#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QTreeWidgetItem>
namespace Ui {
class modelbuilder;
}

class modelbuilder : public QMainWindow
{
    Q_OBJECT

public:
    explicit modelbuilder(QWidget *parent = 0);
    ~modelbuilder();
private slots:
    bool eventFilter(QObject *, QEvent *evt);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
   void startDrag(Qt::DropActions /*supportedActions*/);
   void setupMenus();
   void settool(QTreeWidgetItem *item, int column);
private:
    Ui::modelbuilder *ui;
};

#endif // MODELBUILDER_H
