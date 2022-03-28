#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QThread>
#include <fstream>
#include <iostream>

class Logger: public QObject
{
     Q_OBJECT

public:
    Logger();
    Q_INVOKABLE void log(const QString message);
    void setMode(QString _fileName);

private:
    bool file_mode;
    QString fileName;
    std::mutex m_mutex;
    std::ofstream m_myfile;
};

#endif // LOGGER_H
