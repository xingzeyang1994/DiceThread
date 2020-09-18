#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(&threadA, SIGNAL(started()), this, SLOT(onThreadAStarted()));
    connect(&threadA, SIGNAL(finished()), this, SLOT(onThreadAFinished()));
    connect(&threadA, SIGNAL(newValue(int, int)), this, SLOT(onThreadANewValue(int, int)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::closeEvent(QCloseEvent* event)
{
    if(threadA.isRunning())
    {
        threadA.diceStop();
        threadA.wait();
    }

    event->accept();
}

void Dialog::onThreadAStarted()
{
    ui->statusChangeLabel->setText("Thread Started!");
}

void Dialog::onThreadAFinished()
{
    ui->statusChangeLabel->setText("Thread Finished!");
}

void Dialog::onThreadANewValue(int seq, int diceValue)
{
    QString str = QString::asprintf("第%d次掷骰子,点数为:%d", seq, diceValue);
    ui->diceTextBrowser->append(str);
    QPixmap pic;
    QString picPath = QString::asprintf(":/diceImage/d%d.jpg", diceValue);
    pic.load(picPath);
    ui->pixmapLabel->setPixmap(pic);
}

void Dialog::on_startThreadButton_clicked()
{
    threadA.start();
    ui->startThreadButton->setEnabled(false);
    ui->stopThreadButton->setEnabled(true);
    ui->startDiceButton->setEnabled(true);
    ui->pauseDiceButton->setEnabled(false);
}

void Dialog::on_startDiceButton_clicked()
{
    threadA.diceBegin();
    ui->startDiceButton->setEnabled(false);
    ui->pauseDiceButton->setEnabled(true);
}

void Dialog::on_pauseDiceButton_clicked()
{
    threadA.dicePause();
    ui->startDiceButton->setEnabled(true);
    ui->pauseDiceButton->setEnabled(false);
}
void Dialog::on_stopThreadButton_clicked()
{
    threadA.diceStop();
    threadA.wait();
    ui->startThreadButton->setEnabled(true);
    ui->stopThreadButton->setEnabled(false);
    ui->startDiceButton->setEnabled(false);
    ui->pauseDiceButton->setEnabled(false);
}

void Dialog::on_clearTextButton_clicked()
{
    ui->diceTextBrowser->clear();
}
