#pragma once
#include "GUI.h"

class Game
{
public:
	Game(int screenWidth, int screenHeight, float cellSize, int boardWidth, int boardHeight);
	void init();
	void close();
	void run();
	bool shouldRun() const;
	void drawCells() const;
	bool shouldTick() const;
	void tick();
	int getAliveNeighbours(int pos) const;
	int cellCount;
private:
	struct cell {
		bool isAlive = false;
		bool willLive = false;
	};

	int screenWidth;
	int screenHeight;
	int boardWidth = 300;
	int boardHeight = 100;
	float cellSize;
	cell* board[300 * 100];
	GUI gui;
	double lastTick;
};