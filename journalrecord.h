#ifndef JOURNALRECORD_H
#define JOURNALRECORD_H

#include <ctime>
#include <string>
//#include <assert.h>
using namespace std;

class JournalRecord{
public:
    JournalRecord();
    JournalRecord(tm _accessTime, string _name, string _surname, string _patronymic,
                   string _position, string _academicDegree, double _impactOnAmountOfCoffee);
    JournalRecord(const JournalRecord &consumer);
    tm getAccessTime();
    string getConsumerName() const;
    string getConsumerSurname() const;
    string getConsumerPatronymic() const;
    string getConsumerPosition() const;
    string getConsumerAcademicDegree() const;
    double getImpactOnAmountOfCoffee() const;

    void setAccessTime(tm _accessTime);
    void setConsumerName(string _name);
    void setConsumerSurname(string _surname);
    void setConsumerPatronymic(string _patronymic);
    void setConsumerPosition(string _position);
    void setConsumerAcademicDegree(string _academicDegree);
    void setImpactOnAmountOfCoffee(double _impactOnAmountOfCoffee);
private:
    struct userInfo{
    public:
        string _name;
        string _surname;
        string _patronymic;
        string _position;
        string _academicDegree;
        };
    tm _accessTime;
    userInfo user;
    double _impactOnAmountOfCoffee;
protected:
    tm getDefaultTime();
};
#endif // JOURNALRECORD_H
