#include <trigger.h>
#include <logger.h>
#include <Singletone.h>

Trigger::Trigger(){}

void Trigger::run()
{
    m_label = true;
    while (m_label == true) {
        m_timeData = QTime::currentTime();
        //Singletone<Logger>::instance()->log("Emitted");
        emit sendSignal(m_timeData);
        QThread::sleep(1);
    }
}

void Trigger::getSignal()
{
    m_label = false;
}

Trigger::~Trigger(){}
