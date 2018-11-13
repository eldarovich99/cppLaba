#include "journalcontainer.h"
#include "dutyrecord.h"
#include <iostream>
#include <fstream>
#include <cassert>


//переделать контейнер так, чтобы копировались объекты, а не указатели;
//в функции очистки как и в деструкторе;delete records[i];  удаляет указатель
//переделать наследование, чтобы было различение объектов и далее в контейнере ветвление

//сделать копирование объектов(создание новых объектов) в конструкторе
JournalContainer:: JournalContainer(){
    currentSize = 0;
    sizeOfContainer = 10;
    maxVolume = 30;
    records = new BaseRecord*[sizeOfContainer];
}

JournalContainer:: JournalContainer(int numberOfElements, int maxVolume){
    currentSize = sizeOfContainer = numberOfElements;
    this->maxVolume = maxVolume;
    records = new BaseRecord*[sizeOfContainer];
}

JournalContainer:: ~JournalContainer(){
    for (int i = sizeOfContainer-1; i >=0; i--){
        delete &records[i]; // here was &
    }
    currentSize = 0;
    sizeOfContainer=0;
    delete[](records);
}

JournalContainer:: JournalContainer(const JournalContainer &journal){
    this->currentSize = journal.size();
    this->sizeOfContainer = journal.sizeOfContainer;
    this->maxVolume = journal.maxVolume;
    records = new BaseRecord*[sizeOfContainer];
    for (int i=0; i < journal.size(); i++){
        if (journal.get(i)->defineElement() == 1){
            JournalRecord *helper = dynamic_cast<JournalRecord*>(journal.get(i));
            JournalRecord record(*helper);
            *records[i] = record;
        }
        else if(journal.get(i)->defineElement() == 2){
            DutyRecord *helper = dynamic_cast<DutyRecord*>(journal.get(i));
            DutyRecord record(*helper);
            *records[i] = record;
        }
    }
}


void JournalContainer:: insert(BaseRecord &record, int position){
    if (record.defineElement()==1){
        //auto* journalRecord = dynamic_cast<JournalRecord*>(&record);

       /* assert(position>=0 and position<sizeOfContainer and
               journalRecord->getImpactOnAmountOfCoffee() <= maxVolume
               and (-1)*journalRecord->getImpactOnAmountOfCoffee()>= -maxVolume);*/

        if (position > currentSize) position = currentSize;
        if (currentSize >= sizeOfContainer)
        {                // expand the array
            changeSizeOfContainer(currentSize*2);
        }
        if (position == currentSize){
            if (record.defineElement()==1){
                JournalRecord *helper = dynamic_cast<JournalRecord*>(&record);
                JournalRecord *newRecord = new JournalRecord(*helper);
                records[position] = newRecord;
            }
            else if ((&record)->defineElement()==2){
                DutyRecord *helper = dynamic_cast<DutyRecord*>(&record);
                DutyRecord *newRecord = new DutyRecord(*helper);
                records[position] = newRecord;
            }
        }
        else {
            for (int i = currentSize; i > position;i--){    //move array
                records[i] = records[i-1];
            }
            if (record.defineElement()==1){
                JournalRecord *helper = dynamic_cast<JournalRecord*>(&record);
                JournalRecord *newRecord = new JournalRecord(*helper);
                records[position] = newRecord;
            }
            else if (record.defineElement()==2){
                DutyRecord *helper = dynamic_cast<DutyRecord*>(&record);
                DutyRecord *newRecord = new DutyRecord(*helper);
                records[position] = newRecord;
            }
        }
    }
    currentSize++;
}

void JournalContainer::insert(BaseRecord &record){
    insert(record, currentSize);
}


void JournalContainer:: deleteRecord(int position){       //old method "pop" was renamed (it called deletedRecord because delete is built-in function)
    assert(position >=0 and position < currentSize);
    if (position == currentSize-1){
        delete &records[position];  //here was &
    }
    else{
        for (int i = position; i < currentSize; i++)
            records[i] = records[i+1];

        delete &records[currentSize - 1]; //here was &
    }
    currentSize--;
}
BaseRecord *JournalContainer:: get(int index) const {
    assert(index >= 0 && index < currentSize);
    return records[index];
}

