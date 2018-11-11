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

    virtual double getCurrentAmountOfCoffee() const;
    virtual string getConsumerName() const;
    virtual string getConsumerSurname() const;
    virtual string getConsumerPatronymic() const;
    virtual string getConsumerPosition() const;
    virtual string getConsumerAcademicDegree() const;
    virtual double getImpactOnAmountOfCoffee() const;
    void setCurrentAmountOfCoffee(double amount);
private:
    double _currentAmountOfCoffee;
};

#endif // DUTYRECORD_H
