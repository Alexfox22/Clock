#include <logger.h>
#include <trigger.h>

void Trigger::run()
{
    m_label = true;
    while (m_label == true) {
        m_timeData = QTime::currentTime();
        Logger::instance().log("Sent signal");
        emit sendSignal(m_timeData);
        QThread::sleep(1);
    }
}

void Trigger::getSignal()
{
    m_label = false;
}

Trigger::~Trigger()
{

}
