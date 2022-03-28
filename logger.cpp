#include <logger.h>
#include <fstream>
#include <iostream>

void Logger::log(const QString message)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (file_mode==false)
    {

            fprintf(stderr, "%s \n", message.toStdString().c_str());
            //qInfo(message.toStdString().c_str());
    }
    else
    {
            std::ofstream myfile;
            myfile.open(fileName.toStdString(), std::ofstream::app);
            myfile << message.toStdString() << "\n";
            myfile.close();
    }
}

void Logger::setMode(QString _fileName)
{
    std::ifstream myfile(_fileName.toStdString());
    if (myfile.is_open())
    {
        file_mode = true;
        fileName=_fileName;
        std::ofstream myfile(_fileName.toStdString(),std::ofstream::trunc);
    }
}

Logger::Logger()
{
    file_mode = false;
}
