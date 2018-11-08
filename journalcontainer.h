#ifndef JOURNAL_H
#define JOURNAL_H
#include "journalrecord.h"
#include "dutyrecord.h"
#include <vector>
#include <string>
//#include <fstream>

class JournalContainer
{
public:
    JournalContainer();
    JournalContainer(int numberOfElements, int maxVolume, int currentVolume);
    ~JournalContainer();
    JournalContainer(const JournalContainer &journal);
    void insert(DutyRecord &record, int position);
    void insert(DutyRecord &record);
    void deleteRecord(int position);
    DutyRecord get(int index) const;
    void clear();
    int size() const;
    void trim();
    void writeToFile(std:: string) const;
    void readFromFile(std::string);
    bool compare(JournalContainer container) const;
private:
    DutyRecord *records;
    int sizeOfContainer;
    int currentSize;
    void changeSizeOfContainer(int newSize);
    int currentVolumeOfBulb;
    int maxVolume;
    //inline void printTime(ofstream stream) const;
    //inline void getTime(ofstream stream) const;
};

#endif // JOURNAL_H
