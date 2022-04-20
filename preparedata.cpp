#include <QDebug>
#include <QThread>
#include <logger.h>
#include <Singletone.h>
#include <preparedata.h>

PrepareData::PrepareData(QObject *parent)
    : QObject{parent}
{
    m_format = "";
    m_hours = "";
    m_minutes = "";
    m_seconds = "";
    m_updateAnimation = false;
}

QString PrepareData::readFormat()
{
    return m_format;
}

QString PrepareData::setAmPm(QTime m_time)
{
    if (m_time.hour() < 12)
    {
        return "am";
    }
    else
    {
        return "pm";
    }
}

void PrepareData::changeFormat()
{
    if ((m_format == "am") || (m_format == "pm"))
    {
           m_format = "";
    }
    else
    {
       m_format = setAmPm(m_fullTime);
    }
    changeHours();
    emit updateFormat();
}

void PrepareData::changeHours()
{
    QString buffer = m_hours;

    if (m_format == "")
    {
        m_hours = m_fullTime.toString("HH");
    }
    else
    {
        m_hours = m_fullTime.toString("hhap");
    }
    if (buffer != m_hours)
    {
        if (m_format != "")
        {
            m_format = setAmPm(m_fullTime);
            emit updateFormat();
        }
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
    m_updateAnimation = true;
    emit updateSeconds();
    emit updateAnimation();
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
    //Singletone<Logger>::instance()->log("Updated second ", m_seconds);
    return m_seconds;
}

bool PrepareData::readUpdate()
{
    return m_updateAnimation;
}

QTime PrepareData::readFullTime()
{
    return m_fullTime;
}

void PrepareData::receiveSignal(QTime fullTime)
{
    //Singletone<Logger>::instance()->log("Received");
    m_fullTime = fullTime;
    changeHours();
    changeMinutes();
    changeSeconds();
}
