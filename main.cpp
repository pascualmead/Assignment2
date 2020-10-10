#include "Grid.h"
#include "FileReader.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
using namespace std::this_thread;
using namespace std::chrono;
using namespace std;


int main(){
  int height = 0;
  int width = 0;
  float density = 0.0;
  int mode = 0;
  string inputFile = "";
  Grid* currentGeneration;
  srand(time(NULL));


  cout << "Starting the Game of Life" << endl;
  cout << "Press(1) to make your own grid with random cell assignment.  Press(2) to get a grid from a File.   " << endl;
  int gridChoice;
  cin >> gridChoice;

  //this is if the user would like to use a file input as their grid
  if(gridChoice == 1){
    cout << "Enter number of rows: " << endl;
    cin >> height;
    // Makes sure that the number of rows entered is valid
    if(height < 1){
      cout << "You did not enter enough rows. You need to at least enter 1 row to play." << endl;
      return 1;
    }
    cout << "Enter number of columns: " << endl;
    cin >> width;
    // doing the same for the columns
    if(width < 1){
      cout << "You did not enter enough rows. You need to at least enter 1 column to play." << endl;
      return 1;
    }
    cout << "Enter population density (between 0 and 1): " << endl;
    cin >> density;
    if(density > 1.0 || density < 0.0){
      cout << "The density you entered is not valid. Density need to be between 0 and 1." << endl;
      return 1;
    }
    cout << "Select a game mode: (1)Classic Mode " << endl;
    cin >> mode;
    //checking mode input
    if(mode == 1){
      //does nothing
    }
    else
    {
      cout << "This game mode is not available, please try again." << endl;
      return 1;
    }
    currentGeneration = new Grid(height,width,density,mode);
  }
  //if they want to use a file
  else if(gridChoice == 2){
    cout << "What is the name of the file you would like to use: ";
    cin >> inputFile;
    cout << "Select a Game Mode: (1)Classic mode "; //I ran out of time and could not impement the other game modes
    cin >> mode;
    //check if mode is valid
    if(mode == 1){
      //does nothing
    }
    else{
      cout << "This game mode is not available, please try again.";
      return 1;
    }

    //Try to open the file that the use inputed
    try{
      currentGeneration = new Grid(inputFile, mode);
    }
    //if the user enters an input file that does not exist, the game will not run.
    catch(runtime_error e){
      cout << "This file does not exist." << endl;
      return 1;
    }

    height = currentGeneration -> rows;
    width = currentGeneration -> columns;
  }
  else{
    cout << "Your input is invalid. Try again." << endl;
    return 1;

  }

  int outputChoice = 0;
  cout << "How would you like your game to run? " << endl;
  cout << "Press 1 to print generation with a brief pause" << endl;
  cout << "Press 2 if you would like to manually print generation by pressing the 'Enter' key " << endl;
  cout << "Press 3 if you would like your generation to be loaded to an output file " << endl;
  cin >> outputChoice;

  string outputFile = "";
  //print with pause
  if(outputChoice == 1){
    string currGenOutput = currentGeneration -> gridToString();
    cout << "Generation 0: " << endl;
    currentGeneration -> getPopulation(currGenOutput);
    cout << currGenOutput << endl;
    sleep_for(seconds(1));
  }
  //print by enter
  else if(outputChoice == 2){
    string currGenOutput = currentGeneration -> gridToString();
    cout << "Generation 0: " << endl;
    currentGeneration -> getPopulation(currGenOutput);
    cout << currGenOutput << endl;
    cout << "Press 'ENTER' to make next generation. " << endl;
    cin.get();

  }
  //print to a file
  else if(outputChoice == 3){

    cout << "What would you like your output file to be named: " << endl;
    cin >> outputFile;
    string currGenOutput = currentGeneration -> gridToString();
    string firstGen = "Generation 0: \n";
    FileReader::outputToFile(outputFile, firstGen);
    currentGeneration -> getPopulation(currGenOutput);
    firstGen = currentGeneration -> gridToString() + "\n";
    FileReader::outputToFile(outputFile, firstGen);
  }
  else {
    cout << "You did not make a valid selection " << endl;
    return 1;
  }
  int generationCount = 0;
  bool running = true;
  cin.get();

  //continues making generations
  while(running){
    string nextGenerationStr = currentGeneration -> nextGen();
    Grid* nextGeneration = new Grid(height, width, mode, nextGenerationStr);

    //need to turn this grid into a string
    string gridString = nextGeneration -> gridToString();
    //keeping track of each generation
    cout << "Generation " << generationCount + 1 << endl;
    if(outputChoice == 1){
      nextGeneration -> getPopulation(gridString);
      cout << gridString << endl;
      sleep_for(seconds(1));
    }
    else if(outputChoice == 2){
      nextGeneration -> getPopulation(gridString);
      cout << gridString << endl;
      cout << "Press 'ENTER' to make the next generation. " << endl;
      cin.get();
    }
    else if(outputChoice == 3){
      nextGeneration -> getPopulation(gridString);
      string temp = "Generation " + to_string((generationCount + 1)) + "\n";
      FileReader::outputToFile(outputFile, temp);
      FileReader::outputToFile(outputFile, gridString);
    }
    else{
      cout << "You did not eter a valid input. " << endl;
      return 1;
    }
    currentGeneration -> ~Grid();
    currentGeneration = nextGeneration;
    generationCount++;
  }
  return 0;
}
