#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

#include "grid.hpp"
#include "colors.hpp"

double lastUpdateTime = 0;
//This prevents the sand from falling too fast
bool EventTriggered(double interval){

	double currentTime = GetTime();
	if(currentTime - lastUpdateTime >= interval){

		lastUpdateTime = currentTime;
		return true;

	}

	return false;

}	

int main(){

	//Obligatory Raylib Stuff (The resolution of the window is non-scalable)
	InitWindow(811, 601, "Falling Sand Game");
	SetTargetFPS(100);
	rlImGuiSetup(true);

	//Creating and instance of Grid()
	Grid grid = Grid();

	//The Game loop
	while(WindowShouldClose() == false){

		BeginDrawing();
		//This looks so cursed lol
		ClearBackground(GetCellColors()[8]);
		
		//Drawing and Updating the grid
		grid.Draw();
		if(EventTriggered(0.05)){

			grid.Update();

		}
		
		grid.Interact();
		
		//Rendering the ImGui window
		rlImGuiBegin();
		grid.RenderUI();
		rlImGuiEnd();

		EndDrawing();

	}

	//Shutting everything down and closing the window
	rlImGuiShutdown();
	CloseWindow();

}