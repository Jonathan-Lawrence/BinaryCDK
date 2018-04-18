// Jonathan Lawrence
// jml160230@utdallas.edu
// Program 6
// CS3377.501

#include "program6.h"
#include "BinaryFileHeader.h"
#include "BinaryFileRecord.h"
#include <sstream>
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

  //binary file stream
  fstream file;

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

  file.close();
  
  //Convert to strings
  ostringstream convert;
  string magicNum;
  convert << std::hex << header.magicNumber;
  magicNum = convert.str();
  magicNum = "Magic: 0x" + magicNum;
  convert.str("");


  string versionNum;
  convert << header.versionNumber;
  versionNum = convert.str();
  versionNum = "Version: " + versionNum;
  convert.str("");

  string numRecordsNum;
  convert << header.numRecords;
  numRecordsNum = convert.str();
  numRecordsNum = "NumRecords: " + numRecordsNum;
  convert.str("");

  setCDKMatrixCell(myMatrix, 1, 1, magicNum.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, versionNum.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, numRecordsNum.c_str());
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep(10);


  // Cleanup screen
  endCDK();

  return 0;
}

