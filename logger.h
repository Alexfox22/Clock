#ifndef LOGGER_H
#define LOGGER_H

#include <QtGlobal>
#include <string>
#include <fstream>
#include <iostream>
#include <QObject>

class Logger: public QObject
{
     Q_OBJECT

public:
    explicit Logger (QObject *parent);

    Logger(){};

    Q_INVOKABLE void log_console(const QString message)
    {
        fprintf(stderr, "%s \n", message.toStdString().c_str());
        //qInfo(message.toStdString().c_str());
    }

    Q_INVOKABLE void log_file(std::string fileName, std::string message, bool first_open)
    {
        std::ofstream myfile;
        if (first_open == true)
        {
            myfile.open(fileName, std::ofstream::trunc);
            myfile << message << "\n";
            myfile.close();

        }
        else
        {
            myfile.open(fileName, std::ofstream::app);
            myfile << message << "\n";
            myfile.close();
        }
    }
};

#endif // LOGGER_H
