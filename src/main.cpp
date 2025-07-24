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
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(810, 810, "Falling Sand Game");
	SetTargetFPS(100);
	rlImGuiSetup(true);

	//Creating and instance of Grid()
	Grid grid = Grid();
	Camera2D camera = { 0 }; 
	camera.zoom = 1.0f;

	//The Game loop
	while(WindowShouldClose() == false){

		BeginDrawing();
		//This looks so cursed lol
		ClearBackground(GetCellColors()[8]);
		
		BeginMode2D(camera);

		//Drawing and Updating the grid
		if(EventTriggered(0.03)){

			grid.Update();

		}
		
		//This movement code & the scrolling code are all courtesy of
		//The Raylib core examples which can be found here -> https://www.raylib.com/examples/core/loader.html?name=core_2d_camera_mouse_zoom
		if(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){

			//We get the difference in mouse positions between frames
			Vector2 delta = GetMouseDelta();
			//We scale the camera zoom by the delta
			delta = Vector2Scale(delta, -1.0f/camera.zoom);
			//We add delta to the camera.target, making it move there
			camera.target = Vector2Add(camera.target, delta);

		}	
		
		//This represents how much the wheel has moved
		float wheel = GetMouseWheelMove();
		if(wheel != 0){

			//Get the world point that is under the mouse
			Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
			//Set the offset to where the mouse is
			camera.offset = GetMousePosition();

			//Set the target to match, so that the camera maps the world space point
			//under the cursor to the screen space point under the cursor at any zoom
			camera.target = mouseWorldPos;

			//Zoom increment
			//Uses log scaling to provide consistent zoom speed
			float scale = 0.2f * wheel;
			camera.zoom = Clamp(expf(logf(camera.zoom) + scale), 0.125f, 64.0f);

		}
		
		grid.Draw(camera);
		
		grid.Interact(camera);
		EndMode2D();
		
		//The UI, which we render outside of Mode2D to fix issues
		rlImGuiBegin();
		grid.RenderUI();
		rlImGuiEnd();
		
		EndDrawing();

	}

	//Shutting everything down and closing the window
	rlImGuiShutdown();
	CloseWindow();

}