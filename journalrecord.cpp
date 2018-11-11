#include "journalrecord.h"
JournalRecord::~JournalRecord(){

}
string JournalRecord::getConsumerName() const{
    return user._name;
}
string JournalRecord::getConsumerSurname() const{
    return user._surname;
}
string JournalRecord::getConsumerPatronymic() const{
    return user._patronymic;
}
string JournalRecord::getConsumerPosition() const{
    return user._position;
}
string JournalRecord::getConsumerAcademicDegree() const{
    return user._academicDegree;
}
double JournalRecord::getImpactOnAmountOfCoffee() const{
    return _impactOnAmountOfCoffee;
}
double JournalRecord::getCurrentAmountOfCoffee()const{
    return -1;
}
