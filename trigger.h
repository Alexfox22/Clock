#ifndef TRIGGER_H
#define TRIGGER_H

#include <QObject>

class Trigger : public QObject
{
    Q_OBJECT

public:
    explicit Trigger(QObject *parent = nullptr);

signals:
    void sendSignal(QString timeData);

public slots:
    void runThread();
private:
    QString m_timeData;
};

#endif // TRIGGER_H
