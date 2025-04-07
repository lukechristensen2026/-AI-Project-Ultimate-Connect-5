#ifndef MOVING_OBJECT_HPP
#define MOVING_OBJECT_HPP

#include "raylib.h"
#include "raymath.h"

class MovingObject
{
private:
    Vector2 position;
    Vector2 direction;
    Color myColor;
    int size;
    float speed;
    bool isVisible;

public:

    /// fix this 
    MovingObject()
        : position(Vector2Zero()), direction(Vector2Zero()), myColor(BLACK),
          size(15), speed(100.0f), isVisible(true)
    {
        // Default constructor initializes with zero position, black color, and default size & speed
    }

    MovingObject(float x, float y, Color startColor)
    {
        position = {x, y};
        direction = Vector2Zero();
        myColor = startColor;
        size = 15;
        speed = 100.0f;
        isVisible = true;
    }

    Vector2 getPostion() { return position; }
    Vector2 getDirection() { return direction; }

    void setPosition(Vector2 newPosition)
    {
        position = newPosition;
    }

    void setDirection(Vector2 newDirection)
    {
        direction = newDirection;
    }

    void setSize(int newSize)
    {
        size = newSize;
    }

    void setSpeed(int newSpeed) { speed = newSpeed; }

    void increaseSpeed(int newSpeed)
    {
        // setSpeed() = newSpeed*2;//not sure how to do this?
    }

    void update(double deltaTime)
    {
        if (!Vector2Equals(direction, Vector2Zero()))
        {
            Vector2 deltaPosition = Vector2Scale(direction, speed * deltaTime);
            position = Vector2Add(position, deltaPosition);
        }
    }

    void draw()
    {
        if (isVisible)
        {
            DrawCircle(position.x, position.y, size, myColor);
        }
    }

    void lookTo(Vector2 target)
    {
        direction = Vector2Normalize(Vector2Subtract(target, position));
    }

    void lookTo(MovingObject otherObject)
    {
        Vector2 target = otherObject.position;
        direction = Vector2Normalize(Vector2Subtract(target, position));
    }

    void stop()
    {
        direction = Vector2Zero();
    }

    void hide()
    {
        isVisible = false;
    }

    bool isHidden()
    {
        return isVisible == false;
    }

    void show()
    {
        isVisible = true;
    }
};

#endif
