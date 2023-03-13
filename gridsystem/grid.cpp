#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

#include <iostream>

#include "struct.h"
#include "grid.h"

Grid::Grid(int cellSizeInPixels, int gridSizeInCells)
	: m_GridWidthInCells(gridSizeInCells)
	, m_GridHeightInCells(gridSizeInCells)
	, m_CellSizeInPixels(cellSizeInPixels)
{
	CreateGrid();
}

Grid::Grid(int cellSizeInPixels, int gridWidthInCells, int gridHeightInCells)
	: m_GridWidthInCells(gridWidthInCells)
	, m_GridHeightInCells(gridHeightInCells)
	, m_CellSizeInPixels(cellSizeInPixels)
{
	CreateGrid();
}

//TODO: read up on constructors, memory allocation and the delete function
/*Grid::~Grid()
{
	for (int i = 0; i < m_Grid.size(); i++)
	{
		delete m_Grid(i);
		m_Grid(i) = NULL;
	}
}*/

void Grid::CreateGrid()
{
	for (int w = 0; w < m_GridWidthInCells; w++)
	{
		std::vector<Vector2Int*> colCountainer;
		for (int h = 0; h < m_GridHeightInCells; h++)
			colCountainer.push_back(new Vector2Int(w, h)); // dinamically allocated, can be deleted?
		m_Grid.push_back(colCountainer);
	}
}

void Grid::DrawGrid()
{
	for (int w = 0; w < m_GridWidthInCells; w++)
	{
		for (int h = 0; h < m_GridHeightInCells; h++)
		{
			Vector2Int posOrigin
			{
				m_Grid[w][h]->X * m_CellSizeInPixels,
				m_Grid[w][h]->Y * m_CellSizeInPixels
			};

			glBegin(GL_LINE_STRIP);
			glVertex2f(posOrigin.X, posOrigin.Y + m_CellSizeInPixels);
			glVertex2f(posOrigin.X, posOrigin.Y);
			glVertex2f(posOrigin.X + m_CellSizeInPixels, posOrigin.Y);
			glEnd();
		}

		glBegin(GL_LINE_STRIP);
		glVertex2f(0, m_GridWidthInCells * m_CellSizeInPixels);
		glVertex2f(m_GridWidthInCells * m_CellSizeInPixels, m_GridWidthInCells * m_CellSizeInPixels);
		glVertex2f(m_GridWidthInCells * m_CellSizeInPixels, 0);
		glEnd();
	}
}

bool Grid::SelectCell(Vector2Int mousePos)
{
	// Initiated variables to the mouse clicked position on the grid
	int x = mousePos.X / m_CellSizeInPixels;
	int y = mousePos.Y / m_CellSizeInPixels;

	// Check to see if x and y are inside the grid
	if (x < m_GridWidthInCells && y < m_GridHeightInCells)
	{
		// Set value on cell to the grid value of the click position
		m_pSelectedCell = m_Grid[x][y];
		return true;
	}
	return false;
}

void Grid::FillCell(Vector2Int* pCell)
{
	glBegin(GL_POLYGON);
	glVertex2f(pCell->X * m_CellSizeInPixels, pCell->Y * m_CellSizeInPixels);
	glVertex2f(pCell->X * m_CellSizeInPixels, pCell->Y * m_CellSizeInPixels + m_CellSizeInPixels);
	glVertex2f(pCell->X * m_CellSizeInPixels + m_CellSizeInPixels, pCell->Y * m_CellSizeInPixels + m_CellSizeInPixels);
	glVertex2f(pCell->X * m_CellSizeInPixels + m_CellSizeInPixels, pCell->Y * m_CellSizeInPixels);
	glEnd();
}