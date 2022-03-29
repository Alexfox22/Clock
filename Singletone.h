#ifndef SINGLETONE_H
#define SINGLETONE_H

#include <QThread>

template <typename T>

class Singletone
{
public:
    static T* instance()
    {
        static std::mutex m_mutex;
        std::lock_guard<std::mutex> lock(m_mutex);
        static T myinstance;
        return &myinstance;
    }
};


#endif // SINGLETONE_H
