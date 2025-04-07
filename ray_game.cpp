/***********************************
 * CSC 122 Sample Raylib Game
 *
 * name: Paul W. Bible
 */
#include "raylib.h"
#include "raymath.h"
#include "MovingObject.hpp"
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    // These varaibles are for the screen size
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Create some Custom colors
    Color depauwBlack = Color{35, 31, 32, 255};
    Color depauwGold = Color{253, 221, 6, 255};

    // create some game objects
    MovingObject myCircle = MovingObject(screenWidth / 2, screenHeight / 2, depauwBlack);
    MovingObject target = MovingObject(25, 25, depauwGold);
    myCircle.lookTo(target);

    int collectableCount = 10;
    vector<MovingObject> collectables;
    for (int i = 0; i < collectableCount; i++)
    {
        float x = float(rand() % screenWidth);
        float y = float(rand() % screenHeight);
        collectables.push_back(MovingObject(x, y, BLUE));
    }

    // win conditions
    int score = 0;
    double timeLimit = 30.00;
    bool isGameOver = false;

    // Initialize window and set the screen title
    InitWindow(screenWidth, screenHeight, "CSC122 - Window Title Here");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // current time
    // GetTime gives the number of seconds since start of application.
    double time = GetTime();

    // Main game loop, Draw loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // ***** Processing and updates *****
        // Get the change in time since last frame.
        double lastTime = time;
        time = GetTime();
        double deltaTime = time - lastTime;
        // cout << deltaTime << endl;

        // ***** Process user input *****

        // have object follow mouse
        Vector2 mousePosition = GetMousePosition();
        target.setPosition(mousePosition);
        myCircle.lookTo(target);

        // ***** update game elements *****
        myCircle.update(deltaTime);

        // process collision with the target
        if (Vector2Distance(myCircle.getPostion(), target.getPostion()) < 5)
        {
            myCircle.stop();
        }

        // process collision with other game elements
        for (int i = 0; i < collectables.size(); i++)
        {
            Vector2 position = collectables[i].getPostion();
            // when you get close to a collectable, grab it.
            // really, we just hide my telling the instance not to draw
            if (Vector2Distance(myCircle.getPostion(), position) < 10)
            {
                if (!collectables[i].isHidden())
                {
                    collectables[i].hide();
                    score += 1;
                }
            }
        }

        // ***** Check for game over conditions *****
        if (score >= collectableCount)
        {
            isGameOver = true;
        }

        if (time > timeLimit)
        {
            isGameOver = true;
        }

        // ***** Draw *****
        //----------------------------------------------------------------------------------
        // Main game state
        if (!isGameOver)
        {
            // ***** Draw Regular Game Scene *****
            // Call this at the end of your drawing.
            BeginDrawing();
            ClearBackground(RAYWHITE);

            // draw timer.
            string timeString = to_string(timeLimit - time);
            DrawText(timeString.c_str(), 10, screenHeight - 50, 40, DARKGRAY);

            // draw objects
            myCircle.draw();
            target.draw();

            // draw collectables
            for (int i = 0; i < collectables.size(); i++)
            {
                collectables[i].draw();
            }
            // Call this at the end of your drawing.
            EndDrawing();
        }
        else
        {
            // ***** Draw Game Over Scene *****
            BeginDrawing();
            ClearBackground(RAYWHITE);
            if (score == collectableCount)
            {
                string message = "You win!";
                DrawText(message.c_str(), 100, 100, 40, DARKGRAY);
            }
            else
            {
                DrawText("Better luck next time.", 100, 100, 40, DARKGRAY);
            }

            EndDrawing();
        }
    }

    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
