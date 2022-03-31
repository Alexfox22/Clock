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
    template<typename... Args>
    void log(Args ... message)
    {
            std::lock_guard<std::mutex> lock(m_mutex);
                if (m_writeToFile==false)
                {
                    ((fprintf(stderr, "%s ", ((QVariant)message).toString().toStdString().c_str())), ...);
                    fprintf(stderr, "\n");
                }
                else
                {
                    ((m_myfile << ((QVariant)message).toString().toStdString()<< ' '), ...);
                    m_myfile << "\n";
                }
    }
    Q_INVOKABLE void log(const QString message);
    void setConsoleOutput();
    void setFileOutput(QString _fileName);

private:
    bool m_writeToFile;
    std::mutex m_mutex;
    std::ofstream m_myfile;
};

#endif // LOGGER_H
