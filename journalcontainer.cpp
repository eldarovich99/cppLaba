#include "journalcontainer.h"
#include "journalrecord.h"
#include <iostream>
#include <fstream>
#include <assert.h>

JournalContainer:: JournalContainer(){
    currentSize = 0;
    sizeOfContainer = 10;
    maxVolume = 30;
    currentVolumeOfBulb = maxVolume;
    records = new JournalRecord[sizeOfContainer];
}

JournalContainer:: JournalContainer(int numberOfElements, int maxVolume, int currentVolume){
    currentSize = sizeOfContainer = numberOfElements;
    this->maxVolume = maxVolume;
    this->currentVolumeOfBulb = currentVolume;
    records = new JournalRecord[sizeOfContainer];
}

JournalContainer:: ~JournalContainer(){
    for (int i = 0; i < sizeOfContainer; i++){
        delete &records[i];
    }
    currentSize = 0;
    sizeOfContainer=0;
    delete[](records);
}

JournalContainer:: JournalContainer(const JournalContainer &journal){   // it doesn't work...
    this->currentSize = journal.size();
    this->sizeOfContainer = journal.sizeOfContainer;
    records = new JournalRecord[sizeOfContainer];
    for (int i=0; i < journal.size(); i++){
        this->records[i] = JournalRecord(journal.get(i));
    }
}

void JournalContainer:: insert(JournalRecord &record, int position){
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

void JournalContainer::insert(JournalRecord &record){
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
JournalRecord JournalContainer:: get(int index) const {
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
    JournalRecord *newContainer = new JournalRecord[newSize];
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
            stream << records[i].getAccessTime().tm_hour << '\n';
            stream << records[i].getAccessTime().tm_isdst << '\n';
            stream << records[i].getAccessTime().tm_mday << '\n';
            stream << records[i].getAccessTime().tm_min << '\n';
            stream << records[i].getAccessTime().tm_mon << '\n';
            stream << records[i].getAccessTime().tm_sec<< '\n';
            stream << records[i].getAccessTime().tm_wday << '\n';
            stream << records[i].getAccessTime().tm_yday << '\n';
            stream << records[i].getAccessTime().tm_year << '\n';
            stream << records[i].getConsumerAcademicDegree() << '\n';
            stream << records[i].getConsumerName() << '\n';
            stream << records[i].getConsumerSurname() << '\n';
            stream << records[i].getConsumerPatronymic() << '\n';
            stream << records[i].getConsumerPosition() << '\n';
            if (i != currentSize-1)
                stream << records[i].getImpactOnAmountOfCoffee() << '\n';
            else
                stream << records[i].getImpactOnAmountOfCoffee();
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

            JournalRecord consumer(time,name,surname,patronymic,position,academicDegree,impactOnAmountOfCoffee);
            this->insert(consumer);
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
        if (firstRecord.getConsumerName().compare(secondRecord.getConsumerName())!=0) return false;
        if (firstRecord.getConsumerSurname().compare(secondRecord.getConsumerSurname())!=0) return false;
        if (firstRecord.getConsumerPatronymic().compare(secondRecord.getConsumerPatronymic())!=0) return false;
        if (firstRecord.getConsumerAcademicDegree().compare(secondRecord.getConsumerAcademicDegree())!=0) return false;
        if (firstRecord.getConsumerPosition().compare(secondRecord.getConsumerPosition())!=0) return false;
        if (firstRecord.getImpactOnAmountOfCoffee()!=secondRecord.getImpactOnAmountOfCoffee()) return false;   }
    return true;
}
