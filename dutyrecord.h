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

    DutyRecord(const DutyRecord &record): BaseRecord(static_cast<BaseRecord>(record)){
        this->_currentAmountOfCoffee = record._currentAmountOfCoffee;
    }

    virtual ~DutyRecord();

    virtual inline double getCurrentAmountOfCoffee() const{
        return _currentAmountOfCoffee;
    }

    virtual inline void setCurrentAmountOfCoffee(double amount){
        this->_currentAmountOfCoffee = amount;
    }
    virtual inline double getImpactOnAmountOfCoffee() const{
        return 0;
    }
private:
    double _currentAmountOfCoffee;
};

#endif // DUTYRECORD_H
