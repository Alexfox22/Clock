#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QThread>
#include <QVariant>
#include <fstream>
#include <iostream>

class Logger: public QObject
{
     Q_OBJECT

public:
    Logger();
    Q_INVOKABLE void log(const QVariantList message);
    Q_INVOKABLE void log(const QString message);
    void setConsoleOutput();
    void setFileOutput(QString _fileName);

private:
    bool m_writeToFile;
    std::mutex m_mutex;
    std::ofstream m_myfile;
};

#endif // LOGGER_H