void JournalContainer:: trim(){
    changeSizeOfContainer(currentSize);
}

void JournalContainer:: clear(){
    for (int i = sizeOfContainer-1; i >=0 ; i--){
        delete &records[i];     //here was &
    }
    currentSize = 0;
    sizeOfContainer = 10;
    records = new BaseRecord*[sizeOfContainer];
};

int JournalContainer:: size() const{
    return currentSize;
}

//should be editted
void JournalContainer:: changeSizeOfContainer(int newSize){
    auto **newContainer = new BaseRecord*[newSize];
    for (int i = 0; i < sizeOfContainer; i++){     //copy records to the new container
        newContainer[i] = records[i];
    }
    for (int i = 0; i < sizeOfContainer; i++){      // delete the old container
        delete &records[i];     //here was &
    }
    delete[](records);
    sizeOfContainer = newSize;
    records = newContainer;
}

void JournalContainer:: writeToFile(const string &path) const{
    std::ofstream stream;
    //stream >> i;
    stream.open(path);
    if (stream.is_open()){
        for (int i = 0; i < currentSize; i++){
            BaseRecord *record = records[i];
            tm time = record->getAccessTime();
            stream << time.tm_hour << '\n';
            stream << time.tm_isdst << '\n';
            stream << time.tm_mday << '\n';
            stream << time.tm_min << '\n';
            stream << time.tm_mon << '\n';
            stream << time.tm_sec<< '\n';
            stream << time.tm_wday << '\n';
            stream << time.tm_yday << '\n';
            stream << time.tm_year << '\n';
            stream << (*records[i]).defineElement() << '\n';
            if((*records[i]).defineElement() == 1){
                auto* journalRecord = dynamic_cast<JournalRecord*>(record);
                stream << journalRecord->getConsumerAcademicDegree() << '\n';
                stream << journalRecord->getConsumerName() << '\n';
                stream << journalRecord->getConsumerSurname() << '\n';
                stream << journalRecord->getConsumerPatronymic() << '\n';
                stream << journalRecord->getConsumerPosition() << '\n';
                if (i != currentSize-1)
                    stream << journalRecord->getImpactOnAmountOfCoffee() << '\n';
                else
                    stream << journalRecord->getImpactOnAmountOfCoffee();
            }
            else{
                auto* journalRecord = dynamic_cast<DutyRecord*>(record);
                if (i != currentSize-1)
                    stream << journalRecord->getCurrentAmountOfCoffee() << '\n';
                else
                    stream << journalRecord->getCurrentAmountOfCoffee();
            }
        }
    }
    stream.flush();
    stream.close();
}

