#include <QDebug>
#include <QThread>
#include <QTime>

#include <trigger.h>

Trigger::Trigger(QObject *parent)
    : QObject{parent}
{

}

void Trigger::runThread()
{
    while (true) {
        qDebug() << "First class in " << QThread::currentThread();
        m_timeData = QTime::currentTime().toString("HH:mm:ss");
        emit sendSignal(m_timeData);
        QThread::sleep(1);
    }
}



