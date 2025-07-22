#pragma once
#include<vector>
#include<raylib.h>

class Grid{

public:
    
    Grid();
    void Initialize();
    void Print();
    int grid[20][10];
    void Draw();

private:

    int numRows;
    int NumCols;
    int cellSize;
    std::vector<Color> colors;

};