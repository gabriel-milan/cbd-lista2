#include "Block.h"
#include "Header.h"

#include <vector>

class Heap
{
private:
  uint64_t pos; // Reading block position in the file

public:
  Block *blockp;
  Block *blockg;
  Header* header;

  Heap();
  ~Heap();

  void flush();

  void ins(const char *record);
  const DataRecord *sel(uint32_t uid, bool toDelete=false);
  std::vector<const DataRecord *>selMultiple(uint32_t *uids, const int quant);
  std::vector<const DataRecord *>selRange(float geracaoBegin, float geracaoEnd);
  void del(uint32_t uid);
};