void JournalContainer:: readFromFile(const string &path){
    std::ifstream stream;
    char buffer[50];
    tm time;
    string academicDegree;
    string name;
    string surname;
    string patronymic;
    string position;
    int elementDefinition;
    double impactOnAmountOfCoffee;
    stream.open(path);
        if (stream.is_open()){
            for (int i = 0; !stream.eof(); i++){
                //amount of copypaste reduced
                stream.getline(buffer, 50);
                time.tm_hour = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_isdst = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_mday = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_min = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_mon = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_sec = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_wday = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_yday = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_year = atoi(buffer);
                //*buffer = NULL;


                stream.getline(buffer,50);
                elementDefinition = atoi(buffer);
                //*buffer = NULL;

                if (elementDefinition == 1){
                    stream.getline(buffer,50);
                    academicDegree = string(buffer);
                    //*buffer = NULL;

                    stream.getline(buffer,50);
                    name = string(buffer);
                    //*buffer = NULL;

                    stream.getline(buffer,50);
                    surname = string(buffer);
                    //*buffer = NULL;

                    stream.getline(buffer,50);
                    patronymic = string(buffer);
                    //*buffer = NULL;

                    stream.getline(buffer,50);
                    position = string(buffer);
                    //*buffer = NULL;

                    stream.getline(buffer,50);
                    impactOnAmountOfCoffee = atoi(buffer);
                    //*buffer = NULL;


                    JournalRecord consumer = JournalRecord(time,name,surname,patronymic,position,academicDegree,impactOnAmountOfCoffee);
                    this->insert(consumer);
                }
                else{
                    stream.getline(buffer,50);
                    double currentAmountOfCoffee = atof(buffer);
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
        if (firstRecord->defineElement() == 1 and secondRecord->defineElement()==1){
            auto* firstJournalRecord = dynamic_cast<JournalRecord*>(firstRecord);
            auto* secondJournalRecord = dynamic_cast<JournalRecord*>(secondRecord);
            //if (firstJournalRecord->getConsumerName().compare(secondJournalRecord->getConsumerName())!=0) return false;
            if (firstJournalRecord->getConsumerName()==secondJournalRecord->getConsumerName()) return false;
            if (firstJournalRecord->getConsumerSurname()==(secondJournalRecord->getConsumerSurname())) return false;
            if (firstJournalRecord->getConsumerPatronymic()==(secondJournalRecord->getConsumerPatronymic())) return false;
            if (firstJournalRecord->getConsumerAcademicDegree()==(secondJournalRecord->getConsumerAcademicDegree())) return false;
            if (firstJournalRecord->getConsumerPosition()==(secondJournalRecord->getConsumerPosition())) return false;
            if (firstJournalRecord->getImpactOnAmountOfCoffee() - secondJournalRecord->getImpactOnAmountOfCoffee() > 0.01 ||
                firstJournalRecord->getImpactOnAmountOfCoffee() - secondJournalRecord->getImpactOnAmountOfCoffee() < -0.01) return false;
        }
        else if (firstRecord->defineElement()==2 && secondRecord->defineElement()==2){
            auto* firstDutyRecord = dynamic_cast<DutyRecord*>(firstRecord);
            auto* secondDutyRecord = dynamic_cast<DutyRecord*>(secondRecord);
            if (firstDutyRecord->getCurrentAmountOfCoffee() - secondDutyRecord->getCurrentAmountOfCoffee() > 0.01
                || firstDutyRecord->getCurrentAmountOfCoffee() - secondDutyRecord->getCurrentAmountOfCoffee() < -0.01 ) return false;
        }
        else return false;
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

/*
JournalContainer:: JournalContainer(){
    currentSize = 0;
    sizeOfContainer = 10;
    maxVolume = 30;
    records = new BaseRecord*[sizeOfContainer];
}

JournalContainer:: JournalContainer(int numberOfElements, int maxVolume){
    currentSize = sizeOfContainer = numberOfElements;
    this->maxVolume = maxVolume;
    records = new BaseRecord*[sizeOfContainer];
}

JournalContainer:: ~JournalContainer(){
    for (int i = sizeOfContainer-1; i >=0; i--){
        delete &records[i]; // here was &
    }
    currentSize = 0;
    sizeOfContainer=0;
    delete[](records);
}

JournalContainer:: JournalContainer(const JournalContainer &journal){
    this->currentSize = journal.size();
    this->sizeOfContainer = journal.sizeOfContainer;
    this->maxVolume = journal.maxVolume;
    records = new BaseRecord*[sizeOfContainer];
    for (int i=0; i < journal.size(); i++){
        if (journal.get(i)->defineElement() == 1){
            JournalRecord *helper = dynamic_cast<JournalRecord*>(journal.get(i));
            JournalRecord record(*helper);
            records[i] = &record;
        }
        else if(journal.get(i)->defineElement() == 2){
            DutyRecord *helper = dynamic_cast<DutyRecord*>(journal.get(i));
            DutyRecord record(*helper);
            records[i] = &record;
        }
    }
}

void JournalContainer:: insert(BaseRecord &record, int position){
    if ((&record)->defineElement()==1){
        auto* journalRecord = dynamic_cast<JournalRecord*>(&record);

        assert(position>=0 and position<sizeOfContainer and
               journalRecord->getImpactOnAmountOfCoffee() <= maxVolume
               and (-1)*journalRecord->getImpactOnAmountOfCoffee()>= -maxVolume);

        if (position > currentSize) position = currentSize;
        if (currentSize >= sizeOfContainer)
        {                // expand the array
            changeSizeOfContainer(currentSize*2);
        }
        if (position == currentSize){
            if ((&record)->defineElement()==1){
                JournalRecord *helper = dynamic_cast<JournalRecord*>(&record);
                JournalRecord newRecord(*helper);
                records[position] = &newRecord;
            }
            else if ((&record)->defineElement()==2){
                DutyRecord *helper = dynamic_cast<DutyRecord*>(&record);
                DutyRecord newRecord(*helper);
                records[position] = &newRecord;
            }
        }
        else {
            for (int i = currentSize; i > position;i--){    //move array
                records[i] = records[i-1];
            }
            if ((&record)->defineElement()==1){
                JournalRecord *helper = dynamic_cast<JournalRecord*>(&record);
                JournalRecord newRecord(*helper);
                records[position] = &newRecord;
            }
            else if ((&record)->defineElement()==2){
                DutyRecord *helper = dynamic_cast<DutyRecord*>(&record);
                DutyRecord newRecord(*helper);
                records[position] = &newRecord;
            }
        }
    }
    currentSize++;
}

void JournalContainer::insert(BaseRecord &record){
    insert(record, currentSize);
}


void JournalContainer:: deleteRecord(int position){       //old method "pop" was renamed (it called deletedRecord because delete is built-in function)
    assert(position >=0 and position < currentSize);
    if (position == currentSize-1){
        delete &records[position];  //here was &
    }
    else{
        for (int i = position; i < currentSize; i++)
            records[i] = records[i+1];

        delete &records[currentSize - 1]; //here was &
    }
    currentSize--;
}
BaseRecord *JournalContainer:: get(int index) const {
    assert(index >= 0 && index < currentSize);
    return records[index];
}

void JournalContainer:: trim(){
    changeSizeOfContainer(currentSize);
}

void JournalContainer:: clear(){
    for (int i = sizeOfContainer-1; i >=0 ; i--){
        delete &records[i];     //here was &
    }
    currentSize = 0;
    sizeOfContainer = 10;
    records = new BaseRecord*[sizeOfContainer];
};

int JournalContainer:: size() const{
    return currentSize;
}

//should be editted
void JournalContainer:: changeSizeOfContainer(int newSize){
    auto **newContainer = new BaseRecord*[newSize];
    for (int i = 0; i < sizeOfContainer; i++){     //copy records to the new container
        newContainer[i] = records[i];
    }
    for (int i = 0; i < sizeOfContainer; i++){      // delete the old container
        delete &records[i];     //here was &
    }
    delete[](records);
    sizeOfContainer = newSize;
    records = newContainer;
}

void JournalContainer:: writeToFile(const string &path) const{
    std::ofstream stream;
    //stream >> i;
    stream.open(path);
    if (stream.is_open()){
        for (int i = 0; i < currentSize; i++){
            BaseRecord *record = records[i];
            tm time = record->getAccessTime();
            stream << time.tm_hour << '\n';
            stream << time.tm_isdst << '\n';
            stream << time.tm_mday << '\n';
            stream << time.tm_min << '\n';
            stream << time.tm_mon << '\n';
            stream << time.tm_sec<< '\n';
            stream << time.tm_wday << '\n';
            stream << time.tm_yday << '\n';
            stream << time.tm_year << '\n';
            stream << record->defineElement() << '\n';
            if(record->defineElement() == 1){
                auto* journalRecord = dynamic_cast<JournalRecord*>(record);
                stream << journalRecord->getConsumerAcademicDegree() << '\n';
                stream << journalRecord->getConsumerName() << '\n';
                stream << journalRecord->getConsumerSurname() << '\n';
                stream << journalRecord->getConsumerPatronymic() << '\n';
                stream << journalRecord->getConsumerPosition() << '\n';
                if (i != currentSize-1)
                    stream << journalRecord->getImpactOnAmountOfCoffee() << '\n';
                else
                    stream << journalRecord->getImpactOnAmountOfCoffee();
            }
            else{
                auto* journalRecord = dynamic_cast<DutyRecord*>(record);
                if (i != currentSize-1)
                    stream << journalRecord->getCurrentAmountOfCoffee() << '\n';
                else
                    stream << journalRecord->getCurrentAmountOfCoffee();
            }
        }
    }
    stream.flush();
    stream.close();
}

void JournalContainer:: readFromFile(const string &path){
    std::ifstream stream;
    char buffer[50];
    tm time;
    string academicDegree;
    string name;
    string surname;
    string patronymic;
    string position;
    int elementDefinition;
    double impactOnAmountOfCoffee;
    stream.open(path);
        if (stream.is_open()){
            for (int i = 0; !stream.eof(); i++){
                //amount of copypaste reduced
                stream.getline(buffer, 50);
                time.tm_hour = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_isdst = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_mday = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_min = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_mon = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_sec = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_wday = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_yday = atoi(buffer);
                //*buffer = NULL;

                stream.getline(buffer,50);
                time.tm_year = atoi(buffer);
                //*buffer = NULL;


                stream.getline(buffer,50);
                elementDefinition = atoi(buffer);
                //*buffer = NULL;

                if (elementDefinition == 1){
                    stream.getline(buffer,50);
                    academicDegree = string(buffer);
                    //*buffer = NULL;

                    stream.getline(buffer,50);
                    name = string(buffer);
                    //*buffer = NULL;

                    stream.getline(buffer,50);
                    surname = string(buffer);
                    //*buffer = NULL;

                    stream.getline(buffer,50);
                    patronymic = string(buffer);
                    //*buffer = NULL;

                    stream.getline(buffer,50);
                    position = string(buffer);
                    //*buffer = NULL;

                    stream.getline(buffer,50);
                    impactOnAmountOfCoffee = atoi(buffer);
                    //*buffer = NULL;


                    JournalRecord consumer = JournalRecord(time,name,surname,patronymic,position,academicDegree,impactOnAmountOfCoffee);
                    this->insert(consumer);
                }
                else{
                    stream.getline(buffer,50);
                    double currentAmountOfCoffee = atof(buffer);
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
        if (firstRecord->defineElement() == 1 and secondRecord->defineElement()==1){
            auto* firstJournalRecord = dynamic_cast<JournalRecord*>(firstRecord);
            auto* secondJournalRecord = dynamic_cast<JournalRecord*>(secondRecord);
            //if (firstJournalRecord->getConsumerName().compare(secondJournalRecord->getConsumerName())!=0) return false;
            if (firstJournalRecord->getConsumerName()==secondJournalRecord->getConsumerName()) return false;
            if (firstJournalRecord->getConsumerSurname()==(secondJournalRecord->getConsumerSurname())) return false;
            if (firstJournalRecord->getConsumerPatronymic()==(secondJournalRecord->getConsumerPatronymic())) return false;
            if (firstJournalRecord->getConsumerAcademicDegree()==(secondJournalRecord->getConsumerAcademicDegree())) return false;
            if (firstJournalRecord->getConsumerPosition()==(secondJournalRecord->getConsumerPosition())) return false;
            if (firstJournalRecord->getImpactOnAmountOfCoffee() - secondJournalRecord->getImpactOnAmountOfCoffee() > 0.01 ||
                firstJournalRecord->getImpactOnAmountOfCoffee() - secondJournalRecord->getImpactOnAmountOfCoffee() < -0.01) return false;
        }
        else if (firstRecord->defineElement()==2 && secondRecord->defineElement()==2){
            auto* firstDutyRecord = dynamic_cast<DutyRecord*>(firstRecord);
            auto* secondDutyRecord = dynamic_cast<DutyRecord*>(secondRecord);
            if (firstDutyRecord->getCurrentAmountOfCoffee() - secondDutyRecord->getCurrentAmountOfCoffee() > 0.01
                || firstDutyRecord->getCurrentAmountOfCoffee() - secondDutyRecord->getCurrentAmountOfCoffee() < -0.01 ) return false;
        }
        else return false;
    }
    return true;
}
*/
