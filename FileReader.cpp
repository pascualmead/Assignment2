#include "FileReader.h"
using namespace std;


FileReader::FileReader(string inputFile){
  ReadFile(inputFile);
}


//method for reading a file
void FileReader::ReadFile(string inputFile){
  ifstream inputStream;
  inputStream.open(inputFile);

  if(!inputStream){
    throw runtime_error("Could not open file: " + inputFile);
  }

  //going through the file to count the number of lines in it
  string line;
  int numLines = 0;
  while(getline(inputStream,line)){
    numLines+=1;
  }

  inputStream.clear();
  inputStream.seekg(0);

  //array to hold lines in the file
  string* arrayLines = new string[numLines];
  int count = 0;

  while(getline(inputStream,line)){
    arrayLines[count] = line;
    count+=1;
  }

  inputStream.clear();
  inputStream.seekg(0);
  inputStream.close();


  // turn the first two lines into integers to set the size of the grid
  this->rows = stoi((string)arrayLines[0]);
  this->columns = stoi((string)arrayLines[1]);

  //error checking
  cout << rows << endl;
  cout << columns << endl;



  //if these first two lines are not equal proper values, we need to throw an error
  if(this->rows != numLines - 2 || correctColumns(arrayLines, numLines, columns) == false){
    throw runtime_error("This file does no have the right inputs");
  }


  int cells = 0;
  int populatedCells = 0;
  //this is creating a string that adds array elements and count the number of cells and populated cells
  for(int i = 2; i < numLines; ++i){
    for(int j = 0; j < arrayLines[i].length(); ++j){
      cells+=1;
      gridStringFile += arrayLines[i][j];
      if(arrayLines[i][j] == 'X'){
        populatedCells+=1;
      }
    }
  }

  for(int i = 0; i < gridStringFile.length(); ++i){
    if(gridStringFile[i] == 'X' || gridStringFile[i] == '-'){
      //does nothing
    }
    else{
      throw runtime_error("This file does not have valid characters" );

    }
  }
}


//method for determining if the columns are correct in the file
bool FileReader::correctColumns(string*& arrayLines, int numLines, int columns){
  int i = 2;
  while(i < numLines){
    if((arrayLines[i].length()-1) != columns){
      return false;
    }
    i++;
  }
  return true;

}


//this method allows the user to output to a file
void FileReader::outputToFile(string outputFile, string writeLine){
  ofstream outputStream;
  outputStream.open(outputFile);
  if(!outputStream){
    throw runtime_error("Could not open the file.");
  }
  outputStream << writeLine << endl;
  outputStream.close();
}
