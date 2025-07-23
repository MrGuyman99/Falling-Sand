#pragma once
#include<vector>
#include<raylib.h>

class Grid{

public:
    
    Grid();
    void Update();
    void RenderUI();
    int grid[20][27];
    void Draw();

private:

    int numRows;
    int NumCols;
    int cellSize;
    std::vector<Color> colors;
    void Initialize();
    int ColorSelected;

};