#include <test.h>
#include <preparedata.h>
#include <QtTest/QTest>
#include <QSignalSpy>
#include <charconv>
#include <iostream>

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

void test::changeFormat_test()
{
    PrepareData a;
    QSignalSpy spyHours(&a, SIGNAL(updateHours()));
    QSignalSpy spyFormat(&a, SIGNAL(updateFormat()));
    a.receiveSignal(QTime::fromString("1", "h"));
    a.changeFormat();
    QCOMPARE(spyHours.count(), 1);
    QCOMPARE(spyFormat.count(), 1);
    QVERIFY(a.readFormat() == "am");

    a.changeFormat();
    QVERIFY(a.readFormat() == "");

    a.receiveSignal(QTime::fromString("13", "h"));
    a.changeFormat();
    QVERIFY(a.readFormat() == "pm");
    QVERIFY(a.readHours() != 13);
}

void test::changeHours_test()
{
    PrepareData a;
    QSignalSpy spy(&a, SIGNAL(updateHours()));
    QTime time = QTime::fromString("1.1.1", "h.m.s");
    a.receiveSignal(time);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(a.readHours(), time.toString("HH"));
}

void test::changeMinutes_test()
{
    PrepareData a;
    QSignalSpy spy(&a, SIGNAL(updateMinutes()));
    QTime time = QTime::fromString("1.1.1", "h.m.s");
    a.receiveSignal(time);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(a.readMinutes(), time.toString("mm"));
}

void test::changeSeconds_test()
{
    PrepareData a;
    QSignalSpy spySeconds(&a, SIGNAL(updateSeconds()));
    QSignalSpy spyAnimation(&a, SIGNAL(updateAnimation()));
    QTime time = QTime::fromString("1.1.1", "h.m.s");
    a.receiveSignal(time);
    QCOMPARE(spySeconds.count(), 1);
    QCOMPARE(spyAnimation.count(), 1);
    QCOMPARE(a.readSeconds(), time.toString("ss"));
}

void test::changeHoursMinutes_onlyWhenNecessary()
{
    PrepareData a;
    QSignalSpy spyHours(&a, SIGNAL(updateHours()));
    a.receiveSignal(QTime::fromString("1.1.1", "h.m.s"));
    a.receiveSignal(QTime::fromString("1.1.2", "h.m.s"));
    QCOMPARE(spyHours.count(), 1);

    QSignalSpy spyMinutes(&a, SIGNAL(updateMinutes()));
    a.receiveSignal(QTime::fromString("1.2.1", "h.m.s"));
    a.receiveSignal(QTime::fromString("1.2.2", "h.m.s"));
    QCOMPARE(spyMinutes.count(), 1);
}

void test::all_hours_combinations_24h_data()
{
    QTest::addColumn<QTime>("input");
    QTest::addColumn<QString>("result");
        for (int hour = 0; hour < 24; hour++)
        {
            QString buffer = "";
            if (hour < 10)
                buffer = '0'+ QString::number(hour);
            else
                buffer = QString::number(hour);
            QTest::newRow(("hours: " + buffer).toStdString().c_str()) << QTime::fromString(buffer, "h") << buffer;
        }
}

void test::all_hours_combinations_12h_am_data()
{
    QTest::addColumn<QTime>("input");
    QTest::addColumn<QString>("result");
        for (int hour = 0; hour < 12; hour++)
        {
            QString buffer = "";
            if (hour < 10)
                buffer = '0'+ QString::number(hour);
            else
                buffer = QString::number(hour);
            QTest::newRow(("hours: " + buffer).toStdString().c_str()) << QTime::fromString(buffer, "h") << buffer;
        }
}

void test::all_hours_combinations_12h_pm_data()
{
    QTest::addColumn<QTime>("input");
    QTest::addColumn<QString>("result");
        for (int hour = 0; hour < 12; hour++)
        {
            QString buffer = "";
            if (hour < 10)
                buffer = '0'+ QString::number(hour);
            else
                buffer = QString::number(hour);
            QTest::newRow(("hours: " + buffer).toStdString().c_str()) << QTime::fromString(buffer, "h") << buffer;
        }
}

void test::all_minutes_combinations_data()
{
    QTest::addColumn<QTime>("input");
    QTest::addColumn<QString>("result");
    for (int minute = 0; minute < 60; minute++)
    {
        QString buffer;
        if (minute < 10)
            buffer = '0'+ QString::number(minute);
        else
            buffer = QString::number(minute);
        QTest::newRow(("minutes: " + buffer).toStdString().c_str()) << QTime::fromString(buffer, "m") << buffer;
    }
}

void test::all_seconds_combinations_data()
{
    QTest::addColumn<QTime>("input");
    QTest::addColumn<QString>("result");
    for (int second = 0; second < 60; second++)
    {
        QString buffer;
        if (second < 10)
            buffer = '0'+ QString::number(second);
        else
            buffer = QString::number(second);
        QTest::newRow(("seconds: " + buffer).toStdString().c_str()) << QTime::fromString(buffer, "s") << buffer;
    }
}

void test::receiveSignal_test()
{
    PrepareData a;
    QTime time = QTime::fromString("1.1.1", "h.m.s");
    a.receiveSignal(time);
    QCOMPARE(a.readFullTime().toString("HH:mm:ss"), time.toString("HH:mm:ss"));
}

void test::all_hours_combinations_24h()
{
    PrepareData a;
    QFETCH(QTime, input);
    QFETCH(QString, result);
    a.receiveSignal(input);
    QCOMPARE(a.readHours(), result);
}

void test::all_hours_combinations_12h_am()
{
    PrepareData a;
    a.changeFormat();
    QFETCH(QTime, input);
    QFETCH(QString, result);
    a.receiveSignal(input);
    QCOMPARE(a.readHours(), result);
}

void test::all_hours_combinations_12h_pm()
{
    PrepareData a;
    a.receiveSignal(QTime::fromString("13", "h"));
    a.changeFormat();
    QFETCH(QTime, input);
    QFETCH(QString, result);
    a.receiveSignal(input);
    QCOMPARE(a.readHours(), result);
}

void test::all_minutes_combinations()
{
    PrepareData a;
    QFETCH(QTime, input);
    QFETCH(QString, result);
    a.receiveSignal(input);
    QCOMPARE(a.readMinutes(), result);
}

void test::all_seconds_combinations()
{
    PrepareData a;
    QFETCH(QTime, input);
    QFETCH(QString, result);
    a.receiveSignal(input);
    QCOMPARE(a.readSeconds(), result);
}
QTEST_MAIN(test);
