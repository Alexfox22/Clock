#include <logger.h>
//#include <QtGlobal>
#include <fstream>
#include <iostream>

void Logger::log_console(const QString message)
    {
        fprintf(stderr, "%s \n", message.toStdString().c_str());
        //qInfo(message.toStdString().c_str());
    }

void Logger::log_file(QString fileName, QString message, bool first_open)
    {
        std::ofstream myfile;
        if (first_open == true)
        {
            myfile.open(fileName.toStdString(), std::ofstream::trunc);
            myfile << message.toStdString() << "\n";
            myfile.close();
        }
        else
        {
            myfile.open(fileName.toStdString(), std::ofstream::app);
            myfile << message.toStdString() << "\n";
            myfile.close();
        }
}
