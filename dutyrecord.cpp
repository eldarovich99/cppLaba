#include "dutyrecord.h"
DutyRecord:: ~DutyRecord(){

}

double DutyRecord::getCurrentAmountOfCoffee() const{
    return _currentAmountOfCoffee;
}

void DutyRecord::setCurrentAmountOfCoffee(double amount){
    this->_currentAmountOfCoffee = amount;
}
string DutyRecord::getConsumerName() const{
    return nullptr;
}
string DutyRecord::getConsumerSurname() const{
    return nullptr;
}
string DutyRecord::getConsumerPatronymic() const{
    return nullptr;
}
string DutyRecord::getConsumerPosition() const{
    return nullptr;
}
string DutyRecord::getConsumerAcademicDegree() const{
    return nullptr;
}

double DutyRecord::getImpactOnAmountOfCoffee() const{
    return 0;
}
