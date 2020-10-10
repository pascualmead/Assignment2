#include <iostream>
#include "Grid.h"
#include "FileReader.h"
#include <algorithm>

using namespace std;

//constructor
Grid::Grid(int rows,int columns, float density, int mode){
  this->rows = rows;
  this->columns = columns;
  this->density = density;
  this->mode = mode;
  grid = new char*[rows];
  createGrid();
  string gridString = makeString();
  gridInitializer(gridString);
};

//overloaded constructor for last generation
Grid::Grid(int rows, int columns, int mode, string lastGeneration){
  this->rows = rows;
  this->columns = columns;
  this->mode = mode;
  createGrid();
  gridInitializer(lastGeneration);
  getPopulation(lastGeneration);

};

//overloaded for reading the grid from a user inputted file
Grid::Grid(string inputFile, int mode){
  if(mode < 1 || mode > 3){
    throw runtime_error("You did not enter a valid Game mode. Please try again.");
  }
  this -> mode = mode;

  FileReader reader(inputFile);

  rows = reader.rows;
  columns = reader.columns;
  createGrid();
  gridInitializer(reader.gridStringFile);
  getPopulation(reader.gridStringFile);
}

//Destructor
Grid::~Grid()
{
  for(int r = 0; r < rows; ++r){
    delete[] grid[r];
  }
  delete[] grid;
}

//Here we are making a 2D array with '-' as its values that will represent our grid
void Grid::createGrid(){
  grid = new char*[rows];
  for(int row = 0; row < rows; ++row){
    grid[row] = new char[columns];
    for(int column = 0; column < columns; ++column){
      grid[row][column] = '-';
    }
  }
}

//Method to turn grid into a string.
string Grid::gridToString()
{
  string gridString = "";
  for(int r = 0; r < rows; ++r)
  {
    for(int c = 0; c < columns; ++c)
    {
      gridString += grid[r][c];
    }
    //after each row ras been complete, we make a new line to follow the format of the grid
    gridString += "\n";

  }
  return gridString;
}

//makes a string that has the correct density of populated and unpopulated cells
string Grid::makeString()
{

  int gridSize = rows * columns;
  population = density * gridSize;
  population = (int)population;
  int emptyCells = gridSize - population;


  for(int i = 0; i < population; ++i){
    cellString += "X";
  }

  for(int i =0; i < emptyCells; ++i){
    cellString += "-";
  }
  //shuffles the string
  random_shuffle(cellString.begin(),cellString.end());
  return cellString;
}


//void method to initialize grid
void Grid::gridInitializer(string cellString)
{
  //going through the empty grid and adding
  for(int r = 0; r < rows; ++r)
  {
      for(int c = 0; c < columns; ++c)
      {
        grid[r][c] = cellString[0];
        cellString.erase(0,1);
      }
  }
}

//method to track the population of each generation
int Grid::getPopulation(string input){
  int populationCount = 0;
  for(int i = 0; i < input.length(); ++i){
    if(input[i]=='X'){
      populationCount+=1;
    }
  }
  return populationCount;
}



//This is the classic game mode, did not know how to do the other modes
bool Grid::isNeighbor(int x, int y){
  if(mode == 1){
    if(x < 0){
      return false;
    }
    if(y < 0){
      return false;
    }
    if(x >= rows){
      return false;
    }
    if(y >= columns){
      return false;
    }
    if(grid[x][y] == '-'){
      return false;
    }
    if(grid[x][y] == 'X'){
      return true;
    }
  }
}

//method to count the neighbors
int Grid::countNeighbors(int x, int y)
{
  //Here we are counting all up the neighbors if the isNeighbor() method returns true
  int neighbors = 0;
  if(isNeighbor(x+1,y))
    neighbors++;
  if(isNeighbor(x-1,y))
    neighbors++;
  if(isNeighbor(x,y+1))
    neighbors++;
  if(isNeighbor(x,y-1))
    neighbors++;
  if(isNeighbor(x+1,y+1))
    neighbors++;
  if(isNeighbor(x-1,y-1))
    neighbors++;
  if(isNeighbor(x-1,y+1))
    neighbors++;
  if(isNeighbor(x+1,y-1))
    neighbors++;

  return neighbors;

}


//This method returns a string that correctly fills the cells of the next generation based on the last one
string Grid::nextGen()
{
  string nextGrid = "";
  for(int row = 0; row < rows; ++row){
    for(int column = 0; column < columns; ++column){
      //this is for the unpopulated cells
      if(grid[row][column] == '-'){
        //if their are 3 neighbors around the unpopulated cell, then a new cell is generated
        if(countNeighbors(row,column) == 3){
          nextGrid += "X";
        }
        //anything other than 3 result in an empty cell
        else{
          nextGrid += "-";
        }
      }
      //this is for the populated cells
      else if(grid[row][column] == 'X'){
        //if it has 2 neighbors the cell remains in the next generation
        if(countNeighbors(row,column) == 2){
          nextGrid += "X";
        }
        //if it has 3 neighbors the cell remains in the next generation
        else if(countNeighbors(row,column) == 3){
          nextGrid += "X";
        }
        //anything other than 2 or 3 neighbors results in an empty cell
        else{
          nextGrid += "-";
        }
      }
    }
  }
  return nextGrid;
}
