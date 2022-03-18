#ifndef TRIGGER_H
#define TRIGGER_H

#include <QObject>
#include <qqml.h>

class Trigger : public QObject
{
    Q_OBJECT

public:
    explicit Trigger(QObject *parent = nullptr);

signals:
    void sendSignal();

public slots:
    void runThread();
};

#endif // TRIGGER_H
