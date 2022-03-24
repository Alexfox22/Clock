#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
//#include <QtGlobal>


class Logger: public QObject
{
     Q_OBJECT

public:
    explicit Logger (QObject *parent);

    Logger(){};

    Q_INVOKABLE void log_console(const QString message);

    Q_INVOKABLE void log_file(QString fileName, QString message, bool first_open);
};

#endif // LOGGER_H
