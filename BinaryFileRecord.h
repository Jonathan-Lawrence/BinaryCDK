// Jonathan Lawrence
// jml160230@utdallas.edu
// CS3377.501
// BinaryFileRecord - structure for string to be read from cs3377.bin

#include "program6.h"
using namespace std;

class BinaryFileRecord {
 public:
  uint8_t strLength;
  char stingBuffer[25];
};
