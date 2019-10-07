#include <iostream>
#include <fstream>
#include <list>

#include "include/Heap.h"
#include "include/Sorted.h"
#include "include/Hash.h"

#define DATA_STRUCT Heap

using namespace std;

void printBlocks(DATA_STRUCT* db)
{
  cout << db->blockg->blocks_used << " read blocks used" << endl;
  cout << db->blockp->blocks_used << " write blocks used" << endl;
}

void initDb(DATA_STRUCT* db)
{
  string line;
  ifstream infile("data/gh.csv");
  getline(infile, line);
  if (infile.is_open())
  {
    while (getline(infile, line))
    {
      db->ins(line.c_str());
    }
    infile.close();
    db->flush();
  }
  printBlocks(db);
}

void testInsert(DATA_STRUCT* db)
{
  db->ins("1,1,2017-01-01,46.0");
  db->flush();
  printBlocks(db);
}

void testSelect(DATA_STRUCT* db)
{
  uint32_t uid = 10;
  db->sel(uid);
  printBlocks(db);
}

// void testSelectMultiple(DATA_STRUCT* db)
// {
//   const uint32_t uids = {0};
//   const std::vector<const DataRecord *> records = db->selMultiple(uids, 1);
//   for (int i = 0; i < records.size(); i++)
//   {
//     cout << "Registro " << i << ": " << records[i][0] << endl;
//   }
//   printBlocks(db);
// }

void testSelectRange(DATA_STRUCT *db)
{
  uint32_t uidBegin = 31083286;
  uint32_t uidEnd = 3108358286;
  const std::vector<const DataRecord *> records = db->selRange(uidBegin, uidEnd);
  for (int i = 0; i < records.size(); i++)
  {
    cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  printBlocks(db);
}

void testDelete(DATA_STRUCT *db)
{
  uint32_t uid = 10;
  db->del(uid);
  printBlocks(db);
}

int main(int argc, char **argv)
{
  DATA_STRUCT db;

  // Init database
  initDb(&db);

  // Insert
  testInsert(&db);

  // Select
  // testSelect(&db);

  // Select multiple
  // testSelectMultiple(&db);

  // Select range
  // testSelectRange(&db);

  // Delete
  // testDelete(&db);
  
}
