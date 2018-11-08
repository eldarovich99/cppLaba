#ifndef DUTYRECORD_H
#define DUTYRECORD_H
#include <journalrecord.h>

class DutyRecord : public JournalRecord
{
public:
    DutyRecord();
    DutyRecord(tm timeOfObservation, double currentAmountOfCoffee);

    DutyRecord(const DutyRecord &record);
    inline double getCurrentAmountOfCoffee() const{
        return currentAmountOfCoffee;
    }
    inline void setCurrentAmountOfCoffee(double amount){
        this->currentAmountOfCoffee = amount;
    }
private:
    double currentAmountOfCoffee;
};

#endif // DUTYRECORD_H
