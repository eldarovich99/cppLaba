#ifndef DUTYRECORD_H
#define DUTYRECORD_H
#include <baserecord.h>

class DutyRecord : public BaseRecord
{
public:
    DutyRecord():BaseRecord(){
        _currentAmountOfCoffee = 0;
    }
    DutyRecord(tm timeOfObservation, double currentAmountOfCoffee) : BaseRecord(timeOfObservation){
        _currentAmountOfCoffee = currentAmountOfCoffee;
    }

    DutyRecord(const DutyRecord &record): BaseRecord(record){
        this->_currentAmountOfCoffee = record._currentAmountOfCoffee;
    }

    virtual ~DutyRecord();
    virtual int defineElement() const;
    double getCurrentAmountOfCoffee() const;
    string getConsumerName() const;
    string getConsumerSurname() const;
    string getConsumerPatronymic() const;
    string getConsumerPosition() const;
    string getConsumerAcademicDegree() const;
    double getImpactOnAmountOfCoffee() const;
    void setCurrentAmountOfCoffee(double amount);
private:
    double _currentAmountOfCoffee;
};

#endif // DUTYRECORD_H
