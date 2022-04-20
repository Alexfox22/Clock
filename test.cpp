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

void test::setAmPm_test()
{
    PrepareData a;
    QVERIFY(a.setAmPm(QTime::fromString("1", "h")) == "am");
    QVERIFY(a.setAmPm(QTime::fromString("14", "h")) == "pm");
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
    a.receiveSignal(QTime::fromString("14", "h"));
    QVERIFY(a.readFormat() == "pm");

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

void test::receiveSignal_test()
{
    PrepareData a;
    QTime time = QTime::fromString("1.1.1", "h.m.s");
    a.receiveSignal(time);
    QCOMPARE(a.readFullTime().toString("HH:mm:ss"), time.toString("HH:mm:ss"));
}

void test::all_hours_combinations_24h_data()
{
    QTest::addColumn<QTime>("input");
    QTest::addColumn<QString>("result");
        for (int hour = 0; hour < 24; hour++)
        {
            char buffer[3];
            std::sprintf(buffer, "%02d", hour);
            QTest::newRow(buffer)<< QTime::fromString(buffer, "h") << buffer;
        }
}

void test::all_hoursAndFormat_combinations_12h_data()
{
    QTest::addColumn<QTime>("input");
    QTest::addColumn<QString>("result");
    QTest::addColumn<QString>("format");
    for (int hour = 0; hour < 24; hour++)
    {
        char input[3];
        char expect[3];
        std::sprintf(input, "%02d", hour);
        std::sprintf(expect, "%02d", (hour % 12 == 0)?12:(hour % 12));      //if 24h 00:00, am\pm 12:00
        if (hour < 12)
        {
           QTest::newRow(input)<< QTime::fromString(input, "h") << expect << "am";
        }
        else
        {
            QTest::newRow(input)<< QTime::fromString(input, "h") << expect << "pm";
        }
    }
}

void test::all_minutes_combinations_data()
{
    QTest::addColumn<QTime>("input");
    QTest::addColumn<QString>("result");
    for (int minute = 0; minute < 60; minute++)
    {
        char buffer[3];
        std::sprintf(buffer, "%02d", minute);
        QTest::newRow(buffer)<< QTime::fromString(buffer, "m") << buffer;
    }
}

void test::all_seconds_combinations_data()
{
    QTest::addColumn<QTime>("input");
    QTest::addColumn<QString>("result");
    for (int second = 0; second < 60; second++)
    {
        char buffer[3];
        std::sprintf(buffer, "%02d", second);
        QTest::newRow(buffer)<< QTime::fromString(buffer, "s") << buffer;
    }
}

void test::all_hours_combinations_24h()
{
    PrepareData a;
    QFETCH(QTime, input);
    QFETCH(QString, result);
    a.receiveSignal(input);
    QCOMPARE(a.readHours(), result);
}

void test::all_hoursAndFormat_combinations_12h()
{
    PrepareData a;
    a.changeFormat();
    QFETCH(QTime, input);
    QFETCH(QString, result);
    QFETCH(QString, format);
    a.receiveSignal(input);
    QCOMPARE(a.readHours(), result);
    QCOMPARE(a.readFormat(), format);
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
