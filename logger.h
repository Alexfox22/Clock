#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QThread>
#include <QVariant>
//#include <QString>
#include <fstream>
#include <iostream>

class Logger: public QObject
{
     Q_OBJECT

public:
    Logger();
    std::string to_stdString(QVariant arg);
    std::string to_stdString(int arg);
    std::string to_stdString(std::string arg);
    std::string to_stdString(const char* arg);

    template<typename... Args>
    void log(Args ... message)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_writeToFile==false)
        {
            ((fprintf(stderr, "%s ", (to_stdString(message).c_str()))), ...);
            fprintf(stderr, "\n");
        }
        else
        {
             ((m_myfile << to_stdString(message)), ...);
             m_myfile << "\n";
        }
    }
    Q_INVOKABLE void log(const QVariantList& message);
    void setConsoleOutput();
    void setFileOutput(QString _fileName);   

private:
    bool m_writeToFile;
    std::mutex m_mutex;
    std::ofstream m_myfile;

};

#endif // LOGGER_H
