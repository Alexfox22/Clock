#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QThread>


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
};

#endif // LOGGER_H
