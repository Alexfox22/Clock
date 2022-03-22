#ifndef LOGGER_H
#define LOGGER_H
#include<iostream>
#include<string>
//using namespace std;

class Logger
{
public:
    static Logger instance(){
       return myinstance;
    }
    //std::ostream& log(){
      //  static bool firstLine = true;
        //        if (firstLine)
          //          firstLine = false;
            //    else
              //      std::cout << "\n";

                //return std::cout;
    //}
    void log(std::string str)
    {
        std::cout<<str;
    }
private:
    Logger(){};
    static Logger myinstance;
};

#endif // LOGGER_H
