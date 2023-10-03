#include "Game.h"
#include "GUI.h"
#include "raylib.h"
#include <cmath>

using namespace std;
const float BOARD_PADDING_LEFT = 20;
const float BOARD_PADDING_UP = 50;
Color GRIS = { 30, 30, 30, 255 };

Game::Game(int screenWidth, int screenHeight, float cellSize, int boardWidth, int boardHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->cellSize = cellSize;
    this->boardWidth = boardWidth;
    this->boardHeight = boardHeight;
    this->gui = GUI();
}

void Game::init()
{   
    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetTargetFPS(60);
    lastTick = GetTime();
    
    for (int i = 0; i < boardWidth * boardHeight; i++)
    {
        board[i] = new cell;
    }

    for (int i = 0; i < 50000; i++)
    {
        board[GetRandomValue(2000, 28000)]->willLive = true;
    }

    cellCount = 0;
}

void Game::run()
{
    BeginDrawing();
    ClearBackground(BLACK);
    if (this->shouldTick()) tick();
    this->drawCells();
    gui.draw(cellCount);
    EndDrawing();
}


void Game::close()
{
    for (int i = 0; i < boardWidth * boardHeight; i++) {
        delete board[i];
    }
    CloseWindow();
}

bool Game::shouldRun() const
{
    return !WindowShouldClose();
}

void Game::drawCells() const
{
    for (int i = 0; i < boardWidth * boardHeight; i++)
    {
        if (board[i]->isAlive)
        {
            Rectangle rec = {
                (i % boardWidth) * cellSize + BOARD_PADDING_LEFT,
                (i / boardWidth) * cellSize + BOARD_PADDING_UP,
                cellSize,
                cellSize
            };
            DrawRectangleRec(rec, RAYWHITE);
        }
        else
        {
            Rectangle rec = {
                (i % boardWidth) * cellSize + BOARD_PADDING_LEFT - 0.5f,
                (i / boardWidth) * cellSize + BOARD_PADDING_UP - 0.5f,
                cellSize,
                cellSize
            };
            DrawRectangleLinesEx(rec, (float) 0.5, GRIS);
        }
    }
}


bool Game::shouldTick() const
{
    return true;
    //return GetTime() >= ceil(lastTick);
}

void Game::tick()
{
    int cells = 0;
    int neighbours_count;
    for (int i = 0; i < boardWidth * boardHeight; i++)
    {
        if (board[i]->willLive) 
        {
            board[i]->isAlive = true;
            cells++;
        }
        else
        {
            board[i]->isAlive = false;
        }
    }
    for (int i = 0; i < boardWidth * boardHeight; i++)
    {
        neighbours_count = getAliveNeighbours(i);
        if (board[i]->isAlive)
        {
            board[i]->willLive = (neighbours_count == 3 || neighbours_count == 2);
        }
        else
        {
            if (neighbours_count == 3) board[i]->willLive = true;
        }
    }
    cellCount = cells;
    lastTick = GetTime();
}

int Game::getAliveNeighbours(int pos) const
{
    int count = 0;
    if ((pos - (boardWidth + 1) > -1) && board[pos - (boardWidth + 1)]->isAlive)
        count++;
    if ((pos - boardWidth > -1) && board[pos - boardWidth]->isAlive)
        count++;
    if ((pos - (boardWidth - 1) > -1) && board[pos - (boardWidth - 1)]->isAlive)
        count++;
    if ((pos - 1 > -1) && board[pos - 1]->isAlive) 
        count++;
    if ((pos + 1 < boardWidth * boardHeight) && board[pos + 1]->isAlive)
        count++;
    if ((pos + (boardWidth - 1) < boardWidth * boardHeight) && board[pos + (boardWidth - 1)]->isAlive)
        count++;
    if ((pos + boardWidth < boardWidth * boardHeight) && board[pos + boardWidth]->isAlive)
        count++;
    if ((pos + (boardWidth + 1) < boardWidth * boardHeight) && board[pos + (boardWidth + 1)]->isAlive)
        count++;
    return count;
}
