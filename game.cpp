/***********************************
 * (AI Project) Ultimate Connect 5
 * 
 * Learned raygame and developed a barebones base for a Connect 4 game in a Data Structures class at DePauw University. Worked with Eli VanHaaren on some of this base.
 * Converted into Ultimate Connect 5 and added an AI for a Machine Intelligence Course at the University of Newcastle.
 * name: Luke Christensen
 * 
 * 
 * referenced code and discussion from Paul W. Bible and EliVanHaaren to learn raygame
 * A barebones and unfinished set of code previously discussed was used as the base for this project
 * referenced code from Michael Estes and user Snowbody on StackExchange to gain foundational ideas 
 * of coding connect 4
 * 
 * Game was completed myself
 * Game intelligence was developed myself
 * Ultimate Connect Five game and intelligence was developed myself
 */



#include "raylib.h"
#include "raymath.h"
#include "LinkedList.hpp"
#include "Set.hpp"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Dot
{
public:
    int x;
    int y;
    bool isSlotTaken;
    bool isPlayer1;
    Color checkerColor;

    Dot()
    {
        x = 0;
        y = 0;
        isSlotTaken = false;
    }

    Dot(int xPosition, int yPosition, bool isSlot, bool whatPlayer, Color color)
    {
        x = xPosition;
        y = yPosition;
        isSlotTaken = isSlot;
        isPlayer1 = whatPlayer;
        checkerColor = whatPlayer ? YELLOW : RED;
    }
};

const int boardWidth = 7;
const int boardHeight = 6;
int currentPlayer = 0;
Dot board[boardWidth][boardHeight];
bool isGameOver = false;
Color playerColor;

void switchPlayer()
{
    if (currentPlayer == 1)
    {
        currentPlayer = 0;
    }
    else if (currentPlayer == 0)
    {
        currentPlayer = 1;
    }
    return;
}

/*
void switchColor()
{
    if (currentPlayer == 1)
    {
        playerColor = RED;
    }
    else
    {
        playerColor = YELLOW;
    }
}
*/

void updateBoard(int input)
{
    int column = input - 1;
    for (int row = boardHeight - 1; row >= 0; row--)
    {
        if (!board[column][row].isSlotTaken)
        {
            board[column][row].isSlotTaken = true;
            board[column][row] = Dot(column, row, true, currentPlayer == 0, currentPlayer == 0 ? YELLOW : RED); // Assign color based on currentPlayer
            // switchPlayer();
            // switchColor();
            return;
        }
    }
}

int main(void)
{
    LinkedList row7;
    LinkedList row6;
    LinkedList row5;
    LinkedList row4;
    LinkedList row3;
    LinkedList row2;
    LinkedList row1;

    const int screenWidth = 1500;
    const int screenHeight = 700;

    Color depauwBlack = Color{35, 31, 32, 255};
    Color depauwGold = Color{253, 221, 6, 255};

    InitWindow(screenWidth, screenHeight, "Connect 4 Game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLUE);

        if (!isGameOver)
        {
            bool validMoveMade = false;
            if (IsKeyPressed(KEY_ONE))
            {
                updateBoard(1);
                validMoveMade = true;
            }
            else if (IsKeyPressed(KEY_TWO))
            {
                updateBoard(2);
                validMoveMade = true;
            }
            else if (IsKeyPressed(KEY_THREE))
            {
                updateBoard(3);
                validMoveMade = true;
            }
            else if (IsKeyPressed(KEY_FOUR))
            {
                updateBoard(4);
                validMoveMade = true;
            }
            else if (IsKeyPressed(KEY_FIVE))
            {
                updateBoard(5);
                validMoveMade = true;
            }
            else if (IsKeyPressed(KEY_SIX))
            {
                updateBoard(6);
                validMoveMade = true;
            }
            else if (IsKeyPressed(KEY_SEVEN))
            {
                updateBoard(7);
                validMoveMade = true;
            }
            if (validMoveMade)
            {
                switchPlayer();
                // switchColor(); // Update playerColor based on currentPlayer
            }
        }

        float i = 0;

        float a = 0;
        float b = 0;
        float c = 0;
        float d = 0;
        float k = 0;
        while (i < 7)
        {

            i = i + 1;
            DrawLineEx({60 + k, 10}, {60 + k, 700}, 5, BLACK); // vertical lines

            k += 90;
            DrawLineEx({60, 30 + a}, {700, 30 + c}, 5, BLACK); // horzontal lines
            d += 60;
            a += 100;
            c += 100;
        }
        DrawLineEx({60 + k, 10}, {60 + k, 700}, 5, BLACK); // vertical lines

        for (int y = 0; y < boardHeight; y++)
        {
            for (int x = 0; x < boardWidth; x++)
            {
                if (board[x][y].isSlotTaken)
                {

                    // DrawCircle(position.x, position.y, size, pieceColor);
                    int circleX = 75 + x * 100; // Adjusted x-coordinate for centering
                    int circleY = 75 + y * 100; // Adjusted y-coordinate for centering
                    DrawCircle(circleX, circleY, 40, board[x][y].checkerColor);
                    // DrawCircle(x * 100, y * 50, 15, playerColor);
                    // list.append(10);

                    /*
                    if (y == 0)
                    {
                        row1.insert(1, x);
                    }
                    else if (y == 1)
                    {
                        row2.insert(1, x);
                    }
                    else if (y == 2)
                    {
                        row3.insert(1, x);
                    }
                    else if (y == 3)
                    {
                        row4.insert(1, x);
                    }
                    else if (y == 4)
                    {
                        row5.insert(1, x);
                    }
                    else if (y == 5)
                    {
                        row6.insert(1, x);
                    }
                    else if (y == 6)
                    {
                        row7.insert(1, x);
                    }
                    */

                    // check win conditions
                    if (board[0][0].isPlayer1 && board[0][1].isPlayer1 && board[0][2].isPlayer1 && board[0][3].isPlayer1)
                    {
                        isGameOver = true;
                    }
                    // if (row7.get(0) == 1 && row7.get(0) == 1 && row7.get(0) == 1 && row7.get(0) == 1)
                    //{
                    //
                    //}
                }
            }
        }

        EndDrawing();
    }
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}

// text instructions
// 2 data structures
// lists or stacks?  columns as a stack.
// You could make a stack to hold dots and add
// them to the board.


// Then you need to figure out how to calculate
// when 4 are connected.
