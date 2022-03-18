#include <QDebug>
#include <QThread>

#include <trigger.h>

Trigger::Trigger(QObject *parent)
    : QObject{parent}
{

}

void Trigger::runThread()
{
    while (true) {
        qDebug() << "First class in " << QThread::currentThread();
        emit sendSignal();
        QThread::sleep(1);
    }
}



