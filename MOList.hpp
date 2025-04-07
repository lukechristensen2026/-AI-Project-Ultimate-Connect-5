#ifndef MO_LIST_HPP
#define MO_LIST_HPP

#include "MovingObject.hpp"
#include "raylib.h"
#include "raymath.h"

/**
 * The node holds a moving object as its data.
 * It has a next and prev pointer.
 * This means the list is a doubly linked list.
 */
class Node
{
public:
    MovingObject data;
    Node *next;
    Node *prev;

    Node(MovingObject object)
    {
        data = object;
        next = nullptr;
        prev = nullptr;
    }
};

/**
 * The MOList, MovingObject list
 * This is a doubly linked list with both head and tail pointers.
 * Using a tail pointer makes appending easy, no need to traverse.
 *
 * We will use this class to implement a kind of snake or dragon game element.
 * Each segment can be hit or damaged.
 *
 * Each time a segment is hit, its size goes down by 1 (removing from the end).
 */
class MOList
{
private:
    Node *head;
    Node *tail;
    int chaseLimit; // chase limit, this makes sure the segments don't get too close

public:
    MOList()
    {
        head = nullptr;
        tail = nullptr;
        chaseLimit = 20; // don't allow a segment to get any closer than 20 pixels to the next.
    }

    ~MOList()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }

    /**
     * Always append to the tail end.
     */
    void append(MovingObject object)
    {
        Node *node = new Node(object);
        if (head == nullptr && tail == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
    }

    // This lets the main game access the first element.
    // This is used to steer the dragon.
    Node *headNode()
    {
        return head;
    }

    /**
     * This method traverses the list and updates each moving object.
     * Each segment is a moving object. The head node element is used to steer.
     * Each segment chases the segment in front of it.
     */
    void update(double deltaTime)
    {
        if (head != nullptr)
        {
            // advance the head, this node's object leads the rest.
            head->data.update(deltaTime);
            Node *current = head->next;
            while (current != nullptr)
            {
                // === this is physics based follow ===
                // Get the position of the "previous" element.
                // It is previous in the list, but in the game it leads the current segment.
                Vector2 prevPos = current->prev->data.getPostion();
                Vector2 currentPos = current->data.getPostion();
                // change direction to face the leading element.
                current->data.lookTo(prevPos);
                // if not too close, take a step in the facing direction.
                if (Vector2Distance(currentPos, prevPos) > chaseLimit)
                {
                    current->data.update(deltaTime);
                }
                // advance to the next element.
                current = current->next;
            }
        }
    }

    void draw()
    {
        // interate the list and draw all its elements.
        Node *current = head;
        while (current != nullptr)
        {
            current->data.draw();
            current = current->next;
        }
    }

    // check if the hitPoint collides with any segment.
    // if it does shorten the list by one.
    void processCollision(Vector2 hitPoint, int size)
    {
        bool hit = false;
        // find a balance between the chase limit and the size.
        // This can be adjusted. This is where game design and player feeling are considered.
        // If the hitDistance is too small, dragon seems to never gets hit.
        // If the hitDistance is too large, it seems too easy and always hits.
        float hitDistance = (size + chaseLimit) / 3;
        // iterate every segment and test for a hit.
        Node *current = head;
        while (current != nullptr && hit != true)
        {
            Vector2 position = current->data.getPostion();
            if (Vector2Distance(position, hitPoint) < hitDistance)
            {
                hit = true;
                // current->data.getHit();
                break; // if we hit once, break out of the loop.
            }
            current = current->next;
        }

        // if we get a hit, delete the last element.
        // this is easy with the tail pointer.
        if (hit && head != tail)
        {
            Node *temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
    }
};

#endif
