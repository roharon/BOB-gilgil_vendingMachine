#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QLCDNumber>
#include <stdio.h>

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
}

Widget::~Widget()
{
    delete ui;
}

void Widget::increaseBalance(int value)
{
    count += value;
    lcdNumber->display(count);
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

}

void Widget::on_pbinit_clicked()
{
    count = 0;
    lcdNumber->display(count);
}

void Widget::on_pb10_clicked()
{
    printf("MONEY = %d\n",count);
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
