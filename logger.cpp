#include <logger.h>
#include <iostream>
#include <filesystem>
#include <QString>

#ifdef __cpp_lib_filesystem
namespace fs = std::filesystem;
#else
namespace fs = std::experimental::filesystem;
#endif

void Logger::log(const QVariantList message)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_writeToFile==false)
    {
        for (QVariantList::const_iterator j = message.begin(); j != message.end(); j++)
        {
            fprintf(stderr, "%s ", (*j).toString().toStdString().c_str());
        }
        fprintf(stderr, "\n");
    }
    else
    {
        for (QVariantList::const_iterator j = message.begin(); j != message.end(); j++)
        {
            m_myfile << (*j).toString().toStdString();
        }
        m_myfile << "\n";
    }
}

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
    m_writeToFile = true;
    if (fs::exists(_fileName.toStdString()))
    {
        m_myfile.open(_fileName.toStdString(),std::ofstream::trunc);
        m_myfile.close();
    }
    m_myfile.open(_fileName.toStdString(),std::ofstream::app);
}

void Logger::setConsoleOutput()
{
        m_writeToFile = false;
}

Logger::Logger()
{
    setConsoleOutput();
}
