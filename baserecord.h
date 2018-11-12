#ifndef BASERECORD_H
#define BASERECORD_H
#include <ctime>
#include <string>
using namespace std;

class BaseRecord
{
public:
    BaseRecord();
    BaseRecord(tm accessTime);
    BaseRecord(const BaseRecord &record);
    virtual ~BaseRecord();
    inline tm getAccessTime() const{
        return _accessTime;
    }
    void setAccessTime(tm accessTime){
        if (accessTime.tm_mday>0 && accessTime.tm_mday<=31
                && accessTime.tm_mon>=0 && accessTime.tm_mon<=11
                && accessTime.tm_year>0 && accessTime.tm_year<=getDefaultTime().tm_year
                && accessTime.tm_hour>=0 && accessTime.tm_hour<=24
                &&accessTime.tm_min>=0 && accessTime.tm_min<=59
                && accessTime.tm_sec>=0 && accessTime.tm_sec<=59)
        this->_accessTime = accessTime;
    }


    virtual int defineElement() const=0;
protected:
    tm _accessTime;
    inline tm getDefaultTime() const{
        std::time_t t = std::time(nullptr);   // get time now
        tm *time = std::localtime(&t);
        return *time;
    }
};

#endif // BASERECORD_H
