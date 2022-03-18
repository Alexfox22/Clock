#ifndef PREPAREDATA_H
#define PREPAREDATA_H

#include <QObject>
#include <qqml.h>

class PrepareData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString format READ readFormat NOTIFY updateFormat)
    Q_PROPERTY(QString hours READ readHours NOTIFY updateHours)
    Q_PROPERTY(QString minutes READ readMinutes NOTIFY updateMinutes)
    Q_PROPERTY(QString seconds READ readSeconds NOTIFY updateSeconds)

public:
    explicit PrepareData(QObject *parent = nullptr);

    Q_INVOKABLE void changeFormat();
    QString readFormat();

    QString readHours();
    QString readMinutes();
    QString readSeconds();

signals:
    void updateFormat();
    void updateHours();
    void updateMinutes();
    void updateSeconds();

public slots:
    void receiveSignal();

private:
    QString m_format;
    QString m_hours;
    QString m_minutes;
    QString m_seconds;
};

#endif // PREPAREDATA_H