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


    inline virtual string getConsumerName() const{
        return nullptr;
    }
    virtual string getConsumerSurname() const{
        return nullptr;
    }
    virtual string getConsumerPatronymic() const{
        return nullptr;
    }
    virtual string getConsumerPosition() const{
        return nullptr;
    }
    virtual string getConsumerAcademicDegree() const{
        return nullptr;
    }

    virtual double getCurrentAmountOfCoffee() const{
        return -1;
    }
    virtual double getImpactOnAmountOfCoffee() const{
        return 0;
    }
protected:
    tm timeOfObservation;
    tm _accessTime;
    inline tm getDefaultTime() const{
        std::time_t t = std::time(nullptr);   // get time now
        tm *time = std::localtime(&t);
        return *time;
    }
};

#endif // BASERECORD_H
