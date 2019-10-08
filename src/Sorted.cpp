#include "Sorted.h"

#include <iostream>
#include <cstring>
#include <list>

#define SORTED_DISK "Sorted.cbd"

Sorted::Sorted()
{
  const std::string dataFilename = SORTED_DISK;
  const std::string headerFilename = SORTED_DISK"h";
  this->blockp = new Block(dataFilename.c_str(), 'w');
  this->blockg = new Block(dataFilename.c_str(), 'r');
  this->header = new Header(headerFilename);
  this->sort();
  this->sorted = true;
  this->entryCounter = 0;
}

Sorted::~Sorted()
{
  delete this->blockp;
  delete this->blockg;
}

void Sorted::flush()
{
  this->blockp->persist();
  this->header->write();
  if (this->sorted == false){
    std::cout<<"Chamei o sort()"<<std::endl;
    this->sort();
    std::cout<<"Saí do sort()"<<std::endl;
    this->sorted = true;
  }
}



void Sorted::ins(const char *string)
{
  const DataRecord *record = new DataRecord(string, entryCounter); // Initialize record to be inserted
  entryCounter++;
  this->blockp->write(record);               // Write record in writing block
  this->sorted = false;
}

const DataRecord *Sorted::sel(uint32_t uid, bool toDelete)
{
  if (!this->sorted) {
    this->sort();
    this->sorted = true;
  }
  int64_t start = 0;
  int64_t end = 0;
  const DataRecord *record;
      // std::cout << "B" << std::endl;
  do
  {
    this->pos = this->blockg->read((start + end) / 2);
    // std::cout << "START " << start << std::endl;
    // std::cout << "END " << end << std::endl;
    // std::cout << (record->uid > uid) << std::endl;
      // std::cout << "C" << std::endl;
    record = this->blockg->get(0); //checks if first record is larger
    bool found = 1;
    bool searchAgain = 0;
    if (record->uid != uid) {
      found = 0;
    }
        // std::cout << "A" << std::endl;
    if (record->uid > uid) {
      end = this->pos;
      searchAgain = 1;
    }
        // std::cout << "B" << std::endl;
    if (found)
    {
      if (toDelete){
        // std::cout << "A" << std::endl;
        // Replace the current register with 000's:
        this->blockg->nullify(0, this->pos, SORTED_DISK);
        std::cout << "Deleted";
      }
      else{
        std::cout<<"Found";
      }
      // Finishes printing:
      std::cout << " record " << *record << " in block position " << 0 << std::endl;
      return record;
    }
    else
    {
      if (searchAgain)
      {
        continue;
      }
    }
    record = this->blockg->get(this->blockg->count() - 1); // Checks if last record is smaller
    found = 1;
    searchAgain = 0;

    if (record->uid != uid) {
      found = 0;
    }
    if (record->uid < uid) {
      start = this->pos;
      searchAgain = 1;
    }

    if (found)
    {
      if (toDelete){
        // std::cout << "B" << std::endl;
        // Replace the current register with 000's:
        this->blockg->nullify(0, this->pos, SORTED_DISK);
        std::cout << "Deleted";
      }
      else{
        std::cout<<"Found";
      }
      // Finishes printing:
      std::cout << " record " << *record << " in block position " << this->blockg->count() - 1 << std::endl;
      return record;
    }
    else
    {
      if (searchAgain)
      {
        continue;
      }
    }
    for (int i = 1; i < this->blockg->count() - 1; i++)
    { //check other records
      record = this->blockg->get(i);
      found = 1;
      if (record->uid != uid) {
        found = 0;
      }
      if (found)
      {
      if (toDelete){
        std::cout << "C" << std::endl;
        // Replace the current register with 000's:
        this->blockg->nullify(0, this->pos, SORTED_DISK);
        std::cout << "Deleted";
      }
      else{
        std::cout<<"Found";
      }
      // Finishes printing:
      std::cout << " record " << *record << " in block position " << i << std::endl;
      return record;
      }
    }
    int t = this->blockg->read(this->pos);
      this->pos = t == -1 ? 0 : t;
  } while ( this->pos > 0);
  std::cout << "No record with UID = " << uid << std::endl;
  return nullptr;
}

std::vector<const DataRecord *>Sorted::selMultiple(uint32_t *uids, const int quant)
{
  std::vector<const DataRecord *> output;
  for (int i = 0; i < quant; i++) {
    // std::cout << "A" << std::endl;
    const DataRecord *selectResult = this->sel(uids[i]);
    if (!(selectResult == nullptr))
      output.push_back(selectResult);
  }
  return output;
}

std::vector<const DataRecord *>Sorted::selRange(float geracaoBegin, float geracaoEnd)
{
  this->pos = this->blockg->read(0);
  const DataRecord *record;
  std::vector<const DataRecord *>foundRecords;
  int found = 0;
  do
  {
    for (int i = 0; i < this->blockg->count(); i++)
    {
      record = this->blockg->get(i);
      if (record->geracaoInRange(geracaoBegin, geracaoEnd))
      {
        foundRecords.push_back(record);
        found++;
      }
    }
    int t = this->blockg->read(this->pos);
    this->pos = t == -1 ? 0 : t;
  } while (this->pos > 0);
  return foundRecords;
}

void Sorted::del(uint32_t uid)
{
  // Seek and destroy:
  Sorted::sel(uid, true);
}

void Sorted::sort() {
  std::string line;
  std::ifstream outputFile(SORTED_DISK, std::ios_base::in);
  std::list<DataRecord> records;
  if (outputFile.is_open()) {
    while (std::getline(outputFile, line)){
      DataRecord r(line.c_str());
      records.push_back(r);
    }
    outputFile.close();
  }
  records.sort();
  std::ofstream sortedOutputFile(SORTED_DISK, std::ios_base::out);
  for (std::list<DataRecord>::iterator it = records.begin(); it != records.end(); it++) {
    sortedOutputFile << *it;
  }
}