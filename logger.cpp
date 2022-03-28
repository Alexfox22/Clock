#include <logger.h>
#include <fstream>
#include <iostream>
#include <filesystem>
//#include <cstdint>

namespace fs = std::filesystem;
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
            m_myfile << message.toStdString() << "\n";
    }
}

void Logger::setMode(QString _fileName)
{
    if (std::filesystem::exists(_fileName.toStdString()))
    {
        file_mode = true;
        fileName=_fileName;
        m_myfile.open(_fileName.toStdString(),std::ofstream::trunc);
        m_myfile.close();
        m_myfile.open(_fileName.toStdString(),std::ofstream::app);
    }
}

Logger::Logger()
{
    file_mode = false;
}
