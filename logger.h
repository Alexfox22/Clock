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
    enum m_modeType
    {
        CONSOLE, FILE
    };
    template<typename... Args>
    void log(Args ... message)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_writeToFile == false)
        {
            ((std::cerr << message), ...);
            std::cerr << "\n";
        }
        else
        {
             ((m_myfile << message), ...);
             m_myfile << "\n";
        }
    }
    Q_INVOKABLE void log(const QVariantList& message);
    void setMode(m_modeType modeType, QString fileName = "");
    friend std::ostream& operator<<(std::ostream& stream, const QVariant& data);

private:
    bool m_writeToFile;
    std::mutex m_mutex;
    std::ofstream m_myfile;
};

#endif // LOGGER_H
