// Jonathan Lawrence
// jml160230@utdallas.edu
// Program 6 - CDK/git
// BinaryFileHeader - header record

class BinaryFileHeader {
public:
  uint32_t magicNumber; //0xFEEDFACE
  uint32_t versionNumber;
  uint64_t numRecords;
};
