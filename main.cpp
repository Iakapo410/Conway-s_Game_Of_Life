#include <iostream>
#include <raylib.h>
#include "LifeSimulation.hpp"


int main() 
{
	Color dark_Grey = {29,29,29,255};
	const int window_Width = 1200;
	const int window_Height = 800;
	const int cell_Size = 25;
	int FPS = 12;
	SetTargetFPS(FPS);
	
	LifeSimulation lifeSimulation = { window_Width,window_Height,cell_Size };

	InitWindow(window_Width, window_Height, "Conway's Game of Life");

	//Simulation Loop
	while(WindowShouldClose() == false)
	{
	//1. Event Handling
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			Vector2 mousePosistion = GetMousePosition();
			int row = mousePosistion.y / cell_Size;
			int column = mousePosistion.x / cell_Size;
			lifeSimulation.ToggleCell(row,column);

		}
		if(IsKeyPressed(KEY_ENTER))
		{
			lifeSimulation.Start();
			SetWindowTitle("Running ... ");
		}
		else if(IsKeyPressed(KEY_SPACE))
		{
			lifeSimulation.Stop();
			SetWindowTitle("Stopped");
		}
		else if(IsKeyPressed(KEY_UP))
		{
			FPS += 2;
			SetTargetFPS(FPS);
		}
		else if(IsKeyPressed(KEY_DOWN))
		{
			if(FPS > 5)
			{
				FPS -= 2;
				SetTargetFPS(FPS);
			}
		}
		else if(IsKeyPressed(KEY_R))
		{
			lifeSimulation.CreateRandomState();
		}
		else if(IsKeyPressed(KEY_C))
		{
			lifeSimulation.ClearGrid();
		}
	//2.Updating
		lifeSimulation.Update();

	//3.Drawimg
		BeginDrawing();
		ClearBackground(dark_Grey);
		lifeSimulation.Draw();
		EndDrawing();
	}
	

	CloseWindow();
}