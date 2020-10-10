#include <iostream>
using namespace std;

class Grid{
  public:
    //constructor
    Grid(int rows, int columns, float density, int mode);
    //overloaded constructor
    Grid(int rows, int columns, int mode, string lastGeneration);
    //overloaded constructor
    Grid(string inputFile, int mode);
    //destructor
    ~ Grid();

    int rows;
    int columns;
    int populationCount;
    int population;
    float density;
    string lastGeneration;
    string cellString;
    int mode;
    int totalNeighbors;
    string gridToString();
    string makeString();
    int getPopulation(string input);
    void gridInitializer(string cellString);
    void createGrid();
    int countNeighbors(int x, int y);
    string nextGen();
    char** grid;
    bool isNeighbor(int x, int y);


};
