// Jonathan Lawrence
// jml160230@utdallas.edu
// Program 6
// CS3377.501

#include "program6.h"
using namespace std;

int main()
{
  WINDOW *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX *myMatrix;           // CDK Screen Matrix

  const char *rowTitles[MATRIX_HEIGHT+1] = {"a","a", "b", "c"};
  const char *columnTitles[MATRIX_WIDTH+1] = {"a", "a", "b", "c", "d", "e"};
  int boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

  //Streams
  fstream file;
  ostringstream ss;

  //Class objects to read from bin file
  BinaryFileHeader header; 
  BinaryFileRecord record;

  /*
   * Initialize the Cdk screen.
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
   */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
			  boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);


  //Read from binaryStream
  file.open(BINARY_FILE_NAME, ios::in | ios::binary);
  
  if(file.fail()){
    cerr << "ERROR: Cannot open the file " << endl;
    exit(0);
  }
  
  file.read(reinterpret_cast<char*>(&header.magicNumber), sizeof(header.magicNumber));
  file.read(reinterpret_cast<char*>(&header.versionNumber), sizeof(header.versionNumber));
  file.read(reinterpret_cast<char*>(&header.numRecords), sizeof(header.numRecords));
  
  /*
    First, we will read for the members of the BinaryHeaderFile class.
    
    Since it is not an actual instance of the class that is in the 
    binary file, it is necessary to interpret each member of the 
    BinaryFileHeader class seperately.
   */                    
  string magicNum;
  ss << std::hex << header.magicNumber;
  magicNum = ss.str();
  magicNum = "Magic: 0x" + magicNum;
  ss.str("");

  string versionNum;
  ss << std::dec << header.versionNumber;
  versionNum = ss.str();
  versionNum = "Version: " + versionNum;
  ss.str("");

  string numRecordsNum;
  ss << header.numRecords;
  numRecordsNum = ss.str();
  numRecordsNum = "NumRecords: " + numRecordsNum;
  ss.str("");

  // Set cells in the CDK matrix
  setCDKMatrixCell(myMatrix, 1, 1, magicNum.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, versionNum.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, numRecordsNum.c_str());

  /*
    Actual instances of the BinaryFileRecord class are
    in the binary file. 

    So when reading from the file, you must read for 
    entire BinaryFileRecord objects and not the 
    individual members.
   */
  
  for(int i = 0; i < 4; i++){
    file.read(reinterpret_cast<char*>(&record), sizeof(record));
    
    string recordStrLength;
    ss << strlen(record.stringBuffer);
    recordStrLength = ss.str();
    recordStrLength = "strlen: " + recordStrLength;
    ss.str("");

    string recordStrBuffer;
    ss << record.stringBuffer;
    recordStrBuffer = ss.str();
    ss.str("");

    setCDKMatrixCell(myMatrix, i+2, 1, recordStrLength.c_str());
    setCDKMatrixCell(myMatrix, i+2, 2, recordStrBuffer.c_str());
  }
  drawCDKMatrix(myMatrix, true);    /* required  */
  
  file.close();

  /* so we can see results */
  sleep(10);
 

  // Cleanup screen
  endCDK();

  return 0;
}

