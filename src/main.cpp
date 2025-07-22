#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

#include "grid.hpp"
#include "colors.hpp"

int main(){

	InitWindow(800, 600, "Falling Sand Game");
	SetTargetFPS(60);
	rlImGuiSetup(true);

	Grid grid = Grid();

	while(WindowShouldClose() == false){

		BeginDrawing();
		ClearBackground(GetCellColors()[8]);
	
		grid.Draw();
		grid.Update();

		rlImGuiBegin();
		grid.RenderUI();
		rlImGuiEnd();

		EndDrawing();

	}

	rlImGuiShutdown();
	CloseWindow();

}