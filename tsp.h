#ifndef TSP_H
#define TSP_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "dialog1.h"
#include "modelbuilder.h"
#include "observer.h"
namespace Ui {
class TSP;
}

class TSP : public QMainWindow
{
    Q_OBJECT

public:
    explicit TSP(QWidget *parent = 0);
    ~TSP();

private slots:
    void on_pushButton_clicked();
    void showSelectedImage(QTreeWidgetItem *item, int column);
    void getTool(QTreeWidgetItem *item, int column);
    void makeTool(bool a);
    bool eventFilter(QObject *, QEvent *);
    void getvalue(QMouseEvent *event);
    void getPoint(QMouseEvent *event);
    void toolClick();
    void readsspClick();
private:
    Ui::TSP *ui;
    Dialog1 *dialog;
    modelbuilder *model;
    Observer *obmodel;
};

#endif // TSP_H
