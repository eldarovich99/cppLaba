#ifndef DUTYRECORD_H
#define DUTYRECORD_H
#include <journalrecord.h>

class DutyRecord : public JournalRecord
{
public:
    DutyRecord():JournalRecord(){
        currentAmountOfCoffee = 0;
        timeOfObservation = getDefaultTime();
    }
    DutyRecord(tm _accessTime, string _name, string _surname, string _patronymic,
               string _position, string _academicDegree, double _impactOnAmountOfCoffee,
               tm timeOfObservation, double currentAmountOfCoffee):JournalRecord(_accessTime, _name,  _surname, _patronymic,
                                                                                 _position, _academicDegree, _impactOnAmountOfCoffee)
    {
        this->currentAmountOfCoffee = currentAmountOfCoffee;
        this->timeOfObservation = timeOfObservation;
    }

    DutyRecord(const DutyRecord &record):JournalRecord(static_cast<JournalRecord>(record)){
        this->currentAmountOfCoffee = record.getCurrentAmountOfCoffee();
        this->timeOfObservation = record.getTimeOfObservation();
    }
    inline tm getTimeOfObservation() const{
        return timeOfObservation;
    }
    inline void setTimeOfObservation(tm time){
        this->timeOfObservation = time;
    }
    inline double getCurrentAmountOfCoffee() const{
        return currentAmountOfCoffee;
    }
    inline void setCurrentAmountOfCoffee(double amount){
        this->currentAmountOfCoffee = amount;
    }
private:
    tm timeOfObservation;
    double currentAmountOfCoffee;
};

#endif // DUTYRECORD_H
