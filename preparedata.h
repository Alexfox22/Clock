#ifndef PREPAREDATA_H
#define PREPAREDATA_H

#include <QObject>
#include <QTime>

class PrepareData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString format READ readFormat NOTIFY updateFormat)
    Q_PROPERTY(QString hours READ readHours NOTIFY updateHours)
    Q_PROPERTY(QString minutes READ readMinutes NOTIFY updateMinutes)
    Q_PROPERTY(QString seconds READ readSeconds NOTIFY updateSeconds)
    Q_PROPERTY(bool update READ readUpdate NOTIFY updateSmth)

public:
    explicit PrepareData(QObject *parent = nullptr);

    QString readFormat();

    Q_INVOKABLE void changeFormat();
    void changeHours();
    void changeMinutes();
    void changeSeconds();

    QString readHours();
    QString readMinutes();
    QString readSeconds();
    bool readUpdate();

signals:
    void updateFormat();
    void updateHours();
    void updateMinutes();
    void updateSeconds();
    void updateSmth();

    void exit_proc();   //we can emit this signal to finish work in trigger

public slots:
    void receiveSignal(QTime fullTime);

private:
    QString m_format;
    QString m_hours;
    QString m_minutes;
    QString m_seconds;
    QTime m_fullTime;
    bool m_update_animation;
};

#endif // PREPAREDATA_H
