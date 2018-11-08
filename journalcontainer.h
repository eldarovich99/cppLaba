#ifndef JOURNAL_H
#define JOURNAL_H
#include "journalrecord.h"
#include <vector>
#include <string>

class JournalContainer
{
public:
    JournalContainer();
    JournalContainer(int numberOfElements, int maxVolume, int currentVolume);
    ~JournalContainer();
    JournalContainer(const JournalContainer &journal);
    void insert(JournalRecord &record, int position);
    void insert(JournalRecord &record);
    void deleteRecord(int position);
    JournalRecord get(int index) const;
    void clear();
    int size() const;
    void trim();
    void writeToFile(std:: string) const;
    void readFromFile(std::string);
    bool compare(JournalContainer container) const;
private:
    JournalRecord *records;
    int sizeOfContainer;
    int currentSize;
    void changeSizeOfContainer(int newSize);
    int currentVolumeOfBulb;
    int maxVolume;
};

#endif // JOURNAL_H
