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
    ColorSelected = 3;

}

//This Initializes and resets the grid
void Grid::Initialize(){

    //We iterate through every column and row and set it to 0
    for(int row = 0; row < numRows; row++){

        for(int column = 0; column < NumCols; column++){

            grid[row][column] = 0;

        }

    }

}

void Grid::Draw(){

    //We iterate through the entire grid and color in the tile depending on the value
    for(int row = 0; row < numRows; row++){

        for(int column = 0; column < NumCols; column++){

            //The cellValue in the index of the color vector that we draw
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colors[cellValue]);
        
        }

    }

    //This draws the Preview tile before it's placed
    if(ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == false && ImGui::IsAnyItemHovered() == false){

        //((GetMouseX() / cellSize) * cellSize) is the X position we snapped/rounded in Screen Space coordinates. This aligns it to the grid
        DrawRectangle(((GetMouseX() / cellSize) * cellSize) + 1, ((GetMouseY() / cellSize) * cellSize) + 1, cellSize - 1, cellSize - 1, colors[ColorSelected]);

    }

}

void Grid::Update(){

    //This Updates the tile Color Based on the selected color at the mouse position to the grid
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == false && ImGui::IsAnyItemHovered() == false){

        grid[(GetMouseY() / cellSize)][(GetMouseX() / cellSize)] = ColorSelected;

    }

    //This does the same but just erases (i.e sets to zero) the selected tile
    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == false && ImGui::IsAnyItemHovered() == false){

        grid[(GetMouseY() / cellSize)][(GetMouseX() / cellSize)] = 0;

    }

}

void Grid::RenderUI(){

    ImGui::Begin("Color Selection Window");
    
    //This Resets the grid by re-initializing it
    if(ImGui::Button("Reset Grid", ImVec2(90, 24))){

        Initialize();

    }

    //We make a tree node
    if(ImGui::TreeNode("Colors")){

        //Iterates through the loop
        //We ignore the first and last value because the first is 0, or nothing
        //and the last is the outline color of the grid
        for(size_t i = 1; (i + 1) < colors.size(); i++){

            //Pushes a custom ID for each button
            ImGui::PushID(i);
            //Draws text with the color index value
            ImGui::Text("Color %d", i);
            //We draw a button and if pressed the color selected equals the current index
            if(ImGui::Button("Color", ImVec2(90, 24))){

                ColorSelected = i;

            }

            ImGui::PopID();

        }

        ImGui::TreePop();

    }

    ImGui::End();

}