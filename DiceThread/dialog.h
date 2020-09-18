#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QThread>
#include <QCloseEvent>
#include <QLabel>
#include <qdicethread.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

protected:
    void closeEvent(QCloseEvent* event);

private:
    Ui::Dialog *ui;
    QDiceThread threadA;

private slots:
    void onThreadAStarted();
    void onThreadAFinished();
    void onThreadANewValue(int seq, int diceValue);
    void on_startThreadButton_clicked();
    void on_startDiceButton_clicked();
    void on_pauseDiceButton_clicked();
    void on_stopThreadButton_clicked();
    void on_clearTextButton_clicked();
};

#endif // DIALOG_H
