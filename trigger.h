#ifndef TRIGGER_H
#define TRIGGER_H

#include <QThread>
#include <QTime>

class Trigger : public QThread
{
    Q_OBJECT

    void run();

signals:
    void sendSignal(QTime timeData);

public slots:
    void getSignal();

private:
    QTime m_timeData;
    bool m_label;

public:
    Trigger();
       ~Trigger();

};

#endif // TRIGGER_H
