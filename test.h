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
    void setAmPm_test();

    void receiveSignal_test();

    void changeFormat_test();
    void changeHours_test();
    void changeMinutes_test();
    void changeSeconds_test();
    void changeHoursMinutes_onlyWhenNecessary();

    void all_hours_combinations_24h_data();
    void all_hoursAndFormat_combinations_12h_data();
    void all_minutes_combinations_data();
    void all_seconds_combinations_data();

    void all_hours_combinations_24h();
    void all_hoursAndFormat_combinations_12h();
    void all_minutes_combinations();
    void all_seconds_combinations();

};
#endif // TEST_H

