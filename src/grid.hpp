#pragma once
#include<vector>
#include<raylib.h>

class Grid{

public:
    
    Grid();
    void Update();
    void RenderUI();
    void Interact();
    //Unfortunately this cannot be dynamically allocated and much be changed manually
    int grid[162][162];
    void Draw();

private:

    //grid[numRows][numCols] is the way to format how they're equal
    int numRows;
    int NumCols;
    int cellSize;
    //The vector to store the colors from colors.cpp
    std::vector<Color> colors;
    void Initialize();
    int ColorSelected;
    Color DisplayColor;
    //This is the float we pass to ImGui::ColorPicker4
    float selectedColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};

};