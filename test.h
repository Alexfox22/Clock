#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QtTest/QTest>

class test : public QObject
{
    Q_OBJECT
public:
    explicit test(QObject *parent = nullptr);

private slots:

    void readFormat_test();
    void readHours_test();
    void readMinutes_test();
    void readSeconds_test();
    void readUpdate_test();

    void receiveSignal_test();
    void receiveSignal_wrongData_test();

    void changeFormat_change_test();
    void changeFormat_emit_test();

    void changeHours_change_test();
    void changeHours_emit_test();
    void changeMinutes_change_test();
    void changeMinutes_emit_test();
    void changeSeconds_change_test();
    void changeSeconds_emit_test();

};
#endif // TEST_H

