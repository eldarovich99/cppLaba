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
    JournalContainer(int numberOfElements, int maxVolume);
    ~JournalContainer();
    JournalContainer(const JournalContainer &journal);
    void insert(BaseRecord &record, int position);
    void insert(BaseRecord &record);
    void deleteRecord(int position);
    BaseRecord * get(int index) const;
    void clear();
    int size() const;
    void trim();
    void writeToFile(const std:: string &path) const;
    void readFromFile(const std::string &path);
    bool compare(JournalContainer &container) const;
    DutyRecord convertToDutyRecord(BaseRecord &record) const;
    JournalRecord convertToJournalRecord(BaseRecord &record) const;
private:
    BaseRecord **records;
    int sizeOfContainer;
    int currentSize;
    void changeSizeOfContainer(int newSize);
    int maxVolume;
};

#endif // JOURNAL_H
