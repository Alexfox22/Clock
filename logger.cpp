#include <logger.h>
#include <iostream>
#include <filesystem>
#include <QString>
#include <QDebug>

#ifdef __cpp_lib_filesystem
namespace fs = std::filesystem;
#else
namespace fs = std::experimental::filesystem;
#endif

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
            fprintf(stderr, "%s ", to_stdString(*j).c_str());
        }
        fprintf(stderr, "\n");
    }
    else
    {
        for (QVariantList::const_iterator j = message.begin(); j != message.end(); j++)
        {
            m_myfile << to_stdString(*j);
        }
        m_myfile << "\n";
    }
}

Logger::Logger()
{
   setConsoleOutput();
}

std::string Logger::to_stdString(QVariant arg)
{
    return arg.toString().toStdString();
}

std::string Logger::to_stdString(int arg)
{
    return std::to_string(arg);
}

std::string Logger::to_stdString(std::string arg)
{
    return arg;
}

std::string Logger::to_stdString(const char *arg)
{
    return arg;
}

