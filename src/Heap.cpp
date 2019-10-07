#include "../include/Heap.h"

#include <iostream>
#include <cstring>

#define HEAP_DISK "Heap.cbd"

Heap::Heap()
{
  const std::string dataFilename = HEAP_DISK;
  const std::string headerFilename = HEAP_DISK "h";
  this->blockp = new Block(dataFilename.c_str(), 'w'); // Initialize writing block
  this->blockg = new Block(dataFilename.c_str(), 'r'); // Initialize reading block
  this->header = new Header(headerFilename);
  this->entryCounter = 0;
}

Heap::~Heap()
{
  delete this->blockp; // Delete writing block
  delete this->blockg; // Delete reading block
  delete this->header;
}

void Heap::flush()
{
  this->blockp->persist();
  this->header->write();
}

void Heap::ins(const char *string)
{
  const DataRecord *record = new DataRecord(string, entryCounter); // Initialize record to be inserted
  this->blockp->write(record);               // Write record in writing block
  this->header->addRecord();
}

const DataRecord *Heap::sel(uint32_t uid, bool toDelete)
{
  this->pos = this->blockg->read(0); // Use reading block to read the disk
  const DataRecord *record;              // Initialize a empty record
  do
  {
    for (int i = 0; i < this->blockg->count(); i++)
    {                                // For i = 0 to i = number of reading block's records
      record = this->blockg->get(i); // Put idx record from block into record variable
      bool found = 1;                // Initialize boolean found as true
      if (!record->uidCmp(uid)) {
        found = 0;
        break;
      }
      if (found)
      { // If found record with query's cpf return the record
        if (toDelete)
        {
          // Replace the current register with 000's:
          this->blockg->nullify(i, this->pos, HEAP_DISK);
          std::cout << "Deleted";
        }
        else
        {
          std::cout << "Found";
        }
        // Finishes printing:
        std::cout << " record " << *record << " in block position " << i << std::endl;
        return record;
      }
    }
  } while ((this->pos = this->blockg->read(this->pos)) > 0); // While have records in block
  std::cout << "No record with UID = " << uid << std::endl;
  return nullptr;
}

std::vector<const DataRecord *>Heap::selMultiple(uint32_t *uids, const int quant)
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
      for (int j = 0; j < quant; j++)
      {
        if (record->uid == uids[j])
        {
          foundRecords.push_back(record);
          found++;
          break;
        }
      }
      if (found == quant)
      {
        std::cout << "All records found " << std::endl;
        return foundRecords;
      }
    }
  } while ((this->pos = this->blockg->read(this->pos)) > 0);
  std::cout << "Not all records found " << std::endl;
  return foundRecords;
}

std::vector<const DataRecord *>Heap::selRange(float geracaoBegin, float geracaoEnd)
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
      // if (record->geracaoInRange(geracaoBegin, geracaoEnd))
      // {
      //   foundRecords.push_back(record);
      //   found++;
      // }
    }
  } while ((this->pos = this->blockg->read(this->pos)) > 0);
  return foundRecords;
}

void Heap::del(uint32_t uid)
{
  // Seek and destroy:
  Heap::sel(uid, true);
}
