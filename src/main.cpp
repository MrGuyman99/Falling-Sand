#include "raylib.h"
#include "raymath.h"

#include "imgui.h"
#include "rlImGui.h"

int main(){

	InitWindow(800, 600, "Falling Sand Game");
	SetTargetFPS(60);
	rlImGuiSetup(true);

	while(WindowShouldClose() == false){

		BeginDrawing();
		ClearBackground(WHITE);
		
		DrawFPS(400, 300);
		
		rlImGuiBegin();
		ImGui::ShowDemoWindow();
		rlImGuiEnd();

		EndDrawing();


	}

	rlImGuiShutdown();
	CloseWindow();

}