#include <ctime>
#include <string>
#include <cassert>
#include "journalrecord.h"
#include "journalcontainer.h"
#include <iostream>
#include <dutyrecord.h>
using namespace std;

//const int BOILER_VOLUME = 30;

/*
bool checkImpactOnAmountOfCoffee(double impact){
    return impact <= BOILER_VOLUME && impact >= (-1)*BOILER_VOLUME;
}

double setImpactOnAmountOfCoffee(double impact){
    if (impact <= BOILER_VOLUME && impact >= (-1)*BOILER_VOLUME) return impact;
    else return 0.0;
}*/

//function for displaying all elements

DutyRecord convertToDutyRecord(BaseRecord record){
    BaseRecord *consumerHelper = &record;
    DutyRecord *dutyHelper;
    dutyHelper = static_cast<DutyRecord*>(consumerHelper);
    return  *dutyHelper;
}

JournalRecord convertToJournalRecord(BaseRecord record){
    BaseRecord *consumerHelper = &record;
    JournalRecord *journalHelper;
    journalHelper = static_cast<JournalRecord*>(consumerHelper);
    return  *journalHelper;
}

void displayData(JournalContainer container){
    for (int i = 0; i < container.size(); i++){ // check all
        cout << "Element number #" << i << '\n';
        BaseRecord record = container.get(i);
        cout << record.getAccessTime().tm_hour << '\n';
        cout << record.getAccessTime().tm_isdst << '\n';
        cout << record.getAccessTime().tm_mday << '\n';
        cout << record.getAccessTime().tm_min << '\n';
        cout << record.getAccessTime().tm_mon << '\n';
        cout << record.getAccessTime().tm_sec<< '\n';
        cout << record.getAccessTime().tm_wday << '\n';
        cout << record.getAccessTime().tm_yday << '\n';
        cout << record.getAccessTime().tm_year << '\n';
        if (record.getCurrentAmountOfCoffee()+1<0.01) {
            cout << record.getConsumerAcademicDegree() << '\n';
            cout << record.getConsumerName() << '\n';
            cout << record.getConsumerPatronymic() << '\n';
            cout << record.getConsumerPosition() << '\n';
            cout << record.getConsumerSurname() << '\n';
            cout << record.getImpactOnAmountOfCoffee() << '\n';
        }
        else
            cout <<container.get(i).getCurrentAmountOfCoffee() << '\n';
        cout << '\n';
    }
}

