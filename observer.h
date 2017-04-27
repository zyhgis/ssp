#ifndef OBSERVER_H
#define OBSERVER_H
#include "observerinput.h"
#include <QMainWindow>

namespace Ui {
class Observer;
}

class Observer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Observer(QWidget *parent = 0);
    ~Observer();

private slots:
    void on_editButton_clicked();

    void on_saveButton_clicked();

    void on_buttonBox_2_accepted();

private:
    Ui::Observer *ui;
    observerinput *obinmodel;
};

#endif // OBSERVER_H
