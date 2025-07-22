#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

#include "grid.hpp"
#include "colors.hpp"

int main(){

	InitWindow(300, 600, "Falling Sand Game");
	SetTargetFPS(60);
	rlImGuiSetup(true);
	Color DarkBlue = {44, 44, 127, 255};

	Grid grid = Grid();

	while(WindowShouldClose() == false){

		BeginDrawing();
		ClearBackground(DarkBlue);
		
		grid.Draw();

		rlImGuiBegin();
		rlImGuiEnd();

		EndDrawing();

	}

	rlImGuiShutdown();
	CloseWindow();

}