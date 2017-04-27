#ifndef OBSERVERINPUT_H
#define OBSERVERINPUT_H

#include <QDialog>

namespace Ui {
class observerinput;
}

class observerinput : public QDialog
{
    Q_OBJECT

public:
    explicit observerinput(QWidget *parent = 0);
    ~observerinput();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::observerinput *ui;
};

#endif // OBSERVERINPUT_H
