#include <QDebug>

#include <preparedata.h>

PrepareData::PrepareData(QObject *parent)
    : QObject{parent}
{
    m_format = "";
    m_hours = "";
    m_minutes = "";
    m_seconds = "";
    m_update = false;
}

QString PrepareData::readFormat()
{
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
    emit updateFormat();
}

QString PrepareData::readHours()
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
    return m_hours;
}

QString PrepareData::readMinutes()
{
    QString buffer = m_minutes;
    m_minutes = m_fullTime.toString("mm");
    if (buffer != m_minutes)
    {
    emit updateMinutes();
    }
    return m_minutes;
}

QString PrepareData::readSeconds()
{
    m_seconds = m_fullTime.toString("ss");
    m_update = true;
    emit updateSeconds();
    emit updateSmth();
    return m_seconds;
}

bool PrepareData::readUpdate()
{
    return m_update;
}

void PrepareData::receiveSignal(QTime fullTime)
{
    m_fullTime = fullTime;
    readHours();
    readMinutes();
    readSeconds();
}
