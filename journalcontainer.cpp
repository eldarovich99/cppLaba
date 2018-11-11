#include "journalcontainer.h"
#include "dutyrecord.h"
#include <iostream>
#include <fstream>
#include <assert.h>

JournalContainer:: JournalContainer(){
    currentSize = 0;
    sizeOfContainer = 10;
    maxVolume = 30;
    currentVolumeOfBulb = maxVolume;
    records = new BaseRecord*[sizeOfContainer];
}

JournalContainer:: JournalContainer(int numberOfElements, int maxVolume, int currentVolume){
    currentSize = sizeOfContainer = numberOfElements;
    this->maxVolume = maxVolume;
    this->currentVolumeOfBulb = currentVolume;
    records = new BaseRecord*[sizeOfContainer];
}

JournalContainer:: ~JournalContainer(){
    for (int i = 0; i < sizeOfContainer; i++){
        delete &records[i];
    }
    currentSize = 0;
    sizeOfContainer=0;
    delete[](records);
}

JournalContainer:: JournalContainer(const JournalContainer &journal){
    this->currentSize = journal.size();
    this->sizeOfContainer = journal.sizeOfContainer;
    records = new BaseRecord*[sizeOfContainer];
    for (int i=0; i < journal.size(); i++){
        this->records[i] = journal.get(i);
    }
}

void JournalContainer:: insert(BaseRecord &record, int position){
    //assert(currentVolumeOfBulb+=record.getImpactOnAmountOfCoffee()>=0 && currentVolumeOfBulb < maxVolume);
    assert(position>=0 and position<sizeOfContainer and
           record.getImpactOnAmountOfCoffee() <= maxVolume and (-1)*record.getImpactOnAmountOfCoffee()<=maxVolume);
    if (position > currentSize) position = currentSize;
    if (currentSize >= sizeOfContainer)
    {                // expand the array
        changeSizeOfContainer(currentSize*2);
    }
    if (position == currentSize)
        *(records+position) = &record;
    else {
        for (int i = currentSize; i > position;i--){    //move array
            *(records+i) = *(records+i-1);
        }
        *(records+position) = &record;
    }
    currentSize++;
}

void JournalContainer::insert(BaseRecord &record){
    insert(record, currentSize);
}


void JournalContainer:: deleteRecord(int position){       //old method "pop" was renamed (it called deletedRecord because delete is built-in function)
    assert(position >=0 and position < currentSize);
    if (position == currentSize-1){
        //currentVolumeOfBulb-=records[position].getImpactOnAmountOfCoffee();
        delete &records[position];
    }
    else{
        for (int i = position; i < currentSize; i++)
            records[i] = records[i+1];

        //currentVolumeOfBulb-=records[position].getImpactOnAmountOfCoffee();

        delete &records[currentSize - 1];
    }
    currentSize--;
}
BaseRecord *JournalContainer:: get(int index) const {
    assert(index >= 0 && index < currentSize);
    return *(records + index);
}

void JournalContainer:: trim(){
    changeSizeOfContainer(currentSize);
}

void JournalContainer:: clear(){
    for (int i = 0; i < sizeOfContainer; i++){
        delete &records[i];
    }
    currentSize = 0;
};

int JournalContainer:: size() const{
    return currentSize;
}

void JournalContainer:: changeSizeOfContainer(int newSize){
    BaseRecord **newContainer = new BaseRecord*[newSize];
    for (int i = 0; i < sizeOfContainer; i++){     //copy records to the new container
        newContainer[i] = *(records+i);
    }
    for (int i = 0; i < sizeOfContainer; i++){      // delete the old container
        delete &records[i];
    }
    delete[](records);
    sizeOfContainer = newSize;
    records = newContainer;
}

void JournalContainer:: writeToFile(string path) const{
    std::ofstream stream;
    //stream >> i;
    stream.open(path);
        if (stream.is_open()){
        for (int i = 0; i < currentSize; i++){
            BaseRecord *record = records[i];
            stream << record->getAccessTime().tm_hour << '\n';
            stream << record->getAccessTime().tm_isdst << '\n';
            stream << record->getAccessTime().tm_mday << '\n';
            stream << record->getAccessTime().tm_min << '\n';
            stream << record->getAccessTime().tm_mon << '\n';
            stream << record->getAccessTime().tm_sec<< '\n';
            stream << record->getAccessTime().tm_wday << '\n';
            stream << record->getAccessTime().tm_yday << '\n';
            stream << record->getAccessTime().tm_year << '\n';
            stream << record->getCurrentAmountOfCoffee() << '\n';
            if(record->getCurrentAmountOfCoffee()+1 < 0.01 && (-1)*record->getCurrentAmountOfCoffee()+1>-0.01){
                stream << record->getConsumerAcademicDegree() << '\n';
                stream << record->getConsumerName() << '\n';
                stream << record->getConsumerSurname() << '\n';
                stream << record->getConsumerPatronymic() << '\n';
                stream << record->getConsumerPosition() << '\n';
                if (i != currentSize-1)
                    stream << record->getImpactOnAmountOfCoffee() << '\n';
                else
                    stream << record->getImpactOnAmountOfCoffee();
            }
            else{
                if (i != currentSize-1)
                    stream << record->getCurrentAmountOfCoffee() << '\n';
                else
                    stream << record->getCurrentAmountOfCoffee();
            }
        }
    }
    stream.flush();
}

