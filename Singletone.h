#ifndef SINGLETONE_H
#define SINGLETONE_H

template <typename T>
class Singletone
{
public:
    static T* instance()
    {
        static T myinstance;
        return &myinstance;
    }
};


#endif // SINGLETONE_H
