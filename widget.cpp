#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QLCDNumber>
#include <string>
using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    count = 0;

    lcdNumber = new QLCDNumber(this);

    pb10 = ui->pb10;
    pb50 = ui->pb50;
    pb100 = ui->pb100;
    pb500 = ui->pb500;

    pbinit = ui->pbinit;

    pbMilk = ui->pbMilk;
    pbCoffee = ui->pbCoffee;
    pbTea = ui->pbTea;

    lcdNumber->setMinimumSize(300,100);
    lcdNumber->move(50,20);
    lcdNumber->setDigitCount(10);

    connect(pb10, SIGNAL (press()), this, SLOT (on_pb10_clicked()));
    connect(pb50, SIGNAL (press()), this, SLOT (on_pb50_clicked()));
    connect(pb100, SIGNAL (press()), this, SLOT (on_pb100_clicked()));
    connect(pb500, SIGNAL (press()), this, SLOT (on_pb500_clicked()));
    connect(pbinit, SIGNAL (press()), this, SLOT (on_pbinit_clicked()));

    connect(pbMilk, SIGNAL (press()), this, SLOT (on_pbMilk_clicked()));
    connect(pbTea, SIGNAL (press()), this, SLOT (on_pbTea_clicked()));
    connect(pbCoffee, SIGNAL (press()), this, SLOT (on_pbCoffee_clicked()));

    pbMilk->setEnabled(false);
    pbCoffee->setEnabled(false);
    pbTea->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setEnabledButton()
{
    if(count>=300){
        pbCoffee->setEnabled(true);
        pbMilk->setEnabled(true);
        pbTea->setEnabled(true);
    }
    else if(count>=200){
        pbMilk->setEnabled(true);
        pbCoffee->setEnabled(true);
        pbTea->setEnabled(false);
    }
    else if(count>=100){
        pbCoffee->setEnabled(true);
        pbMilk->setEnabled(false);
        pbTea->setEnabled(false);
    }
    else{
        pbCoffee->setEnabled(false);
        pbMilk->setEnabled(false);
        pbTea->setEnabled(false);
    }
}

void Widget::increaseBalance(int value)
{
    count += value;
    lcdNumber->display(count);

    setEnabledButton();

}

void Widget::decreaseBalance(int value)
{
    if(count - value >= 0){
        count -= value;
        lcdNumber->display(count);
    }
    else{
        QMessageBox::information(
                    this, tr("QT자판기"), tr("돈이 부족합니다")
        );
    }

    setEnabledButton();

}

void Widget::on_pbinit_clicked()
{
    int left500 = count / 500;
    int left100 = (count-(left500*500)) / 100;
    int left50 = (count-(left500*500 + left100*100)) / 50;
    int left10 = (count - (left500*500 + left100*100 + left50*50)) / 10;

    string str = "500원 : " + to_string(left500) + "\n100원 : " + to_string(left100) + "\n50원 : "+ to_string(left50) + "\n10원" + to_string(left10);

    QMessageBox::information(
                this, tr("반환"), tr(str.c_str())
    );

    decreaseBalance(count);
}

void Widget::on_pb10_clicked()
{
    increaseBalance(10);
}

void Widget::on_pb50_clicked()
{
    increaseBalance(50);
}

void Widget::on_pb100_clicked()
{
    increaseBalance(100);
}

void Widget::on_pb500_clicked()
{
    increaseBalance(500);
}

void Widget::on_pbTea_clicked()
{
    decreaseBalance(300);
}

void Widget::on_pbMilk_clicked()
{
    decreaseBalance(200);
}

void Widget::on_pbCoffee_clicked()
{
    decreaseBalance(100);
}
