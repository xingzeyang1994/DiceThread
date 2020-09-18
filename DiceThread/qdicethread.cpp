#include "qdicethread.h"
#include <QTime>

QDiceThread::QDiceThread()
{

}

void QDiceThread::diceBegin()
{
    m_Paused = false;
}

void QDiceThread::dicePause()
{
    m_Paused = true;
}

void QDiceThread::diceStop()
{
    m_Stop = true;
}

void QDiceThread::run()
{
    m_Stop = false;
    m_seq = 0;
    qsrand(static_cast<unsigned int>(QTime::currentTime().msec()));

    while(!m_Stop)
    {
        if(!m_Paused)
        {
            m_diceValue = qrand();
            m_diceValue = (m_diceValue % 6) + 1;//1 - 6
            m_seq++;

            emit newValue(m_seq, m_diceValue);
        }

        msleep(500);
    }

    quit();
}
