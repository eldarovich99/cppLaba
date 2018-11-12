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
    JournalRecord(const JournalRecord &consumer) : BaseRecord(consumer){
        user._name = consumer.user._name;
        user._surname = consumer.user._surname;
        user._patronymic = consumer.user._patronymic;
        user._position = consumer.user._position;
        user._academicDegree = consumer.user._academicDegree;
        _impactOnAmountOfCoffee = consumer._impactOnAmountOfCoffee;
    }

    virtual ~JournalRecord();
    virtual int defineElement() const;
    string getConsumerName() const;
    string getConsumerSurname() const;
    string getConsumerPatronymic() const;
    string getConsumerPosition() const;
    string getConsumerAcademicDegree() const;
    double getImpactOnAmountOfCoffee() const;
    double getCurrentAmountOfCoffee() const;
    inline void setConsumerName(string name){
        if (!name.empty())
            user._name =name;
    }
    inline void setConsumerSurname(string surname){
        if (!surname.empty())
            user._surname = surname;
    }
    inline void setConsumerPatronymic(string patronymic){
        user._patronymic = patronymic;
    }
    inline void setConsumerPosition(string position){
        if (!position.empty())
            user._position = position;
    }
    inline void setConsumerAcademicDegree(string academicDegree){
        if (!academicDegree.empty())
            user._academicDegree = academicDegree;
    }
    inline void setImpactOnAmountOfCoffee(double impactOnAmountOfCoffee){
        _impactOnAmountOfCoffee = impactOnAmountOfCoffee;
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

