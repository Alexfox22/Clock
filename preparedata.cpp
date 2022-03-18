#include <QDebug>
#include <QTime>
#include <QThread>

#include <preparedata.h>

PrepareData::PrepareData(QObject *parent)
    : QObject{parent}
{
    m_format="";
    m_hours="";
    m_minutes="";
    m_seconds="";
}

QString PrepareData::readFormat()
{
    return m_format;
}

void PrepareData::changeFormat()
{
    if ((m_format=="am")||(m_format=="pm"))
    {
           m_format="";
    }
    else
    {
        if (m_hours.toInt()<13)
        {
            m_format="am";
        }
        else
        {
            m_format="pm";
        }
    }
    emit updateFormat();
}

QString PrepareData::readHours()
{
    QString buffer=m_hours;
    if (m_format=="")
    {
        m_hours = QTime::currentTime().toString("HH");
    }
    else
    {
        m_hours = QTime::currentTime().toString("hhAP");
    }
    if (buffer!=m_hours)
    {
    emit updateHours();
    }
    return m_hours;
}

QString PrepareData::readMinutes()
{
    QString buffer=m_minutes;
    m_minutes = QTime::currentTime().toString("mm");
    if (buffer!=m_minutes)
    {
    emit updateMinutes();
    }
    return m_minutes;
}

QString PrepareData::readSeconds()
{
    m_seconds = QTime::currentTime().toString("ss");
    emit updateSeconds();
    return m_seconds;
}

void PrepareData::receiveSignal()
{
    //qDebug() << "Second class in " << QThread::currentThread();
    readHours();
    readMinutes();
    readSeconds();
}
