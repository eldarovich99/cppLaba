#include "baserecord.h"
#include <ctime>
using namespace std;

BaseRecord:: BaseRecord(){
    _accessTime = getDefaultTime();
}

BaseRecord::BaseRecord(tm accessTime){
    if (accessTime.tm_mday>0 && accessTime.tm_mday<=31
            && accessTime.tm_mon>=0 && accessTime.tm_mon<=11
            && accessTime.tm_year>0 && accessTime.tm_year<=getDefaultTime().tm_year
            && accessTime.tm_hour>=0 && accessTime.tm_hour<=24
            &&accessTime.tm_min>=0 && accessTime.tm_min<=59
            && accessTime.tm_sec>=0 && accessTime.tm_sec<=59)
        _accessTime = accessTime;
    else
        _accessTime = getDefaultTime();
}
BaseRecord::BaseRecord(const BaseRecord &record){
    this->_accessTime = record._accessTime;
}
BaseRecord::~BaseRecord(){
}
/*
string BaseRecord::getConsumerName() const{
    return nullptr;
}
string BaseRecord::getConsumerSurname() const{
    return nullptr;
}
string BaseRecord::getConsumerPatronymic() const{
    return nullptr;
}
string BaseRecord::getConsumerPosition() const{
    return nullptr;
}
string BaseRecord::getConsumerAcademicDegree() const{
    return nullptr;
}

double BaseRecord::getCurrentAmountOfCoffee() const{
    return -1;
}
double BaseRecord::getImpactOnAmountOfCoffee() const{
    return 0;
}*/
