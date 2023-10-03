#pragma once

class GUI
{
public:
	GUI();
	void draw(int cellCount);
	void drawFPS();
	void drawTime();
	void drawCellCount(int cellCount);
private:
	char fpsString[256];
	char timeString[256];
	char cellCountString[256];
};