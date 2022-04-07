#include <logger.h>
#include <iostream>
#include <filesystem>
#include <QString>
#include <typeinfo>

#ifdef __cpp_lib_filesystem
namespace fs = std::filesystem;
#else
namespace fs = std::experimental::filesystem;
#endif

std::ostream& operator<<(std::ostream& stream, const QVariant& data)
{
    stream << data.toString().toStdString();
    return stream;
}

void Logger::setMode(m_modeType modeType, QString fileName)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (modeType == m_modeType::CONSOLE)
    {
        m_writeToFile = false;
    }
    else
    {
        if (fileName != "")
        {
            if (fs::exists(fileName.toStdString()) == true)
            {
                m_myfile.open(fileName.toStdString(), std::ofstream::trunc);
                m_myfile.close();
            }
            m_myfile.open(fileName.toStdString(), std::ofstream::app);
            if (m_myfile.is_open() == true)
            {
                m_writeToFile = true;
            }
        }
    }
}

void Logger::log(const QVariantList& message)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_writeToFile == false)
    {
        for (QVariantList::const_iterator iterator = message.begin(); iterator != message.end(); iterator++)
        {
            std::cerr << (*iterator);
        }
        std::cerr << "\n";
    }
    else
    {
        for (QVariantList::const_iterator iterator = message.begin(); iterator != message.end(); iterator++)
        {
            m_myfile << (*iterator);
        }
        m_myfile << "\n";
    }
}

Logger::Logger()
{
   m_writeToFile = false;
}
