#pragma once

#include <vector>

class Grid
{
public:
	Grid(int cellSizeInPixels, int gridSizeInCells);
	Grid(int cellSizeInPixels, int gridWidthInCells, int gridHeightInCells);
	~Grid() = default;

	void CreateGrid();
	void DrawGrid();
	void FillCell(Vector2Int* cell);
	bool SelectCell(Vector2Int mousePos);
	Vector2Int* GetSelectedCell() const { return m_pSelectedCell; }


private:
	//Vector2Int** gridArray;
	std::vector<std::vector<Vector2Int*>> m_Grid; //containers with first in first out
	const int m_GridWidthInCells;
	const int m_GridHeightInCells;
	const int m_CellSizeInPixels; // TODO: m_CellSizeInPixels

	Vector2Int* m_pSelectedCell{};
};

/*
int* - normal, needs deletion
std::smart_pointer - fancy, delete themselves
std::unique_pointer - smart pointers, but jealous
int& - make pointer out of variable
*/

// TODO: a first attempt with normal pointer, a second attempt with smart pointers