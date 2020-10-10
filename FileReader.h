#include <iostream>
#include <fstream>
using namespace std;

class FileReader{
public:


  int rows;
  int columns;
  string gridStringFile;

  FileReader(string inputFile);

  //function that checks if the file has the correct amount of columns
  bool correctColumns(string*& arrayLines, int numLines, int numColumns);
  //function that allows writing to a file
  static void outputToFile(string inputFile, string writeLine);
  //function that reads from a file
  void ReadFile(string inputFile);

};
