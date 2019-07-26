#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pb10_clicked();
    void on_pb50_clicked();
    void on_pb100_clicked();
    void on_pb500_clicked();
    void on_pbinit_clicked();

    void on_pbCoffee_clicked();
    void on_pbMilk_clicked();
    void on_pbTea_clicked();

    void setEnabledButton();
    void increaseBalance(int value);
    void decreaseBalance(int value);

private:
    Ui::Widget *ui;
    QLCDNumber *lcdNumber;

    QPushButton *pb10;
    QPushButton *pb50;
    QPushButton *pb100;
    QPushButton *pb500;

    QPushButton *pbinit;
    QPushButton *pbMilk;
    QPushButton *pbCoffee;
    QPushButton *pbTea;

    int count;
};

#endif // WIDGET_H
