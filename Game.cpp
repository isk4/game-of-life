#include "Game.h"
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
    gui.init(this);
    lastTick = 0;
    speed = 10;
    cellCount = 0;
    
    for (int i = 0; i < boardWidth * boardHeight; i++)
    {
        board[i] = new cell;
    }
}

void Game::run()
{
    BeginDrawing();
    ClearBackground(BLACK);
    if (this->shouldTick()) tick();
    this->drawCells();
    gui.draw();
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


bool Game::shouldTick()
{
    lastTick += GetFrameTime();
    if (lastTick >= 1 / speed)
    {
        lastTick = 0;
        return true;
    }
    else
    {
        return false;
    }
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
        board[i]->willLive = (board[i]->isAlive && neighbours_count == 2) || neighbours_count == 3;
    }
    cellCount = cells;
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

void Game::resetBoard()
{
    for (int i = 0; i < boardWidth * boardHeight; i++)
    {
        board[i]->isAlive = false;
    }
    for (int i = 0; i < boardWidth * boardHeight; i++)
    {
        board[i]->willLive = GetRandomValue(0, 1);
    }
}