void JournalContainer:: readFromFile(string path){
    std::ifstream stream;
    char buffer[50];
    tm time;
    string academicDegree;
    string name;
    string surname;
    string patronymic;
    string position;
    double currentAmountOfCoffee;
    double impactOnAmountOfCoffee;
    stream.open(path);
        if (stream.is_open()){
            for (int i = 0; !stream.eof(); i++){
                //amount of copypaste reduced
                stream.getline(buffer, 50);
                time.tm_hour = atoi(buffer);
                *buffer = NULL;

                stream.getline(buffer,50);
                time.tm_isdst = atoi(buffer);
                *buffer = NULL;

                stream.getline(buffer,50);
                time.tm_mday = atoi(buffer);
                *buffer = NULL;

                stream.getline(buffer,50);
                time.tm_min = atoi(buffer);
                *buffer = NULL;

                stream.getline(buffer,50);
                time.tm_mon = atoi(buffer);
                *buffer = NULL;

                stream.getline(buffer,50);
                time.tm_sec = atoi(buffer);
                *buffer = NULL;

                stream.getline(buffer,50);
                time.tm_wday = atoi(buffer);
                *buffer = NULL;

                stream.getline(buffer,50);
                time.tm_yday = atoi(buffer);
                *buffer = NULL;

                stream.getline(buffer,50);
                time.tm_year = atoi(buffer);
                *buffer = NULL;


                stream.getline(buffer,50);
                currentAmountOfCoffee = atof(buffer);
                *buffer = NULL;

                if (currentAmountOfCoffee + 1 < 0.01){
                    stream.getline(buffer,50);
                    academicDegree = string(buffer);
                    *buffer = NULL;

                    stream.getline(buffer,50);
                    name = string(buffer);
                    *buffer = NULL;

                    stream.getline(buffer,50);
                    surname = string(buffer);
                    *buffer = NULL;

                    stream.getline(buffer,50);
                    patronymic = string(buffer);
                    *buffer = NULL;

                    stream.getline(buffer,50);
                    position = string(buffer);
                    *buffer = NULL;

                    stream.getline(buffer,50);
                    impactOnAmountOfCoffee = atoi(buffer);
                    *buffer = NULL;


                    JournalRecord consumer = JournalRecord(time,name,surname,patronymic,position,academicDegree,impactOnAmountOfCoffee);
                    this->insert(consumer);
                }
                else{
                    DutyRecord record = DutyRecord(time,currentAmountOfCoffee);
                    this->insert(record);
                }
            }
        }
}

bool JournalContainer::compare(JournalContainer &container) const
{
    //if (container.size()!=this->size()) return false;
    for (int i=0; i < container.currentSize; i++){
        // обращение к записи каждый раз неэффективно
        BaseRecord *firstRecord = container.get(i);
        BaseRecord *secondRecord = this->get(i);
        if (firstRecord->getAccessTime().tm_hour != secondRecord->getAccessTime().tm_hour) return false;
        if (firstRecord->getAccessTime().tm_min != secondRecord->getAccessTime().tm_min) return false;
        if (firstRecord->getCurrentAmountOfCoffee() + 1 < 0.01 and secondRecord->getCurrentAmountOfCoffee() + 1 < 0.01
            and (-1)*firstRecord->getCurrentAmountOfCoffee() + 1 >  -0.01 and (-1)*secondRecord->getCurrentAmountOfCoffee() + 1 > -0.01){
            if (firstRecord->getConsumerName().compare(secondRecord->getConsumerName())!=0) return false;
            if (firstRecord->getConsumerSurname().compare(secondRecord->getConsumerSurname())!=0) return false;
            if (firstRecord->getConsumerPatronymic().compare(secondRecord->getConsumerPatronymic())!=0) return false;
            if (firstRecord->getConsumerAcademicDegree().compare(secondRecord->getConsumerAcademicDegree())!=0) return false;
            if (firstRecord->getConsumerPosition().compare(secondRecord->getConsumerPosition())!=0) return false;
            if (firstRecord->getImpactOnAmountOfCoffee() - secondRecord->getImpactOnAmountOfCoffee() > 0.01 ||
                firstRecord->getImpactOnAmountOfCoffee() - secondRecord->getImpactOnAmountOfCoffee() < -0.01) return false;
        }
        else if (firstRecord->getImpactOnAmountOfCoffee() - secondRecord->getImpactOnAmountOfCoffee() > 0.01 ||
                 firstRecord->getImpactOnAmountOfCoffee() - secondRecord->getImpactOnAmountOfCoffee() < -0.01) return false;
    }
    return true;
}

/*DutyRecord JournalContainer::convertToDutyRecord(BaseRecord record) const{
    DutyRecord *dutyHelper;
    dutyHelper = static_cast<DutyRecord*>(&record);
    return  *dutyHelper;
}

JournalRecord JournalContainer::convertToJournalRecord(BaseRecord record) const{
    JournalRecord *journalHelper;
    journalHelper = static_cast<JournalRecord*>(&record);
    return  *journalHelper;
}*/

