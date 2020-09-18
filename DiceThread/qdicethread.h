#ifndef QDICETHREAD_H
#define QDICETHREAD_H

#include <QObject>
#include <QThread>

class QDiceThread : public QThread
{
    Q_OBJECT
public:
    QDiceThread();
    void diceBegin();
    void dicePause();
    void diceStop();

signals:
    void newValue(int seq, int diceValue);

public slots:

protected:
    void run() Q_DECL_OVERRIDE;

private:
    int m_seq = 0;//number
    int m_diceValue;//value
    bool m_Paused = true;
    bool m_Stop = false;
};

#endif // QDICETHREAD_H
