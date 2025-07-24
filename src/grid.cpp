#include "grid.hpp"
#include "colors.hpp"
#include "raylib.h"
#include "imgui.h"

Grid::Grid(){

    cellSize = 5;
    numRows = 162;
    NumCols = 162; 
    Initialize();
    //I keep the default colors in color.cpp for organizational reasons
    //There's some spare colors in there that are/were used for testing purposes 
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

//This Draws each cell on the grid depending on the given color
void Grid::Draw(Camera2D &camera){

    //This is the Screen Space mouse coordinates
    Vector2 ConvertedMousePos = GetScreenToWorld2D(GetMousePosition(), camera);

    //We iterate through the entire grid and color in the tile depending on the value
    for(int row = 0; row < numRows; ++row){

        for(int column = 0; column < NumCols; ++column){

            //The cellValue in the index of the color vector that we draw
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize + 1, row * cellSize + 1, cellSize, cellSize, colors[cellValue]);
        
        }

    }

    //This draws the Preview tile before it's placed
    if(ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == false && ImGui::IsAnyItemHovered() == false){

        //((GetMouseX() / cellSize) * cellSize) is the X position we snapped/rounded in Screen Space coordinates. This aligns it to the grid
        DrawRectangle(((ConvertedMousePos.x / cellSize) * cellSize) - (cellSize / 2), ((ConvertedMousePos.y / cellSize) * cellSize) - (cellSize / 2), cellSize, cellSize, colors[ColorSelected]);

    }

}

void Grid::Update(){

    //Checking if the block should fall (row is different because we're iterating top to bottom)
    for(int row = numRows - 2; row >= 0; row--){

        for(int column = 0; column < NumCols; column++){

            //Not Falling (If the tile = 0 or 3)
            if(grid[row][column] == 0 || grid[row][column] == 3 || grid[row - 1][column] == 3){

                continue;

            }

            //Falling (If the tile below = 0 or != 3)
            else if(grid[row + 1][column] == 0){
                
                //We replace the given cell and reset the current one to zero
                //Making it look like it's moving downward
                //(This is the same for the rest of the else if's, just with different parameters)
                grid[row + 1][column] = grid[row][column];
                grid[row][column] = 0;
                continue;

            }

            //If the Diagonal Left Side is clear (if both are clear we just default to left)
            else if(grid[row + 1][column - 1] == 0 && grid[row + 1][column] != 3){

                grid[row + 1][column - 1] = grid[row][column];
                grid[row][column] = 0;
                continue;

            }

            //If the Diagonal right side is clear
            else if(grid[row + 1][column + 1] == 0 && grid[row + 1][column] != 3){
 
                grid[row + 1][column + 1] = grid[row][column];
                grid[row][column] = 0;
                continue;

            } 

        }

    }

}

void Grid::Interact(Camera2D &camera){

    Vector2 ConvertedMousePos = GetScreenToWorld2D(GetMousePosition(), camera);
    //Fixes an odd crash
    if(ConvertedMousePos.x / cellSize > 800){return;}
    if(ConvertedMousePos.y / cellSize > 800){return;}

    //This Updates the tile Color Based on the selected color at the mouse position to the grid
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == false && ImGui::IsAnyItemHovered() == false){

        //GetMouseY() / cellSize is the position in Grid Space
        grid[((int)ConvertedMousePos.y / cellSize)][(int)ConvertedMousePos.x / cellSize] = ColorSelected;

    }

    //This does the same but just erases (i.e sets to zero) the selected tile
    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == false && ImGui::IsAnyItemHovered() == false){

        grid[((int)ConvertedMousePos.y / cellSize)][(int)ConvertedMousePos.x / cellSize] = 0;

    }

}

void Grid::RenderUI(){

    ImGui::Begin("Color Selection Window");
    
    //This Resets the grid by re-initializing it
    if(ImGui::Button("Reset Grid", ImVec2(90, 24))){

        Initialize();
        //We clear and reset the color vector so that the memory Usage doesn't get crazy
        //This doesn't effect anything because the all the sand with those colors are gone
        colors.clear();
        colors = GetCellColors();
        ColorSelected = 3;

    }

    if(ImGui::Button("Place Floor", ImVec2(90, 24))){

        //(Floor is the third index of colors)
        //If ColorSelected doesn't equal the floor index then we set it to equal that
        //Otherwise it equals the most recent color
        if(ColorSelected != 3){

            ColorSelected = 3;

        }

        else if(ColorSelected == 3){

            ColorSelected = (colors.size() - 1);

        }

    }

    //The color picker code
    if(ImGui::ColorPicker4("Color Picker", selectedColor)){

        //This converts the selectedColor array into rgba values for Display Color
        DisplayColor.r = (unsigned char)(selectedColor[0] * 255.0f);
        DisplayColor.g = (unsigned char)(selectedColor[1] * 255.0f);
        DisplayColor.b = (unsigned char)(selectedColor[2] * 255.0f);
        DisplayColor.a = (unsigned char)(selectedColor[3] * 255.0f);
        //We place the new color at the back of the vector
        //We don't erase the color vector so that all the colors for the sand can still display
        colors.emplace_back(DisplayColor);
        //Then we set the current Color Selected to equal the back of the Vector 
        //(The -1 is to account for the fact that vectors start at 0)
        ColorSelected = (colors.size() - 1); 

    }

    ImGui::End();

}