int main()
{

    JournalRecord defaultConsumer;     // default constructor
    auto *u2 = new tm();
    assert(defaultConsumer.getConsumerName().compare("Name")==0);
    assert(defaultConsumer.getConsumerSurname().compare("Surname")==0);
    assert(defaultConsumer.getConsumerPatronymic().compare("Patronymic")==0);
    assert(defaultConsumer.getConsumerPosition().compare("Position")==0);
    assert(defaultConsumer.getConsumerAcademicDegree().compare("Academic degree")==0);
    assert(defaultConsumer.getImpactOnAmountOfCoffee()==0.0);
    std::time_t t = std::time(nullptr);   // get time now
    tm *accessTime = std::localtime(&t);
    assert(defaultConsumer.getAccessTime().tm_hour == accessTime->tm_hour
           && defaultConsumer.getAccessTime().tm_min == accessTime->tm_min);

    //cout << timer.tm_hour;
    u2->tm_sec = 45;
    u2->tm_min = 34;
    u2->tm_hour = 19;
    u2->tm_mday = 5;
    u2->tm_mon = 7;
    u2->tm_yday = 134;
    u2->tm_year = 25;
    //std::time_t t = std::time(0);   // get time now
   // tm *_accessTime = std::localtime(&t);
    double impact1 = -5.0;
    JournalRecord someConsumer(*u2, "Nikolay", "Sobolev", "Yurievich", "Youtuber", "Graduate", impact1);  // initialized constructor
    assert(someConsumer.getConsumerName().compare("Nikolay")==0);
    assert(someConsumer.getConsumerSurname().compare("Sobolev")==0);
    assert(someConsumer.getConsumerPatronymic().compare("Yurievich")==0);
    assert(someConsumer.getConsumerPosition().compare("Youtuber")==0);
    assert(someConsumer.getConsumerAcademicDegree().compare("Graduate")==0);
    assert(someConsumer.getImpactOnAmountOfCoffee() == impact1);

    double fakeImpact = 300.0;
    JournalRecord fakeConsumer(*u2, "", "", "Yurievich", "", "", fakeImpact);  // constructor with bad values
    assert(fakeConsumer.getConsumerName().compare("")!=0);
    assert(fakeConsumer.getConsumerSurname().compare("")!=0);
    assert(fakeConsumer.getConsumerPatronymic().compare("Yurievich")==0);
    assert(fakeConsumer.getConsumerPosition().compare("")!=0);
    assert(fakeConsumer.getConsumerAcademicDegree().compare("")!=0);
    assert(fakeConsumer.getImpactOnAmountOfCoffee() == fakeImpact);

    JournalRecord anotherConsumer(someConsumer);       // copying the object
    assert(anotherConsumer.getConsumerName().compare(someConsumer.getConsumerName())==0);
    assert(anotherConsumer.getConsumerSurname().compare(someConsumer.getConsumerSurname())==0);
    assert(anotherConsumer.getConsumerPatronymic().compare(someConsumer.getConsumerPatronymic())==0);
    assert(anotherConsumer.getConsumerPosition().compare(someConsumer.getConsumerPosition())==0);
    assert(anotherConsumer.getConsumerAcademicDegree().compare(someConsumer.getConsumerAcademicDegree())==0);
    assert(anotherConsumer.getImpactOnAmountOfCoffee() == impact1);

    anotherConsumer.setConsumerName("Vladimir");
    anotherConsumer.setConsumerName("");
    assert(anotherConsumer.getConsumerName().compare("Vladimir")==0);
    assert(someConsumer.getConsumerName().compare("Nikolay")==0);   // original object remains the same
    anotherConsumer.setConsumerSurname("Lenin");
    assert(anotherConsumer.getConsumerSurname().compare("Lenin")==0);
    double impact2 = 8.0;
    anotherConsumer.setImpactOnAmountOfCoffee(impact2);
    anotherConsumer.setImpactOnAmountOfCoffee(impact2);       //uncorrect values are ignored
    assert(anotherConsumer.getImpactOnAmountOfCoffee()==impact2);
    assert(someConsumer.getImpactOnAmountOfCoffee()==impact1);
    anotherConsumer.setAccessTime(*accessTime);     // set current time
    assert(anotherConsumer.getAccessTime().tm_hour==accessTime->tm_hour
           && anotherConsumer.getAccessTime().tm_min == accessTime->tm_min);
    auto *u3 = new tm();
    u3->tm_hour=3;
    JournalRecord thirdConsumer(*u3, "Valeriy", "Petuhov", "Nickolaevich", "Youtuber", "Graduate", -5.0);  // field accessTime with error replaced by default
    assert(thirdConsumer.getAccessTime().tm_min == accessTime->tm_min);
    delete(u2);
    delete(u3);



    // Part 2
//изменить проверку на объем кофе,добавить сравнение элементов; изменить метод для получения объектов из файлов(воид вместо журнала); зменить сиауты на ассерты в контейнере;


    JournalContainer container = JournalContainer(); // tests for default constructor
    container.insert(someConsumer);
    container.insert(anotherConsumer);
    container.insert(someConsumer,1);
    assert(container.size()==3);    // check size
    container.insert(defaultConsumer);
    assert(container.size()==4);    // check size after inserting



    container.writeToFile("d:/data.txt");      //write to file

    //displayData(container);
    //read from file
    //JournalContainer thirdContainer = JournalContainer();
    //thirdContainer.readFromFile("d:/data.txt");
    cout << "\n\n\n";
    //displayData(thirdContainer);
    /*
    assert(thirdContainer.compare(container));      // compare recovered container from file
    //cout << container.size() << " " << thirdContainer.size();
    //cout << thirdContainer.get(3).getConsumerName();

    //compare with copy
    assert(container.get(0).getConsumerName().compare(someConsumer.getConsumerName())==0);
    assert(container.get(1).getConsumerName().compare(someConsumer.getConsumerName())==0);
    assert(container.get(2).getConsumerName().compare(anotherConsumer.getConsumerName())==0);
    container.deleteRecord(2);
    assert(container.size()==3);    //check size after deletion

    JournalContainer anotherContainer = JournalContainer(container);        // copying test
    assert(anotherContainer.get(0).getConsumerPosition().compare(container.get(0).getConsumerPosition()) == 0);
    record = convert(anotherConsumer);
    anotherContainer.insert(record,0);
    assert(anotherContainer.get(0).getConsumerName().compare(container.get(0).getConsumerName()) != 0);

    //displaying all elements
    displayData(anotherContainer);

    container.clear();      // check clear function
    assert(container.size()==0);*/
    return 0;
}


