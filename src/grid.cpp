#include "grid.hpp"
#include<iostream>
#include "colors.hpp"

Grid::Grid(){

    numRows = 20;
    NumCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();

}

void Grid::Initialize(){

    for(int row = 0; row < numRows; row++){

        for(int column = 0; column < NumCols; column++){

            grid[row][column] = 0;

        }

    }

}

void Grid::Print(){


    for(int row = 0; row < numRows; row++){

        for(int column = 0; column < NumCols; column++){

            std::cout << grid[row][column] << " ";

        }

        std::cout << std::endl;

    }

}

void Grid::Draw(){

    for(int row = 0; row < numRows; row++){

        for(int column = 0; column < NumCols; column++){

            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colors[cellValue]);
        }

    }

}