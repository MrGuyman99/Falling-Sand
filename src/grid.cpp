#include "grid.hpp"
#include<iostream>
#include "colors.hpp"
#include "raylib.h"
#include "imgui.h"

Grid::Grid(){

    cellSize = 30;
    numRows = 20;
    NumCols = 27;
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


void Grid::Draw(){

    for(int row = 0; row < numRows; row++){

        for(int column = 0; column < NumCols; column++){

            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colors[cellValue]);
        
        }

    }

    if(ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == false){

        DrawRectangle(((GetMouseX() / cellSize) * cellSize) + 1, ((GetMouseY() / cellSize) * cellSize) + 1, cellSize - 1, cellSize - 1, colors[3]);

    }

}

void Grid::Update(){

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == false){

        grid[(GetMouseY() / cellSize)][(GetMouseX() / cellSize)] = 3;

    }

    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == false){

        grid[(GetMouseY() / cellSize)][(GetMouseX() / cellSize)] = 0;

    }

}

void Grid::RenderUI(){

    ImGui::Begin("Test Window");
    
    if(ImGui::Button("Reset Grid", ImVec2(90, 24))){

        Initialize();

    }

    ImGui::End();

}