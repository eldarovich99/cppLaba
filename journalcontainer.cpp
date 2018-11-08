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
    records = new DutyRecord[sizeOfContainer];
}

JournalContainer:: JournalContainer(int numberOfElements, int maxVolume, int currentVolume){
    currentSize = sizeOfContainer = numberOfElements;
    this->maxVolume = maxVolume;
    this->currentVolumeOfBulb = currentVolume;
    records = new DutyRecord[sizeOfContainer];
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
    records = new DutyRecord[sizeOfContainer];
    for (int i=0; i < journal.size(); i++){
        this->records[i] = DutyRecord(journal.get(i));
    }
}

void JournalContainer:: insert(DutyRecord &record, int position){
    //assert(currentVolumeOfBulb+=record.getImpactOnAmountOfCoffee()>=0 && currentVolumeOfBulb < maxVolume);
    assert(position>=0 and position<sizeOfContainer and
           record.getImpactOnAmountOfCoffee() <= maxVolume and (-1)*record.getImpactOnAmountOfCoffee()<=maxVolume);
    if (position > currentSize) position = currentSize;
    if (currentSize >= sizeOfContainer)
    {                // expand the array
        changeSizeOfContainer(currentSize*2);
    }
    if (position == currentSize)
        *(records+position) = record;
    else {
        for (int i = currentSize; i > position;i--){    //move array
            *(records+i) = *(records+i-1);
        }
        *(records+position) = record;
    }
    currentSize++;
}

void JournalContainer::insert(DutyRecord &record){
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
DutyRecord JournalContainer:: get(int index) const {
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
    DutyRecord *newContainer = new DutyRecord[newSize];
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
            DutyRecord thisRecord = records[i];
            stream << thisRecord.getAccessTime().tm_hour << '\n';
            stream << thisRecord.getAccessTime().tm_isdst << '\n';
            stream << thisRecord.getAccessTime().tm_mday << '\n';
            stream << thisRecord.getAccessTime().tm_min << '\n';
            stream << thisRecord.getAccessTime().tm_mon << '\n';
            stream << thisRecord.getAccessTime().tm_sec<< '\n';
            stream << thisRecord.getAccessTime().tm_wday << '\n';
            stream << thisRecord.getAccessTime().tm_yday << '\n';
            stream << thisRecord.getAccessTime().tm_year << '\n';
            stream << thisRecord.getCurrentAmountOfCoffee() << '\n';
            if(thisRecord.getCurrentAmountOfCoffee()==-1){
                stream << thisRecord.getConsumerAcademicDegree() << '\n';
                stream << thisRecord.getConsumerName() << '\n';
                stream << thisRecord.getConsumerSurname() << '\n';
                stream << thisRecord.getConsumerPatronymic() << '\n';
                stream << thisRecord.getConsumerPosition() << '\n';
                if (i != currentSize-1)
                    stream << thisRecord.getImpactOnAmountOfCoffee() << '\n';
                else
                    stream << thisRecord.getImpactOnAmountOfCoffee();
            }
            else{
                stream << thisRecord.getCurrentAmountOfCoffee() << '\n';
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
    int impactOnAmountOfCoffee;
    stream.open(path);
        if (stream.is_open()){
            for (int i = 0; !stream.eof(); i++){
                //amount of copypaste reduced
                stream.getline(buffer, 50);
                time.tm_hour = atoi(buffer);

                stream.getline(buffer,50);
                time.tm_isdst = atoi(buffer);

                stream.getline(buffer,50);
                time.tm_mday = atoi(buffer);

                stream.getline(buffer,50);
                time.tm_min = atoi(buffer);

                stream.getline(buffer,50);
                time.tm_mon = atoi(buffer);

                stream.getline(buffer,50);
                time.tm_sec = atoi(buffer);

                stream.getline(buffer,50);
                time.tm_wday = atoi(buffer);

                stream.getline(buffer,50);
                time.tm_yday = atoi(buffer);

                stream.getline(buffer,50);
                time.tm_year = atoi(buffer);


                stream.getline(buffer,50);
                currentAmountOfCoffee = atoi(buffer);

                if (currentAmountOfCoffee == -1){
                    stream.getline(buffer,50);
                    academicDegree = string(buffer);

                    stream.getline(buffer,50);
                    name = string(buffer);

                    stream.getline(buffer,50);
                    surname = string(buffer);

                    stream.getline(buffer,50);
                    patronymic = string(buffer);

                    stream.getline(buffer,50);
                    position = string(buffer);

                    stream.getline(buffer,50);
                    impactOnAmountOfCoffee = atoi(buffer);


                    JournalRecord consumer(time,name,surname,patronymic,position,academicDegree,impactOnAmountOfCoffee), *consumerHelper = &consumer;
                    DutyRecord *dutyHelper;
                    dutyHelper = static_cast<DutyRecord*>(consumerHelper);
                    this->insert(*dutyHelper);
                }
                else{
                    DutyRecord record(time,currentAmountOfCoffee);
                    this->insert(record);
                }
            }
        }
}

bool JournalContainer::compare(JournalContainer container) const
{
    //if (container.size()!=this->size()) return false;
    for (int i=0; i < container.currentSize; i++){
        // обращение к записи каждый раз неэффективно
        JournalRecord firstRecord = container.get(i);
        JournalRecord secondRecord = this->get(i);
        if (firstRecord.getAccessTime().tm_hour != secondRecord.getAccessTime().tm_hour) return false;
        if (firstRecord.getAccessTime().tm_min != secondRecord.getAccessTime().tm_min) return false;
        if (firstRecord.getCurrentAmountOfCoffee() == -1 and secondRecord.getCurrentAmountOfCoffee() == -1){
            if (firstRecord.getConsumerName().compare(secondRecord.getConsumerName())!=0) return false;
            if (firstRecord.getConsumerSurname().compare(secondRecord.getConsumerSurname())!=0) return false;
            if (firstRecord.getConsumerPatronymic().compare(secondRecord.getConsumerPatronymic())!=0) return false;
            if (firstRecord.getConsumerAcademicDegree().compare(secondRecord.getConsumerAcademicDegree())!=0) return false;
            if (firstRecord.getConsumerPosition().compare(secondRecord.getConsumerPosition())!=0) return false;
            if (firstRecord.getImpactOnAmountOfCoffee()!=secondRecord.getImpactOnAmountOfCoffee()) return false;
        }
        else if (firstRecord.getCurrentAmountOfCoffee() != secondRecord.getCurrentAmountOfCoffee()) return false;
    }
    return true;
}
