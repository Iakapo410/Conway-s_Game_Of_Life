#include "LifeSimulation.hpp"
#include <vector>
#include <utility>


void LifeSimulation::Draw()
{
	grid.Draw();
}

void LifeSimulation::SetValue(int row, int column, int value)
{
	grid.SetValue(row, column, value);
}

int LifeSimulation::AliveNeighbours(int row, int column)
{
	int LiveNeighbours = 0;
	std::vector<std::pair<int, int>> neighbourOffsets =
	{
		{-1,0}, //Directly above
		{1,0}, //Directly below
		{0,-1}, //Directly Left
		{0,1}, //Directly right
		{-1,-1}, //Diagonal upper left
		{1,1}, //Diagonal lower right
		{1,-1}, //Diagonal lower left
		{-1,1} //Diagonal upper right
	};

	for(const auto& offset : neighbourOffsets)
	{
		int neighbourRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
		int neighbourColumn = (column + offset.second + grid.GetColumns()) % grid.GetColumns();
		LiveNeighbours += grid.GetValue(neighbourRow, neighbourColumn);
	}
	return LiveNeighbours;
}

void LifeSimulation::Update()
{
	if(IsRunning())
	{
		for (int row = 0; row < grid.GetRows(); row++)
		{
			for (int column = 0; column < grid.GetColumns(); column++)
			{
				int liveNeighbours = AliveNeighbours(row, column);
				int cellValue = grid.GetValue(row, column);

				if (cellValue == 1)
				{
					if (liveNeighbours > 3 || liveNeighbours < 2)
					{
						tempGrid.SetValue(row, column, 0);
					}
					else
					{
						tempGrid.SetValue(row, column, 1);
					}
				}
				else
				{
					if (liveNeighbours == 3)
					{
						tempGrid.SetValue(row, column, 1);
					}
					else
					{
						tempGrid.SetValue(row, column, 0);
					}
				}
			}
		}
		grid = tempGrid;
	}
}

void LifeSimulation::ClearGrid()
{
	if(!IsRunning())
	{
		grid.Clear();
	}
}

void LifeSimulation::CreateRandomState()
{
	if(!IsRunning())
	{
		grid.FillRandom();
	}
}

void LifeSimulation::ToggleCell(int row, int column)
{
	if(!IsRunning())
	{
		grid.ToggleCell(row, column);
	}
}
