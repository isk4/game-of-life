#include "raylib.h"
#include "GUI.h"
#include <string>
#include <cmath>

GUI::GUI()
{
    fpsString[0] = '\0';
    timeString[0] = '\0';
    cellCountString[0] = '\0';
}

void GUI::draw(int cellCount)
{
    drawFPS();
    drawCellCount(cellCount);
    drawTime();
}

void GUI::drawFPS()
{
    sprintf_s(fpsString, 256, "FPS: %d", GetFPS());
    DrawRectangle(50, 0, 100, 25, RAYWHITE);
    DrawText(fpsString, 60, 0, 20, BLACK);
}

void GUI::drawCellCount(int cellCount)
{
    sprintf_s(cellCountString, 256, "Cantidad de celulas vivas: %d", cellCount);
    DrawRectangle(200, 0, 400, 25, RAYWHITE);
    DrawText(cellCountString, 210, 0, 20, BLACK);
}
void GUI::drawTime()
{
    sprintf_s(timeString, "Tiempo transcurrido: %0.2f s", GetTime());
    DrawRectangle(800, 0, 400, 25, RAYWHITE);
    DrawText(timeString, 810, 0, 20, BLACK);
}
