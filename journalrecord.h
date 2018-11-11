#ifndef JOURNALRECORD_H
#define JOURNALRECORD_H

#include <ctime>
#include <string>
#include <baserecord.h>
using namespace std;

class JournalRecord : public BaseRecord{
public:
    JournalRecord() : BaseRecord(){
        user._name = "Name";
        user._surname = "Surname";
        user._patronymic = "Patronymic";
        user._position = "Position";
        user._academicDegree = "Academic degree";
        _accessTime = getDefaultTime();
        _impactOnAmountOfCoffee = 0.0;
    }
    JournalRecord(tm accessTime, string name, string surname, string patronymic,
                  string position, string academicDegree, double impactOnAmountOfCoffee) : BaseRecord(accessTime){
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
    JournalRecord(const JournalRecord &consumer) : BaseRecord(static_cast<BaseRecord>(consumer)){
        user._name = consumer.user._name;
        user._surname = consumer.user._surname;
        user._patronymic = consumer.user._patronymic;
        user._position = consumer.user._position;
        user._academicDegree = consumer.user._academicDegree;
        _impactOnAmountOfCoffee = consumer._impactOnAmountOfCoffee;
    }

    virtual ~JournalRecord();

    virtual inline string getConsumerName() const{
        return user._name;
    }
    virtual inline string getConsumerSurname() const{
        return user._surname;
    }
    virtual inline string getConsumerPatronymic() const{
        return user._patronymic;
    }
    virtual inline string getConsumerPosition() const{
        return user._position;
    }
    virtual inline string getConsumerAcademicDegree() const{
        return user._academicDegree;
    }
    virtual inline double getImpactOnAmountOfCoffee() const{
        return _impactOnAmountOfCoffee;
    }

    virtual inline void setConsumerName(string name){
        if (!name.empty())
            user._name =name;
    }
    virtual inline void setConsumerSurname(string surname){
        if (!surname.empty())
            user._surname = surname;
    }
    virtual inline void setConsumerPatronymic(string patronymic){
        user._patronymic = patronymic;
    }
    virtual inline void setConsumerPosition(string position){
        if (!position.empty())
            user._position = position;
    }
    virtual inline void setConsumerAcademicDegree(string academicDegree){
        if (!academicDegree.empty())
            user._academicDegree = academicDegree;
    }
    virtual inline void setImpactOnAmountOfCoffee(double impactOnAmountOfCoffee){
        _impactOnAmountOfCoffee = impactOnAmountOfCoffee;
    }
    virtual inline double getCurrentAmountOfCoffee() const{
        return -1;
    }
private:
    struct userInfo{
    public:
        string _name;
        string _surname;
        string _patronymic;
        string _position;
        string _academicDegree;
        };
    userInfo user;
    double _impactOnAmountOfCoffee;
};
#endif // JOURNALRECORD_H

