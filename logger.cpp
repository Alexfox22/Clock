#include <logger.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <QString>
#include <typeinfo>

#ifdef __cpp_lib_filesystem
namespace fs = std::filesystem;
#else
namespace fs = std::experimental::filesystem;
#endif

std::ostream& operator<<(std::ostream& os, const QVariant& dt)
{
    os << dt.toString().toStdString();
    return os;
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

void Logger::log(const QVariantList& message)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_writeToFile==false)
    {
        for (QVariantList::const_iterator j = message.begin(); j != message.end(); j++)
        {
            std::cerr << (*j);
        }
        std::cerr << "\n";
    }
    else
    {
        for (QVariantList::const_iterator j = message.begin(); j != message.end(); j++)
        {
            m_myfile << (*j);
        }
        m_myfile << "\n";
    }
}

Logger::Logger()
{
   setConsoleOutput();
}
