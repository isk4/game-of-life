#include "raylib.h"
#include "GUI.h"
#include "Game.h"
#include <string>

void GUI::init(Game* game)
{
    this->game = game;
}

void GUI::draw()
{
    handleKeys();
    drawFPS();
    drawCellCount();
    drawTime();
    drawControlls();
}

void GUI::drawFPS()
{
    sprintf_s(fpsString, 256, "FPS: %d", GetFPS());
    DrawRectangle(50, 0, 100, 25, RAYWHITE);
    DrawText(fpsString, 60, 0, 20, BLACK);
}

void GUI::drawCellCount()
{
    sprintf_s(cellCountString, 256, "Cantidad de celulas vivas: %d", game->cellCount);
    DrawRectangle(200, 0, 400, 25, RAYWHITE);
    DrawText(cellCountString, 210, 0, 20, BLACK);
}


void GUI::drawTime()
{
    sprintf_s(timeString, "Tiempo transcurrido: %0.2f s", GetTime());
    DrawRectangle(800, 0, 400, 25, RAYWHITE);
    DrawText(timeString, 810, 0, 20, BLACK);
}

int prueba = 0;
void GUI::drawControlls()
{
    sprintf_s(speedString, "Velocidad: %0.1fx", game->speed / 10);
    /*int tecla = GetKeyPressed();
    if (tecla != 0) prueba = tecla;
    sprintf_s(speedString, "Tecla: %d", prueba);*/
    DrawRectangle(800, 500, 400, 25, RAYWHITE);
    DrawText(speedString, 810, 500, 20, BLACK);
}

void GUI::handleKeys()
{
    switch (GetKeyPressed())
    {
    case 32:
        game->resetBoard();
        break;
    // Arrow up
    case 264:
        game->speed -= 1;
        break;
    // Arrow down
    case 265:
        game->speed += 1;
        break;
    }
}
