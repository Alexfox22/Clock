#include <logger.h>
#include <iostream>
#include <filesystem>
#include <QString>

#ifdef __cpp_lib_filesystem
namespace fs = std::filesystem;
#else
namespace fs = std::experimental::filesystem;
#endif

void Logger::log(const QString message)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_writeToFile==false)
    {
            fprintf(stderr, "%s \n", message.toStdString().c_str());
    }
    else
    {
            m_myfile << message.toStdString() << "\n";
    }
}

void Logger::setFileOutput(QString _fileName)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (fs::exists(_fileName.toStdString()))
    {
        m_myfile.open(_fileName.toStdString(),std::ofstream::trunc);
        m_myfile.close();
    }
    m_myfile.open(_fileName.toStdString(),std::ofstream::app);
    if (m_myfile.is_open() == true)   
    {
        m_writeToFile = true;
    }
}

void Logger::setConsoleOutput()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_writeToFile = false;
}

Logger::Logger()
{
   setConsoleOutput();
}
