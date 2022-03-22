#include <QDebug>
#include <logger.h>
#include <preparedata.h>

PrepareData::PrepareData(QObject *parent)
    : QObject{parent}
{
    m_format = "";
    m_hours = "";
    m_minutes = "";
    m_seconds = "";
    m_update_animation = false;
    m_update_format = false;
}

QString PrepareData::readFormat()
{
    Logger::instance().log("Updated format");
    return m_format;
}

void PrepareData::changeFormat()
{
    if ((m_format == "am") || (m_format == "pm"))
    {
           m_format = "";
    }
    else
    {
        if (m_hours.toInt() < 13)
        {
            m_format = "am";
        }
        else
        {
            m_format = "pm";
        }
    }
    m_update_format = true;
}

void PrepareData::changeHours()
{
    QString buffer = m_hours;
    m_hours = m_fullTime.toString("HH");
    if ((m_format == "am") || (m_format == "pm"))
    {
        m_hours = QVariant(m_hours.toInt() % 12).toString();
    }
    if (buffer != m_hours)
    {
    emit updateHours();
    }
}

void PrepareData::changeMinutes()
{
    QString buffer = m_minutes;
    m_minutes = m_fullTime.toString("mm");
    if (buffer != m_minutes)
    {
    emit updateMinutes();
    }
}

void PrepareData::changeSeconds()
{
    m_seconds = m_fullTime.toString("ss");
    m_update_animation = true;
    emit updateSeconds();
    emit updateSmth();
    if (m_update_format == true)
    {
        emit updateFormat();
        m_update_format = false;
    }

}

QString PrepareData::readHours()
{    
    return m_hours;
}

QString PrepareData::readMinutes()
{    
    return m_minutes;
}

QString PrepareData::readSeconds()
{
    Logger::instance().log("Updated second");
    return m_seconds;
}

bool PrepareData::readUpdate()
{
    return m_update_animation;
}

void PrepareData::receiveSignal(QTime fullTime)
{
    Logger::instance().log("Get signal");
    m_fullTime = fullTime;
    changeHours();
    changeMinutes();
    changeSeconds();
}
