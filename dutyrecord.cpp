#include "dutyrecord.h"
DutyRecord:: DutyRecord()
{
    currentAmountOfCoffee = 0;
    _accessTime = getDefaultTime();
}
DutyRecord:: DutyRecord(tm timeOfObservation, double currentAmountOfCoffee){
    this->currentAmountOfCoffee = currentAmountOfCoffee;
    _accessTime = timeOfObservation;
}
DutyRecord::DutyRecord(const DutyRecord &record){
    this->currentAmountOfCoffee = record.getCurrentAmountOfCoffee();
    _accessTime = record._accessTime;
}
