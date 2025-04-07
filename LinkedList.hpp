// name: Luke Christensen
// partner: Eli VanHaaren

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    Node(int value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

class LinkedList {
private:
   Node *head;
   Node *tail;

public:
   LinkedList()
   {
      head = nullptr;
      tail = nullptr;
   };

   void insert(int value, int index)
   {
      Node *newNode = new Node(value);
      if (index < 0)
      {
         cout << "Error" << endl;
      }
      else if (index == 0)
      {
         newNode->next = head;
         //head->prev = newNode;
         head = newNode;
      }
      else
      {
         Node *temporary = head;
         for (int i = 0; temporary != nullptr && i < index - 1; i++)
         {
            temporary = temporary->next;
         }
         if (temporary == nullptr)
         {
            cout << "Error" << endl;
            delete newNode;
            return;
         }
         newNode->next = temporary->next;
         //newNode->prev = temporary;
         temporary->next = newNode;

      }
   }

   void prepend(int value)
   {
      insert(value, 0);
   }

   void append(int value)
   {
      Node *newNode = new Node(value);
      if (head == nullptr)
      {
         head = newNode;
      }
      else
      {
         Node *temporary = head;
         while (temporary->next != nullptr)
         {
            temporary = temporary->next;
         }
         temporary->next = newNode;
      }
   }

   int remove(int index)
   {
      if (head == nullptr || index < 0)
      {
         cout << "Error" << endl;
         return -1;
      }

      else if (index == 0)
      {
         Node *temp = head;
         head = head->next;
         int removedValue = temp->data;
         delete temp;
         return removedValue;
      }
      else
      {
         Node *temp = head;
         for (int i = 0; temp != nullptr && i < index - 1; ++i)
         {
            temp = temp->next;
         }

         if (temp == nullptr || temp->next == nullptr)
         {
            cout << "Error" << endl;
            return -1;
         }

         Node *nodeToRemove = temp->next;
         temp->next = nodeToRemove->next;
         int removedValue = nodeToRemove->data;
         delete nodeToRemove;
         return removedValue;
      }
   }

   int removeFirst()
   {
      return remove(0);
   }

   int removeLast()
   {
      if (head == nullptr)
         return -1;

      int removedValue;
      if (head->next == nullptr)
      {
         removedValue = head->data;
         delete head;
         head = nullptr;
         tail = nullptr;
         return removedValue;
      }

      Node *current = head;
      while (current->next->next != nullptr)
      {
         current = current->next;
      }
      Node *lastNode = current->next;
      removedValue = lastNode->data;
      delete lastNode;
      current->next = nullptr;
      tail = current;
      return removedValue;
   }

   int getSize()
   {

      if (head == nullptr)
      {
         return 0;
      }
      else
      {
         int counter = 0;
         Node *current = head;
         while (current != nullptr)
         {
            counter++;
            current = current->next;
         }
         return counter;
      }
   }

   int get(int index)
   {
      Node *current = head;
      if (index < 0)
      {
         return -1;
      }
      else
      {
         int counter = 0;
         Node *current = head;
         while (counter < index && current != nullptr)
         {
            current = current->next;
            counter++;
         }
         return current->data;
      }
   }

   void set(int value, int index)
   {
      if (index < 0 || index >= getSize())
      {
         cout << "Index out of bounds" << endl;
         return;
      }
      int counter = 0;
      Node *current = head;
      while (counter < index && current != nullptr)
      {
         current = current->next;
         counter++;
      }
      if (current != nullptr)
         current->data = value;
   }

   void printAll()
   {
      Node *current = head;
      while (current != nullptr)
      {
         cout << current->data << endl;
         current = current->next;
      }
   }

   bool isEmpty()
   {
      if (head == nullptr)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
};
#endif