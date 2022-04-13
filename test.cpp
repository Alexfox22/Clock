#include <test.h>
#include <preparedata.h>
#include <QtTest/QTest>
#include <QSignalSpy>

test::test(QObject *parent)
    : QObject{parent}
{}

void test::readFormat_test()
{
    PrepareData a;
    QCOMPARE(a.readFormat(),"");
}

void test::readHours_test()
{
    PrepareData a;
    QCOMPARE(a.readHours(),"");
}

void test::readMinutes_test()
{
    PrepareData a;
    QCOMPARE(a.readMinutes(),"");
}

void test::readSeconds_test()
{
    PrepareData a;
    QCOMPARE(a.readSeconds(),"");
}

void test::readUpdate_test()
{
    PrepareData a;
    QCOMPARE(a.readUpdate(), false);
}

void test::changeFormat_change_test()
{
    PrepareData a;
    a.changeFormat();
    QCOMPARE(a.readFormat(), ("am"));
}

void test::changeFormat_emit_test()
{
    PrepareData a;
    QSignalSpy spyHours(&a, SIGNAL(updateHours()));
    QSignalSpy spyFormat(&a, SIGNAL(updateFormat()));
    a.changeFormat();
    QCOMPARE(spyHours.count(), 1);
    QCOMPARE(spyFormat.count(), 1);
}

void test::changeHours_change_test()
{
    PrepareData a;
    a.receiveSignal(QTime::currentTime());
    QCOMPARE(a.readHours(), QTime::currentTime().toString("HH"));
}

void test::changeHours_emit_test()
{
    PrepareData a;
    QSignalSpy spy(&a, SIGNAL(updateHours()));
    a.receiveSignal(QTime::currentTime());
    QCOMPARE(spy.count(), 1);
}

void test::changeMinutes_change_test()
{
    PrepareData a;
    a.receiveSignal(QTime::currentTime());
    QCOMPARE(a.readMinutes(), QTime::currentTime().toString("mm"));
}

void test::changeMinutes_emit_test()
{
    PrepareData a;
    QSignalSpy spy(&a, SIGNAL(updateMinutes()));
    a.receiveSignal(QTime::currentTime());
    QCOMPARE(spy.count(), 1);
}

void test::changeSeconds_change_test()
{
    PrepareData a;
    a.receiveSignal(QTime::currentTime());
    QCOMPARE(a.readSeconds(), QTime::currentTime().toString("ss"));
}

void test::changeSeconds_emit_test()
{
    PrepareData a;
    QSignalSpy spySeconds(&a, SIGNAL(updateSeconds()));
    QSignalSpy spyAnimation(&a, SIGNAL(updateAnimation()));
    a.receiveSignal(QTime::currentTime());
    QCOMPARE(spySeconds.count(), 1);
    QCOMPARE(spyAnimation.count(), 1);
}

void test::receiveSignal_test()
{
    PrepareData a;
    a.receiveSignal(QTime::currentTime());
    QCOMPARE(a.readFullTime().toString("HH:mm"), QTime::currentTime().toString("HH:mm"));
}

void test::receiveSignal_wrongData_test()
{
    PrepareData a;
    a.receiveSignal(QTime::currentTime());
    QTest::qWait(2);
    QEXPECT_FAIL("", "", Continue);
    QCOMPARE(a.readFullTime(), QTime::currentTime());
}

QTEST_MAIN(test);
