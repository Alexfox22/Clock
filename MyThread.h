#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QObject>
#include <QThread>

class MyThread : public QThread
 {
    Q_OBJECT
protected:
    void run();
 };
void MyThread::run()
{

}


#endif // MYTHREAD_H
