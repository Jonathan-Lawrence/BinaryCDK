// Jonathan Lawrence
// jml160230@utdallas.edu
// CS3377.501
// BinaryFileHeader - used to read from cs3377.bin

#include "program6.h"
using namespace std;

class BinaryFileHeader {
 public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};
