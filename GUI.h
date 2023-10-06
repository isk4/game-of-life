#pragma once
class Game;
class GUI
{
public:
	void init(Game* game);
	void draw();
	void drawFPS();
	void drawTime();
	void drawCellCount();
	void drawControlls();
	void handleKeys();
private:
	Game* game;
	char fpsString[256];
	char timeString[256];
	char cellCountString[256];
	char speedString[256];
};