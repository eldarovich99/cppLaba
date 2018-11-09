#include "journalrecord.h"
#include <ctime>

JournalRecord::JournalRecord()
{
        user._name = "Name";
        user._surname = "Surname";
        user._patronymic = "Patronymic";
        user._position = "Position";
        user._academicDegree = "Academic degree";
        _accessTime = getDefaultTime();
        _impactOnAmountOfCoffee = 0.0;
        }


    JournalRecord::JournalRecord(tm accessTime, string name, string surname, string patronymic,
                   string position, string academicDegree, double impactOnAmountOfCoffee){
        if (accessTime.tm_mday>0 && accessTime.tm_mday<=31
                && accessTime.tm_mon>=0 && accessTime.tm_mon<=11
                && accessTime.tm_year>0 && accessTime.tm_year<=getDefaultTime().tm_year
                && accessTime.tm_hour>=0 && accessTime.tm_hour<=24
                &&accessTime.tm_min>=0 && accessTime.tm_min<=59
                && accessTime.tm_sec>=0 && accessTime.tm_sec<=59)
           _accessTime = accessTime;
        else
            _accessTime = getDefaultTime();
        if (!name.empty())
            user._name =name;
        else
            user._name = "Name";
        if (!surname.empty())
            user._surname = surname;
        else
            user._surname = "Surname";
        user._patronymic = patronymic;

        if (!position.empty())
            user._position = position;
        else
            user._position = "Position";
        if (!academicDegree.empty())
            user._academicDegree = academicDegree;
        else
            user._academicDegree = "Academic Degree";
         _impactOnAmountOfCoffee = impactOnAmountOfCoffee;
        }

   JournalRecord:: JournalRecord(const JournalRecord &consumer){
        _accessTime = consumer._accessTime;
        user._name = consumer.user._name;
        user._surname = consumer.user._surname;
        user._patronymic = consumer.user._patronymic;
        user._position = consumer.user._position;
        user._academicDegree = consumer.user._academicDegree;
        _impactOnAmountOfCoffee = consumer._impactOnAmountOfCoffee;
    }

    tm JournalRecord::getAccessTime(){
        return _accessTime;
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
    string JournalRecord::getConsumerAcademicDegree() const {
        return user._academicDegree;
    }
    double JournalRecord::getImpactOnAmountOfCoffee() const {
        return _impactOnAmountOfCoffee;
    }


    void JournalRecord::setAccessTime(tm accessTime){
        if (accessTime.tm_mday>0 && accessTime.tm_mday<=31
                && accessTime.tm_mon>=0 && accessTime.tm_mon<=11
                && accessTime.tm_year>0 && accessTime.tm_year<=getDefaultTime().tm_year
                && accessTime.tm_hour>=0 && accessTime.tm_hour<=24
                &&accessTime.tm_min>=0 && accessTime.tm_min<=60)
            _accessTime = accessTime;
    }
    void JournalRecord::setConsumerName(string name){
        if (!name.empty())
            user._name =name;
    }
    void JournalRecord::setConsumerSurname(string surname){
        if (!surname.empty())
            user._surname = surname;
    }
    void JournalRecord::setConsumerPatronymic(string patronymic){
        user._patronymic = patronymic;
    }
    void JournalRecord::JournalRecord::setConsumerPosition(string position){
        if (!position.empty())
            user._position = position;
    }
    void JournalRecord::setConsumerAcademicDegree(string academicDegree){
        if (!academicDegree.empty())
            user._academicDegree = academicDegree;
    }
    void JournalRecord::setImpactOnAmountOfCoffee(double impactOnAmountOfCoffee){
         _impactOnAmountOfCoffee = impactOnAmountOfCoffee;
    }

    double JournalRecord::getCurrentAmountOfCoffee() const{
        return -1;
    }

    tm JournalRecord::getDefaultTime(){
        std::time_t t = std::time(nullptr);   // get time now
        tm *time = std::localtime(&t);
        return *time;
    }
